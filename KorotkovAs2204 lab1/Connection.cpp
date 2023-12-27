#include "Connection.h"
#include "CPipe.h"
#include "Cks.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <utility>
#include <stdlib.h>
#include <stdio.h>


using namespace std;


void Connection::addConnect(unordered_map<int, Pipe>& groupOfPipe,
	unordered_map<int, KS>& groupOfKs)
{
	unordered_set<int> avaibleIds;
	while (true)
	{
		if (groupOfKs.size() >= 2)
		{
			for (auto& ks : groupOfKs)
			{
				cout << "id: " << ks.first << endl;
				avaibleIds.insert(ks.first);
			}
			int indexFirst;
			int indexSecond;
			while (true)
			{
				cout << "choose first ks" << endl;
				indexFirst = getCorrectID(avaibleIds);
				cout << "choose second ks" << endl;
				indexSecond = getCorrectID(avaibleIds);
				if (indexFirst != indexSecond)
					break;
			}
			cout << "Choose pipe diameter:" << endl
				<< "1. 500" << endl
				<< "2. 700" << endl
				<< "3. 1000" << endl
				<< "4. 1400";
			int num = getCorrectNumber(1, 4);
			int diameter = (num == 1 ? 500 : num == 2 ? 700 : num == 3 ? 1000 : 1400);
			avaibleIds.clear();
			for (auto& pipe : groupOfPipe)
			{
				if (pipe.second.diameter == diameter)
				{
					avaibleIds.insert(pipe.first);
				}
			}
			set<int> id;
			for (auto ids : connections)
			{
				id.insert(ids.second);
			}
			for (auto i:id)
			{
				auto iter = find(avaibleIds.begin(), avaibleIds.end(), i);
				avaibleIds.erase(iter);
			}
			for (auto i : avaibleIds)
				cout << "ids" << i << " ";
			if (avaibleIds.size() == 0)
			{
				cout << "There is no pipes with same diameter.\n\nWould you like to add some?" << endl
					<< "1. Add pipe" << endl
					<< "2. Return to menu";
				if (getCorrectNumber(1, 2) == 1)
				{
					Pipe pipe;
					cout << "Type name:";
					cin.ignore();
					getline(cin, pipe.name);
					cout << "Type lenght:";
					pipe.length = getCorrectNumber(50., 200.);
					pipe.diameter = diameter;
					cout << "Is this pipe in repair?(Yes-1,No-0)";
					pipe.repair = getCorrectNumber(0, 1);
					avaibleIds.insert(pipe.getId());
				}
				else
					break;
			}
			cout << "Choose pipe";
			num = getCorrectID(avaibleIds);
			cout << "Pipe directed in one direction?(1. Yes 2. No)" << endl;
			int choose=getCorrectNumber(1, 2);
			if (choose==1)
				connections.insert({ make_pair(indexFirst, indexSecond) , num });
			else
			{
				connections.insert({ make_pair(indexFirst, indexSecond) , num });
				connections.insert({ make_pair(indexSecond, indexFirst) , num });
			}
			break;
		}
		else
		{
			cout << "Not enough CS.\n\nWould you like to add some?" << endl
				<< "1. Add CS" << endl
				<< "2. Return to menu";
			if (getCorrectNumber(1, 2) == 1)
			{
				KS ks;
				cin >> ks;
				groupOfKs.insert({ ks.getId(),ks });
				addConnect(groupOfPipe,groupOfKs);
			}
			else
				break;
		}
	}
}
void Connection::topologicalSort()
{
	if (connections.size() != 0)
	{
		set<int> ids;
		for (auto& i : connections)
		{
			ids.insert(i.first.second);
			ids.insert(i.first.first);
		}
		map<int, int> incomingEdges;
		for (auto i : ids)
			incomingEdges[i] = 0;

		map<int, vector<int> > graph;
		for (auto& edges : connections)
		{
			graph[edges.first.first].push_back(edges.first.second);
			incomingEdges[edges.first.second] += 1;
		}
		vector<int> cand;
		for (const auto& [edge, numberOfEdges] : incomingEdges)
		{
			if (numberOfEdges == 0)
				cand.push_back(edge);
		}
		vector<int> answer;
		while (cand.size() != 0)
		{
			int CurentElement = cand[cand.size() - 1];
			cand.pop_back();
			for (auto edge : graph[CurentElement])
			{
				incomingEdges[edge] -= 1;
				if (incomingEdges[edge] == 0)
				{
					cand.push_back(edge);
				}
			}
			answer.push_back(CurentElement);
		}
		if (answer.size() == ids.size())
		{
			for (auto& i : answer)
				cout << i << " ";
			cout << endl;
		}
		else
			cout << "Error" << endl;
	}
	else
		cout << "You have zero connections" << endl;
	
}
void Connection::viewConnection()
{	
	for (auto con : connections)
		cout << "Begin of KS id: " << con.first.first << " End of KS id: " << con.first.second << " id of Pipe: " << con.second<<endl;
}
void Connection::SaveConnection(ofstream& fout) 
{
	fout << connections.size()<<endl;
	for (auto&con: connections)
	{
		fout << con.first.first << endl;
		fout << con.first.second << endl;
		fout << con.second << endl;
	}
}
void Connection::LoadConnection(ifstream& fin)
{
	int startId;
	int endId;
	int PipeId;
	fin >> startId;
	fin >> endId;
	fin >> PipeId;
	connections.insert(pair<pair< int, int >, int >( {startId, endId}, PipeId ));
}
void Connection::deleteByLine(int id)
{
	map<pair< int, int >,int>::iterator it=connections.begin();
	while (it != connections.end())
	{
		if (it->second == id)
		{
			connections.erase(it);
			it = connections.begin();
		}
		else
		{
			++it;
		}
	}

}
void Connection::deleteByVer(int id)
{
	map<pair< int, int >, int>::iterator it= connections.begin();
	while (it != connections.end())
	{
		if ((it->first).first == id or (it->first).second == id)
		{
			connections.erase(it);
			it = connections.begin();
		}
		else
		{
			++it;
		}
	}
}
void Connection::shortestPath(int current,int finish, unordered_map<int, Pipe>& groupOfPipe)
{
	int start = current;
	set<int> avaibleVetex;
	for (auto& i : connections)
	{
		avaibleVetex.insert(i.first.second);
		avaibleVetex.insert(i.first.first);
	}
	map<int, double> lenghToEdges;
	for (auto i : avaibleVetex)
		lenghToEdges[i] = numeric_limits<double>::max();
	map<int, vector<int> > graph;
	for (auto& edges : connections)
		graph[edges.first.first].push_back(edges.first.second);
	lenghToEdges[current] = 0;
	while (true)
	{
		for (auto incidentVertex : graph[current])
		{
			lenghToEdges[incidentVertex] = min(lenghToEdges[incidentVertex], 
				lenghToEdges[current]+
				groupOfPipe[connections[pair<int, int>(current, incidentVertex)]].length);
		}
		graph.erase(current);
		map<int, vector<int>>::iterator it = graph.begin();
		while (it != graph.end())
		{
			(graph[it->first]).erase(remove((it->second).begin(), (it->second.end()), current), (it->second).end());
			++it;
		}
		
		double minn = numeric_limits<double>::max();
		avaibleVetex.erase(current);
		for (auto i : avaibleVetex)
			minn = min(minn, lenghToEdges[i]);
		for (auto i:lenghToEdges)
		{
			if (i.second == minn and i.first != current)
			{
				current = i.first;
				break;

			}
		}
		if (avaibleVetex.size() == 0)
			break;
	}
	for (auto i : lenghToEdges)
		if (i.first==finish)
			cout <<"distance betwen " << start <<" and "<<finish << " : " << i.second << endl;
}
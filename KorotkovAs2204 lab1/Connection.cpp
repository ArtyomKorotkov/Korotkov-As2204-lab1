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
			cout << "choose first ks" << endl;
			indexFirst = getCorrectID(avaibleIds);
			cout << "choose second ks" << endl;
			indexSecond = getCorrectID(avaibleIds);
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
					cout << "id: " << pipe.first << endl;
					avaibleIds.insert(pipe.first);
				}
			}
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
				}
				else
					break;
			}
			cout << "Choose pipe";
			num = getCorrectID(avaibleIds);

			connections.insert({ make_pair(indexFirst, indexSecond) , num });
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
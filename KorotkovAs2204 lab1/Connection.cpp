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
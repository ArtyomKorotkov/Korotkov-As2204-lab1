#pragma once
#pragma once
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <unordered_map>
#include "Cks.h"
#include "CPipe.h"

using namespace std;
class Connection
{
private:
	int startKs;
	int endKs;
	int PipeId;
	map<pair<int, int>, int> connections;
public:
	void addConnect(unordered_map<int, Pipe>& groupOfPipe,
		unordered_map<int, KS>& groupOfKs);
	void topologicalSort();
	void viewConnection();
	int size() { return connections.size(); };
	void deleteByLine(int id);
	void deleteByVer(int id);
	void SaveConnection(ofstream& fout);
	void LoadConnection(ifstream& fin);
	void shortestPath(int start,int finish, unordered_map<int, Pipe>& groupOfPipe);
};


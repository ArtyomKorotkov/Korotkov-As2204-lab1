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
	map<pair<int, int>, int> connections;
public:
	void addConnect(unordered_map<int, Pipe>& groupOfPipe,
		unordered_map<int, KS>& groupOfKs);
	void topologicalSort();
	void viewConnection();
	int size() { return connections.size(); };
};


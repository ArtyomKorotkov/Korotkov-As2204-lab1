#pragma once
#include <iostream>
#include <string>
#include "utils.h"

using namespace std;

class Pipe
{
public:
    string name;
    double length;
    double diameter;
    bool repair;
    friend ostream& operator << (ostream& out, const Pipe& pip);
    friend istream& operator >> (istream& in, Pipe& pipe);
};


#pragma once
#include <iostream>
#include <string>
#include "utils.h"

using namespace std;

class Pipe
{
    int id;
public:
    static int MaxId;
    string name;
    double length;
    double diameter;
    bool repair;
    Pipe();
    friend ostream& operator << (ostream& out, const Pipe& pip);
    friend istream& operator >> (istream& in, Pipe& pipe);
};


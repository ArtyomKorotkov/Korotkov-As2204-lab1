#pragma once
#include <iostream>
#include <string>
#include "utils.h"
using namespace std;
class KS
{
public:
    string name;
    int amoutOfShop;
    int amountWorkingShop;
    string effectiveness;
    friend istream& operator >> (istream& in,  KS& ks);
    friend ostream& operator << (ostream& out, const KS& ks);
};


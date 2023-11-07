#pragma once
#include <iostream>
#include <string>
#include "utils.h"
using namespace std;
class KS
{
    int id;
public:
    static int MaxId;
    string name;
    int amoutOfShop;
    int amountWorkingShop;
    string effectiveness;
    KS();
    friend istream& operator >> (istream& in,  KS& ks);
    friend ostream& operator << (ostream& out, const KS& ks);
};


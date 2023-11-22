#pragma once
#include <iostream>
#include <string>
#include "utils.h"
using namespace std;
class KS
{
public:
    int amountWorkingShop;

    string name;
    static int MaxId;
    int amoutOfShop;
    string effectiveness;
    KS();
    friend istream& operator >> (istream& in,  KS& ks);
    friend ostream& operator << (ostream& out, const KS& ks);
    int getId() { return id; };
    void editKS();
    void SaveKS(ofstream& fout);
    void LoadKS(ifstream& fin);
    string getTypeOfEffectiveness(int Number);
private: 
    int id;
};


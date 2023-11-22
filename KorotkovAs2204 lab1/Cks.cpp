#include "Cks.h"
#include "utils.h"
#include "CPipe.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int KS::MaxId=1;
KS::KS()
{
    id = MaxId++;
}

istream& operator >> (istream& in, KS& ks)
{
    cout << "Type name:";
    in.ignore();
    getline(in, ks.name);
    cout << "Type how much shop you have:";
    ks.amoutOfShop = getCorrectNumber(1, 10000);
    cout << "Type how much working shop you have:";
    ks.amountWorkingShop = getCorrectNumber(0, ks.amoutOfShop);
    cout << "Type what is effectiveness you have\n 1-Low \n 2-Midle \n 3-Hight" << endl;
    ks.effectiveness = ks.getTypeOfEffectiveness((getCorrectNumber(1, 3)));
    return in;
}

ostream& operator << (ostream& out, const KS& ks)
{
    out << "ID:" << ks.id
        << "\tName:" << ks.name
        << "\tAmount of shop:" << ks.amoutOfShop
        << "\tAmount of working shop:" << ks.amountWorkingShop
        << "\tEffectiveness:" << ks.effectiveness << endl;
    return out;
}
void KS::editKS()
{
    cout << "Enter new number of working workshops:";
    amountWorkingShop = getCorrectNumber(0, amoutOfShop);
}
void KS::SaveKS(ofstream& fout)
{
    fout << id << endl
        << name << endl
        << amoutOfShop << endl
        << amountWorkingShop << endl
        << effectiveness << endl;
}
void KS::LoadKS(ifstream& fin)
{
    fin >> id;
    fin.ignore();
    getline(fin, name);
    fin >> amoutOfShop;
    fin >> amountWorkingShop;
    fin >> effectiveness;
}
string KS:: getTypeOfEffectiveness(int Number)
{
    if (Number == 1)
        return "Low";
    else if (Number == 2)
        return "Midle";
    else
        return "Hight";
}

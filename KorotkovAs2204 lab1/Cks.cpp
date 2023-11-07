#include "Cks.h"
#include "utils.h"
using namespace std;

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
    ks.effectiveness = getTypeOfEffectiveness((getCorrectNumber(1, 3)));
    return in;
}

ostream& operator << (ostream& out, const KS& ks)
{
    out << "Name:" << ks.name
        << "\tAmount of shop:" << ks.amoutOfShop
        << "\tAmount of working shop:" << ks.amountWorkingShop
        << "\tEffectiveness:" << ks.effectiveness << endl;
    return out;
}
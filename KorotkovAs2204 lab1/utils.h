#pragma once
#include <iostream>
using namespace std;
template <typename t>
 t getCorrectNumber(t min, t max)
{
    int x;
    while ((cin >> x).fail() || x < min || x>max)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Type number between " << min << " and " << max << endl;
    }
    return x;
}
inline string getTypeOfEffectiveness(int Number)
 {
     if (Number == 1)
         return "Low";
     else if (Number == 2)
         return "Midle";
     else
         return "Hight";
 }

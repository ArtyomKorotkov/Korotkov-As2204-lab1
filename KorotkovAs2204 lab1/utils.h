#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;
template <typename t>
 t getCorrectNumber(t min, t max)
{
     t x;
    while ((cin >> x).fail() || x < min || x>max)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Type number between " << min << " and " << max << endl;
    }
    return x;
}
inline int getCorrectID(unordered_set<int>& id)
{
    cout << "input id" << endl;
    int x;
    while ((cin >> x).fail() || find(id.begin(), id.end(), x) == id.end())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "input some of this ids" << endl;
        for (auto i : id)
            cout << i << endl;
    }
    auto iter = find(id.begin(), id.end(), x);
    id.erase(iter);
    return x;
}


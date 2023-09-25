
#include <vector>
#include <iostream>
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

struct Pipe{
    string name;
    double length;
    double diameter;
    bool repair;
};

struct KS {
    string name;
    int amoutOfShop;
    int amountWorkingShop;
    double KPD;
};
istream& operator >> (istream& in, Pipe& pipe)
{
    cout << "Type name:";
    in >> pipe.name;
    cout << "Type lenght:";
    pipe.length = getCorrectNumber(50, 200);
    cout << "Type diameter:";
    pipe.diameter = getCorrectNumber(8, 35);
    cout << "Is this pipe in repair?(Yes-0,No-1)";
    pipe.repair = getCorrectNumber(0, 1);
    return in;
}
ostream& operator << (ostream& out, const Pipe& pip)
{
    out << "Name:" << pip.name
        << "\tLength:" << pip.length
        << "\tDiameter:" << pip.diameter
        << "\tRepair:" << pip.repair << endl;
    return out;
}
void PrintMenu()
{
    cout << "1. Add pipe" << endl
        << "2. Add KS" << endl
        << "3. Show all objects" << endl
        << "4. Edit pipe" << endl
        << "5. Edit KS" << endl
        << "6. Save" << endl
        << "7. Load" << endl
        << "0. Exit" << endl;
}
int main()
{
    vector  <Pipe> muchPipes;
    vector <KS> muchKS;
    while (1) 
    {
        PrintMenu();
        switch (getCorrectNumber(0,7))
        {
        case 1:
        {
            Pipe pipe;
            cin >> pipe;
            muchPipes.push_back(pipe);
            break;
        }
        case 2:
        {
            break;
        }
        case 3:
        {
            cout << "Pipes:" << endl;
            for (auto& pip : muchPipes)
                cout << pip << endl;
            break;
        }
        case 4:
        {
            break;
        }
        case 5:
        {
            break;
        }
        case 6:
        {
            break;
        }
        case 7:
        {
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
        {
            cout << "Wrong action" << endl;
        }
        }

    }
}


#include <iostream>
#include <fstream>
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
    string repair;
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
    cout << "Is this pipe in repair?(Yes-1,No-0)";
    pipe.repair = (getCorrectNumber(0, 1)==1) ? "Yes":"No";
    return in;
}
istream& operator >> (istream& in, KS& ks)
{
    cout << "Type name:";
    in >> ks.name;
    cout << "Type how much shop you have:";
    ks.amoutOfShop = getCorrectNumber(0, 10000) ;
    cout << "Type how much working shop you have:";
    ks.amountWorkingShop = getCorrectNumber(0, ks.amoutOfShop);
    double usefulA = ks.amountWorkingShop;
    double A = ks.amoutOfShop;
    ks.KPD = usefulA / A;
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
ostream& operator << (ostream& out, const KS& ks)
{
    out << "Name:" << ks.name
        << "\tAmount of shop:" << ks.amoutOfShop
        << "\tAmount of working shop:" << ks.amountWorkingShop
        << "\tKPD:" << ks.KPD << endl;
    return out;
}
void SavePipes(ofstream& fout, const Pipe& pipe)
{
    fout << pipe.name << endl
        << pipe.length << endl
        << pipe.diameter << endl
        << pipe.repair << endl;
}
void SaveKS(ofstream& fout, const KS& ks)
{
    fout << ks.name << endl
        << ks.amoutOfShop << endl
        << ks.amountWorkingShop << endl
        << ks.KPD << endl;
}
Pipe LoadPipes(ifstream& fin)
{
    Pipe pip;
    fin >> pip.name;
    fin >> pip.length;
    fin >> pip.diameter;
    fin >> pip.repair;
    return pip;
}
KS LoadKS(ifstream& fin)
{
    KS ks;
    fin >> ks.name;
    fin >> ks.amoutOfShop;
    fin >> ks.amountWorkingShop;
    fin >> ks.KPD;
    return ks;
}
void EditPipe(Pipe& pipe)
{
    pipe.repair = (pipe.repair=="Yes")? "No" : "Yes";
}
void EditKS(KS& ks)
{
    cout << "Type how much working shop you have:";
    ks.amountWorkingShop = getCorrectNumber(0, ks.amoutOfShop);
    double usefulA = ks.amountWorkingShop;
    double A = ks.amoutOfShop;
    ks.KPD = usefulA / A;
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
    Pipe pipe;
    KS ks;
    while (1) 
    {
        PrintMenu();
        switch (getCorrectNumber(0,7))
        {
        case 1:
        {
            cin >> pipe;
            break;
        }
        case 2:
        {
            cin >> ks;
            break;
        }
        case 3:
        {
            cout << "Pipes:" << endl;
            if (!pipe.name.empty())
                cout << pipe << endl;
            else
                cout << "Not found" << endl;
            cout << "KS:" << endl;
            if (!ks.name.empty())
                cout << ks << endl;
            else
                cout << "Not found" << endl;
            break;
        }
        case 4:
        {
            EditPipe(pipe);
            break;
        }
        case 5:
        {
            EditKS(ks);
            break;
        }
        case 6:
        {
            ofstream fout;
            fout.open("data.txt", ios::out);
            if (fout.is_open())
            {
                SavePipes(fout, pipe);
                SaveKS(fout, ks);
            }
            fout.close();
            break;
        }
        case 7:
        {
            ifstream fin;
            fin.open("data.txt", ios::in);
            if (fin.is_open())
            {
                pipe = LoadPipes(fin);
                ks = LoadKS(fin);
            }
            fin.close();
            break;
        }
        case 0:
        {
            return 0;
        }
        }
    }
}


#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int getCorrectNumber(int min, int max)
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
    string effectiveness;
};
istream& operator >> (istream& in, Pipe& pipe)
{
    cout << "Type name:";
    in.ignore();
    getline(in,pipe.name);
    cout << "Type lenght:";
    pipe.length = getCorrectNumber(50, 200);
    cout << "Type diameter:";
    pipe.diameter = getCorrectNumber(8, 35);
    cout << "Is this pipe in repair?(Yes-1,No-0)";
    pipe.repair = getCorrectNumber(0, 1);
    return in;
}
string getTypeOfEffectiveness(int Number)
{
    if (Number == 1)
        return "Low";
    else if (Number == 2)
        return "Midle";
    else
        return "Hight";
}
istream& operator >> (istream& in, KS& ks)
{
    cout << "Type name:";
    in.ignore();
    getline(in, ks.name);
    cout << "Type how much shop you have:";
    ks.amoutOfShop = getCorrectNumber(1, 10000) ;
    cout << "Type how much working shop you have:";
    ks.amountWorkingShop = getCorrectNumber(0, ks.amoutOfShop);
    cout << "Type what is effectiveness you have\n 1-Low \n 2-Midle \n 3-Hight" << endl;
    ks.effectiveness = getTypeOfEffectiveness(getCorrectNumber(1,3));
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
        << "\tEffectiveness:" << ks.effectiveness << endl;
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
        << ks.effectiveness << endl;
}
Pipe LoadPipes(ifstream& fin)
{
    Pipe pip;
    fin.ignore();
    getline(fin,pip.name);
    fin >> pip.length;
    fin >> pip.diameter;
    fin >> pip.repair;
    return pip;
}
KS LoadKS(ifstream& fin)
{
    KS ks;
    fin.ignore();
    getline(fin,ks.name);
    fin >> ks.amoutOfShop;
    fin >> ks.amountWorkingShop;
    fin >> ks.effectiveness;
    return ks;
}
void EditPipe(Pipe& pipe)
{
    if (!pipe.name.empty())
        pipe.repair = !pipe.repair;// == "Yes") ? "No" : "Yes
    else
        cout << "Please load or input pipe" << endl;
}
void EditKS(KS& ks)
{
    if (!ks.name.empty())
    {
        cout << "Type how much working shop you have:";
        ks.amountWorkingShop = getCorrectNumber(0, ks.amoutOfShop);
    }
    else
        cout << "Please load or input ks" << endl;
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
                if (!pipe.name.empty()) 
                {
                    fout << 1<<endl;
                    SavePipes(fout, pipe);
                }
                else
                    fout << 0<<endl;
                if (!ks.name.empty()) 
                {
                    fout <<1<<endl;
                    SaveKS(fout, ks);
                }
                else
                    fout << 0<<endl;

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
                string existPipe;
                string existKS;
                fin >> existPipe;
                if (existPipe == "1")
                    pipe = LoadPipes(fin);
                fin >> existKS;
                if (existKS=="1")
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

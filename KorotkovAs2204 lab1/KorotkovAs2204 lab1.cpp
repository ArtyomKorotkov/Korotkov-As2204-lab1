#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "utils.h"
#include "CPipe.h"
#include "Cks.h"



using namespace std;


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
        pipe.repair = !pipe.repair;
    else
        cout << "Please load or input pipe" << endl;
}
void EditKS(KS& ks)
{
    if (!ks.name.empty())
    {
        cout << "Type how much working shop you have:";
        ks.amountWorkingShop =  getCorrectNumber(0, ks.amoutOfShop);
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
        << "8. Search Pipe" << endl
        << "9. Search KS" << endl
        << "0. Exit" << endl;
}
template <typename t>
t& Select(vector<t>& group)
{
    if (!group.empty())
    {
        cout << "Type index: ";
        int sizeOfgroup = group.size();
        int index = getCorrectNumber(1, sizeOfgroup);
        return group[index - 1];
    }
    
}
template <typename T>
using FilterPipe = bool(*)(const Pipe& pipe, T param);


template <typename T>
using FilterKS = bool(*)(const KS& ks, T param);

template <typename T>
bool checkByName(const T& object, string param)
{
    return object.name == param;
}
bool checkByRepair(const Pipe& pipe, bool param)
{
    return pipe.repair == param;
}
bool checkByUnusedWorkshops(const KS& ks, double param)
{
    double percentOfUnusedWorkshops = (double (ks.amoutOfShop - ks.amountWorkingShop) * 100) / ks.amoutOfShop;
    return percentOfUnusedWorkshops >=param;
}
template <typename T>

vector <int> FindPipebyFilter(const vector<Pipe>& groupOfPipe,FilterPipe<T> f, T param)
{
    vector <int> res;
    int i = 0;
    for (auto& pipe : groupOfPipe)
    {
        if (f(pipe,param))
            res.push_back(i);
        i++;
    }
    return res;
}

template <typename T>
vector <int> FindKSbyFilter(const vector<KS>& groupOfKs, FilterKS<T> f, T param)
{
    vector <int> res;
    int i = 0;
    for (auto& KS : groupOfKs)
    {
        if (f(KS, param))
            res.push_back(i);
        i++;
    }
    return res;
}
int main()
{
    double d;
    d = getCorrectNumber(0., 100.);
    cout<<d<< endl;
    vector <Pipe> groupOfPipe;
    vector <KS> groupOfKs;
    while (1) 
    {
        PrintMenu();
        switch (getCorrectNumber(0,9))
        {
        case 1:
        {
            Pipe pipe;
            cin >> pipe;
            groupOfPipe.push_back(pipe);
            break;
        }
        case 2:
        {
            KS ks;
            cin >> ks;
            groupOfKs.push_back(ks);
            break;
        }
        case 3:
        {
            cout << "Pipes:" << endl;
            if (!groupOfPipe.empty())
                for (Pipe& pipe:groupOfPipe)
                    cout << pipe << endl;
            else
                cout << "Not found" << endl;
            cout << "KS:" << endl;
            if (!groupOfKs.empty())
                for (KS& ks:groupOfKs)
                    cout << ks << endl;
            else
                cout << "Not found" << endl;
            break;
        }
        case 4:
        {

            EditPipe(Select(groupOfPipe));
            break;
        }
        case 5:
        {
            EditKS(Select(groupOfKs));
            break;
        }
        case 6:
        {
            ofstream fout;
            fout.open("data.txt", ios::out);
            if (fout.is_open())
            {
                fout << groupOfPipe.size()<<endl;
                for (Pipe pipe: groupOfPipe)
                    SavePipes(fout, pipe);
                fout << groupOfKs.size() << endl;
                for (KS ks:groupOfKs)
                    SaveKS(fout, ks);
                fout.close();
            }
            break;
        }
        case 7:
        {
            ifstream fin;
            fin.open("data.txt", ios::in);
            if (fin.is_open())
            {
                int countOfPipe;
                int countOfKS;
                fin >> countOfPipe;
                while(countOfPipe--)
                    groupOfPipe.push_back(LoadPipes(fin));
                fin >> countOfKS;
                while (countOfKS--)
                    groupOfKs.push_back(LoadKS(fin));
                fin.close();
            }
            break;
        }
        case 8:
        {
            int choose;
            cout << "Search pipe by name(1) by status of repair(2): ";
            choose = getCorrectNumber(1, 2);
            if (choose==1)
            {
                string name;
                cout << "Type the name of pipe:" << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                getline(cin, name);
                for (int i : FindPipebyFilter(groupOfPipe, checkByName, name))
                    cout << groupOfPipe[i];
            }
            else
            {
                bool status;
                cout << "Type the statys of pipe(Yes-1,No-0):" << endl;
                status = getCorrectNumber(0, 1);
                for (int i : FindPipebyFilter(groupOfPipe, checkByRepair, status))
                    cout << groupOfPipe[i];
            }
            break;
        }
        case 9:
        {
            int choose;
            cout << "Search KS by name(1) by number of unused workshops(2): ";
            choose = getCorrectNumber(1, 2);
            if (choose == 1)
            {
                string name;
                cout << "Type the name of ks:" << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                getline(cin, name);
                for (int i : FindKSbyFilter(groupOfKs, checkByName, name))
                    cout << groupOfKs[i];
            }
            else
            {
                double percent;
                cout << "Enter the percent of unused workshops";
                percent = getCorrectNumber(0., 100.);
                for (int i : FindKSbyFilter(groupOfKs, checkByUnusedWorkshops, percent))
                    cout << groupOfKs[i] << (double(groupOfKs[i].amoutOfShop - groupOfKs[i].amountWorkingShop) * 100) / groupOfKs[i].amoutOfShop;
            
            }
            break;
        }
        case 0:
        {
            return 0;
        }
        }
    }
}
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
int main()
{
    vector <Pipe> groupOfPipe;
    vector <KS> groupOfKs;
    while (1) 
    {
        PrintMenu();
        switch (getCorrectNumber(0,7))
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
        case 0:
        {
            return 0;
        }
        }
    }
}

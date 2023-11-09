#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "utils.h"
#include "CPipe.h"
#include "Cks.h"
#include <algorithm>


using namespace std;
double percentOfUnusedWorkshops(const KS &ks)
{
    return (double(ks.amoutOfShop - ks.amountWorkingShop) * 100) / ks.amoutOfShop;
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
    return percentOfUnusedWorkshops(ks) >= param;
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
vector<int> FindKSsID(vector<KS>& groupOfKs)
    {
        vector<int> ID;
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
            ID=FindKSbyFilter(groupOfKs, checkByName, name);
        }
        else
        {
            double percent;
            cout << "Enter the percent of unused workshops";
            percent = getCorrectNumber(0., 100.);
            ID = FindKSbyFilter(groupOfKs, checkByUnusedWorkshops, percent);
        }
        return ID;
}
vector<int> FindPipesID(vector<Pipe>& groupOfPipe)
{

    vector<int> ID;
    int choose;
    cout << "Search Pipe by name(1) by number status of repairing(2): ";
    choose = getCorrectNumber(1, 2);
    if (choose == 1)
    {
        string name;
        cout << "Type the name of pipe:" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        getline(cin, name);
        ID = FindPipebyFilter(groupOfPipe, checkByName, name);
    }
    else
    {
        bool status;
        cout << "Type the status of pipe(Yes-1,No-0):" << endl;
        status = getCorrectNumber(0, 1);
        ID = FindPipebyFilter(groupOfPipe, checkByRepair, status);
    }
    return ID;
}
int getCorrectID(vector <int>& Ids)
{
    int x;
    while ((cin >> x).fail() || find(Ids.begin(), Ids.end(),x)==Ids.end())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "input some of this ids" << endl;
        for (int id : Ids)
            cout << id<<endl;
    }
    auto iter = find(Ids.begin(), Ids.end(), x);
    Ids.erase(iter);
    return x;
}

void EditKS(vector<KS>& groupOfKs)
{

    if (groupOfKs.size() != 0)
    {
        cout << "1.Edit KS 2. Delete KS :";
        int choose;
        choose = getCorrectNumber(1, 2);
        if (choose == 1)
        {
            cout << "1.Edit by filter 2.Edit by ids:";
            int choose2;
            choose2 = getCorrectNumber(1, 2);
            if (choose2 == 1)
            {
                vector <int> ids;
                ids = FindKSsID(groupOfKs);
                cout << "1.Edit all kss 2.Edit some kss:";
                int choose3;
                choose3 = getCorrectNumber(1, 2);
                if (choose3 == 1)
                {
                    if (ids.size() != 0)
                    {
                        int minAmountOfWorkingShops = INT_MAX;
                        for (int id : ids)
                            minAmountOfWorkingShops = min(minAmountOfWorkingShops, groupOfKs[id].amoutOfShop);
                        cout << "Enter chenged amount of working shops: ";
                        int changedAmountOfWS = getCorrectNumber(0, minAmountOfWorkingShops);
                        for (int id : ids)
                            groupOfKs[id].amountWorkingShop = changedAmountOfWS;
                    }
                    else
                        cout << "You cant change anything"<<endl;
                }
                else
                {
                    if (ids.size() > 0)
                    {
                        int countOfKS;
                        cout << "How much KSs you want to change" << endl;
                        cout << "You can change " << ids.size() << " KSs" << endl;
                        int countOfIds = ids.size();
                        countOfKS = getCorrectNumber(0, countOfIds);
                        while (countOfKS != 0)
                        {
                            groupOfKs[getCorrectID(ids)].editKS();
                            countOfKS--;
                        }
                    }
                    else
                        cout << "You cant change anything"<<endl;

                }
            }
            else
            {
                if (KS::MaxId > 0)
                {
                    cout << "How much KSs you want to change" << endl;
                    int countOfKS;
                    countOfKS = getCorrectNumber(1, KS::MaxId);
                    vector <int> id;
                    for (int i = 0; i < KS::MaxId; i++)
                        id.push_back(i);
                    vector<int> ids;
                    while (countOfKS != 0)
                    {
                        cout << "Choose id ks to edit:";
                        int x = getCorrectID(id);
                        ids.push_back(x);
                        countOfKS--;
                    }
                    cout << "1.Edit all kss 2.Edit some kss:";
                    int choose3;
                    choose3 = getCorrectNumber(1, 2);
                    if (choose3 == 2)
                    {
                        for (int& i : ids)
                        {
                            cout << "Now you change KS with id: " << i << endl;
                            groupOfKs[i].editKS();
                        }
                    }
                    else
                    {
                        if (ids.size() != 0)
                        {
                            int minAmountOfWorkingShops = INT_MAX;
                            for (int id : ids)
                                minAmountOfWorkingShops = min(minAmountOfWorkingShops, groupOfKs[id].amoutOfShop);
                            cout << "Enter chenged amount of working shops: ";
                            int changedAmountOfWS = getCorrectNumber(0, minAmountOfWorkingShops);
                            for (int id : ids)
                                groupOfKs[id].amountWorkingShop = changedAmountOfWS;
                        }
                        else
                            cout << "You cant change anything" << endl;
                    }
                }
               
            }
        }
        else
        {
            cout << "1.Delete by filter 2.Delete by ids:";
            int choose2;
            choose2 = getCorrectNumber(1, 2);
            if (choose2 == 1)
            {
                vector <int> ids;
                ids = FindKSsID(groupOfKs);
                if (ids.size() != 0)
                {
                    cout << "1 delete all ks 2 delete some ks";
                    int choose4;
                    choose4 = getCorrectNumber(1, 2);
                    if (choose4 == 1)
                    {
                        vector <int>necessaryID;
                        int i = 0;
                        while (necessaryID.size() != KS::MaxId - ids.size())
                        {
                            if (find(ids.begin(), ids.end(), i) == ids.end())
                                necessaryID.push_back(i);
                            i++;
                        }
                        vector <KS>copygroupOfKs = groupOfKs;
                        groupOfKs.clear();
                        for (int x : necessaryID)
                        {
                            groupOfKs.push_back(copygroupOfKs[x]);
                        }
                        KS::MaxId = 0;
                        for (auto& i : groupOfKs)
                            i.updateID();
                    }
                    else
                    {
                        int countOfKS;
                        cout << "How much KS you want to delete" << endl;
                        if (ids.size() > 0)
                        {
                            cout << "You can change" << ids.size() << "KSs" << endl;
                            int countOfIds = ids.size();
                            countOfKS = getCorrectNumber(0, countOfIds);
                            vector<int> idForDeleted;
                            while (countOfKS != 0)
                            {
                                idForDeleted.push_back(getCorrectID(ids));
                                countOfKS--;
                            }
                            vector <int>necessaryID;
                            int i = 0;
                            while (necessaryID.size() != KS::MaxId - idForDeleted.size())
                            {
                                if (find(idForDeleted.begin(), idForDeleted.end(), i) == idForDeleted.end())
                                    necessaryID.push_back(i);
                                i++;
                            }
                            vector <KS>copygroupOfKS = groupOfKs;
                            groupOfKs.clear();
                            for (int x : necessaryID)
                            {
                                groupOfKs.push_back(copygroupOfKS[x]);
                            }
                            KS::MaxId = 0;
                            for (auto& i : groupOfKs)
                                i.updateID();
                        }
                        else
                            cout << "You cant change anything" << endl;
                    }
                }
                else
                    cout << "You cant change anything"<<endl;

            }
            else 
            {
                cout << "How much KSs you want to delete" << endl;
                int countOfKS;
                countOfKS = getCorrectNumber(1, KS::MaxId);
                vector <int> id;
                for (int i = 0; i < KS::MaxId; i++)
                    id.push_back(i);
                vector<int> ids;
                while (countOfKS != 0)
                {
                    cout << "Choose id ks to edit:";
                    int x = getCorrectID(id);
                    ids.push_back(x);
                    countOfKS--;
                }
                if (ids.size() != 0)
                {
                    vector <int>necessaryID;
                    int i = 0;
                    while (necessaryID.size() != KS::MaxId - ids.size())
                    {
                        if (find(ids.begin(), ids.end(), i) == ids.end())
                            necessaryID.push_back(i);
                        i++;
                    }
                    vector <KS>copygroupOfKs = groupOfKs;
                    groupOfKs.clear();
                    for (int x : necessaryID)
                    {
                        groupOfKs.push_back(copygroupOfKs[x]);
                    }
                    KS::MaxId = 0;
                    for (auto& i : groupOfKs)
                        i.updateID();
                }
                else
                    cout << "You cant change anything";
            }
        }
    }
    else
    {
        cout << "Please load or input ks" << endl;
    }
}
void EditPipe(vector<Pipe>& groupOfPipe)
{

    if (groupOfPipe.size() != 0)
    {
        cout << "1.Edit pipe 2. Delete pipe :";
        int choose;
        choose = getCorrectNumber(1, 2);
        if (choose == 1)
        {
            cout << "1.Edit by filter 2.Edit by ids:";
            int choose2;
            choose2 = getCorrectNumber(1, 2);
            if (choose2 == 1)
            {
                vector <int> ids;
                ids = FindPipesID(groupOfPipe);
                cout << "1.Edit all pipes 2.Edit some pipes:";
                int choose3;
                choose3 = getCorrectNumber(1, 2);
                if (choose3 == 1)
                {
                    if (ids.size() != 0)
                    {
                        cout << "New status (1:yes 0:no)";
                        bool changedStatus = getCorrectNumber(0, 1);
                        for (int id : ids)
                            groupOfPipe[id].repair = changedStatus;
                    }
                    else
                        cout << "You cant change anyting"<<endl;
                }
                else
                {
                    int countOfPipe;
                    cout << "How much Pipes you want to change" << endl;
                    if (ids.size() > 0)
                    {
                        cout << "You can change " << ids.size() << " Pipes" << endl;
                        int countOfIds = ids.size();
                        countOfPipe = getCorrectNumber(0, countOfIds);
                        while (countOfPipe != 0)
                        {
                            groupOfPipe[getCorrectID(ids)].editPipe();
                            countOfPipe--;
                        }
                    }
                    else
                        cout << "you cant change anything" << endl;
                }
            }
            else
            {
                cout << "How much Pipes you want to change" << endl;
                int countOfPipe;
                countOfPipe = getCorrectNumber(1, Pipe::MaxId);
                vector <int> id;
                for (int i = 0; i < Pipe::MaxId; i++)
                    id.push_back(i);
                vector<int> ids;
                while (countOfPipe != 0)
                {
                    cout << "Choose id pipe to edit:";
                    int x = getCorrectID(id);
                    ids.push_back(x);
                    countOfPipe--;
                }
                cout << "1.Edit all pipes 2.Edit some pipes:";
                int choose3;
                choose3 = getCorrectNumber(1, 2);
                if (choose3 == 2)
                {
                    for (int& i : ids)
                    {
                        cout << "Now you change pipe with id: " << i << endl;
                        groupOfPipe[i].editPipe();
                    }
                }
                else
                {
                    if (ids.size() != 0)
                    {
                        cout << "Input new status";
                        int changedStatus = getCorrectNumber(0, 1);
                        for (int id : ids)
                            groupOfPipe[id].repair = changedStatus;
                    }
                    else
                        cout << "You cant change anything";
                }

            }
        }
        else
        {
            cout << "1.Delete by filter 2.Delete by ids:";
            int choose2;
            choose2 = getCorrectNumber(1, 2);
            if (choose2 == 1)
            {
                vector <int> ids;
                ids = FindPipesID(groupOfPipe);
                if (ids.size() != 0)
                {
                    cout << "1 delete all found 2 choice deleted item";
                    int choose4;
                    choose4 = getCorrectNumber(1, 2);
                    if (choose4 == 1) {
                        vector <int>necessaryID;
                        int i = 0;
                        while (necessaryID.size() != Pipe::MaxId - ids.size())
                        {
                            if (find(ids.begin(), ids.end(), i) == ids.end())
                                necessaryID.push_back(i);
                            i++;
                        }
                        vector <Pipe>copygroupOfPipe = groupOfPipe;
                        groupOfPipe.clear();
                        for (int x : necessaryID)
                        {
                            groupOfPipe.push_back(copygroupOfPipe[x]);
                        }
                        Pipe::MaxId = 0;
                        for (auto& i : groupOfPipe)
                            i.updateID();
                    }
                    else
                    {
                        int countOfPipe;
                        cout << "How much Pipes you want to delete" << endl;
                        if (ids.size() > 0)
                        {
                            cout << "You can change" << ids.size() << "Pipes" << endl;
                            int countOfIds = ids.size();
                            countOfPipe = getCorrectNumber(0, countOfIds);
                            vector<int> idForDeleted;
                            while (countOfPipe != 0)
                            {
                                for (int id : ids)
                                    cout << id << endl;

                                idForDeleted.push_back( getCorrectID(ids));
                                countOfPipe--;
                            }
                            vector <int>necessaryID;
                            int i = 0;
                            while (necessaryID.size() != Pipe::MaxId - idForDeleted.size())
                            {
                                if (find(idForDeleted.begin(), idForDeleted.end(), i) == idForDeleted.end())
                                    necessaryID.push_back(i);
                                i++;
                            }
                            vector <Pipe>copygroupOfPipe = groupOfPipe;
                            groupOfPipe.clear();
                            for (int x : necessaryID)
                            {
                                groupOfPipe.push_back(copygroupOfPipe[x]);
                            }
                            Pipe::MaxId = 0;
                            for (auto& i : groupOfPipe)
                                i.updateID();
                        }
                        else
                            cout << "you cant change anything" << endl;
                    }
                }

            }
            else
            {
                cout << "Enter the number of Pipe which you want to delete";
                int countOfPipe;
                countOfPipe = getCorrectNumber(1, Pipe::MaxId);
                vector<int> allId;
                for (int i=0; i < Pipe::MaxId; i++)
                    allId.push_back(i);
                int idFordeleted;
                vector<int> ids;
                while (countOfPipe != 0)
                {
                    cout << "Choose id pipe to delete:";
                    idFordeleted=(getCorrectID(allId));
                    ids.push_back(idFordeleted);
                    countOfPipe--;
                }
                if (ids.size() != 0)
                {
                    vector <int>necessaryID;
                    int i = 0;
                    while (necessaryID.size() != Pipe::MaxId - ids.size())
                    {
                        if (find(ids.begin(), ids.end(), i) == ids.end())
                            necessaryID.push_back(i);
                        i++;
                    }
                    vector <Pipe>copygroupOfPipe = groupOfPipe;
                    groupOfPipe.clear();
                    for (int x : necessaryID)
                    {
                        groupOfPipe.push_back(copygroupOfPipe[x]);
                    }
                    Pipe::MaxId = 0;
                    for (auto& i : groupOfPipe)
                        i.updateID();
                }
                else
                    cout << "you cant change anything"<<endl;


            }

        }
    }
    else
    {
        cout << "Please load or input pipe" << endl;
    }
}
int main()
{
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

            EditPipe(groupOfPipe);
            break;
        }
        case 5:
        {
            EditKS(groupOfKs);
            break;
        }
        case 6:
        {
            ofstream fout;
            cout << "Enter name for file to save your data: ";
            string nameData;
            cin >> nameData;
            fout.open(nameData+".txt", ios::out);
            if (fout.is_open())
            {
                fout << groupOfPipe.size()<<endl;
                for (Pipe pipe: groupOfPipe)
                    pipe.SavePipes(fout);
                fout << groupOfKs.size() << endl;
                for (KS ks:groupOfKs)
                    ks.SaveKS(fout);
                fout.close();
            }
            else
            {
                cout << "Record error" << endl;;
            }
            break;
        }
        case 7:
        {
            cout << "enter name for input file: ";
            string nameInput;
            cin >> nameInput;
            ifstream fin;
            fin.open(nameInput+".txt", ios::in);
            if (fin.is_open())
            {
                int countOfPipe;
                int countOfKS;
                fin >> countOfPipe;
                while (countOfPipe--)
                {
                    Pipe pipe;
                    pipe.LoadPipes(fin);
                    groupOfPipe.push_back(pipe);
                }
                fin >> countOfKS;
                while (countOfKS--)
                {
                    KS ks;
                    ks.LoadKS(fin);
                    groupOfKs.push_back(ks);
                }
                fin.close();
            }
            else
                cout << "Reading error"<<endl;
            break;
        }
        case 8:
        {
            if (groupOfPipe.size() != 0)
            {
                vector<int> ID;
                ID = FindPipesID(groupOfPipe);
                for (int i : ID)
                    cout << groupOfPipe[i];
            }
            else
                cout << "Group of pipe is empty"<<endl;
            break;
        }
        case 9:
        {
            if (groupOfKs.size() != 0)
            {
                vector<int> ID;
                ID = FindKSsID(groupOfKs);
                for (int i : ID)
                    cout << groupOfKs[i];
            }
            else
                cout << "Group of ks is empty"<<endl;
            break;
        }
        case 0:
        {
            return 0;
        }
        }
    }
}
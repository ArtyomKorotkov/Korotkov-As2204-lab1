#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "utils.h"
#include "CPipe.h"
#include "Cks.h"
#include "Connection.h"
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>


using namespace std;
unordered_map<int, Pipe> groupOfPipe;
unordered_map<int, KS> groupOfKs;
Connection connections;

void PrintMenu()
{
    cout << "1. Add pipe" << endl
        << "2. Add KS" << endl
        << "3. Show all objects" << endl
        << "4. Search Pipe" << endl
        << "5. Search KS" << endl
        << "6. Save" << endl
        << "7. Load" << endl
        << "8. Add connect" << endl
        <<"9. Topological sort"<<endl
        <<"10. View connections"<<endl
        << "0. Exit" << endl;
}


template <typename T>
using FilterPipe = bool(*)(const Pipe& pipe, T param);


template <typename T>
using FilterKS = bool(*)(const KS& ks, T param);

template <typename T>
bool checkByName(const T& object, string param)
{
    return object.name.find(param)!=string::npos;
}
bool checkByRepair(const Pipe& pipe, bool param)
{
    return pipe.repair == param;
}

bool checkByUnusedWorkshops( const KS& ks, double param)
{
    return (double(ks.amoutOfShop - ks.amountWorkingShop) * 100) / ks.amoutOfShop>= param;
}
template <typename T>

unordered_set<int> FindPipebyFilter(const unordered_map<int, Pipe>& groupOfPipe,FilterPipe<T> f, T param)
{
    unordered_set<int> res;
    for (auto& pipe : groupOfPipe)
    {
        if (f(pipe.second,param))
            res.insert(pipe.first);
    }
    return res;
}

template <typename T>
unordered_set<int> FindKSbyFilter( unordered_map<int, KS>& groupOfKs, FilterKS<T> f, T param)
{
    unordered_set<int> res;
    for (auto& KS : groupOfKs)
    {
        if (f(KS.second, param))
            res.insert(KS.first);
    }
    return res;
}
unordered_set<int> FindKSsID(unordered_map<int,KS>& groupOfKs)
    {
        unordered_set<int> ID;
        int choose;
        cout << "Search KS by name(1) by number of unused workshops(2) by id(3): ";
        choose = getCorrectNumber(1, 3);
        if (choose == 1)
        {
            string name;
            cout << "Type the name of ks:" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            getline(cin, name);
            ID=FindKSbyFilter(groupOfKs, checkByName, name);
        }
        else if(choose==2)
        {
            double percent;
            cout << "Enter the percent of unused workshops";
            percent = getCorrectNumber(0., 100.);
            ID = FindKSbyFilter(groupOfKs, checkByUnusedWorkshops, percent);
        }
        else if(choose==3)
        {
            unordered_set<int> allId;
            cout << "All id you can input"<<endl;
            for (auto x : groupOfKs)
            {
                cout << x.first << endl;
                allId.insert(x.first);
            }
            while (1)
            {
                ID.insert(getCorrectID(allId));
                if (allId.size() == 0)
                    break;
                cout << "you want to stop? (1 yes) (2 No)" << endl;
                int choose = getCorrectNumber(1, 2);
                if (choose == 1)
                    break;
            }
        }
        return ID;
}
unordered_set<int> FindPipesID(unordered_map<int, Pipe>& groupOfPipe)
{

    unordered_set<int> ID;
    int choose;
    cout << "Search Pipe by name(1) by number status of repairing(2) by ids(3): ";
    choose = getCorrectNumber(1, 3);
    if (choose == 1)
    {
        string name;
        cout << "Type the name of pipe:" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        getline(cin, name);
        ID = FindPipebyFilter(groupOfPipe, checkByName, name);
    }
    else if(choose==2)
    {
        bool status;
        cout << "Type the status of pipe(Yes-1,No-0):" << endl;
        status = getCorrectNumber(0, 1);
        ID = FindPipebyFilter(groupOfPipe, checkByRepair, status);
    }
    else if (choose == 3)
    {
        unordered_set<int> allId;
        cout << "All id you can input" << endl;
        for (auto x : groupOfPipe)
        {
            cout << x.first << endl;
            allId.insert(x.first);
        }
        while (1)
        {
            ID.insert(getCorrectID(allId));
            if (allId.size() == 0)
                break;
            cout << "you want to stop? (1 yes) (2 No)" << endl;
            int choose = getCorrectNumber(1, 2);
            if (choose == 1)
                break;
        }
    }
    return ID;
}

template <typename T>
void ShowSearchObject(T& groupOfObject,unordered_set<int>& id)
{
    for (auto& i : id)
        cout << groupOfObject[i] << endl;
}
void editKs(unordered_map<int, KS>& groupOfKs, unordered_set<int>& id)
{
    if (id.size() > 1)
    {
        int choose;
        cout << "Edit All(1), edit some ks(2)";
        choose = getCorrectNumber(1, 2);
        if (choose == 1)
        {
            int minAmountOfWorkingShops = INT_MAX;
            for (int i : id)
                minAmountOfWorkingShops = min(minAmountOfWorkingShops, groupOfKs[i].amoutOfShop);
            cout << "Enter chenged amount of working shops: ";
            int changedAmountOfWS = getCorrectNumber(0, minAmountOfWorkingShops);
            for (int i : id)
                groupOfKs[i].amountWorkingShop = changedAmountOfWS;
        }
        else
        {
            unordered_set<int>::iterator itr;
            while (1)
            {
                groupOfKs[getCorrectID(id)].editKS();
                if (id.size() == 0)
                    break;
                cout << "you want to stop? (1 yes) (2 No)" << endl;
                int choose = getCorrectNumber(1, 2);
                if (choose == 1)
                    break;
            }
        }
    }
    else 
    {
        for (int i : id)
            groupOfKs[i].editKS();
    }
}

void deleteKS(unordered_map<int, KS>& groupOfKs, unordered_set<int>& id)
{
    if (id.size() > 1)
    {
        int choose;
        cout << "delete All(1), delete some ks(2)";
        choose = getCorrectNumber(1, 2);
        if (choose == 1)
        {
            for (int i : id)
            {
                groupOfKs.erase(i);
                connections.deleteByVer(i);
            }
        }
        else
        {
            unordered_set<int>::iterator itr;
            while (1)
            {
                int i = getCorrectID(id);
                groupOfKs.erase(i);
                connections.deleteByVer(i);
                cout << "you want to stop? (1 yes) (2 No)" << endl;
                if (id.size() == 0)
                    break;
                int choose = getCorrectNumber(1, 2);
                if (choose == 1)
                    break;
            }
        }
    }
    else
    {
        for (int i : id)
        {
            groupOfKs.erase(i);
            connections.deleteByVer(i);
        }
    }
}
void ShowEditKs(unordered_map<int, KS>& groupOfKs)
{
    if (groupOfKs.size() != 0)
    {
        auto id = FindKSsID(groupOfKs);
        if (id.size() != 0)
        {
            ShowSearchObject(groupOfKs, id);
            int choose;
            cout << "Edit(1), Delete(2), Exit(0)";
            choose = getCorrectNumber(0, 2);
            if (choose == 1)
            {
                editKs(groupOfKs, id);
            }
            else if (choose == 2)
            {
                deleteKS(groupOfKs, id);
            }
        }
        else
            cout << "No such kss" << endl;;
    }
    else
        cout << "You have zero ks" << endl;
}
void editPipe(unordered_map<int, Pipe>& groupOfPipe, unordered_set<int>& id)
{
    if (id.size() > 1)
    {
        int choose;
        cout << "Edit All(1), edit some Pipe(2)";
        choose = getCorrectNumber(1, 2);
        if (choose == 1)
        {
            cout << "New status (1:yes 0:no)";
            bool changedStatus = getCorrectNumber(0, 1);
            for (int i : id)
                groupOfPipe[i].repair = changedStatus;
        }
        else
        {
            unordered_set<int>::iterator itr;
            while (1)
            {
                groupOfPipe[getCorrectID(id)].editPipe();
                cout << "you want to stop? (1 yes) (2 No)" << endl;
                if (id.size() == 0)
                    break;
                int choose = getCorrectNumber(1, 2);
                if (choose == 1)
                    break;
            }
        }
    }
    else
    {
        for (int i : id)
            groupOfPipe[i].editPipe();
    }
}

void deletePipe(unordered_map<int, Pipe>& groupOfPipe, unordered_set<int>& id)
{
    if (id.size() > 1)
    {
        int choose;
        cout << "delete All(1), delete some pipe(2)";
        choose = getCorrectNumber(1, 2);
        if (choose == 1)
        {
            for (int i : id)
            {
                groupOfPipe.erase(i);
                connections.deleteByLine(i);
            }
        }
        else
        {
            unordered_set<int>::iterator itr;
            while (1)
            {
                int i = getCorrectID(id);
                groupOfPipe.erase(i);
                connections.deleteByLine(i);
                cout << "you want to stop? (1 yes) (2 No)" << endl;
                if (id.size() == 0)
                    break;
                int choose = getCorrectNumber(1, 2);
                if (choose == 1)
                    break;
             }
        }
    }
    else
    {
        for (int i : id)
        {
            connections.deleteByLine(i);
            groupOfPipe.erase(i);
        }
    }
}
void ShowEditPipe(unordered_map<int, Pipe>& groupOfPipe)
{
    if (groupOfPipe.size() != 0)
    {
        auto id = FindPipesID(groupOfPipe);
        if (id.size() != 0)
        {
            ShowSearchObject(groupOfPipe, id);
            int choose;
            cout << "Edit(1), Delete(2), Exit(0)";
            choose = getCorrectNumber(0, 2);
            if (choose == 1)
            {
                editPipe(groupOfPipe, id);
            }
            else if (choose == 2)
            {
                deletePipe(groupOfPipe, id);
            }
        }
        else
            cout << "No such pipe"<<endl;
    }
    else
        cout << "You have zero pipes"<<endl;
}

int main()
{
    while (1) 
    {
        PrintMenu();
        switch (getCorrectNumber(0,10))
        {
        case 1:
        {
            Pipe pipe;
            cin >> pipe;
            groupOfPipe.insert({ pipe.getId(), pipe});
            break;
        }
        case 2:
        {
            KS ks;
            cin >> ks;
            groupOfKs.insert({ks.getId(),ks});
            break;
        }
        case 3:
        {
            cout << "Pipes:" << endl;
            if (!groupOfPipe.empty())
                for (auto& pipe : groupOfPipe)
                    cout << pipe.second << endl;
            else
                cout << "Not found" << endl;
            cout << "KS:" << endl;
            if (!groupOfKs.empty())
                for (auto& ks : groupOfKs)
                    cout << ks.second << "\t" << endl;
            else
                cout << "Not found" << endl;
            cout << "Connections" << endl;
            if (connections.size() != 0)
            {
                connections.viewConnection();
            }
            else
                cout << "Not found"<<endl;
            break;
        }
        case 4:
        {

            ShowEditPipe(groupOfPipe);
            break;
        }
        case 5:
        {
            ShowEditKs(groupOfKs);
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
                fout << Pipe::MaxId<<endl;
                for (auto &pipe: groupOfPipe)
                    pipe.second.SavePipes(fout);
                fout << groupOfKs.size() << endl;
                fout << KS::MaxId<<endl;
                for (auto &ks:groupOfKs)
                    ks.second.SaveKS(fout);
                connections.SaveConnection(fout);
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
                int ksMaxId;
                int pipeMaxId;
                int countOfConnections;

                fin >> countOfPipe;
                fin >> pipeMaxId;
                while (countOfPipe--)
                {
                    Pipe pipe;
                    pipe.LoadPipes(fin);
                    groupOfPipe.insert({ pipe.getId(),pipe });
                }
                Pipe::MaxId = pipeMaxId;
                fin >> countOfKS;
                fin >> ksMaxId;
                while (countOfKS--)
                {
                    KS ks;
                    ks.LoadKS(fin);
                    groupOfKs.insert({ks.getId(), ks});
                }
                KS::MaxId = ksMaxId ;
                fin >> countOfConnections;
                while (countOfConnections--)
                {
                    connections.LoadConnection(fin);
                }
                fin.close();
            }
            else
                cout << "Reading error"<<endl;
            break;
        }
        case 8: 
        {
            connections.addConnect(groupOfPipe,groupOfKs);
            break;
        }
        case 9:
        {
            connections.topologicalSort();
            break;
        }
        case 10:
        {
            int start;
            int finish;
            unordered_set<int> ids;
            for (auto& ks : groupOfKs)
                ids.insert(ks.first);
            cout << "Input start Vertex";
            start=getCorrectID(ids);
            cout << "Intput finish vertex";
            finish=getCorrectID(ids);
            connections.shortestPath(start, finish, groupOfPipe);
            break;
        }
        case 0:
        {
            return 0;
        }
        }
    }
}
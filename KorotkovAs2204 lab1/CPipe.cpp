#include "CPipe.h"
#include "utils.h"
#include <fstream>

#include <iostream>
using namespace std;

int Pipe::MaxId = 1;

Pipe::Pipe()
{
    id = MaxId++;
}
ostream& operator << (ostream& out, const Pipe& pip)
{
    out << "ID:" << pip.id
        << "\tName:" << pip.name
        << "\tLength:" << pip.length
        << "\tDiameter:" << pip.diameter
        << "\tRepair:" << pip.repair << endl;
    return out;
}
istream& operator >> (istream& in, Pipe& pipe)
{
    cout << "Type name:";
    in.ignore();
    getline(in, pipe.name);
    cout << "Type lenght:";
    pipe.length = getCorrectNumber(5., 200.);
    cout << "Type diameter(1-500,2-700,3-1000,4-1700):";
    int numOfDim = getCorrectNumber(1, 4);
    pipe.diameter = (numOfDim == 1 ? 500 : numOfDim == 2 ? 700 : numOfDim == 3 ? 1000 : 1400);
    cout << "Is this pipe in repair?(Yes-1,No-0)";
    pipe.repair = getCorrectNumber(0, 1);
    return in;
}

void Pipe::editPipe()
{
    repair = !repair;
}

void Pipe::SavePipes(ofstream& fout)
{
    fout << id << endl
        << name << endl
        << length << endl
        << diameter << endl
        << repair << endl;
}
void Pipe::LoadPipes(ifstream& fin)
{
    fin >> id;
    fin.ignore();
    getline(fin, name);
    fin >> length;
    fin >> diameter;
    fin >> repair;
}

#include "CPipe.h"
#include "utils.h"
#include "Cks.h"
using namespace std;

int Pipe::MaxId = 0;

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
    pipe.length = getCorrectNumber(50., 200.);
    cout << "Type diameter:";
    pipe.diameter = getCorrectNumber(8., 35.);
    cout << "Is this pipe in repair?(Yes-1,No-0)";
    pipe.repair = getCorrectNumber(0, 1);
    return in;
}

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Student {
public:
    string ime, jmbag;
    Student() {}
    Student(string _ime, string _jmbag) {
        ime = _ime;
        jmbag = _jmbag;
    }
};

class Bodovi {
public:
    Student student;
    int bodovi;
    Bodovi(Student _student, int _bodovi) 
    {
        student = _student;
        bodovi = _bodovi;
    }
};

class Kolegij {
public:
    string ime;
    vector<Bodovi> bodovi;
    Kolegij(string _ime, vector <Bodovi> _bodovi) 
    {
        bodovi = _bodovi;
        ime = _ime;
    }
};

bool usporedba(Bodovi a, Bodovi b) 
{
    return a.bodovi < b.bodovi;
}

int main() {
    vector<Bodovi> OOPBodovi
    {
        Bodovi(Student("Ivana Ivic", "0246002475"), 25),
        Bodovi(Student("Ivica Ivanovic", "0246005654"), 20),
        Bodovi(Student("Marko Markic", "0246004234"), 32)
    };

    Kolegij OOP("Objektno orijentirano programiranje", OOPBodovi);

    sort(OOP.bodovi.begin(), OOP.bodovi.end(), usporedba);

    for (int i = 0; i < OOP.bodovi.size(); i++)
        cout << OOP.bodovi[i].student.ime << "\t"
        << OOP.bodovi[i].student.jmbag << "\t"
        << OOP.bodovi[i].bodovi << endl;

    return 0;
}



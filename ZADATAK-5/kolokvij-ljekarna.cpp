#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Lijek {
public:
    string naziv;
    double cijena;
    static int skupi_lijek;

    Lijek(){}
    Lijek(string _naziv, double _cijena) {
        naziv = _naziv;
        cijena = _cijena;
        if (cijena > 120)
            skupi_lijek++;
    }

    static int getSkupiLijek() {
        return skupi_lijek;
    }
};

int Lijek::skupi_lijek = 0;

namespace Farmacija {
class Ljekarna {
public:
    vector<Lijek> lijekovi;

    Ljekarna(){}
    Ljekarna(initializer_list<Lijek> args) : lijekovi({args}) {}

    virtual string getVrsta() {
        return "vrsta lijeka";
    }

    virtual ~Ljekarna() {

    }
};
}

Farmacija::Ljekarna operator +(Farmacija::Ljekarna& z1, Farmacija::Ljekarna& z2) {
    Farmacija::Ljekarna rezultat;

    for (int i = 0; i < z1.lijekovi.size(); i++) {
        rezultat.lijekovi.push_back(z1.lijekovi[i]);
    }
    for (int j = 0; j < z2.lijekovi.size(); j++) {
        rezultat.lijekovi.push_back(z2.lijekovi[j]);
    }

    return rezultat;
}

ostream& operator <<(ostream& izlaz, Farmacija::Ljekarna& ljekarna) {
    for (int i = 0; i < ljekarna.lijekovi.size(); i++) {
        cout << ljekarna.lijekovi[i].naziv << " ima cijenu: " << ljekarna.lijekovi[i].cijena << "kn" << endl;
    }
    return izlaz;
}

class receptna_ljekarna : public Farmacija::Ljekarna {
public:

    string getVrsta() override {
        return "Lijekovi s receptom";
    }
};

class bezreceptna_ljekarna : public Farmacija::Ljekarna {
public:

    string getVrsta() override {
        return "Lijekovi bez recepta";
    }
};

int broj_istih = 0;

bool usporediti(Lijek jedan, Lijek dva){
    if (broj_istih >= 2)
        return jedan.naziv < dva.naziv;
    else
        return jedan.cijena < dva.cijena;
}


class Usporedba {
public:

    bool operator ()(Lijek a, Lijek b) {
        if (broj_istih >= 2)
            return a.naziv < b.naziv;
        else
            return a.cijena < b.cijena;
    }
};

class Pacijent {
public:
    Farmacija::Ljekarna* ljekarna;

    Pacijent(Pacijent&& drugi) {
        ljekarna = drugi.ljekarna;
        drugi.ljekarna = NULL;
    }

    Pacijent& operator =(Pacijent&& drugi) {
        delete ljekarna;
        ljekarna = drugi.ljekarna;
        drugi.ljekarna = NULL;
        return *this;
    }

    ~Pacijent(){
        delete ljekarna;
    }
};

class ELijek {
public:

    void ispis() {
        cout << "cijena ne smije biti negativna!" << endl;
    }
};

int main()
{
    cout << Lijek::getSkupiLijek() << endl;

    Lijek a, b, c;

    Lijek d("aspirin", 30);

    Farmacija::Ljekarna ljekarna1{ a, b, c };
    Farmacija::Ljekarna ljekarna2{ d };

    Farmacija::Ljekarna ljekarna3 = ljekarna1 + ljekarna2;


    cout << ljekarna2 << endl;


    Farmacija::Ljekarna* ljekarna4;
    receptna_ljekarna rec;
    ljekarna4 = &rec;
    cout << ljekarna4->getVrsta() << endl;

    bezreceptna_ljekarna bez;
    ljekarna4 = &bez;
    cout << ljekarna4->getVrsta() << endl;


    Farmacija::Ljekarna Ljek1;
    Lijek lijek1("aspirin", 40), lijek2("penicilin", 100), lijek3("paracetamol", 60);

    Ljek1 = { lijek1, lijek2, lijek3 };

    for (int i = 0; i < Ljek1.lijekovi.size() - 1; i++) {
        for (int j = i + 1; j < Ljek1.lijekovi.size(); j++) {
            if (Ljek1.lijekovi[i].cijena == Ljek1.lijekovi[j].cijena)
                broj_istih++;
        }
    }
    
    sort(Ljek1.lijekovi.begin(), Ljek1.lijekovi.end(), usporediti);

    sort(Ljek1.lijekovi.begin(), Ljek1.lijekovi.end(), Usporedba());

    sort(Ljek1.lijekovi.begin(), Ljek1.lijekovi.end(), [](Lijek a, Lijek b) {if (broj_istih >= 2)
        return a.naziv < b.naziv;
    else
        return a.cijena < b.cijena; });

    try {
        Lijek neki("naziv", -10);

        if (neki.cijena < 0)
            throw ELijek();

        ljekarna1.lijekovi.push_back(neki);
    }

    catch (ELijek iznimka) {
        iznimka.ispis();
    }


    return 0;
}

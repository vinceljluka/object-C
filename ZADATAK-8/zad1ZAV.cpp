#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <exception> 

using namespace std;

class ZnimkaISVUSifra{
private:
    string poruka;
    inline static int brojac = 0;

public:
    ZnimkaISVUSifra(const string& pogresnaSifra) 
    {
        brojac++;
        poruka = "Iznimka " + to_string(brojac) + ": Pogresna ISVU sifra " + pogresnaSifra;
    }

    void ispis() const {
        cout << poruka << endl;
    }
};

class Predmet {
private:
    int ISVUsifra;
public:
    string naziv;
    int ECTSa;
    string vrsta;

    Predmet(string _naziv, int _ECTSa, int _ISVUsifra, string _vrsta) : naziv(_naziv), ECTSa(_ECTSa), vrsta(_vrsta) 
    {
        setISVUsifra(_ISVUsifra);
    }


    Predmet() = default;

    void setISVUsifra(int _ISVUsifra) 
    {
        if (to_string(_ISVUsifra).length() != 6) 
        {
            throw ZnimkaISVUSifra(to_string(_ISVUsifra));
        }
        ISVUsifra = _ISVUsifra;
    }


    int getISVUsifra() const {
        return ISVUsifra;
    }

};

class Nastavnik {
public:
    string ime;
    string prezime;
    string adresa;
    vector<Predmet> vPredmeti;

    Nastavnik(string _ime, string _prezime, string _adresa)
        : ime(_ime), prezime(_prezime), adresa(_adresa) {}

    template <typename... Predmeti>
    Nastavnik(string _ime, string _prezime, string _adresa, Predmeti... predmeti);

    virtual ~Nastavnik() = default;

    virtual int ukupnaSatnica() const = 0;

    Nastavnik() = default;
};


template <typename... Predmeti>
Nastavnik::Nastavnik(string _ime, string _prezime, string _adresa, Predmeti... predmeti)
    : ime(_ime), prezime(_prezime), adresa(_adresa) {
    (vPredmeti.push_back(predmeti), ...);
}


ostream& operator<<(ostream& os, const Predmet& predmet) {
    os << "Naziv: " << predmet.naziv
        << ", ECTS: " << predmet.ECTSa << endl;
    return os;
}

ostream& operator << (ostream& izlaz, const Nastavnik& nastavnik) {

    vector <Predmet> sortiraniPredmeti = nastavnik.vPredmeti;

    sort(sortiraniPredmeti.begin(), sortiraniPredmeti.end(), [](const Predmet& a, const Predmet& b) {
        return a.getISVUsifra() < b.getISVUsifra();
        });

    izlaz << "Predmeti:" << endl;
    for (int i = 0; i < sortiraniPredmeti.size(); i++)
    {
        izlaz << sortiraniPredmeti[i];
    }
    return izlaz;
}


class Predavac : public Nastavnik {
public:
    Predavac(string _ime, string _prezime, string _adresa)
        : Nastavnik(_ime, _prezime, _adresa) {}

    template <typename... Predmeti>
    Predavac(string _ime, string _prezime, string _adresa, Predmeti... predmeti)
        : Nastavnik(_ime, _prezime, _adresa, predmeti...) {}

    int ukupnaSatnica() const override {
        return vPredmeti.size() * 20;
    }
};

class VisiPredavac : public Nastavnik {
public:
    VisiPredavac(string _ime, string _prezime, string _adresa)
        : Nastavnik(_ime, _prezime, _adresa) {}

    template <typename... Predmeti>
    VisiPredavac(string _ime, string _prezime, string _adresa, Predmeti... predmeti)
        : Nastavnik(_ime, _prezime, _adresa, predmeti...) {}

    int ukupnaSatnica() const override {
        return vPredmeti.size() * 30;
    }
};

int UkupnaSatnica(const vector<Nastavnik*>& nastavnici) {
    int total = 0;
    for (int i = 0; i < nastavnici.size(); i++) 
    {
        total += nastavnici[i]->ukupnaSatnica();
    }
    return total;
}

class ZamrznutiPredmeti {
private:
    vector<Predmet*> predmeti;
public:
   
    ~ZamrznutiPredmeti()
    {
        for (int i = 0; i < predmeti.size(); i++)
        {
            delete predmeti[i];
        }
        predmeti.clear();
    }

    ZamrznutiPredmeti(const ZamrznutiPredmeti& p)
    {
        for (int i = 0; i < p.predmeti.size(); i++)
        {
            predmeti.push_back(new Predmet);
            *predmeti[i] = *p.predmeti[i];
        }
    }

    ZamrznutiPredmeti& operator =(ZamrznutiPredmeti&& privremeni)
    {
        for (int i = 0; i < predmeti.size(); i++)
        {
            delete predmeti[i];
        }
        predmeti.clear();
        for (int i = 0; i < privremeni.predmeti.size(); i++)
        {
            predmeti.push_back(privremeni.predmeti[i]);
            privremeni.predmeti[i] = NULL;
        }
        return *this;
    }

};

int main() {
    try {
        Predmet matematika("Matematika", 6, 101101, "Obavezni");
        Predmet fizika("Fizika", 5, 102102, "Izborni");
        Predmet kemija("Kemija", 4, 103103, "Obavezni");

        Predavac predavac("Ivan", "Horvat", "Zagreb", matematika, fizika);
        VisiPredavac visiPredavac("Ana", "Kovač", "Split", kemija);

        vector <Nastavnik*> nastavnici = { &predavac, &visiPredavac };

        cout << predavac;
        cout << visiPredavac;

        int ukupnaSatnica = UkupnaSatnica(nastavnici);
        cout << "Ukupna satnica svih nastavnika: " << ukupnaSatnica << " sati" << endl;
    }
    catch (const ZnimkaISVUSifra& e) {
        e.ispis();
    }   

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <exception> 
#include <initializer_list>

using namespace std;

class Let {
public:
    int sifraLeta;
    string destinacija;

    Let() = default;

    Let(int _sifraLeta, string _destinacija)
        : sifraLeta(_sifraLeta), destinacija(_destinacija) {}

    virtual void ispisiInformacije(){
        cout << "Sifra leta: " << sifraLeta << ", Destinacija: " << destinacija << endl;
    }
};


class DomaciLet : public Let {
public:
    string opisD;
    DomaciLet(int _sifraLeta, string _destinacija, string _opisD) : Let(_sifraLeta, _destinacija), opisD(_opisD) {}

    void ispisiInformacije() override {
        cout << sifraLeta << " " << destinacija << " " << opisD << endl;
    }
};


class MedjunarodniLet : public Let {
public:
    string opisM;
    MedjunarodniLet(int _sifraLeta, string _destinacija, string _opisM) : Let(_sifraLeta, _destinacija), opisM(_opisM) {}

    void ispisiInformacije() override{
        cout << sifraLeta << " " << destinacija << " " << opisM << endl;
    }
};

void ispisOpisaLetova(const vector<Let*>& letovi) {
    for (int i = 0; i < letovi.size(); i++) {
        letovi[i]->ispisiInformacije();
    }
}

class Pilot {
private:
    int satLET;
public:
    string ime;
    int brojLET;
    vector <Let> letovi;
    inline static int brojac = 0;
    inline static double brojLetenja = 0;

    Pilot& dodajLet(const Let& let) {
        letovi.push_back(let);
        return *this;
    }

    void dodaj2() {}

    template<typename... Args>
    void dodaj2(Let let, Args... args) {
        letovi.push_back(let);
        dodaj2(args...);
    }


    Pilot(string _ime, int _brojLET, int _satLET, initializer_list <Let> _letovi)
    {
        ime = _ime;
        brojLET = _brojLET;
        letovi = _letovi;
        setSATLET(_satLET);
        brojac++;
        brojLetenja += _brojLET;
    }

    void setSATLET(int _satLET)
    {
        if (_satLET > 45)
        {
            satLET = _satLET;
        }
    }

    int getSATLET()
    {
        return satLET;
    }

    static double prosjekLetova()
    {
        return brojLetenja / (double)brojac;
    }

};

bool operator < (Pilot A, Pilot B) {
    if (A.getSATLET() == B.getSATLET())
    {
        return A.brojLET > B.brojLET;
    }
    else
    {
        return A.getSATLET() > B.getSATLET();
    }   
}

namespace ZracnaLuka {
    class AvioKompanija {
    private:
        vector<Pilot*> piloti;

    public:
        AvioKompanija(AvioKompanija&& other) {
            for (int i = 0; i < other.piloti.size(); ++i) {
                piloti.push_back(other.piloti[i]);
                other.piloti[i] = nullptr; 
            }
            other.piloti.clear(); 
        }
      
        AvioKompanija& operator = (const AvioKompanija& other) {
            if (this != &other) {
                for (int i = 0; i < piloti.size(); ++i) {
                    delete piloti[i];
                }
                piloti.clear();

                for (int i = 0; i < other.piloti.size(); ++i) {
                    piloti.push_back(new Pilot(*other.piloti[i]));
                }
            }
            return *this;
        }

        ~AvioKompanija() {
            for (int i = 0; i < piloti.size(); ++i) {
                delete piloti[i];
            }
            piloti.clear();
        }

    };
}


int main() {

    vector <Pilot> pilot = {
        Pilot("John", 20, 500, { {1, "New York"}, {2, "London"}, {3, "Paris"} }),
        Pilot("Hrco", 30, 600, { {1, "New York"}, {2, "London"}, {3, "Paris"} }),
        Pilot("Nikita", 40, 600, { {1, "New York"}, {2, "London"}, {3, "Paris"} })
    };

    Pilot L("Luka", 10, 5100, { {112, "New York"}, {212, "London"}, {312, "Paris"} });

    Let let1, let2, let3;

    L.dodaj2(let1, let2, let3);

    sort(pilot.begin(), pilot.end(), [](Pilot A, Pilot B) {
        if (A.getSATLET() == B.getSATLET())
        {
            return A.brojLET > B.brojLET;
        }
        else
        {
            return A.getSATLET() > B.getSATLET();
        }
        });

    for (int i = 0; i < pilot.size(); i++)
    {
        cout << pilot[i].ime << " " << pilot[i].brojLET << " " << pilot[i].getSATLET() << endl;
    }

    DomaciLet domaci1(1, "Zagreb", "domaci");
    DomaciLet domaci2(2, "Split", "domaci");
    MedjunarodniLet medjunarodni1(3, "New York", "medjunarodni");
    MedjunarodniLet medjunarodni2(4, "London", "medjunarodni");

    vector<Let*> letovi = { &domaci1, &domaci2, &medjunarodni1, &medjunarodni2 };
    ispisOpisaLetova(letovi);

    cout << Pilot::prosjekLetova() << endl;

    return 0;
}

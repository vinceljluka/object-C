#include <iostream>
#include <vector>
using namespace std;

class Racunalo
{
public:
    string naziv, procesor, memorija;
};

class Ucionica
{
public:
    Racunalo* racunala;
    int brRacunala;
    Ucionica() {}
    Ucionica(int brojR, string _naziv, string _procesor, string _memorija) : brRacunala(brojR)
    {
        racunala = new Racunalo[brRacunala];
        for (int i = 0; i < brRacunala; ++i)
        {
            racunala[i].naziv = _naziv;
            racunala[i].procesor = _procesor;
            racunala[i].memorija = _memorija;
        }
    }

    //Instanciranje + inicijalizacija lvalue objektom = kopirni konstruktor
    Ucionica(const Ucionica& u) // za "Ucionica B = A;" ili "Ucionica B(A);"
    {
        racunala = new Racunalo[u.brRacunala];
        for (int i = 0; i < u.brRacunala; ++i)
        {
            racunala[i].naziv = u.racunala[i].naziv;
            racunala[i].procesor = u.racunala[i].procesor;
            racunala[i].memorija = u.racunala[i].memorija;
        }
        brRacunala = u.brRacunala;
    }

    //Instanciranje + inicijalizacija rvalue objektom = konstruktor prijenosa
    Ucionica(Ucionica&& p) //"Ucionica C = move(B);"
    {
        racunala = p.racunala;
        p.racunala = NULL;
        brRacunala = p.brRacunala;
        p.brRacunala = 0;
    }

    //inicijalizacija rvalue objektom = operator pridruživanja (prijenos)
    Ucionica& operator = (Ucionica&& p) // za privremeni "B = Ucionica(15, "Dell", "Intel I7", "8 GB");"
    {
        if (this != &p)
        {
            delete[] racunala;
            racunala = p.racunala;
            p.racunala = NULL;
            brRacunala = p.brRacunala;
            p.brRacunala = 0;
        }
        return *this;
    }
};

int main()
{
    // Učionica 'A' s 15 računala istih specifikacija
    Ucionica A(15, "Koncar", "Intel I5", "4 GB");
    // Učionica B ima također 15 računala istih specifikacija kao i učionica 'A'
    Ucionica B = A;
    cout << B.brRacunala << endl; // 15
    // Računala iz učionice 'B' se prenose u  učionicu 'C'
    Ucionica C = move(B);
    cout << B.brRacunala << endl; // 0
    // Privremena ucionica se zatvara i njena racunala se prenose u ucionicu 'B'
    B = Ucionica(15, "Dell", "Intel I7", "8 GB");
    return 0;
}
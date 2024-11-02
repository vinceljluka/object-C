#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Osoba { //APSTRAKTNA KLASA
//Nije moguæe kreirati objekt apstraktne klase, veæ tek pokazivaè na njega
protected:
    string ime;
    string prezime;
    double osnovnaPlaca;

public:
    Osoba(string ime, string prezime, double osnovnaPlaca)
        : ime(ime), prezime(prezime), osnovnaPlaca(osnovnaPlaca) {}

    virtual void ispis() = 0; 
    virtual double izracunPlace() = 0;
    virtual ~Osoba() {}
};

class Igrac : public Osoba {
private:
    int golovi;
    int asistencije;

public:
    Igrac(string ime, string prezime, double osnovnaPlaca)
        : Osoba(ime, prezime, osnovnaPlaca), golovi(0), asistencije(0) {}

    void dodajGolove(int broj) { golovi += broj; }
    void dodajAsistencije(int broj) { asistencije += broj; }

    double izracunPlace() override {
        double bonus = (golovi / 10 + asistencije / 5) * 0.1 * osnovnaPlaca;
        return osnovnaPlaca + bonus;
    }

    void ispis() override {
        cout << ime << " " << prezime << " - golova: " << golovi << ", asistencija: " << asistencije << endl;
    }
};

class Trener : public Osoba {
private:
    int pobjede;
    int remi;
    int izgubljene;

public:
    Trener(string ime, string prezime, double osnovnaPlaca)
        : Osoba(ime, prezime, osnovnaPlaca), pobjede(0), remi(0), izgubljene(0) {}

    void dodajPobjede(int broj) { pobjede += broj; }
    void dodajRemi(int broj) { remi += broj; }
    void dodajIzgubljene(int broj) { izgubljene += broj; }

    double izracunPlace() override {
        double bonus = (pobjede / 5 + remi / 10) * 0.1 * osnovnaPlaca;
        double kazna = (izgubljene / 8) * 0.1 * osnovnaPlaca;
        return osnovnaPlaca + bonus - kazna;
    }

    void ispis() override {
        cout << ime << " " << prezime << " - Omjer (W/D/L): " << pobjede << " / " << remi << " / " << izgubljene << endl;
    }
};

int main()
{
	Igrac i("Luka", "Modric", 100000); //Ime, prezime, osnovica plaÄ‡e
	i.dodajGolove(7);
	i.dodajAsistencije(12);
	i.ispis(); //Luka Modric - golova: 7, asistencija: 12
	cout << "Placa: " << i.izracunPlace() << endl; //Placa: 120000
	

	Igrac i2("C", "Ronaldo", 234505);
	i2.dodajGolove(57);
	i2.dodajAsistencije(32);
	i2.ispis(); //C Ronaldo - Golova : 57, Asistencije : 32.
	cout << "Placa: " << i2.izracunPlace() << endl; //Placa : 492461

	Trener t1("Hose", "Murinjo", 143009); //Ime, prezime, osnovica plaÄ‡e
	t1.dodajPobjede(88); //Dodati broj pobjeda (W)
	t1.dodajRemi(12); //Dodati broj nerijeÅ¡enih utakmica (D)
	t1.dodajIzgubljene(0); //Dodati broj izgubljenih (L)
	t1.ispis(); //Hose Murinjo - Omjer (W/D/L): 88 / 12 / 0
	cout << "Placa: " << t1.izracunPlace() << endl; //Placa: 400425

	t1.dodajPobjede(11);
	t1.dodajIzgubljene(47);
	t1.ispis(); //Hose Murinjo - Omjer (W/D/L): 99 / 12 / 47
	cout << "Placa: " << t1.izracunPlace() << endl; //Placa: 357523

    //POLIMORFIZAM U FUNKCIJI MAIN! 1.NasljeÄ‘ivanje, 2.Pretvorba na viÅ¡e, 3.Virtualne metode u baznoj klasi!
    Osoba* o1;
    Igrac i1("Luka", "Vincelj", 123123);
    o1 = &i1;

}




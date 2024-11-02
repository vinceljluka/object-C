#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class IznimkaCitatelj {
public:
	int broj;
	IznimkaCitatelj(int _broj) : broj(_broj) {}
	void opis() {
		cout << broj << " nije ispravna vrijednost!" << endl;
	}

};

class Citatelj {
private:
	string ime;
	int brProcitanih;
public:
	inline static int kol = 0;
	Citatelj(string _ime, int _brProcitanih) {
		setIme(_ime), setBrProcitanih(_brProcitanih);
	}
	void setIme(string novoIme) {
		ime = novoIme;
	}
	string getIme() {
		return ime;
	}
	void setBrProcitanih(int noviBr) {
		if (noviBr < 0) {
			throw IznimkaCitatelj(noviBr);
		}
		else {
			brProcitanih = noviBr;
		}
		if (brProcitanih == 0) {
			kol++;
		}
	}
	int getBrProcitanih() {
		return brProcitanih;
	}
	Citatelj() = default;

	static int prvaKnjiga() {
		return kol;
	}
};

class Knjiga {
public:
	vector<Citatelj*> citatelji;
	string naslov;
	int stranice;
	Knjiga(string _naslov, int _stranice) : naslov(_naslov), stranice(_stranice) {}
	virtual void getOpis() {
		cout << "bzvz." << endl;
	}
	Knjiga& dodajCitatelja(Citatelj* citatelj) {
		citatelji.push_back(citatelj);
		return *this;
	}
	auto sortirajCitatelje() {
		sort(citatelji.begin(), citatelji.end(), [](Citatelj* a, Citatelj* b) {
			return a->getBrProcitanih() > b->getBrProcitanih();
			});
	}
	void ispisiCitatelje() {
		for (int i = 0; i < citatelji.size(); i++) {
			cout << citatelji[i]->getIme() << " " << citatelji[i]->getBrProcitanih() << endl;
		}
	}
	template<class... T>
	void dodaj(T... args) {
		(citatelji.push_back(args), ...);
	}

	//kopirni konstruktor
	Knjiga(const Knjiga& k) {
		for (int i = 0; i < k.citatelji.size(); i++) {
			citatelji.push_back(new Citatelj);
			*citatelji[i] = *k.citatelji[i];
		}
		naslov = k.naslov;
		stranice = k.stranice;
	}

	//prijenosni konstruktor
	Knjiga(Knjiga&& k) {
		for (int i = 0; i < k.citatelji.size(); i++) {
			citatelji.push_back(k.citatelji[i]);
			k.citatelji[i] = NULL;
		}
		naslov = k.naslov;
		stranice = k.stranice;
	}
	
	//operator = (prijenos)
	Knjiga& operator = (Knjiga&& k) {
		//dealokacija
		for (int i = 0; i < k.citatelji.size(); i++) {
			delete k.citatelji[i];
		}
		citatelji.clear();
		//prijenosni konstruktor
		for (int i = 0; i < k.citatelji.size(); i++) {
			citatelji.push_back(k.citatelji[i]);
			k.citatelji[i] = NULL;
		}
		naslov = k.naslov;
		stranice = k.stranice;
	}
	~Knjiga() {
		for (int i = 0; i < citatelji.size(); i++) {
			delete citatelji[i];
		}
		citatelji.clear();
	}
};

namespace Citaonica {
	class Roman : public Knjiga {
	public:
		Roman(string naslov, int stranice) : Knjiga(naslov, stranice) {}
		Roman() = default;
		void getOpis() override;
	};
	class ZbirkaKratkihPrica : public Knjiga {
	public:
		ZbirkaKratkihPrica(string naslov, int stranice) : Knjiga(naslov, stranice) {}
		ZbirkaKratkihPrica() = default;
		void getOpis() override;
	};
}

void Citaonica::Roman::getOpis() {
	cout << "Roman." << endl;
}

void Citaonica::ZbirkaKratkihPrica::getOpis() {
	cout << "Zbirka kratkih prica." << endl;
}

int main() {
	Knjiga k1("naslov1", 123);
	Citatelj* c1 = new Citatelj("Marko", 322);
	Citatelj* c2 = new Citatelj("Ivan", 213);
	Citatelj* c3 = new Citatelj("Josip", 123);

	k1.dodajCitatelja(c1).dodajCitatelja(c2).dodajCitatelja(c3);

	Citatelj* c4 = new Citatelj("Fran", 112);
	Citatelj* c5 = new Citatelj("Marin", 341);
	Citatelj* c6 = new Citatelj("Darko", 215);

	k1.dodaj(c4, c5, c6);

	k1.sortirajCitatelje();

	k1.ispisiCitatelje();

	Citatelj* c7 = new Citatelj("Filip", 435);
	try {
		c7->setBrProcitanih(-435);
	}
	catch (IznimkaCitatelj e) {
		e.opis();
	}

	Citatelj* c8 = new Citatelj("Nikola", 0);
	Citatelj* c9 = new Citatelj("Leon", 0);

	cout << Citatelj::prvaKnjiga() << endl;

	Citaonica::Roman k2("naslov2roman", 234);
	Citaonica::ZbirkaKratkihPrica k3("naslov3zbirka", 159);

	k1.getOpis();
	k2.getOpis();
	k3.getOpis();


	return 0;
}
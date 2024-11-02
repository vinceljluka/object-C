#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Knjiga {
public:
	string autor;
	string naslov;
	string ISBN;
	Knjiga(string _autor, string _naslov, string _ISBN)
	{
		autor = _autor;
		naslov = _naslov;
		ISBN = _ISBN;
		cout << "Knjiga constructor called" << endl;
	}
	~Knjiga()
	{
		cout << "Knjiga destructor called" << endl;
	}
};

class Knjiznica {
private:
	string adresa;
	string naziv;
	string kategorija;
public:
	vector <Knjiga> vKnjige;

	string formatirajNaziv(string Fnaziv)
	{
		string res = Fnaziv;
		res[0] = toupper(res[0]);
		for (int i = 1; i < res.size(); i++)
		{
			res[i] = tolower(res[i]);
		}
		return res;
	}

	void setAdresa(string novaAdresa){
		adresa = novaAdresa;
	}
	string getAdresa() const{
		return adresa;
	}

	void setNaziv(string noviNaziv){
		naziv = formatirajNaziv(noviNaziv);
	}

	string getNaziv() const {
		return naziv;
	}

	void setKategorija(string novaKategorija) {
		if (novaKategorija == "djecja" || novaKategorija == "znanstvena" || novaKategorija == "citaonica" || novaKategorija == "opcenito")
		{
			kategorija = novaKategorija;
		}
	}

	string getKategorija() const {
		return kategorija;
	}

	void dodajKnjigu1(Knjiga z){
		vKnjige.push_back(z);
	}

	void dodajKnjigu2(Knjiga& z) {
		vKnjige.push_back(z);
	}

	void dodajKnjigu3(Knjiga* z) {
		vKnjige.push_back(*z);
	}

	void ispisSvihKnjiga()
	{
		for (int i = 0; i < vKnjige.size(); i++)
		{
			cout << vKnjige[i].autor << " " << vKnjige[i].naslov << " " << vKnjige[i].ISBN << endl;
		}
	}

	Knjiga nadjiKnjigu1(string isbn) 
	{
		for (int i = 0; i < vKnjige.size(); i++)
		{
			if (vKnjige[i].ISBN == isbn)
			{
				//cout << "SUCESS" << endl;
				return vKnjige[i];
			}
		}
	}

	Knjiga* nadjiKnjigu2(string isbn)
	{
		for (int i = 0; i < vKnjige.size(); i++)
		{
			if (vKnjige[i].ISBN == isbn)
			{
				//cout << "SUCESS" << endl;
				return &(vKnjige[i]);
			}
		}
	}

	Knjiga& nadjiKnjigu3(string isbn)
	{
		for (int i = 0; i < vKnjige.size(); i++)
		{
			if (vKnjige[i].ISBN == isbn)
			{
				//cout << "SUCESS" << endl;
				return vKnjige[i];
			}
		}
	}

};


int main()
{
	Knjiznica Krapina;
	Krapina.setAdresa("mimarska 4");
	Krapina.setNaziv("gradska knjiznica");
	Krapina.setKategorija("djecja");

	Knjiga k1("Ivana", "Regoc", "012341");
	Knjiga k2("Josipa", "Marmun", "0123111");
	Knjiga k3("Teresa", "Gorila", "11111");

	Krapina.dodajKnjigu1(k1);
	Krapina.dodajKnjigu2(k2);
	Krapina.dodajKnjigu3(&k3);

	//Krapina.ispisSvihKnjiga();

	cout << endl << "Izmjena knjige pronadene pomocu nadjiKnjigu1:" << endl;

	Knjiga knjiga1 = Krapina.nadjiKnjigu1("012341");
	knjiga1.autor = "Novi Autor";

	Krapina.ispisSvihKnjiga();

	cout << endl << "Izmjena knjige pronadene pomocu nadjiKnjigu2:" << endl;

	Knjiga* ptrKnjiga = Krapina.nadjiKnjigu2("0123111");
	if (ptrKnjiga) 
	{
		ptrKnjiga->naslov = "Novi Naslov";
	}

	Krapina.ispisSvihKnjiga();

	cout << endl << "Izmjena knjige pronadene pomocu nadjiKnjigu3:" << endl;

	Knjiga& refKnjiga = Krapina.nadjiKnjigu3("11111");
	refKnjiga.ISBN = "000000000";

	Krapina.ispisSvihKnjiga();

	return 0;
}


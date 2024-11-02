#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class Kljuc {
public:
    string Ime;
    string Prezime;
    Kljuc(string _ime, string _prezime) 
    {
        Ime = _ime;
        Prezime = _prezime;
    }
    Kljuc() {}
};

class Garaza {
public:
    int sirina;
    int duljina;
    int cijena;
    string lokacija;
    vector <Kljuc> kljucevi;
    Garaza(int _sirina, int _duljina, int _cijena, string _lokacija)
    {
        sirina = _sirina;
        duljina = _duljina;
        cijena = _cijena;
        lokacija = _lokacija;
    }
    Garaza() {}   
};

int main() {
	
    vector <Garaza> NIZgaraze;
    vector <Kljuc> NIZkljucevi;

    cout << "Unesite broj garaza (N): ";
    int N;
    cin >> N;
    cin.ignore(); 

    for (int i = 0; i < N; i++) {
        int sirina, duljina, cijena;
        string lokacija;
        cout << "Unesite velicinu, lokaciju i cijenu za " << i + 1 << ". garazu:" << endl;
        cin >> sirina >> duljina;
        cin.ignore();
        getline(cin, lokacija);
        cin >> cijena;
        NIZgaraze.push_back(Garaza(sirina, duljina, cijena, lokacija));
    }

    cout << "Unesite broj kljuceva (M): ";
    int M;
    cin >> M;
    cin.ignore(); 
    
    int temp;

    for (int j = 0; j < M; j++) 
    {
        string Ime, Prezime;
        cout << "Unesite redni broj garaze kojoj pripada " << j + 1 << ". kljuc: ";
        cin >> temp;
        cout << "Unesite ime vlasnika kljuca: ";
        cin >> Ime >> Prezime;
        NIZgaraze[temp - 1].kljucevi.push_back(Kljuc(Ime, Prezime));    
    }

    cout << endl;

    cout << "Ispis garaza i kljuceva: " << endl;

    for (int i = 0; i < N; i++)
    {
        cout << i + 1 << ". " << NIZgaraze[i].lokacija << " " << NIZgaraze[i].sirina << "x" << NIZgaraze[i].duljina << " " << " - kljucevi:";

        for (int j = 0; j < NIZgaraze[i].kljucevi.size(); j++)
        {
            cout << " " << NIZgaraze[i].kljucevi[j].Ime << " " << NIZgaraze[i].kljucevi[j].Prezime;
        }
        cout << endl;
    }

    return 0;
}

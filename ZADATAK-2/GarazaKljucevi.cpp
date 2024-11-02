#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class Kljuc {
public:
    string Ime;
    string Prezime;
    int rbGaraze;
};

class Garaza {
public:
    int sirina;
    int duljina;
    int cijena;
    string lokacija;
    vector<Kljuc> kljucevi;
};

int main() {
    vector<Garaza> NIZgaraze;
    vector<Kljuc> NIZkljucevi;

    cout << "Unesite broj garaza (N): ";
    int N;
    cin >> N;
    cin.ignore(); 

    for (int i = 0; i < N; i++) {
        Garaza garaze1;
        cout << "Unesite velicinu, lokaciju i cijenu za " << i + 1 << ". garazu: " << endl;
        cin >> garaze1.sirina >> garaze1.duljina;
        cin.ignore(); 
        getline(cin, garaze1.lokacija);
        cin >> garaze1.cijena;
        cin.ignore(); 
        NIZgaraze.push_back(garaze1);
    }

    cout << "Unesite broj kljuceva (M): ";
    int M;
    cin >> M;
    cin.ignore(); 

    for (int j = 0; j < M; j++) {
        Kljuc kljucevi1;
        cout << "Unesite redni broj garaze kojoj pripada " << j + 1 << ". kljuc: ";
        cin >> kljucevi1.rbGaraze;
        cin.ignore(); 
        cout << "Unesite ime vlasnika kljuca: ";
        cin >> kljucevi1.Ime >> kljucevi1.Prezime;
        NIZkljucevi.push_back(kljucevi1);
    }

    cout << endl;

    cout << "Ispis garaza i kljuceva: " << endl;

    for (int k = 0; k < NIZgaraze.size(); k++) 
	{
        cout << k + 1 << ". " << NIZgaraze[k].lokacija << " " << NIZgaraze[k].sirina << "x" << NIZgaraze[k].duljina << " - kljucevi: ";
        for (int j = 0; j < NIZkljucevi.size(); j++) 
		{
            if (NIZkljucevi[j].rbGaraze == k + 1) 
			{
                cout << NIZkljucevi[j].Ime << " " << NIZkljucevi[j].Prezime << " ";
            }
        }
        cout << endl;
    }

    return 0;
}

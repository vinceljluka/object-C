#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Racunalo {
protected:
    string operacijskiSustav;

public:
    Racunalo(string os) : operacijskiSustav(os) {}
    virtual ~Racunalo() {}

    string getOS() const { return operacijskiSustav; }
    virtual bool isTablet() const = 0;  
};


class Tablet : public Racunalo {
public:
    Tablet(string os) : Racunalo(os) {}

    bool isTablet() const override { return true; }  
};


class Laptop : public Racunalo {
public:
    Laptop(string os) : Racunalo(os) {}

    bool isTablet() const override { return false; }  
};

// Funkcija za analizu racunala u ucionici
void AnalizaUcionice(const vector<Racunalo*>& ucionica, int* brTableta, int* brLaptopa, int* brAndroida, int* brWindowsa, int* brLinuxa) {
    *brTableta = *brLaptopa = *brAndroida = *brWindowsa = *brLinuxa = 0;  // Inicijalizacija brojaca

    for (int i = 0; i < ucionica.size(); i++) {
        Racunalo* racunalo = ucionica[i];

        if (racunalo->isTablet())
            (*brTableta)++;
        else
            (*brLaptopa)++;

        string os = racunalo->getOS();
        if (os == "Android")
            (*brAndroida)++;
        else if (os == "Windows")
            (*brWindowsa)++;
        else if (os == "Linux")
            (*brLinuxa)++;
    }
}


int main()
{
    Tablet Acer("Android"), Prestigio("Windows");
    Laptop Dell("Linux"), IBM("Windows"), Toshiba("Windows");

    vector<Racunalo*> Ucionica1 = { &Acer, &Prestigio, &Dell, &IBM, &Toshiba };
    int brTableta, brLaptopa, brAndroida, brWindowsa, brLinuxa;
    AnalizaUcionice(Ucionica1, &brTableta, &brLaptopa, &brAndroida, &brWindowsa, &brLinuxa);

    cout << "U ucionici se nalazi " << Ucionica1.size() << " racunala" << endl;
    cout << "Broj tablet racunala: " << brTableta << endl;
    cout << "Broj laptop racunala: " << brLaptopa << endl;
    cout << "Android OS: " << brAndroida << endl;
    cout << "Windows OS: " << brWindowsa << endl;
    cout << "Linux OS: " << brLinuxa << endl;

    return 0;
}




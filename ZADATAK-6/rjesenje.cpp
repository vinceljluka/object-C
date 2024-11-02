#include <iostream>
#include <vector>
#include <string>

using namespace std;

class KompleksniVektorException {
public:
    void ispis() 
    {
       cout << "Neispravan indeks!" << endl;
    }
};

class Kompleksni {
public:
    double re;  
    double im;  
    inline static int c = 0;

    Kompleksni()
    {
        ++c;
    }

    Kompleksni(double r, double i) : re(r), im(i) 
    {
        ++c;
    }

    ~Kompleksni()
    {
        --c;
    }

    static int brojac()
    {
        return c;
    }

    Kompleksni& operator++() {
        ++re;
        ++im;
        return *this;
    }

    Kompleksni operator++(int) {
        Kompleksni temp = (*this);
        re++;
        im++;
        return temp;
    }

    bool operator == (const Kompleksni& B)
    {
        if (re == B.re && im == B.im)
        {
            return true;
        }
        return false;
    }

};


class KompleksniVektor {
private:
    vector <Kompleksni> VektorKompleksnih;
public:

    int getVelicina()
    {
        return VektorKompleksnih.size();
    }

    KompleksniVektor() {};

    KompleksniVektor(vector <Kompleksni> _VektorKompleksnih)
    {
        VektorKompleksnih = _VektorKompleksnih;
    }

    void dodajKompleksni(const Kompleksni& c) 
    {
        VektorKompleksnih.push_back(c);
    }

    Kompleksni GetElemnt(int index);

    KompleksniVektor operator ++()
    {
        Kompleksni A;
        for (int i = 0; i < VektorKompleksnih.size(); i++)
        {
            A = VektorKompleksnih[i];
            ++A;
            VektorKompleksnih[i] = A;
        }
    }

    KompleksniVektor operator ++(int)
    {
        Kompleksni A;
        for (int i = 0; i < VektorKompleksnih.size(); i++)
        {
            A = VektorKompleksnih[i];
            A++;
            VektorKompleksnih[i] = A;
        }
    }

};

ostream& operator << (ostream& izlaz, KompleksniVektor A)
{
    for (int i = 0; i < A.getVelicina(); i++)
    {
        Kompleksni B = A.GetElemnt(i);
        izlaz << B.re << " " << B.im << endl;
    }
    return izlaz;
}

istream& operator >> (istream& ulaz, KompleksniVektor B)
{
    double re, im;
    cout << "Unesite realni i imaginarni dio kompleksnog broja: ";
    ulaz >> re >> im;
    B.dodajKompleksni(Kompleksni(re, im));
    return ulaz;
}

KompleksniVektor operator == (KompleksniVektor a, KompleksniVektor b)
{
    KompleksniVektor rezultat;
    for (int i = 0; i < a.getVelicina(); i++)
    {
        for (int j = 0; j < b.getVelicina(); j++)
        {
            if (a.GetElemnt(i) == b.GetElemnt(j))
            {
                rezultat.dodajKompleksni(a.GetElemnt(i));
            }
        }
    }
    return rezultat;
}

Kompleksni KompleksniVektor::GetElemnt(int index)
{
    if (index < 0 || index >= VektorKompleksnih.size())
    {
        throw KompleksniVektorException();
    }
    return VektorKompleksnih[index];
}

int main()
{
    KompleksniVektor v;
    KompleksniVektor v1;

    v.dodajKompleksni(Kompleksni(1, 2));
    v.dodajKompleksni(Kompleksni(3, 4));
    v.dodajKompleksni(Kompleksni(5, -6));

    v1.dodajKompleksni(Kompleksni(1, 2));
    v1.dodajKompleksni(Kompleksni(2, 4));
    v1.dodajKompleksni(Kompleksni(2, -6));

    KompleksniVektor v2 = v1 == v;

    try {
        Kompleksni c = v.GetElemnt(1); // Valjan indeks
        c = v.GetElemnt(-1); // Nevaljan indeks, baca iznimku
    }
    catch (KompleksniVektorException e) 
    {
        e.ispis();
    }

    Kompleksni A = v2.GetElemnt(0);

    cout << A.re << " " << A.im;

    return 0;
}



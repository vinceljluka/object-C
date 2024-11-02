#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Slika {
public:
    double cijena;

    inline static double sumaCijena = 0;
    inline static int kol = 0;

    Slika(double _cijena) : cijena(_cijena) 
    {
        sumaCijena += _cijena;
        kol++;
    }

    static double ProsjecnaCijena() 
    {
        return sumaCijena / kol;
    }

};

/*
double Slika::sumaCijena = 0;
int Slika::kol = 0;
*/

int main()
{

    Slika Slika1(2000); // 2000 eura
    Slika Slika2(3000); // 3000 eura
    Slika Slika3(1800); // 1800 eura
    cout << Slika::ProsjecnaCijena() << " eura"; // 2266.67 eura

    return 0;
}

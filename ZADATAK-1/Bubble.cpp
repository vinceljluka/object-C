#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Bubble {
public:
    string boja;
    double radijus;
    
    Bubble() {};

    Bubble(string _boja, double _radijus)
    {
        boja = _boja;
        radijus = _radijus;
    }

    double volumen() const 
    {
        return (4.0 / 3.0) * 3.14 * pow(radijus, 3);
    }

    Bubble operator +(Bubble B)
    {
        double pomV = this->volumen() + B.volumen();
        double pomR = pow(pomV / (4.0 / 3.0 * 3.14), 1.0 / 3.0);

        if (this->radijus >= B.radijus) {
            return Bubble(this->boja, pomR);
        }
        else {
            return Bubble(B.boja, pomR);
        }
    }

    Bubble operator -(Bubble B)
    {
        double pomV = this->volumen() - B.volumen();
        double pomR = pow(pomV / (4.0 / 3.0 * 3.14), 1.0 / 3.0);
        return Bubble(this->boja, pomR);     
    }

    bool operator ==(const Bubble& B) const 
    {
        if (this->boja == B.boja) 
        {
            if (abs(this->radijus - B.radijus) <= 0.0001) 
            {
                return true;
            }
        }
        return false;
    }

};

ostream& operator << (ostream& os, const Bubble& B) {
    os << B.boja << ": " << floor(B.radijus * 100)/100 << endl;
    return os;
}

int main()
{
    Bubble a("blue", 10.4);
    Bubble b("red", 7.2);
    Bubble c("green", 18.8);

    Bubble x = a + b; //nastat će novi bubble obujma 6275.27
    cout << x; //blue: 11.44
    Bubble y = x + c;
    cout << y; //green: 20.12

    Bubble z = y - x;
    cout << z; //green: 18.8

    if (z == c)
        cout << "OK" << endl; //OK

    return 0;
}

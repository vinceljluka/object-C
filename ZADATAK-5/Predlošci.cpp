#include <iostream>
#include <vector>

using namespace std;

template<class T>
class Niz {
private:
    vector <T> v;

public:
    Niz(const vector<T>& _v) : v(_v) {}

    void print() const {
        for (const auto& elem : v) {
            cout << elem << " ";
        }
        cout << endl;
    }

    bool manje_od(const Niz& niz) const {
        for (const auto& elem1 : v) {
            for (const auto& elem2 : niz.v) {
                if (elem1 >= elem2) {
                    return false;
                }
            }
        }
        return true;
    }
};

template<typename T>

bool operator < (const Niz<T>& niz1, const Niz<T>& niz2) 
{
    return niz1.manje_od(niz2);
}

template<typename T>

bool operator >= (const Niz<T>& lhs, const Niz<T>& rhs) 
{
    return !(lhs < rhs);
}


template<typename T>
class Niz2 {
private:
    vector<T> elements;

public:
    Niz2(const vector<T>& arr) : elements(arr) {}

    void print() const {
        for (const auto& elem : elements) {
            cout << elem << " ";
        }
        cout << endl;
    }

    bool operator < (const Niz2& other) const {
        for (const auto& elem : elements) {
            for (const auto& other_elem : other.elements) {
                if (elem >= other_elem) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    // a) ------------------------------
    vector<int> v1 = { 1, 2, 3 };
    vector<int> v2 = { 11, 4, 13 };

    Niz<int> p1(v1);
    Niz<int> p2(v2);

    cout << "p1: ";
    p1.print();

    cout << "p2: ";
    p2.print();

    // b) ------------------------------
    cout << "p1.manje_od(p2): " << p1.manje_od(p2) << endl;         //1
    cout << "p2.manje_od(p1): " << p2.manje_od(p1) << endl << endl; //0

    // c) ------------------------------
    cout << "(p1 < p2): " << (p1 < p2) << endl;             // 1
    cout << "(p2 < p1): " << (p2 < p1) << endl << endl;     // 0

    // d) ------------------------------
    cout << "(p1 >= p2): " << (p1 >= p2) << endl;           //0
    cout << "(p2 >= p1): " << (p2 >= p1) << endl << endl;   //1

    return 0;
}

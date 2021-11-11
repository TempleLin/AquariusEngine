// @Code in the project is for syntax testing.

#include <iostream>
#include "TestSFINAE.h"
#include "AnyTest.h"

using namespace std;

class X {
    friend X operator+(const X& x1, const X& x2) {
        return X(x1.m_data + x2.m_data);
    }

public:
    X(int data) : m_data(data) {}
    int Dump() const { return m_data; }
private:
    int m_data;
};

int main() {
    //// Integer
    //int i = 4;
    //cout <<
    //    "Plus(i, 9) = " <<
    //    Plus(i, 9) << endl;

    //// Floating point
    //float dx = 4.0;
    //float dy = 9.5;
    //cout <<
    //    std::setprecision(3) <<
    //    "Plus(dx, dy) = " <<
    //    Plus(dx, dy) << endl;

    //// String
    //string hello = "Hello, ";
    //string world = "world!";
    //cout << Plus(hello, world) << endl;

    //// Custom type
    //X x1(20);
    //X x2(22);
    //X x3 = Plus(x1, x2);
    //cout <<
    //    "x3.Dump() = " <<
    //    x3.Dump() << endl;

    anys.push_back(E(14));
    anys.push_back(F(15));
    std::any_cast<E>(anys.at(0)).printE();
    std::any_cast<F>(anys.at(1)).printE();

}
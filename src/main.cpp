#include <iostream>
#include "Complex.h"
#include "Matrix.h"

using namespace std;


int main()
{

    /*
    M=
    1 2 3
    0 1 4
    5 6 0
    =>
    M^-1
    -24 18 5
    20 -15 -4
    -5 4 1

    */
    Matrix m("M1",3,3);

    Fraction nulimaginaire(0,1);

    Fraction f00(1,1);
    Complex c00(f00,nulimaginaire);
    m.set(0,0,c00);


    Fraction f01(2,1);
    Complex c01(f01,nulimaginaire);
    m.set(0,1,c01);
    Fraction f02(3,1);
    Complex c02(f02,nulimaginaire);
    m.set(0,2,c02);

    Fraction f10(0,1);
    Complex c10(f10,nulimaginaire);
    m.set(1,0,c10);

    Fraction f11(1,1);
    Complex c11(f11,nulimaginaire);
    m.set(1,1,c11);

    Fraction f12(4,1);
    Complex c12(f12,nulimaginaire);
    m.set(01,2,c12);

    Fraction f20(5,1);
    Complex c20(f20,nulimaginaire);
    m.set(2,0,c20);

    Fraction f21(6,1);
    Complex c21(f21,nulimaginaire);
    m.set(2,1,c21);

    Fraction f22(0,1);
    Complex c22(f22,nulimaginaire);
    m.set(2,2,c22);

    cout<<m<<endl;
    cout<<"DET="<<m.determinant()<<endl;

    cout<<m.inverse()<<endl;

     cout<<m+m.inverse()<<endl;
    return 0;
}

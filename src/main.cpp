#include <iostream>
#include "Complex.h"
#include "Matrix.h"
using namespace std;



int main()
{

        cout << "Hello world!" << endl;

        Complex c1(10, 5), c2(2, 4);

        Complex c3 = c1 + c2;

        cout<<c3<<"module:"<<c3.module()<<endl;
        Fraction c4(4,2);
        cout<<c4<<endl;
        Fraction f5(4,3);
        cout<<f5<<endl;

    /*
    Matrix m("M1",3,3);
    m.alea();
    cout<<"carree?"<<m.isSquare()<<"symetrique?"<<m.isSymetrique()<<endl;
    cout<<"trace:"<<m.trace()<<endl;
    cout<<m<<endl;


    cout<<"determinant:"<<m.determinant()<<endl;
    cout<<m.inverse()<<endl;
    */

    return 0;
}

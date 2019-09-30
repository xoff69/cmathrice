#ifndef MATRIX_H
#define MATRIX_H

#include <ostream>
#include <list>
#include <iterator>
#include <vector>
#include "Complex.h"
// Matrix declaration
class Matrix
{
private:
    std::string name;
    Complex ** matrice;
    int rowmax;
    int colmax;
    Complex finaldeterminant(Complex a, Complex b, Complex c, Complex d);
    Complex determinant(int lig, int coldebut, int colfin, std::vector <int> colexclues);

public:
    Matrix(std::string name,int nbrow,int nbcol);
    virtual ~Matrix();
    Matrix(Matrix const &obj) ;
    bool operator != (Matrix const &obj);
    // fill matrix with random number
    void alea();
    //  true if matrix size is n*n
    bool isSquare();
    bool isSymetrique();
    Complex trace();
    Matrix operator + (Matrix const &other);
    Matrix operator * (Matrix const &other);
    Matrix operator * (int const scalar);
    Matrix operator / (Complex const &other);
    void set(int l,int c, Complex const value)
    {
        matrice[l][c]=value;
    };
    Matrix transpose ();
    Matrix inverse();
    Complex determinant();

    friend std::ostream& operator<<(std::ostream&, const Matrix&);
protected:

};

#endif // MATRIX_H

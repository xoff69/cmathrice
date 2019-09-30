#include "Matrix.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cassert>
#include <ostream>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>
#include "Complex.h"

using namespace std;
// for cout matrix
std::ostream& operator<<(std::ostream &strm, const Matrix &a)
{

    strm<<endl<<a.name<<"("<<endl;
    for(int i = 0; i < a.rowmax; ++i)
    {
        for(int j = 0; j < a.colmax; ++j)
        {
            strm << a.matrice[i][j] <<" ";
        }
        strm << endl;
    }
    strm<<   ")";
    return strm;
}

// construct matrix
Matrix::Matrix(string nam,int nbrow,int nbcol)
{
    matrice = new Complex*[nbrow];
    for(int i = 0; i < nbrow; ++i)
        matrice[i] = new Complex[nbcol];
    rowmax = nbrow;
    colmax = nbcol;
    name=nam;
}
// copy construct
Matrix::Matrix(Matrix const &obj)
{
    matrice = new Complex*[obj.rowmax];
    for(int i = 0; i < obj.rowmax; ++i)
        matrice[i] = new Complex[obj.colmax];
    rowmax = obj.rowmax;
    colmax = obj.colmax;
    name=obj.name;
}
Matrix::~Matrix()
{
    // cout<<"delete matrice"<<endl;
    for(int i = 0; i < rowmax; ++i)
        delete [] matrice[i];
    delete [] matrice;
}
// isMatrix square?
bool   Matrix:: isSquare()
{
    return rowmax == colmax;
}
// tMatrix, transposition
Matrix Matrix::transpose()
{
    Matrix transposee("t"+name,colmax, rowmax);
    for (int i = 0; i < rowmax; i++)
    {
        for (int j = 0; j < colmax; j++)
        {
            transposee.matrice[j][i] = matrice[i][j];
        }
    }
    return transposee;
}
// trace of the matrix
Complex   Matrix::trace()
{
    assert (isSquare());
    Complex trace ;
    int i = 0;
    // on a rowmax=col
    while (i < rowmax)
    {
        trace =trace+ matrice[i][i];
        i++;
    }
    return trace;
}
// return true if matrix is symetric
bool   Matrix::isSymetrique()
{

    for (int i = 0; i < rowmax; i++)
    {
        for (int j = 0; j < colmax; j++)
        {
            if (matrice[i][j] != matrice[j][i]) return false;
        }
    }
    return true;
}
// fill matrix with random number
void   Matrix:: alea()
{
    for(int i = 0; i < rowmax; ++i)
    {
        for(int j = 0; j < colmax; ++j)
        {
            Fraction f1(rand() % 7,rand() % 7);
            Fraction f2(rand() % 7,rand() % 7);
            Complex cx(f1,f2);
            matrice[i][j]=cx;
        }
    }
}
// matrix (m,n) + matrix(m,n)
Matrix Matrix::operator + (Matrix const &other)
{
    assert(rowmax==other.rowmax&&colmax==other.colmax)
    Matrix res(name+"+"+other.name,rowmax,colmax);
    for(int i = 0; i < rowmax; ++i)
    {
        for(int j = 0; j < colmax; ++j)
        {
            res.matrice[i][j] =matrice[i][j]+other.matrice[i][j];
        }
    }

    return res;
}
// matrix / complex
Matrix Matrix::operator / (Complex const &other)
{
    Matrix res(name,rowmax,colmax);
    for(int i = 0; i < rowmax; ++i)
    {
        for(int j = 0; j < colmax; ++j)
        {
            res.matrice[i][j] =matrice[i][j] /other;
        }
    }

    return res;

}
// matrix * matrix
Matrix Matrix::operator * (Matrix const &other)
{
    assert(colmax==other.rowmax);
    Matrix produit (name,rowmax, other.colmax);
    for (int i = 0; i < produit.rowmax; i++)
    {
        for (int j = 0; j < produit.colmax; j++)
        {
            // matrice 1 1 c'est le produit de la premiere ligne par les elements de la premiere colonne
            Complex prod (0,1);
            for (int k = 0; k < colmax; k++)
            {
                prod =prod+ matrice[i][k] * other.matrice[k][j];
            }

            produit.matrice[i][j] = prod;
        }
    }
    return produit;
}
// Matrix * scalar
Matrix Matrix::operator * (int const scalar)
{
    Matrix res(name,rowmax,colmax);
    for(int i = 0; i < rowmax; ++i)
    {
        for(int j = 0; j < colmax; ++j)
        {
            res.matrice[i][j]=matrice[i][j]*scalar;
        }
    }
    return res;
}
// private intermediate method
Complex   Matrix::finaldeterminant(Complex a, Complex b, Complex c, Complex d)
{
    return a * d + (b * c)*(-1);
}
// private intermediate method
Complex   Matrix::determinant(int lig, int coldebut, int colfin, std::vector<int> colexclues)
{
    if (rowmax- lig == 2)
    {
        // on va trouver les deux colonnes restantes (non exclues)
        std::vector<int> inc;
        for (int i = 0; i < colmax; i++)
        {
            if (!std::count(colexclues.begin(), colexclues.end(), i))
            {
                inc.push_back(i);
            }
        }
        // inc size =2
        return finaldeterminant(matrice[lig][inc.at(0)], matrice[lig][inc.at(1)], matrice[lig + 1][inc.at(0)], matrice[lig + 1][inc.at(1)]);
    }
    int signe = 1;
    Complex ldeterminant (0,0);
    for (int i = coldebut; i < colfin; i++)
    {
        if (!std::count(colexclues.begin(), colexclues.end(), i))
        {
            std::vector<int> localList;
            localList.insert(localList.end(), colexclues.begin(), colexclues.end());

            localList.push_back(i);
            Complex loc = matrice[lig][i] * determinant(lig + 1, coldebut, colfin, localList);
            // cout <<"signe:"<<signe<<"/avant "<<ldeterminant<<"=>"<<loc<<"->"<<(loc*signe)<<endl;
            ldeterminant = ldeterminant + (loc * signe);
            // cout <<"apres "<<ldeterminant<<endl;
            signe = -signe;
        }
    }
    //  cout<<"det:"<<ldeterminant<<endl;
    return ldeterminant;
}

// public method to compute determinant
Complex   Matrix::determinant()
{
    std::vector<int> inc;
    return determinant(0, 0, colmax, inc);
}
// M^-1
Matrix   Matrix::inverse()
{

    Matrix inverse (""+name+"-1",rowmax, colmax);
    // a: calcul du determinant !=0
    Complex ldeterminant = determinant();

    assert (!ldeterminant.iszero());

    // b: cofacteur
    // b1: calcul de cofacteur
    for (int i = 0; i < rowmax; i++)
    {
        for (int j = 0; j < colmax; j++)
        {
            // sous matrice ne contenant pas i,j
            Matrix sub ("N",rowmax - 1, colmax - 1);
            int k = 0, l = 0;
            for (int u = 0; u < rowmax; u++)
            {
                for (int v = 0; v < colmax; v++)
                {
                    if (u != i && v != j)
                    {
                        sub.matrice[k][l++] = matrice[u][v];
                    }
                }
                if (u != i)
                {
                    k++;
                }
                l = 0;
            }

            inverse.matrice[i][j] = sub.determinant();
        }
    }
    //  cout<<"etape 1\n:" << inverse;
    Matrix inverse2 (inverse / ldeterminant);

    // cout<<"etape 2:" << inverse2;
    // b2: on met le signe du cofacteur
    int signe = 1;
    for (int i = 0; i < rowmax; i++)
    {
        for (int j = 0; j < colmax; j++)
        {
            // cout<<"cofacteur="<<inverse2.matrice[i][j]<<endl;
            inverse2.matrice[i][j] = inverse2.matrice[i][j] * signe;
            signe = -signe;
        }
    }
    // c: transposee
    //  cout<<"etape 3:"<< inverse2;
    return inverse2.transpose();
}

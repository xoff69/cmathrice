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

std::ostream& operator<<(std::ostream &strm, const Matrix &a)
{

    strm<<endl<<a.name<<"(";
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


Matrix::Matrix(string nam,int nbrow,int nbcol)
{
    matrice = new Complex*[nbrow];
    for(int i = 0; i < nbrow; ++i)
        matrice[i] = new Complex[nbcol];
    rowmax = nbrow;
    colmax = nbcol;
    name=nam;
}

Matrix::~Matrix()
{
    // cout<<"delete matrice"<<endl;
    for(int i = 0; i < rowmax; ++i)
        delete [] matrice[i];
    delete [] matrice;
}
bool   Matrix:: isSquare()
{
    return rowmax == colmax;
}
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

bool   Matrix::isSymetrique()
{
    Matrix transposee=transpose();
    for (int i = 0; i < rowmax; i++)
    {
        for (int j = 0; j < colmax; j++)
        {
            if (matrice[i][j] != transposee.matrice[i][j]) return false;
        }
    }
    return true;
}
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

Matrix Matrix::operator + (Matrix const &other)
{
    Matrix res(name,rowmax,colmax);
    cout<<"todo+"<<endl;
    return res;
}
Matrix Matrix::operator / (Complex const &other){
    Matrix res(name,rowmax,colmax);
cout<<"todo //"<<endl;
    return res;

}
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

Complex   Matrix::finaldeterminant(Complex a, Complex b, Complex c, Complex d)
{
    return a * d + (b * c)*(-1);
}

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
            ldeterminant = ldeterminant + (loc * signe);

            signe = -signe;
        }
    }
    return ldeterminant;
}


Complex   Matrix::determinant()
{
    std::vector<int> inc;
    return determinant(0, 0, colmax, inc);
}

Matrix   Matrix::inverse()
{

    Matrix inverse (""+name+"-1",rowmax, colmax);
    // a: calcul du determinant !=0
    Complex ldeterminant = determinant();
    assert (!ldeterminant.iszero());
    assert (isSymetrique() != 0);
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
                        //   System.out.println("("+i+","+j+")"+"("+u+","+v+")->k="+k+"-"+l);
                        sub.matrice[k][l++] = matrice[u][v];
                    }
                }
                if (u != i)
                {
                    k++;
                }
                l = 0;
            }

            //    System.out.println("sub:\n" + sub);
            // System.out.println("det:"+i+"-"+j+":"+sub.determinant());
            inverse.matrice[i][j] = sub.determinant();
        }
    }
    //    System.out.println("etape 1\n:" + inverse);
    inverse=inverse / ldeterminant;
    //    System.out.println("etape 2:" + inverse);
    // b2: on met le signe du cofacteur
    int signe = 1;
    for (int i = 0; i < rowmax; i++)
    {
        for (int j = 0; j < colmax; j++)
        {

            inverse.matrice[i][j] = inverse.matrice[i][j] * signe;
            signe = -signe;
        }
    }
    // c: transposee
    //    System.out.println("etape 3:" + inverse);
    return inverse.transpose();
}

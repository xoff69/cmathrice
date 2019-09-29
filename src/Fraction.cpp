#include "Fraction.h"


#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <cassert>
#include <ostream>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>
#include "Fraction.h"

using namespace std;

std::ostream& operator<<(std::ostream &strm, const Fraction &fraction)
{
    Fraction w=fraction.simplify();
    strm<<w.getNumerateur();
    if (w.getDenominateur()!=1)
    {
        strm<<"/"<<w.getDenominateur();
    }
    //strm<<endl;
    return strm;
}
Fraction::Fraction(int n, int d )
{
    assert(d!=0);
    numerateur = n;
    denominateur = d;
}
Fraction Fraction::operator + (Fraction const &obj)
{
    Fraction res;
    res.numerateur = numerateur*obj.denominateur + obj.numerateur*denominateur;
    res.denominateur = denominateur*obj.denominateur;
    return res;
}
Fraction Fraction::operator * (Fraction const &obj)
{
    Fraction res;
    res.numerateur = numerateur*obj.numerateur;
    res.denominateur = denominateur*obj.denominateur;
    return res;
}
Fraction Fraction::simplify() const
{
    Fraction res;
    res.numerateur=numerateur;
    res.denominateur=denominateur;
    if (numerateur%denominateur==0)
    {
        res.numerateur=numerateur/denominateur;
        res.denominateur=1;
    }
    return res;
}

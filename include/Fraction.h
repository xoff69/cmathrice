#ifndef FRACTION_H
#define FRACTION_H
#include <ostream>
#include <list>
#include <iterator>
#include <vector>


class Fraction
{
private:
    int numerateur;
    int denominateur;

public:


    Fraction(int n = 0, int d =1);
    Fraction operator + (Fraction const &obj);
    Fraction operator * (Fraction const &obj);
    bool operator != (Fraction const &obj);
    friend std::ostream& operator<<(std::ostream&, const Fraction&);

    int getNumerateur() const {return numerateur;};
    int getDenominateur() const {return denominateur;};
    bool iszero() const {return numerateur==0;};
    float getfloat() const {return (float) numerateur/denominateur;};
    Fraction simplify () const;
protected:


};

#endif // FRACTION_H

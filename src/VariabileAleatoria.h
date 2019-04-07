#ifndef VARIABILEALEATORIA
#define VARIABILEALEATORIA
#include <QVector>
#include <cmath>
#include <iostream>

class VariabileAleatoria{
private:
    static unsigned long long NCaux(unsigned n, unsigned k, double ret){
        if(n==k || k==0) return ret;
        return NCaux(n-1, k-1, ret*(n/static_cast<double>(k)));
    }

public:
    static unsigned long long NC(unsigned n, unsigned k){
        return NCaux(n, k, 1);
    }
    virtual VariabileAleatoria* clone() const = 0;
    virtual VariabileAleatoria* somma(const VariabileAleatoria&) const =0;
    virtual VariabileAleatoria* differenza(const VariabileAleatoria&) const=0;
    virtual VariabileAleatoria* prodotto(const VariabileAleatoria&) const=0;
    virtual VariabileAleatoria* quoziente(const VariabileAleatoria&) const=0;

    virtual double densita(int k) const =0;
    virtual double media() const =0;
    virtual QVector<int>* moda() const =0;
    virtual double varianza() const =0;
    virtual QString toQString(QString n) const =0;
};

#endif

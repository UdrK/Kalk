#include "Poisson.h"
#include "CustomException.h"
#include <typeinfo>

// Constructors ------------------------------

Poisson::Poisson(double l){
    if (l<=0) throw CustomException("Parametro invalido");

    this->l=l;
}

Poisson::Poisson(): Poisson(1) {}

Poisson::Poisson(QString s){
    bool k;
    double il = s.toDouble(&k);
    if(!k) throw CustomException("Probabilita non valida");

    if (il<=0) throw CustomException("Parametro invalido");

    this->l=il;
}

Poisson* Poisson::clone()const{
    return new Poisson(*this);
}


// Methods ----------------------------------

Poisson* Poisson::somma(const VariabileAleatoria& p) const{

    const Poisson* px;
    try{
        const Poisson& x = dynamic_cast<const Poisson&>(p);
        px=&x;
    }
    catch(std::bad_cast e){ throw CustomException("Operando del tipo sbagliato");}

    return new Poisson(l+px->l);
}

Skellam* Poisson::differenza(const VariabileAleatoria& p) const{

    const Poisson* px;
    try{
        const Poisson& x = dynamic_cast<const Poisson&>(p);
        px=&x;
    }
    catch(std::bad_cast e){ throw CustomException("Operando del tipo sbagliato");}

    return new Skellam(l, px->l);
}

Poisson* Poisson::prodotto(const VariabileAleatoria& p) const{

    const Poisson* px;
    try{
        const Poisson& x = dynamic_cast<const Poisson&>(p);
        px=&x;
    }
    catch(std::bad_cast e){ throw CustomException("Operando del tipo sbagliato");}

    return new Poisson(l*px->l);
}

Poisson* Poisson::quoziente(const VariabileAleatoria& p) const{

    const Poisson* px;
    try{
        const Poisson& x = dynamic_cast<const Poisson&>(p);
        px=&x;
    }
    catch(std::bad_cast e){ throw CustomException("Operando del tipo sbagliato");}

    return new Poisson(l/px->l);
}

double Poisson::densita(int k) const{
    int kfact=1;
    for(int i=k; i>1; i--)
        kfact *= i;
    return pow(l, k)/kfact*exp(-l);
}

double Poisson::media() const{
    return l;
}

QVector<int>* Poisson::moda() const{
    return new QVector<int>(1, floor(l));
}

double Poisson::varianza() const{
    return l;
}

double Poisson::informazione() const{
    return 1/l;
}

QString Poisson::toQString(QString nome) const{
    return QString(nome+"~P("+QString::number(l)+")");
}

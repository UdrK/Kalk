#include <Ipergeometrica.h>
#include "CustomException.h"
#include <typeinfo>

// Constructors ------------------------------

Ipergeometrica::Ipergeometrica(int n, int h, int r) {

    if(n<=0 || h<0 || r<=0 || n<h || n<r)
        throw CustomException("Uno o piu parametri di inizializzazione invalidi");

    this->n=n;
    this->h=h;
    this->r=r;

}

Ipergeometrica::Ipergeometrica(): Ipergeometrica(2, 1, 1) {}

Ipergeometrica::Ipergeometrica(QString s){

    bool k = true;
    int v = s.indexOf(",");
    int v2 = s.indexOf(",", v+1);
    QString ns = s.mid(0, v);
    QString hs = s.mid(v+1, v2-v-1);
    QString rs = s.mid(v2+1, s.length()-v-1);
    if(ns.isEmpty()||hs.isEmpty()||rs.isEmpty()) throw CustomException("Parametri mancanti");
    int in = ns.toInt(&k);
    if(!k) throw CustomException("Numero (n) non valido");
    k=true;
    int ih = hs.toDouble(&k);
    if(!k) throw CustomException("Numero (h) non valido");
    k=true;
    int ir = rs.toDouble(&k);
    if(!k) throw CustomException("Probabilita non valida");

    if(in<=0 || ih<0 || ir<=0 || in<ih || in<ir)
        throw CustomException("Uno o piu parametri di inizializzazione invalidi");

    this->n=in;
    this->h=ih;
    this->r=ir;

}


Ipergeometrica* Ipergeometrica::clone()const{
    return new Ipergeometrica(*this);
}

// Methods ----------------------------------

Ipergeometrica* Ipergeometrica::somma(const VariabileAleatoria& i) const {

    const Ipergeometrica* px;
    try{
        const Ipergeometrica& x = dynamic_cast<const Ipergeometrica&>(i);
        px=&x;
    }
    catch(std::bad_cast e){ throw CustomException("Operando del tipo sbagliato");}

    if(r!=px->r)
        throw CustomException("Operandi non compatibili");

    return new Ipergeometrica(n+px->n, h+px->h, r);

}

Ipergeometrica* Ipergeometrica::differenza(const VariabileAleatoria& i) const {

    const Ipergeometrica* px;
    try{
        const Ipergeometrica& x = dynamic_cast<const Ipergeometrica&>(i);
        px=&x;
    }
    catch(std::bad_cast e){ throw CustomException("Operando del tipo sbagliato");}

    if(r!=px->r || n<px->n || h<px->h)
        throw CustomException("Operandi non compatibili");

    return new Ipergeometrica(n-px->n, h-px->h, r);

}

Ipergeometrica* Ipergeometrica::prodotto(const VariabileAleatoria& i) const {

    const Ipergeometrica* px;
    try{
        const Ipergeometrica& x = dynamic_cast<const Ipergeometrica&>(i);
        px=&x;
    }
    catch(std::bad_cast e){ throw CustomException("Operando del tipo sbagliato");}

    if(r!=px->r)
        throw CustomException("Operandi non compatibili");

    return new Ipergeometrica(n*px->n, h*px->h, r);

}

Ipergeometrica* Ipergeometrica::quoziente(const VariabileAleatoria&) const { throw CustomException("Quest'operazione non e possibile con questo tipo"); }

double Ipergeometrica::densita(int k) const {

    if(k<0 || k>n)
        throw CustomException("Parametro invalido");

    return ( VariabileAleatoria::NC(h, k) * VariabileAleatoria::NC(n-h, r-k) ) / VariabileAleatoria::NC(n, r);

}

double Ipergeometrica::media() const {

    return r*h/static_cast<double>(n);

}

QVector<int>* Ipergeometrica::moda() const {

    return new QVector<int>(1, floor(((r+1)*(n+1))/static_cast<double>(n+2)));

}

double Ipergeometrica::varianza() const {
    if(n==1) return 0;
    return (r*(n-r)*h*(n*h))/static_cast<double>(n*n*(n-1));

}


QString Ipergeometrica::toQString(QString nome) const{
    return QString(nome+"~H("+QString::number(n)+", "+QString::number(h)+", "+QString::number(r)+")");
}

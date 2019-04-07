#include "Geometrica.h"
#include "CustomException.h"
#include <typeinfo>

// Constructors ------------------------------

Geometrica::Geometrica(double p){
    if(p<0 || p>1)
        throw CustomException("Probabilita non valida");
    this->p=p;
}

Geometrica::Geometrica() : Geometrica(0.5) {}

Geometrica::Geometrica(QString s){
    bool k = true;
    double ip = s.toDouble(&k);
    if(!k) throw CustomException("Probabilita non valida");

    if(ip<0 || ip>1)
        throw CustomException("Probabilita non valida");
    this->p=ip;

}

Geometrica* Geometrica::clone()const{
    return new Geometrica(*this);
}

// Methods -----------------------------------

double Geometrica::getP()const{return p;}

Pascal* Geometrica::somma(const VariabileAleatoria& g) const{
    bool geo=true, pas=true;

    const Geometrica* px;
    try{
        const Geometrica& x = dynamic_cast<const Geometrica&>(g);
        px=&x;
    }
    catch(std::bad_cast e){ geo=false; }

    const Pascal* py;
    try{
        const Pascal& y = dynamic_cast<const Pascal&>(g);
        py=&y;
    }
    catch(std::bad_cast e){ pas=false; }

    if(!geo && !pas) throw CustomException("Operando del tipo sbagliato");
    else if(pas){
        if(p!=py->getP())
            throw CustomException("Operandi non compatibili");
        return new Pascal(p, py->getN()+1);
    }
    else if(geo){
        if(p!=px->getP())
            throw CustomException("Operandi non compatibili");
        return new Pascal(p, 2);
    }
    else throw CustomException("Pas e geo non sono false, ma nessuna delle 2 e' vera. Se vedi quest'eccezione prova a spegnere e riaccendere la logica");
}

Geometrica* Geometrica::differenza(const VariabileAleatoria&) const { throw CustomException("Quest'operazione non e possibile con questo tipo"); }
Geometrica* Geometrica::prodotto(const VariabileAleatoria&) const { throw CustomException("Quest'operazione non e possibile con questo tipo"); }
Geometrica* Geometrica::quoziente(const VariabileAleatoria&) const { throw CustomException("Quest'operazione non e possibile con questo tipo"); }

double Geometrica::densita(int k) const{
    if(k<1)
        throw CustomException("Parametro non valido");
    return p*pow((1-p), (k-1));
}

double Geometrica::media() const{
    if(p==0) return 0;

    return 1/p;
}

QVector<int>* Geometrica::moda() const{
    return new QVector<int>(1, 1);
}

double Geometrica::varianza() const{
    if(p==0) return 0;
    return (1-p)/(p*p);
}

double Geometrica::entropia() const{
    if(p==0 || p==1) return 0;
    return (-(1-p)*log2(1-p)-p*log2(p))/p;
}

QString Geometrica::toQString(QString nome) const{
    return QString(nome+"~G("+QString::number(p)+")");
}

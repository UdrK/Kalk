#include "Bernoulli.h"
#include "CustomException.h"
#include <typeinfo>

// Constructors ------------------------------

Bernoulli::Bernoulli(double p){
    if(p<0 || p>1)
        throw CustomException("Probabilita non valida");
    this->p=p;

}

Bernoulli::Bernoulli(): Bernoulli(0.5) {}

Bernoulli::Bernoulli(QString s){

    bool k = true;
    double ip = s.toDouble(&k);
    if(!k) throw CustomException("Probabilita non valida");

    if(ip<0 || ip>1)
        throw CustomException("Probabilita non valida");
    this->p=ip;

}

Bernoulli* Bernoulli::clone()const{
    return new Bernoulli(*this);
}

// Methods -----------------------------------

double Bernoulli::getP()const{return p;}

Binomiale* Bernoulli::somma(const VariabileAleatoria& b) const {

    bool bin = true, bern = true;
    const Bernoulli* px;
    try{
        const Bernoulli& x = dynamic_cast<const Bernoulli&>(b);
        px=&x;
    }
    catch(std::bad_cast e){ bern=false; }

    const Binomiale* py;
    try{
        const Binomiale& y = dynamic_cast<const Binomiale&>(b);
        py=&y;
    }
    catch(std::bad_cast e){ bin=false; }
    if(!bin && !bern) throw CustomException("Operando del tipo sbagliato");
    else if(bin){
        if(p!=py->getP())
            throw CustomException("Operandi non compatibili");
        return new Binomiale(py->getN()+1, p);
    }
    else if(bern){
        if(p!=px->getP())
            throw CustomException("Operandi non compatibili");
        return new Binomiale(2, p);
    }
    else throw CustomException("Se vedi quest'eccezione, le leggi causali sono probabilmente collassate");
}

//undefined operations ---------------------------

Bernoulli* Bernoulli::differenza(const VariabileAleatoria&) const { throw CustomException("Quest'operazione non e possibile con questo tipo"); }
Bernoulli* Bernoulli::prodotto(const VariabileAleatoria&) const { throw CustomException("Quest'operazione non e possibile con questo tipo"); }
Bernoulli* Bernoulli::quoziente(const VariabileAleatoria&) const { throw CustomException("Quest'operazione non e possibile con questo tipo"); }

//undefined operations ---------------------------

double Bernoulli::densita(int k) const {
    if(k==0) return 1-p;
    else if(k==1) return p;
    else throw CustomException("Parametro invalido (dev'essere 0 o 1')");
}

double Bernoulli::media() const {
    return p;
}

QVector<int>* Bernoulli::moda() const {
    if(p<0.5) return new QVector<int>(1, 0);
    else if(p>0.5) return new QVector<int>(1, 1);

    QVector<int>* v = new QVector<int>(1, 0);
    v->append(1);
    return v;
}

double Bernoulli::varianza() const {
    return p*(1-p);
}

double Bernoulli::entropia() const {
    if(p==0 || p==1) return 0;

    return -(1-p)*log(1-p)-p*log(p);
}

double Bernoulli::informazione() const {
    if(p==0 || p==1) return 0;

    return 1/(p*(1-p));
}

QString Bernoulli::toQString(QString nome) const{
    return QString(nome+"~B("+QString::number(p)+")");
}





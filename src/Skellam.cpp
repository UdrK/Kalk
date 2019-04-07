#include "Skellam.h"
#include "CustomException.h"
#include <typeinfo>

// Constructors ------------------------------

Skellam::Skellam(double l1, double l2){
    if(l1<=0 || l2<=0)
        throw CustomException("Uno o piu parametri invalidi");
    this->l1=l1;
    this->l2=l2;
}

Skellam::Skellam(double l1): Skellam(l1, l1){}

Skellam::Skellam(): Skellam(1, 1) {}

Skellam::Skellam(QString s){
    bool k = true;
    int v = s.indexOf(",");
    QString l1s = s.mid(0, v);
    QString l2s = s.mid(v+1, s.length()-v-1);
    double il1 = l1s.toDouble(&k);
    if(!k) throw CustomException("Numero non valido");
    k=true;
    double il2 = l2s.toDouble(&k);
    if(!k) throw CustomException("Probabilita non valida");

    if(il1<=0 || il2<=0)
        throw CustomException("Uno o piu parametri invalidi");
    this->l1=il1;
    this->l2=il2;

}

Skellam* Skellam::clone()const{
    return new Skellam(*this);
}

// Methods ----------------------------------

Skellam* Skellam::somma(const VariabileAleatoria& s) const{

    const Skellam* px;
    try{
        const Skellam& x = dynamic_cast<const Skellam&>(s);
        px=&x;
    }
    catch(std::bad_cast e){ throw CustomException("Operando del tipo sbagliato");}

    return new Skellam(l1+px->l1, l2+px->l2);
}

Skellam* Skellam::differenza(const VariabileAleatoria& s) const{

    const Skellam* px;
    try{
        const Skellam& x = dynamic_cast<const Skellam&>(s);
        px=&x;
    }
    catch(std::bad_cast e){ throw CustomException("Operando del tipo sbagliato");}

    return new Skellam(l1-px->l1, l2-px->l2);

}

Skellam* Skellam::prodotto(const VariabileAleatoria& s) const{

    const Skellam* px;
    try{
        const Skellam& x = dynamic_cast<const Skellam&>(s);
        px=&x;
    }
    catch(std::bad_cast e){ throw CustomException("Operando del tipo sbagliato");}

    return new Skellam(l1*px->l1, l2*px->l2);

}

Skellam* Skellam::quoziente(const VariabileAleatoria& s) const{

    const Skellam* px;
    try{
        const Skellam& x = dynamic_cast<const Skellam&>(s);
        px=&x;
    }
    catch(std::bad_cast e){ throw CustomException("Operando del tipo sbagliato");}

    return new Skellam(l1/px->l1, l2/px->l2);

}

double Skellam::densita(int k) const{
    return exp(-(l1+l2))*pow((l1/l2), k/2.0);
}

QString Skellam::densitas(int k) const{
    QString res = QString::number(densita(k), 'f', 3);
    res.append(QString("I")+QString::number(k)+QString("(")+QString::number(2*sqrt(l1*l2))+QString(")"));
    return res;
}

double Skellam::media() const{
    return l1-l2;
}

QVector<int>* Skellam::moda() const{
    throw CustomException("Operazione non disponibile");
}

double Skellam::varianza() const{
    return l1+l2;
}

QString Skellam::toQString(QString nome) const{
    return QString(nome+"~S("+QString::number(l1)+", "+QString::number(l2)+")");
}

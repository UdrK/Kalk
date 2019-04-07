#include "Pascal.h"
#include "CustomException.h"
#include "Geometrica.h"
#include <typeinfo>

// Constructors ------------------------------

Pascal::Pascal(double p, int n){
    if(n<=0)
        throw CustomException("Numero (n) non valido questo altro");
    if(p<0 || p>1)
        throw CustomException("Probabilita non valida");

    this->p = p;
    this->n = n;
}

Pascal::Pascal(): Pascal(0.5, 1){}

Pascal::Pascal(QString s){
    bool k = true;
    int v = s.indexOf(",");
    QString ps = s.mid(0, v);
    QString ns = s.mid(v+1, s.length()-v-1);
    int in = ns.toInt(&k);
    if(!k) throw CustomException("Numero non valido");
    k=true;
    double ip = ps.toDouble(&k);
    if(!k) throw CustomException("Probabilita non valida");

    if(in<=0)
        throw CustomException("Numero (n) non valido questo");
    if(ip<0 || ip>1)
        throw CustomException("Probabilita non valida");

    this->p = ip;
    this->n = in;


}

Pascal* Pascal::clone()const{
    return new Pascal(*this);
}

// Methods ----------------------------------

double Pascal::getP() const{ return p; }
int Pascal::getN() const{ return n; }

Pascal* Pascal::somma(const VariabileAleatoria& nb) const { //geometrica

    bool pas=true, geo=true;
    const Pascal* px;
    const Geometrica* py;

    try{
        const Pascal& x = dynamic_cast<const Pascal&>(nb);
        px=&x;
    }
    catch(std::bad_cast e){ pas=false; }

    try{
        const Geometrica& y = dynamic_cast<const Geometrica&>(nb);
        py=&y;
    }
    catch(std::bad_cast e){ geo=false; }

    if(!pas&& !geo) throw CustomException("Operando del tipo sbagliato");
    else if(pas){
        if(p!=px->p)
            throw CustomException("Operandi non compatibili");

        return new Pascal(p, n+px->n);
    }
    else if(geo){
        if(p!=py->getP())
            throw CustomException("Operandi non compatibili");

        return new Pascal(p, n+1);
    }
    else throw CustomException("Pas e geo non sono false, ma nessuna delle 2 e' vera. Se vedi quest'eccezione prova a spegnere e riaccendere la logica");
}


Pascal* Pascal::differenza(const VariabileAleatoria& nb) const {

    const Pascal* px;
    try{
        const Pascal& x = dynamic_cast<const Pascal&>(nb);
        px=&x;
    }
    catch(std::bad_cast e){ throw CustomException("Operando del tipo sbagliato");}

    if(p!=px->p || n<=px->n)
        throw CustomException("Operandi non compatibili");

    return new Pascal(p, n-px->n);

}

Pascal* Pascal::prodotto(const VariabileAleatoria& nb) const {

    const Pascal* px;
    try{
        const Pascal& x = dynamic_cast<const Pascal&>(nb);
        px=&x;
    }
    catch(std::bad_cast e){ throw CustomException("Operando del tipo sbagliato");}

    if(p!=px->p)
        throw CustomException("Operandi non compatibili");

    return new Pascal(p, n*px->n);
}

Pascal* Pascal::quoziente(const VariabileAleatoria&) const { throw CustomException("Quest'operazione non e possibile con questo tipo"); }

double Pascal::densita(int k) const {
    if(k<0)
        throw CustomException("Parametro invalido");
    return VariabileAleatoria::NC(k+n-1, k);
}

double Pascal::media() const {
    if(p==0) return 0;
    return n/p;
}

QVector<int>* Pascal::moda() const {
    return new QVector<int>(1, floor((p*(n-1))/(1-p)));
}

double Pascal::varianza() const {
    if(p==0) return 0;
    return n*(1-p)/(p*p);
}

double Pascal::informazione() const {
    if(p==0) return 0;
    return n/((1-p)*(1-p)*p);
}

QString Pascal::toQString(QString nome) const{
    return QString(nome+"~NB("+QString::number(p)+", "+QString::number(n)+")");
}

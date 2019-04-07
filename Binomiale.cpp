#include <Binomiale.h>
#include "Bernoulli.h"
#include "CustomException.h"
#include <typeinfo>

// Constructors ------------------------------

Binomiale::Binomiale(int n, double p) {

    if(n<0)
        throw CustomException("Numero (n) non valido");
    if(p<0 || p>1)
        throw CustomException("Probabilita non valida");

    this->n = n;
    this->p = p;

}

Binomiale::Binomiale(): Binomiale(1, 0.5) {}

Binomiale::Binomiale(QString s){
    bool k = true;

    int v = s.indexOf(",");
    QString ns = s.mid(0, v);
    QString ps = s.mid(v+1, s.length()-v-1);

    int in = ns.toInt(&k);
    if(!k) throw CustomException("Numero non valido");
    k=true;
    double ip = ps.toDouble(&k);
    if(!k) throw CustomException("Probabilita non valida");

    if(in<0)
        throw CustomException("Numero (n) non valido");
    if(ip<0 || ip>1)
        throw CustomException("Probabilita non valida");

    this->n = in;
    this->p = ip;
}

Binomiale* Binomiale::clone()const{
    return new Binomiale(*this);
}

// Methods ----------------------------------

double Binomiale::getP() const{ return p; }
int Binomiale::getN() const{ return n; }

Binomiale* Binomiale::somma(const VariabileAleatoria& b) const {

    bool bin=true, bern=true;
    const Binomiale* px;
    const Bernoulli* py;
    try{
        const Binomiale& x = dynamic_cast<const Binomiale&>(b);
        px=&x;
    }
    catch(std::bad_cast e){ bin=false; }

    try{
        const Bernoulli& y = dynamic_cast<const Bernoulli&>(b);
        py=&y;
    }
    catch(std::bad_cast e){ bern=false; }

    if(!bin && !bern) throw CustomException("Operando del tipo sbagliato");
    else if(bin){
        if(p!=px->p){
            qDebug(QString::number(p).toLatin1()+" "+QString::number(px->p).toLatin1());
            throw CustomException("Operandi non compatibili");

        }

        return new Binomiale(n+px->n, p);
    }
    else if(bern){
        if(p!=py->getP())
            throw CustomException("Operandi non compatibili");

        return new Binomiale(n+1, p);
    }
    else throw CustomException("Se vedi quest'eccezione, lo spazio tempo e' probabilmente collassato");

}

Binomiale* Binomiale::differenza(const VariabileAleatoria& b) const {

    const Binomiale* px;
    try{
        const Binomiale& x = dynamic_cast<const Binomiale&>(b);
        px=&x;
    }
    catch(std::bad_cast e){ throw CustomException("Operando del tipo sbagliato");}

    if(p!=px->p || n < px->n)
        throw CustomException("Operandi non compatibili");

    Binomiale* res = new Binomiale(n-px->n, p);
    return res;

}

Binomiale* Binomiale::prodotto(const VariabileAleatoria& b) const {

    const Binomiale* px;
    try{
        const Binomiale& x = dynamic_cast<const Binomiale&>(b);
        px=&x;
    }
    catch(std::bad_cast e){ throw CustomException("Operando del tipo sbagliato");}

    if(p!=px->p)
        throw CustomException("Operandi non compatibili");

    Binomiale* res = new Binomiale(n*px->n, p);
    return res;

}

Binomiale* Binomiale::quoziente(const VariabileAleatoria&) const { throw CustomException("Quest'operazione non e possibile con questo tipo"); }

double Binomiale::densita(int k) const {

    if(k<0 || k>n)
        throw CustomException("Parametro non valido");

    return VariabileAleatoria::NC(n, k)*pow(p, k)*pow((1-p), n-k);

}

double Binomiale::media() const {

    return n*p;

}

QVector<int>* Binomiale::moda() const {
    double epsilon = 0.0000001;
    double moda = (n+1)*p;
    if(abs(moda-floor(moda))>epsilon || moda==0)
        return new QVector<int>(1, floor(moda));
    else if(abs(moda-n+1)<epsilon) return new QVector<int>(1, n);
    else if(abs(moda-floor(moda))<epsilon && moda<=n){
        QVector<int>* v = new QVector<int>(1, moda);
        v->append(moda-1);
        return v;
    }
    else throw CustomException();


}

double Binomiale::varianza() const {

    return n*p*(1-p);

}

double Binomiale::entropia() const {
    if(p==0) return 0;
    return 0.5*log2(2*M_PI*M_E*n*p*(1-p));
}

double Binomiale::informazione() const {

    if(p==0 || p==1)
        return 0;

    return n/p*(1-p);
}

QString Binomiale::toQString(QString nome) const{
    return QString(nome+"~Bin("+QString::number(n)+", "+QString::number(p)+")");
}

/*  Variabile Aleatoria (v.a.) Binomiale
    Notazione: Bin(n, p)
    Parametri: 'n'>0 intero, 'p' reale, compreso tra [0,1]
    Operazioni:
    --------------------------------------------------------
        SOMMA v1=Bin(n1, p) + v2=Bin(n2, p)
            Vincoli: v1.p == v2.p
            Risultato: Bin(n1+n2, p)
    --------------------------------------------------------
        DIFFERENZA v1=Bin(n1, p) - v2=Bin(n2, p)
            Vincoli: v1.p == v2.p, n1>n2
            Risultato: Bin(n1-n2, p)
    --------------------------------------------------------
        PRODOTTO v1=Bin(n1, p) * v2=Bin(n2, p)
            Vincoli: v1.p == v2.p
            Risultato: Bin(n1*n2, p)
    --------------------------------------------------------
        DENSITA' di parametro intero k
            Vincoli: k compreso tra [0,n]
            Risultato: Coefficiente Binomiale (n k) * p^k * (1-p)^(n-k)
    --------------------------------------------------------
        MEDIA:
            Risultato: np
    --------------------------------------------------------
        MODA:
            Risultato: floor(p(n+1)) se p(n+1)=0 o p(n+1) non appartiene ai naturali
                       p(n+1),(p-1)(n+1) se p(n+1) appartiene ai naturali
                       n se p=1
    --------------------------------------------------------
        VARIANZA:
            Risultato: np(1-p)
    --------------------------------------------------------
        ENTROPIA:
            Risultato: 0 se p=0 o p=1
                       0.5*log2(2pi*e*np(p1-)) altrimenti
    --------------------------------------------------------
        INFORMAZIONE:
            Risultato: 0 se p=0 o p=1
                       n/(p(1-p)) altrimenti
*/

#ifndef BINOMIALE
#define BINOMIALE
#include "VariabileAleatoria.h"

class Binomiale : public VariabileAleatoria {
private:
    int n;
    double p;
public:
    Binomiale(QString);
    Binomiale(int, double);
    Binomiale();
    Binomiale* clone() const;
    Binomiale* somma(const VariabileAleatoria&) const;
    Binomiale* differenza(const VariabileAleatoria&) const;
    Binomiale* prodotto(const VariabileAleatoria&) const;
    Binomiale* quoziente(const VariabileAleatoria&) const;
    double getP() const;
    int getN() const;
    double densita(int k) const;
    double media() const;
    QVector<int>* moda() const;
    double varianza() const;
    double entropia() const;
    double informazione() const;
    QString toQString(QString n) const;
};

#endif // BINOMIALE

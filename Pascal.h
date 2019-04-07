/*  Variabile Aleatoria (v.a.) Pascal (o binomiale negativa)
    Notazione: NB(p, n)
    Parametri: 'n'>0 intero, 'p' reale, compreso tra [0,1]
    Operazioni:
    --------------------------------------------------------
        SOMMA v1=NB(p, n1) + v2=NB(p, n2)
            Vincoli: v1.p == v2.p
            Risultato: NB(p, n1+n2)
    --------------------------------------------------------
        DIFFERENZA v1=NB(p, n1) - v2=NB(p, n2)
            Vincoli: v1.p == v2.p, n1>n2
            Risultato: NB(p, n1-n2)
    --------------------------------------------------------
        PRODOTTO v1=NB(p, n1) - v2=NB(p, n2)
            Vincoli: v1.p == v2.p
            Risultato: NB(p, n1*n2)
    --------------------------------------------------------
        DENSITA' di parametro intero k
            Vincoli: k>0
            Risultato: Coefficiente Binomiale (k+n k-1) * p^k
      --------------------------------------------------------
        MEDIA:
            Risultato: 0 se p=0
                       n/p altrimenti
      --------------------------------------------------------
        MODA:
            Risultato: 0 se p=0 o p=1
                       floor(p(n-1)/(1-p)) altrimenti
       --------------------------------------------------------
        VARIANZA:
            Risultato: 0 se p=0 o p=1
                       n(1-p)/p^2 altrimenti
       --------------------------------------------------------
        INFORMAZIONE:
            Risultato: 0 se p=0 o p=1
                       n/(p(1-p)^2) altrimenti
*/
#ifndef PASCAL_H
#define PASCAL_H
#include "VariabileAleatoria.h"

class Geometrica;

class Pascal : public VariabileAleatoria{
private:
    int n;
    double p;
public:
    Pascal(QString);
    Pascal(double p, int n);
    Pascal();
    Pascal* clone() const;
    Pascal* somma(const VariabileAleatoria&) const;
    Pascal* differenza(const VariabileAleatoria&) const;
    Pascal* prodotto(const VariabileAleatoria&) const;
    Pascal* quoziente(const VariabileAleatoria&) const;
    double getP() const;
    int getN() const;
    double densita(int k) const;
    double media() const;
    QVector<int>* moda() const;
    double varianza() const;
    double informazione() const;
    QString toQString(QString n) const;
};

#endif // PASCAL_H

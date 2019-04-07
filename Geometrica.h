/*  Variabile Aleatoria (v.a.) Geometrica
    Notazione: G(p)
    Parametri: 'p' reale, compreso tra [0,1]
    Operazioni:
    --------------------------------------------------------
        SOMMA v1=G(p) + v2=G(p)
            Vincoli: v1.p == v2.p
            Risultato: NB(p, 2) ovvero un v.a. di Pascal (anche detta binomiale negativa)
    --------------------------------------------------------
        DENSITA' di parametro intero k
            Vincoli: k>=1
            Risultato: p(1-p)^(k-1)
    --------------------------------------------------------
        MEDIA:
            Risultato: 0 se p=0
                       1*p altrimenti
    --------------------------------------------------------
        MODA:
            Risultato: 1
    --------------------------------------------------------
        VARIANZA:
            Risultato: 0 se p=0 o p=1
                       (1-p)/p^2 altrimenti
    --------------------------------------------------------
        ENTROPIA:
            Risultato: 0 se p=0 o p=1
                       -log(p)-(1-p)/p*log(1-p) altrimenti
*/

#ifndef GEOMETRICA_H
#define GEOMETRICA_H
#include "VariabileAleatoria.h"
#include "Pascal.h"

class Pascal;

class Geometrica : public VariabileAleatoria {
private:
    double p;
public:
    Geometrica(QString);
    Geometrica(double);
    Geometrica();
    Geometrica* clone() const;
    double getP()const;
    Pascal* somma(const VariabileAleatoria&) const;
    Geometrica* differenza(const VariabileAleatoria&) const;
    Geometrica* prodotto(const VariabileAleatoria&) const;
    Geometrica* quoziente(const VariabileAleatoria&) const;
    double densita(int k) const;
    double media() const;
    QVector<int>* moda() const;
    double varianza() const;
    double entropia() const;
    QString toQString(QString n) const;
};

#endif // GEOMETRICA_H

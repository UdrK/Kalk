/*  Variabile Aleatoria (v.a.) Bernoulliana
    Notazione: B(p)
    Parametri: 'p' reale, compreso tra [0,1]
    Operazioni:
        SOMMA v1=B(p) + v2=B(p)
            Vincoli: v1.p == v2.p
            Risultato: Bin(2, p) ovvero una v.a. Binomiale
        DENSITA' di parametro intero k
            Vincoli: k=0 o k=1
            Risultato: 1-p se k=0
                       p se k=1
        MEDIA:
            Risultato: p
        MODA:
            Risultato: 0 se p<0.5
                       1 se p>0.5
                       0,1 altrimenti
        VARIANZA:
            Risultato: p(1-p)
        ENTROPIA:
            Risultato: 0 se p=0 o p=1
                       -(1-p)ln(1-p)-pln(p) altrimenti
        INFORMAZIONE:
            Risultato: 0 se p=0 o p=1
                       1/(p(1-p)) altrimenti
*/

#ifndef BERNOULLI_H
#define BERNOULLI_H
#include "VariabileAleatoria.h"
#include "Binomiale.h"

class Binomiale;

class Bernoulli : public VariabileAleatoria {
private:
    double p;
public:
    Bernoulli(double);
    Bernoulli();
    Bernoulli(QString);
    Bernoulli* clone() const;
    Binomiale* somma(const VariabileAleatoria&) const;
    Bernoulli* differenza(const VariabileAleatoria&) const;
    Bernoulli* prodotto(const VariabileAleatoria&) const;
    Bernoulli* quoziente(const VariabileAleatoria&) const;
    double getP() const;
    double densita(int k) const;
    double media() const;
    QVector<int>* moda() const;
    double varianza() const;
    double entropia() const;
    double informazione() const;
    QString toQString(QString n) const;
};

#endif // BERNOULLI_H

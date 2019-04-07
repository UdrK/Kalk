/*  Variabile Aleatoria (v.a.) Poisson
    Notazione: P(l)
    Parametri: 'l' reale, 'l'>0
    Operazioni:
    --------------------------------------------------------
        SOMMA v1=P(l1) + v2=P(l2)
            Risultato: P(l1+l2)
    --------------------------------------------------------
        DIFFERENZA v1=P(l1) - v2=P(l2)
            Risultato: S(l1, l2) ovvero una v.a. di Skellam
    --------------------------------------------------------
        PRODOTTO v1=P(l1) * v2=P(l2)
            Risultato: P(l1*l2)
    --------------------------------------------------------
        QUOZIENTE v1=P(l1) / v2=P(l2)
            Risultato: P(l1/l2)
    --------------------------------------------------------
        DENSITA' di parametro intero k
            Vincoli: k>=0
            Risultato: (l^k/k!)*e^-l
    --------------------------------------------------------
        MEDIA:
            Risultato: l
    --------------------------------------------------------
        MODA:
            Risultato: floor(l)
    --------------------------------------------------------
        VARIANZA:
            Risultato: l
    --------------------------------------------------------
        INFORMAZIONE:
            Risultato: 1/l
*/

#ifndef POISSON_H
#define POISSON_H
#include "VariabileAleatoria.h"
#include "Skellam.h"

class Skellam;

class Poisson : public VariabileAleatoria {
private:
    double l;
public:
    Poisson(QString);
    Poisson(double);
    Poisson();
    Poisson* clone() const;
    Poisson* somma(const VariabileAleatoria&) const;
    Skellam* differenza(const VariabileAleatoria&) const;
    Poisson* prodotto(const VariabileAleatoria&) const;
    Poisson* quoziente(const VariabileAleatoria&) const;
    double densita(int k) const;
    double media() const;
    QVector<int>* moda() const;
    double varianza() const;
    double informazione() const;
    QString toQString(QString n) const;
};

#endif // POISSON_H

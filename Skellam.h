/*  Variabile Aleatoria (v.a.) Skellam
    Notazione: S(l1, l2)
    Parametri: 'l1', 'l2' reale, 'l1', 'l2'>0
    Operazioni:
    --------------------------------------------------------
        SOMMA v1=S(l1, l2) + v2=S(l3, l4)
            Risultato: S(l1+l3, l2+l4)
    --------------------------------------------------------
        DIFFERENZA v1=S(l1, l2) - v2=S(l3, l4)
            Vincoli: l1-l3>0, l2-l4>0
            Risultato: S(l1-l3, l2-l4)
    --------------------------------------------------------
        PRODOTTO v1=S(l1, l2) * v2=S(l3, l4)
            Risultato: S(l1*l3, l2*l4)
    --------------------------------------------------------
        QUOZIENTE v1=S(l1, l2) / v2=S(l3, l4)
            Risultato: S(l1/l3, l2/l4)
    --------------------------------------------------------
        DENSITA' di parametro intero k
            Vincoli: k>=0
            Risultato: (l1^k/2)/l2 * e^-(l1-l2)
    --------------------------------------------------------
        MEDIA:
            Risultato: l1-l2
    --------------------------------------------------------
        MODA:
            Risultato: N/A
    --------------------------------------------------------
        VARIANZA:
            Risultato: l1+l2
*/

#ifndef SKELLAM_H
#define SKELLAM_H
#include "VariabileAleatoria.h"

class Skellam : public VariabileAleatoria {
private:
    double l1, l2;
public:
    Skellam(QString);
    Skellam(double, double);
    Skellam(double);
    Skellam();
    Skellam* clone() const;
    Skellam* somma(const VariabileAleatoria&) const;
    Skellam* differenza(const VariabileAleatoria&) const;
    Skellam* prodotto(const VariabileAleatoria&) const;
    Skellam* quoziente(const VariabileAleatoria&) const;
    double densita(int) const;
    QString densitas(int) const;
    double media() const;
    QVector<int>* moda() const;
    double varianza() const;
    QString toQString(QString n) const;
};

#endif // SKELLAM_H

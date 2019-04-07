/*  Variabile Aleatoria (v.a.) Ipergeometrica
    Notazione: H(n, h, r)
    Parametri: 'n', 'h', 'r' interi, n>h, n>r
    Operazioni:
    --------------------------------------------------------
        SOMMA v1=H(n1, h1, r) + v2=H(n2, h2, r)
            Vincoli: v1.r == v2.r
            Risultato: H(n1+n2, h1+h2, r)
    --------------------------------------------------------
        DIFFERENZA v1=H(n1, h1, r) - v2=H(n2, h2, r)
            Vincoli: v1.r == v2.r
            Risultato: H(n1-n2, h1-h2, r)
    --------------------------------------------------------
        PRODOTTO v1=H(n1, h1, r) * v2=H(n2, h2, r)
            Vincoli: v1.r == v2.r
            Risultato: H(n1*n2, h1*h2, r)
    --------------------------------------------------------
        DENSITA' di parametro intero k
            Vincoli: k compreso tra [0,r]
            Risultato: Coefficiente Binomiale (h k) * Coefficiente Binomiale (n-h r-k) / Coefficiente Binomiale (n r)
    --------------------------------------------------------
        MEDIA:
            Risultato: rh/n
    --------------------------------------------------------
        MODA:
            Risultato: floor[((r+1)*(n+1))/(n+2)]
    --------------------------------------------------------
        VARIANZA:
            Risultato: 0 se n=1
                       (r(n-r)h(nh))/((n-1)n^2);
*/

#ifndef IPERGEOMETRICA
#define IPERGEOMETRICA
#include "VariabileAleatoria.h"

class Ipergeometrica : public VariabileAleatoria {
private:
    int n, h, r;
public:
    Ipergeometrica(QString);
    Ipergeometrica(int, int, int);
    Ipergeometrica();
    Ipergeometrica* clone() const;
    Ipergeometrica* somma(const VariabileAleatoria&) const;
    Ipergeometrica* differenza(const VariabileAleatoria&) const;
    Ipergeometrica* prodotto(const VariabileAleatoria&) const;
    Ipergeometrica* quoziente(const VariabileAleatoria&) const;
    double densita(int k) const;
    double media() const;
    QVector<int>* moda() const;
    double varianza() const;
    QString toQString(QString n) const;

};

#endif // IPERGEOMETRICA

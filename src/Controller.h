#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QString>
#include "VariabileAleatoria.h"
#include "CustomException.h"
#include "Bernoulli.h"
#include "Binomiale.h"
#include "Pascal.h"
#include "Geometrica.h"
#include "Poisson.h"

class Controller{
private:

    QString par="()";
    QString operandi="xyXY";
    QString operazioni="+-*/";

public:
    Controller();
    bool bilanciate(QString, int, int) const;
    bool valutabile(QString, QString) const;
    VariabileAleatoria* valutaespressione(QString, const VariabileAleatoria&, const VariabileAleatoria&) const;
    VariabileAleatoria* valuta(QString, QString, const VariabileAleatoria&, const VariabileAleatoria&) const;
    QString monoperando(const VariabileAleatoria&, QString, int) const;
};

#endif // CONTROLLER_H

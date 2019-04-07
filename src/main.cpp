#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "VariabileAleatoria.h"
#include "Binomiale.h"
#include "Skellam.h"
#include "CustomException.h"
#include "Bernoulli.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

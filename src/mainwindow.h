#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CustomException.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void signalException(CustomException);

private:
    Ui::MainWindow *ui;

private slots:
    void write_pressed();
    void fun_pressed();
    void canc_pressed();
    void uguale_pressed();
    void tipo_changed();

};

#endif // MAINWINDOW_H

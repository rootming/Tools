#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    calc = new Calc();

    setWindowTitle("NetCalc");
    setMinimumSize(600, 480);
    setMaximumSize(600, 480);

    setCentralWidget(calc);

}

MainWindow::~MainWindow()
{

}

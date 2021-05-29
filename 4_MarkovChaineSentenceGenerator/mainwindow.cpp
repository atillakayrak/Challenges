#include "mainwindow.h"

#include "Matrix.h"
#include "Tools.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    QDEBUG() << "test";
    try
    {
        auto m1 = core::Matrix({{1, 2}, {3, 4}});
        auto m2 = core::Matrix(m1).cast<double>();
        // m2[1][1] = 2;
        QDEBUG().nospace() << '\n' << m1.toStr().c_str();
        QDEBUG().nospace() << '\n' << m2.toStr().c_str();
        QDEBUG() << (m1 == m2);
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what() << '\n';
    }

    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

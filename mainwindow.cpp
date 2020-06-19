#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui->setupUi(this);

    db = new DataBase();
    db->connectToDataBase();

}
MainWindow::~MainWindow()
{

}
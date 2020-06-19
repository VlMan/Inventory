#pragma once

#include <QtWidgets/QMainWindow>
#include "DB_Driver.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();
private:
    Ui::MainWindow *ui;

    DataBase *db;

};

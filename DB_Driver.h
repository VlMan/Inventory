#pragma once

#include <QObject>
#include <QtSql/qtsqlglobal.h>
#include <QtSql/qsql.h>
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlerror.h>
#include <QFile>
#include <QDate>
#include <QDebug>
#include "mainwindow.h"

#define DATABASE_NAME "Shop_inventory"
#define DATABASE_HOSTNAME "Shop_inventory.db"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject* parent = 0);
    ~DataBase();
    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
     * */
    void connectToDataBase();
    bool inserIntoTable(const QVariantList& data);

private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase    db = QSqlDatabase::addDatabase(DATABASE_NAME);

private:
    /* Внутренние методы для работы с базой данных
     * */
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTable();
};
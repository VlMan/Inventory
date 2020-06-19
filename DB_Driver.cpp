#include "DB_Driver.h"

DataBase::DataBase(QObject* parent) : QObject(parent)
{
    db.setHostName("localhost"); // или, например, "my1.server.ru"
    db.setDatabaseName("mydb1");
    db.setUserName("root");
    db.setPassword("");

    bool connected = db.open();
}

DataBase::~DataBase()
{

}

/* ћетоды дл€ подключени€ к базе данных
 * */
void DataBase::connectToDataBase()
{
    /* ѕеред подключением к базе данных производим проверку на еЄ существование.
     * ¬ зависимости от результата производим открытие базы данных или еЄ восстановление
     * */
    if (!QFile("C:/My_cpp_proj/Inventory/" DATABASE_NAME).exists()) {
        this->restoreDataBase();
    }
    else {
        this->openDataBase();
    }
}

/* ћетоды восстановлени€ базы данных
 * */
bool DataBase::restoreDataBase()
{
    if (this->openDataBase()) {
        if (!this->createTable()) {
            return false;
        }
        else {
            return true;
        }
    }
    else {
        qDebug() << "Ќе удалось восстановить базу данных";
        return false;
    }
    return false;
}

/* ћетод дл€ открыти€ базы данных
 * */
bool DataBase::openDataBase()
{
    /* Ѕаза данных открываетс€ по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("C:/My_cpp_proj/Inventory/" DATABASE_NAME);
    if (db.open()) {
        return true;
    }
    else {
        return false;
    }
}

/* ћетоды закрыти€ базы данных
 * */
void DataBase::closeDataBase()
{
    db.close();
}

/* ћетод дл€ создани€ таблицы в базе данных
 * */
bool DataBase::createTable()
{
    /* ¬ данном случае используетс€ формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;
    if (!query.exec("CREATE TABLE Item_Data ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name VARCHAR            NOT NULL,"
        "sender VARCHAR            NOT NULL,"
        "price INT         NOT NULL,"
        " )"
    )) {

        qDebug() << query.lastError().text();
        return false;
    }
    else {
        return true;
    }
    return false;
}

/* ћетод дл€ вставки записи в базу данных
 * */
bool DataBase::inserIntoTable(const QVariantList& data)
{
    /* «апрос SQL формируетс€ из QVariantList,
     * в который передаютс€ данные дл€ вставки в таблицу.
     * */
    QSqlQuery query;
    /* ¬ начале SQL запрос формируетс€ с ключами,
     * которые потом св€зываютс€ методом bindValue
     * дл€ подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO Item_Data ( name, sender, price ) "
        "VALUES (:name, :sender, :price )");
    query.bindValue(":name", "123");
    query.bindValue(":sender", "123");
    query.bindValue(":price", 123123);

    // ѕосле чего выполн€етс€ запросом методом exec()
    if (!query.exec()) {
        qDebug() << query.lastError().text();
        return false;
    }
    else {
        return true;
    }
    return false;
}
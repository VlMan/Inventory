#include "DB_Driver.h"

DataBase::DataBase(QObject* parent) : QObject(parent)
{
    db.setHostName("localhost"); // ���, ��������, "my1.server.ru"
    db.setDatabaseName("mydb1");
    db.setUserName("root");
    db.setPassword("");

    bool connected = db.open();
}

DataBase::~DataBase()
{

}

/* ������ ��� ����������� � ���� ������
 * */
void DataBase::connectToDataBase()
{
    /* ����� ������������ � ���� ������ ���������� �������� �� � �������������.
     * � ����������� �� ���������� ���������� �������� ���� ������ ��� � ��������������
     * */
    if (!QFile("C:/My_cpp_proj/Inventory/" DATABASE_NAME).exists()) {
        this->restoreDataBase();
    }
    else {
        this->openDataBase();
    }
}

/* ������ �������������� ���� ������
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
        qDebug() << "�� ������� ������������ ���� ������";
        return false;
    }
    return false;
}

/* ����� ��� �������� ���� ������
 * */
bool DataBase::openDataBase()
{
    /* ���� ������ ����������� �� ��������� ����
     * � ����� ���� ������, ���� ��� ����������
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

/* ������ �������� ���� ������
 * */
void DataBase::closeDataBase()
{
    db.close();
}

/* ����� ��� �������� ������� � ���� ������
 * */
bool DataBase::createTable()
{
    /* � ������ ������ ������������ ������������ ������ SQL-�������
     * � ����������� ��� �����������.
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

/* ����� ��� ������� ������ � ���� ������
 * */
bool DataBase::inserIntoTable(const QVariantList& data)
{
    /* ������ SQL ����������� �� QVariantList,
     * � ������� ���������� ������ ��� ������� � �������.
     * */
    QSqlQuery query;
    /* � ������ SQL ������ ����������� � �������,
     * ������� ����� ����������� ������� bindValue
     * ��� ����������� ������ �� QVariantList
     * */
    query.prepare("INSERT INTO Item_Data ( name, sender, price ) "
        "VALUES (:name, :sender, :price )");
    query.bindValue(":name", "123");
    query.bindValue(":sender", "123");
    query.bindValue(":price", 123123);

    // ����� ���� ����������� �������� ������� exec()
    if (!query.exec()) {
        qDebug() << query.lastError().text();
        return false;
    }
    else {
        return true;
    }
    return false;
}
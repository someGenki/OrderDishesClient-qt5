#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtDebug>

int main(int argc, char *argv[])
{
    // 建立数据库 可直接 QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    QSqlDatabase database=QSqlDatabase::contains("qt_sql_default_connection")
            ?QSqlDatabase::database("qt_sql_default_connection")
           : QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("MyOrder.db");
    // 打开数据库
    database.open()? qDebug()<<"Open success":  qDebug() << "Failed to connect database." << database.lastError();
    // 建立表格 TODO 测试用
    QSqlQuery sql_query;
    sql_query.exec("create table student(id int primary key, name text, age int)")
            ?qDebug() << "Table created!":qDebug() << sql_query.lastError();


    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("点菜系统v0.1   -LYQ");
    w.setWindowIcon(QIcon(":/static/wallpaper.ico"));
    w.show();
    return a.exec();
}

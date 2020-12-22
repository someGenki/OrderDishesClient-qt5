#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtDebug>
#include <myUtil.h>
int main(int argc, char *argv[])
{
    // 建立数据库对象 可直接 QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    QSqlDatabase database=QSqlDatabase::contains("qt_sql_default_connection")
            ?QSqlDatabase::database("qt_sql_default_connection")
           :QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("MyOrder.db");

    // 打开数据库
    database.open()? qDebug()<<"Open success":  qDebug() << database.lastError();

    // 读取数据库文件并建立表格
    QSqlQuery sql_query;
    QString sql= UTILS::FileUtil::ReadFILEToQString(":/static/tables.sql");
    UTILS::SqliteUtil::CreateTablesByQString(sql,sql_query);

    // 查看创建的表
    qDebug()<< database.tables();

    // 表里没数据则创建数据记录 TODO 待抽离以创建内置数据
    sql_query.exec("select count(1) from menu");
    if( sql_query.next()&& sql_query.value(0)=="0"){
        QFile file1(":/static/built-in.jpg"),file2(":/static/built-in2.jpg");
           if (!file1.open(QIODevice::ReadOnly)||!file2.open(QIODevice::ReadOnly)) return -1;
        QByteArray byteArray1 = file1.readAll();
        sql_query.prepare("INSERT INTO menu(name,price,pic) VALUES('土豆炒西红柿','10.0',:imgData);");
        sql_query.bindValue(":imgData",byteArray1);
       qDebug()<<  sql_query.exec()<<database.lastError();

        QByteArray byteArray2 = file2.readAll();
        sql_query.prepare("INSERT INTO menu(name,price,pic) VALUES('番茄炒马铃薯','10.0',:imgData);");
        sql_query.bindValue(":imgData",byteArray2);
         qDebug()<<  sql_query.exec()<<database.lastError();
        qDebug()<<"创建内置数据完成";
    }

//    sql_query.exec("select * from menu;");
//    while(sql_query.next()){
//            qDebug()<<123;
//            qDebug()<< sql_query.value(3).toString();
//    }


    QApplication a(argc, argv);
    MainWindow w;
    // 桌号的设置可以使用argv
    w.setWindowTitle("当前桌号 No.1        点菜系统v0.1-LYQ");
    w.setWindowIcon(QIcon(":/static/wallpaper.ico"));
    w.show();
    return a.exec();
}

#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtDebug>
#include <MyUtil.h>

int main(int argc, char *argv[])
{
    // 建立数据库对象 or QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    QSqlDatabase database=QSqlDatabase::contains("qt_sql_default_connection")
            ?QSqlDatabase::database("qt_sql_default_connection")
           :QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("MyOrder.db");

    // 打开数据库
    database.open()? qDebug()<<"Open success":  qDebug() << database.lastError();

    // 读取数据库文件并建立表格
    QSqlQuery sql_query;
    QString sql= UTILS::FileUtil::ReadFileToQString(":/static/tables.sql");
    UTILS::SqliteUtil::CreateTablesByQString(sql,sql_query);

    // 查看已创建的表
    qDebug()<<"当前表:" <<database.tables();

    // menu表里没数据则自动创建数据记录
    sql_query.exec("select count(*) from menu");
    if( sql_query.next() && sql_query.value(0)=="0"){
        QString sql= UTILS::FileUtil::ReadFileToQString(":/static/insert.ini");
        UTILS::SqliteUtil::InsertDataWithBinaryByFile(sql,sql_query);
        qDebug()<<"创建内置数据完成";
    }

    // 查看menu表里的数据
    UTILS::SqliteUtil::SelectAndShowByRange("menu",sql_query,5);


    QApplication a(argc, argv);
    MainWindow w;
    // 桌号的设置可以使用argv
    w.setWindowTitle("当前桌号 No.1        点菜系统v0.1-LYQ");
    w.setWindowIcon(QIcon(":/static/bilibili.ico"));
    w.show();
    return a.exec();
}

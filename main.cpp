#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <MyUtil.h>

int main(int argc, char *argv[])
{
    // 建立数据库对象
    //	QSqlDatabase database = QSqlDatabase::contains("qt_sql_default_connection")
    //    ?QSqlDatabase::database("qt_sql_default_connection")
    //    :QSqlDatabase::addDatabase("QSQLITE");
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");

    // 设置数据库文件的路径并打开数据库
    database.setDatabaseName("MyOrder.db");
    database.open()? qDebug() << "open success": qDebug() << database.lastError();

    // 读取数据库文件
    QSqlQuery *sql_query = new QSqlQuery(database);
    QString sql_str = UTILS::FileUtil::ReadFileToQString(":/static/tables.sql");

    // 根据sql语句建立数据表并查看创建的表（建表语句有`IF NOT EXISTS`)
    UTILS::SqliteUtil::CreateTablesBySQL(sql_str, sql_query);
    qDebug() << "当前表:" << database.tables();

    // menu表里没数据则读取文件自动创建数据记录
    sql_query->exec("select count(*) from menu");
    if (sql_query->next() && sql_query->value(0) == "0") {
        QString sql_str = UTILS::FileUtil::ReadFileToQString(":/static/insert.ini");
        UTILS::SqliteUtil::InsertDataWithBinaryBySQL(sql_str, sql_query);
        qDebug() << "创建内置数据完成";
    }

    // 查看menu表里的数据 从0-range列
    UTILS::SqliteUtil::SelectAndShowByRange("menu", sql_query, 5);


    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("当前桌号 No.1         点菜系统v0.1-LYQ");
    w.setWindowIcon(QIcon(":/static/bilibili.ico"));
    w.show();
    return a.exec();
}

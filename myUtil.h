#ifndef MYUTILS_H
#define MYUTILS_H

#include <QSqlQuery>
#include <QtDebug>
#include <QSqlError>
#include <QFile>

namespace UTILS
{

class   FileUtil{
public:
    // 读取sql文件并返回一个Qstring对象
    static  QString ReadFILEToQString(const char* path);


};

class SqliteUtil{
public:
   // 用QString字符串中的表信息来创建表;建表语句之间用';'分割，其他地方不能出现';'
   static  bool CreateTablesByQString(const QString qs, QSqlQuery qq);
};

}

#endif // MYUTILS_H

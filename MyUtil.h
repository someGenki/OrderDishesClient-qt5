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
    // 读取文件并返回一个Qstring对象
    static  QString ReadFileToQString(const char* path);


};

class SqliteUtil{
public:
   // 用QString字符串中的表信息来创建表;建表语句之间用';'分割，其他地方不能出现';'
   static  bool CreateTablesByQString(const QString qs, QSqlQuery qq);

   // 读取文件，每行内容为预编译语句，有且仅有一个":imgData"占位符存在。
   // 二进制图片在:/foodPic名字为i.jpg
   static  bool InsertDataWithBinaryByFile(const QString qs,QSqlQuery qq);

   // 查询数据库表的字段以及列（需要指定要查看的列数0-range)
   static  void SelectAndShowByRange(QString tablename,QSqlQuery qq,int range);

};

}

#endif // MYUTILS_H

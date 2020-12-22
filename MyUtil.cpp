#include "MyUtil.h"


namespace UTILS
{

   QString FileUtil::ReadFileToQString(const char * path){
        QFile f(path);
        if (!f.exists()|!f.open(QIODevice::ReadOnly|QIODevice::Text))//打开指定文件
        {
           qDebug()<<"打开失败";
           return nullptr;
        }
        QTextStream in(&f);
        in.setCodec("UTF-8");
        return in.readAll();
    }

   bool SqliteUtil::CreateTablesByQString(const QString qs, QSqlQuery qq){
      QStringList qlist =  qs.split(";");

      for (int i = 0; i < qlist.size() - 1; i++) {
              QString qs1 = qlist.at(i).toUtf8();
              try {
                    qq.exec(qs1);
              } catch (...) {
                  qDebug()<<"创建失败"<<qs1;
              }
      }

      return true;
   }

   bool SqliteUtil::InsertDataWithBinaryByFile(const QString qs,QSqlQuery qq){
       QStringList qlist =  qs.split(";");
       QString qs2=":/foodPic/";
       qDebug()<<"size:"<<qlist.size();
       for (int i = 0; i < qlist.size() - 1; i++) {
               QString qs1 = qlist.at(i).toUtf8();
               try {
                   //qDebug()<<qs2.asprintf(":/foodPic/%d.jpg",i+1);
                   QFile file(qs2.asprintf(":/foodPic/%d.jpg",i+1));
                   if (!file.open(QIODevice::ReadOnly)) return false;
                   QByteArray byte=file.readAll();
                   qq.prepare(qs1);
                   qq.bindValue(":imgData",byte);
                   qq.exec();
               } catch (...) {
                   qDebug()<<"创建失败"<<qs1;
                   return false;
               }
       }
       return true;
   }

   void SqliteUtil::SelectAndShowByRange(QString tablename,QSqlQuery qq,int range){
       QString qs("select * from "+tablename+";");
       qq.exec(qs);
       while(qq.next()){
           QString tqs;
           for (int i=0;i<range;i++) {
                tqs=tqs.append(qq.value(i).toString()+";");
           }
           qDebug()<<tqs;
       }
   }
}

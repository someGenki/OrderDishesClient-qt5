#include "myUtil.h"


namespace UTILS
{
   QString FileUtil::ReadFILEToQString(const char * path){
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
}

#include "menu.h"
Menu::Menu()
{
}

QString Menu::toString(){
    return QString()+name+type;
}
Menu* Menu::getMenusFromDB(QSqlQuery qq){
    QString qs("select * from menu");
    int i=0;
    qq.exec(qs);
    Menu* ms=new Menu[20];
    while(qq.next()){
        QString tqs;
        ms[i].id=qq.value("id").toInt();
        ms[i].name=qq.value("name").toString();
        ms[i].price=qq.value("price").toString();
        ms[i].pic=qq.value("pic").toByteArray();
        ms[i].type=qq.value("type").toInt();
        i++;
    }
    return ms;
}

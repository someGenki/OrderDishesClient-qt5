#include "menu.h"
Menu::Menu()
{
}

Menu::Menu(Menu *_menu){

    this->id=_menu->id;
    this->name=_menu->name;
    this->pic=_menu->pic;
    this->price=_menu->price;
    this->type=_menu->type;
}

QString Menu::toString(){
    return QString()+name+type;
}
Menu* Menu::getMenusFromDB(QSqlQuery qq){
    QString qs("select * from menu");
    int i=0;
    qq.exec(qs);
    Menu* ms=new Menu[20];
    while(qq.next()) {
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

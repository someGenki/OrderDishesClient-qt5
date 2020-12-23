#include "menu.h"
Menu::Menu()
{
}

Menu::Menu(Menu *_menu)
{
    this->id = _menu->id;
    this->name = _menu->name;
    this->pic = _menu->pic;
    this->price = _menu->price;
    this->type = _menu->type;
}

Menu *Menu::getMenusFromDB(QSqlQuery qq, int& size)
{
    QString qs("select * from menu");
    QString tqs;
    Menu *ms = nullptr;
    int i = 0;

    // 不能直接用.size()获取大小 用sqlite数据库会返回-1
    qq.exec(qs);
    if (qq.last()) {
        size = qq.at() + 1;
        qq.first();
        qq.previous();
    }
    ms = new Menu[size];
    while (qq.next()) {
        ms[i].id = qq.value("id").toInt();
        ms[i].name = qq.value("name").toString();
        ms[i].price = qq.value("price").toString();
        ms[i].pic = qq.value("pic").toByteArray();
        ms[i].type = qq.value("type").toInt();
        i++;
    }
    return ms;
}

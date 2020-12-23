#ifndef MENU_H
#define MENU_H

#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

//菜单表Entity
class Menu
{
public:
Menu();
Menu(Menu *_menu);
int id;
int type;
QString name;
QString price;
QByteArray pic;
static Menu *getMenusFromDB(QSqlQuery, int&);
};
Q_DECLARE_METATYPE(Menu)
// QVariant存储自定义类型↑

#endif // MENU_H

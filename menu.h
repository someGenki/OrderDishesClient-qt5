#ifndef MENU_H
#define MENU_H
#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
//-- 菜单表
class Menu
{
public:
    Menu();
   // enum Type{STAPLE_FOOD=1,SNACK,DESSERT,SOUP};
    int id;
    QString name;
    QString price;
    QByteArray pic;
    int type;
    static Menu* getMenusFromDB(QSqlQuery);
    QString toString();
};

#endif // MENU_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtDebug>
#include <QString>
#include <QTimer>
#include <QDateTime>
#include <QTreeWidget>
#include "menu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
// 一个宏： 定义了一个静态的元对象 开启信号和槽机制
Q_OBJECT

public:
MainWindow(QWidget *parent = nullptr);
~MainWindow();
#include "menu.h"


private slots:
void on_seatConfirmBtn_clicked();
void time_update();     //时间更新槽函数，状态栏显示时间
void on_payBtn_clicked();
void menuTree_clicked(QTreeWidgetItem* item);
void addToOrderBtn1_clicked();

void on_deleteBtn_clicked();

void on_callWaiterBtn_clicked();

void on_orderConfirmBtn_clicked();

private:
Ui::MainWindow *ui;

QSqlQuery sql_query;
bool used=false;     // 使用状态 默认未使用
QTimer *timer=nullptr;
Menu* checkedMenu;
float money=0.0;
void    iniTreeWidget();    //目录树初始化
void setPicToPicShowLableAdaptive(QPixmap& pixmap);
};

#endif // MAINWINDOW_H

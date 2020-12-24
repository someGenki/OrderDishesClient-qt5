#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTreeWidget>
#include <QSqlQuery>
#include <QDateTime>
#include <QtDebug>
#include <QTimer>
#include "menu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
// 一个宏： 定义了一个静态的元对象 开启信号和槽机制
Q_OBJECT

public:
// 深拷贝构造函数
MainWindow(QWidget *parent = nullptr);
~MainWindow();

//定义槽
private slots:

// 点击Tree的Item
void menuTree_clicked(QTreeWidgetItem *item);
// 把当前选中的Menu项添加到右侧已点列表中
void addToOrderBtn1_clicked();
// 时间更新槽函数，状态栏显示时间
void time_update();
// 点击付款按钮
void on_payBtn_clicked();
// 右侧已点菜单中删除未选中的菜单
void on_deleteBtn_clicked();
// 通知服务员
void on_callWaiterBtn_clicked();
// 入座确认
void on_seatConfirmBtn_clicked();
// 点菜完毕确认
void on_orderConfirmBtn_clicked();

void on_action_triggered();

private:
Ui::MainWindow *ui;
QSqlQuery sql_query;

// 状态栏更新定时器
QTimer *timer = nullptr;
// App使用状态 默认未使用
bool used = false;
// 预计花费金额
float money = 0.0;
// 当前预览的菜单
Menu *checkedMenu;

// 窗口初始化
void init();
// 目录树初始化
void    iniTreeWidget();
// 显示图片到Label中并自动适应大小
void setPicToPicShowLableAdaptive(QPixmap& pixmap);
};

#endif // MAINWINDOW_H

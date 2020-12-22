#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtDebug>
#include <QString>
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

    void on_payBtn_clicked();

private:
    Ui::MainWindow *ui;
    QSqlQuery sql_query;
    bool used=false; // 使用状态 默认未使用
    void    iniTree();//目录树初始化
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    // 显示图片在lab中
//    sql_query.exec("select * from menu;");
//    if(sql_query.next()){
//            QPixmap pixmap;
//            pixmap.loadFromData(sql_query.value(3).toByteArray());
//            ui->pic_lab->setPixmap(pixmap);
//    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


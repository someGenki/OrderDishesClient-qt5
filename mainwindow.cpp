#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    显示图片在lab中
    QPixmap pixmap(":/static/unknown.jpg");
    pixmap.scaled(ui->pic_show->size(), Qt::KeepAspectRatio);
    ui->pic_show->setScaledContents(true);
    ui->pic_show->setPixmap(pixmap);
    ui->statusbar->showMessage("当前没有客户使用  等待中");
    iniTree();
}

MainWindow::~MainWindow()
{
    delete ui;
}

 //初始化Tree
void MainWindow::iniTree()
{
    Menu*  menus=Menu::getMenusFromDB(sql_query);
    //QTreeWidgetItem *item; //节点
    ui->menuTree->clear();//清除目录树所有节点
    QIcon icon;
    icon.addFile(":/static/steam.ico"); //设置ICON的图标

    QStringList qs_arr={"主食","小吃","甜点","汤"};
    int i=1;
    for (const QString& qs : qs_arr) {
        QTreeWidgetItem*  item=new QTreeWidgetItem(1001); //新建节点时设定类型
        item->setIcon(0,icon); //设置第1列的图标
        item->setText(0,qs); //设置第1列的文字
        // TODO 遍历数据库,挂载到子节点上,绑定点击事件
        for (int j=0;j<5;j++) {
            if(menus[j].type==i){
                QTreeWidgetItem*  item1=new QTreeWidgetItem(1001); //新建节点时设定类型
                item1->setText(0,menus[j].name); //设置第1列的文字
                item->addChild(item1);  //添加成子节点
            }
        }
        ui->menuTree->addTopLevelItem(item);//添加顶层节点
        i++;
    }


}
// 入座确认
void MainWindow::on_seatConfirmBtn_clicked()
{
    if(used==true){
        QString dlgTitle="对话框";
            QString strInfo="当前正在使用者";
            QMessageBox::critical(this, dlgTitle, strInfo);
    }else{
        QString dlgTitle="消息框";
           QString strInfo="欢迎使用~";
           used=true;
           // TODO  初始化工作
          QMessageBox::information(this, dlgTitle, strInfo,
                                     QMessageBox::Ok,QMessageBox::NoButton);
    }

}
// 结账
void MainWindow::on_payBtn_clicked()
{

    if(used==true){
        QString dlgTitle="是否结账";
        QString strInfo="您已消费xxx元!";
        QMessageBox::StandardButton  defaultBtn=QMessageBox::NoButton; //缺省按钮
        QMessageBox::StandardButton result; //返回选择的按钮
        result=QMessageBox::question(this, dlgTitle, strInfo,
                          QMessageBox::Yes| QMessageBox::No | QMessageBox::Cancel,defaultBtn);
        if (result==QMessageBox::Yes){
            QString dlgTitle="对话框";
            QString strInfo="正在通知服务员过来结账!";
            QMessageBox::information(this, dlgTitle, strInfo);
            used=false;
            // TODO 首尾工作
        }

    }else{
        QString dlgTitle="对话框";
        QString strInfo="当前设备未在使用，结账失败";
        QMessageBox::critical(this, dlgTitle, strInfo);
    }
}

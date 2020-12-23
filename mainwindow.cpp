#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    iniTreeWidget();
    connect(ui->menuTree, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
        this, SLOT(menuTree_clicked(QTreeWidgetItem*)));
    connect(ui->addToOrderBtn, SIGNAL(clicked()),
        this, SLOT(addToOrderBtn1_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 初始化窗口
void MainWindow::init()
{
    this->ui->statusbar->showMessage("当前没有客户使用  等待中");
    setPicToPicShowLableAdaptive(*new QPixmap(":/static/unknown.jpg"));
    this->money = 2;
}
//把当前选中的Menu项添加到右侧已点列表
void MainWindow::addToOrderBtn1_clicked()
{
    Menu *m = this->checkedMenu;

    if (m == nullptr) {
        qDebug() << "null";
    } else {
        qDebug() << m->name;
        // 具体操作
        QListWidgetItem *item = new QListWidgetItem();
        item->setCheckState(Qt::Checked); //设置为选中状态
        item->setData(Qt::UserRole, m->price);
        QString qs;
        item->setText(qs.asprintf("%d_", m->id) + m->name);
        item->setToolTip(QDateTime::currentDateTime().toString("加入时间：hh:mm:ss 单价(元/份):" + m->price.toUtf8()));
        this->money += m->price.toFloat();
        this->ui->order_list->addItem(item);
    }
}

// 设置图片到pic_show并且自适应大小
void MainWindow::setPicToPicShowLableAdaptive(QPixmap& pixmap)
{
    pixmap.scaled(ui->pic_show->size(), Qt::KeepAspectRatio);
    ui->pic_show->setScaledContents(true);
    ui->pic_show->setPixmap(pixmap);
}

// 当点击Tree的Item的事件  1001是自定义的type，为TreeWidget的二级item
void MainWindow::menuTree_clicked(QTreeWidgetItem *item)
{
    if (item->type() == 1001) {
        QPixmap pixmap;
        Menu menu = item->data(0, Qt::UserRole).value<Menu>();
        this->checkedMenu = new Menu(item->data(0, Qt::UserRole).value<Menu>());
        pixmap.loadFromData(menu.pic);
        setPicToPicShowLableAdaptive(pixmap);
        if (used == true) ui->addToOrderBtn->setEnabled(true);
    }
}

// 初始化TreeWidget [一级节点的名字可设置从配置文件中读取]
void MainWindow::iniTreeWidget()
{
    int i = 0;
    int size = 0;
    QIcon icon;
    Menu *menus = Menu::getMenusFromDB(sql_query, size);
    QStringList qs_arr = { "主食", "小吃", "甜点", "汤" }; // 一级节点的名字

    ui->menuTree->clear();                          //清除目录树所有节点item
    ui->menuTree->setColumnWidth(0, 250);
    icon.addFile(":/static/bilibili.ico");          //设置ICON的图标

    // 遍历Menu表的数据，生成一级节点
    for (const QString& qs : qs_arr) {
        i++;
        QTreeWidgetItem *item = new QTreeWidgetItem(1000);      //新建节点时设定类型
        item->setIcon(0, icon);                                 //设置第0列的图标
        item->setText(0, qs);                                   //设置第0列的文字
        // 生成二级节点根据类型挂载到不同的一级节点上，绑定点击事件
        for (int j = 0; j < size; j++) {
            if (menus[j].type == i) {
                QVariant t;
                t.setValue(menus[j]);
                QTreeWidgetItem *item1 = new QTreeWidgetItem(1001);     //新建节点时设定类型
                item1->setData(0, Qt::UserRole, t);                     //给节点带一个数据:为图片
                item1->setText(0, menus[j].name);                       //设置第1列的文字
                item1->setText(1, menus[j].price + " 元");               //设置第2列的文字
                item->addChild(item1);                                  //添加成item的子节点
            }
        }
        ui->menuTree->addTopLevelItem(item);
    }
    ui->menuTree->expandAll();
}

// 入座
void MainWindow::on_seatConfirmBtn_clicked()
{
    if (used == true) {
        QString dlgTitle = "对话框";
        QString strInfo = "当前正在使用中";
        QMessageBox::critical(this, dlgTitle, strInfo);
    } else {
        QString dlgTitle = "消息框";
        QString strInfo = "欢迎使用~";
        QMessageBox::information(this, dlgTitle, strInfo,
                     QMessageBox::Ok, QMessageBox::NoButton);
        if ((timer) == nullptr)
            timer = new QTimer(this);
        timer->start(1000); //每隔1000ms发送timeout的信号触发状态栏更新
        connect(timer, SIGNAL(timeout()), this, SLOT(time_update()));
        this->used = true;
    }
}

// 结账
void MainWindow::on_payBtn_clicked()
{
    if (used == false) {
        QString dlgTitle = "对话框";
        QString strInfo = "当前设备未在使用，结账失败";
        QMessageBox::critical(this, dlgTitle, strInfo);
    } else {
        QString dlgTitle = "是否结账";
        QString strInfo = strInfo.asprintf("本次累计消费%.2lf元，是否现在结账", this->money);
        QMessageBox::StandardButton defaultBtn = QMessageBox::NoButton; //缺省按钮
        QMessageBox::StandardButton result = QMessageBox::question(this, dlgTitle, strInfo,
                                       QMessageBox::Yes | QMessageBox::No, defaultBtn);
        if (result == QMessageBox::Yes) {
            QString dlgTitle = "对话框";
            QString strInfo = "正在通知服务员过来结账!";
            QMessageBox::information(this, dlgTitle, strInfo);
            this->used = false;
            // 收尾工作
            disconnect(timer, SIGNAL(timeout()), this, SLOT(time_update()));
            if (used == true) ui->addToOrderBtn->setEnabled(false);
            int cnt = ui->order_list->count();//项个数
            for (int i = 2; i < cnt; i++) {
                QListWidgetItem *aItem = ui->order_list->item(i);
                delete  aItem;
            }
            if (timer->isActive())
                timer->stop();
            init();
            setPicToPicShowLableAdaptive(*new QPixmap(":/static/unknown.jpg"));
        }
    }
}

// 状态栏时间更新
void MainWindow::time_update()
{
    QDateTime current_time = QDateTime::currentDateTime();
    QString timestr = current_time.toString(timestr.asprintf("yyyy年MM月dd日 hh:mm:ss    预计消费：%.2lf元", this->money));  //设置显示的格式

    ui->statusbar->showMessage(timestr);                                                                            //设置label的文本内容为时间
}
// 删除未选 虾机霸写的
void MainWindow::on_deleteBtn_clicked()
{
    while (1) {
        if (ui->order_list->count() == 2) break;
        bool deleted = false;;
        for (int i = 2; i < ui->order_list->count(); i++) {
            QListWidgetItem *a = ui->order_list->item(i);
//            qDebug() << a->checkState();
            if (a->checkState() == Qt::CheckState::Unchecked) {
                this->money -= a->data(Qt::UserRole).toFloat();
                delete  a;
                deleted = true;
                break;
            }
        }
        if (deleted == false) break;
    }
}
// 通知服务员 [[随意]
void MainWindow::on_callWaiterBtn_clicked()
{
    QString dlgTitle = "是否呼叫服务员";
    QString strInfo = "确定？";
    QMessageBox::StandardButton defaultBtn = QMessageBox::NoButton; //缺省按钮
    QMessageBox::StandardButton result;                             //返回选择的按钮

    result = QMessageBox::question(this, dlgTitle, strInfo, QMessageBox::Yes | QMessageBox::Cancel, defaultBtn);
    if (result == QMessageBox::Yes) {
        QString dlgTitle = "对话框";
        QString strInfo = "正在通知服务员";
        QMessageBox::information(this, dlgTitle, strInfo);
    }
}
// 完成点单并通知后厨  [随意]
void MainWindow::on_orderConfirmBtn_clicked()
{
    QString dlgTitle = "对话框";
    QString strInfo = "后厨已经收到本次订单了";

    QMessageBox::information(this, dlgTitle, strInfo);
}

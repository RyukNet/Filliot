#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileInfo>
#include <QDebug>
#include <QTableWidgetItem>
#include <QDateTime>


#include "explorerwidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /***
     * TO ADD: Set the app start-up time according to settings data
     *
    ***/
    ui->setupUi(this);
    ui->splitter->setSizes(QList<int>{300,1000});

    ExplorerWidget *expWidget = new ExplorerWidget(this,"D:/");

    ui->tabWidget->addTab(expWidget,"D:/");
    ui->tabWidget->setTabsClosable(true);

    connect(expWidget, SIGNAL(openInNewTabSignal(QString)), this, SLOT(openFolderInNewTab(QString)));
    connect(expWidget, SIGNAL(titleChanged(QString)), this, SLOT(changeTabName(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::openFolderInNewTab(QString path){
    qDebug() << path;
    ExplorerWidget *expWidget_buff = new ExplorerWidget(this,path);
    ui->tabWidget->addTab(expWidget_buff,path);
    connect(expWidget_buff,SIGNAL(openInNewTabSignal(QString)),this,SLOT(openFolderInNewTab(QString)));
    connect(expWidget_buff, SIGNAL(titleChanged(QString)), this, SLOT(changeTabName(QString)));
}

void MainWindow::changeTabName(QString name){
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),name);
}

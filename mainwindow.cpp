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

    fileSysModel = new QFileSystemModel(this);
    fileSysModel->setRootPath("/");
    fileSysModel->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    ui->treeView->setModel(fileSysModel);
    ui->treeView->setExpandsOnDoubleClick(false);
    for (int i = 1; i < fileSysModel->columnCount(); ++i)
        ui->treeView->hideColumn(i);
    connect(ui->treeView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(changeCurrentTabPath(QModelIndex)));
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

void MainWindow::changeCurrentTabPath(QModelIndex index){
    //qDebug() << index.data(Qt::UserRole+1).toString(); //QFileSystemModel by default give to (Qt::UserRole+1) the file path
    ((ExplorerWidget*)ui->tabWidget->currentWidget())->cd(index.data(Qt::UserRole+1).toString());

}

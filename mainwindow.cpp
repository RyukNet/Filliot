#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileInfo>
#include <QDebug>
#include <QTableWidgetItem>
#include <QDateTime>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dir = new QDir("D:/");
    fileIconProvider = new QFileIconProvider();

    //ui->treeWidget->QTreeView::setDropIndicatorShown(false);
    ui->treeWidget->setColumnCount(2);

    /*for(auto entryInfo : dir->entryInfoList()){
        addTreeItem(entryInfo);
    }*/
    updateTreeWidget();
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(aboutDoubleClick(QTreeWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTreeItem(const QFileInfo fileInfo){
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    item->setIcon(0,fileIconProvider->icon(fileInfo));
    item->setText(0, fileInfo.fileName());
    item->setText(1, fileInfo.birthTime().toString());

}

void MainWindow::aboutDoubleClick(QTreeWidgetItem *item){
    qDebug() << item->text(0);
    if(dir->cd(item->text(0)))
        updateTreeWidget();
}

void MainWindow::updateTreeWidget(){
    ui->treeWidget->clear();
    for(auto entryInfo : dir->entryInfoList()){
        addTreeItem(entryInfo);
    }
}

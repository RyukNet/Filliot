#include "explorerwidget.h"

#include <QDebug>
#include <QDateTime>

ExplorerWidget::ExplorerWidget(QWidget *parent) : QWidget(parent)
{

    //setting the menu (probably will put it in a another class in the future)
    menu = new QMenu(treeWidget);
    menu->addAction("Copy");
    menu->addAction("Cut");
    menu->addAction("Paste");
    menu->addSeparator();
    menu->addAction("Move to new folder");
    //setting the layout and widgets to be rendered in the TabView
    vBoxLayout = new QVBoxLayout(this);
    vBoxLayout->setMargin(0);
    treeWidget = new QTreeWidget();
    treeWidget->setFrameShape(QFrame::NoFrame);//just changing the frame of the treeWidget
    vBoxLayout->addWidget(treeWidget);

    treeWidget->setColumnCount(3);
    treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    /***
     * TO ADD : Removing Tree handles in case of list like presentation
    ***/

    //dir = new QDir(QDir::currentPath());
    dir = new QDir("D:/");
    dir->setFilter(QDir::AllEntries | QDir::NoDot);
    fileIconProvider = new QFileIconProvider();

    updateTreeWidget();//first load
    connect(treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(cdInDirItem(QTreeWidgetItem*)));
    connect(treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showMenu(QPoint)));

}


void ExplorerWidget::addTreeItem(const QFileInfo fileInfo){
    qDebug() << fileInfo.fileName();
    QTreeWidgetItem *item = new QTreeWidgetItem(treeWidget);
    //item->QWidget::contextMenuEvent();
    item->setIcon(0,fileIconProvider->icon(fileInfo));
    item->setText(0, fileInfo.fileName());
    item->setText(1, fileInfo.birthTime().toString());
    if(fileInfo.isFile()){
        item->setData(2,Qt::DisplayRole,fileInfo.suffix());
    }else if(fileInfo.isDir()){
        item->setData(2,Qt::DisplayRole,tr("File folder"));
    }
}

void ExplorerWidget::cdInDirItem(QTreeWidgetItem *item){
    if(dir->cd(item->text(0)))
        updateTreeWidget();
}

void ExplorerWidget::updateTreeWidget(){
    treeWidget->clear();
    for(auto entryInfo : dir->entryInfoList()){

        addTreeItem(entryInfo);
    }
    treeWidget->sortByColumn(2,Qt::AscendingOrder);
}

void ExplorerWidget::showMenu(const QPoint &pos){
    qDebug() << pos << treeWidget->itemAt(pos)->text(0);
    //menu->popup(pos);
    menu->exec(QCursor::pos());
}

#include "explorerwidget.h"

#include <QDebug>
#include <QDateTime>

const int EntryType = Qt::UserRole;

ExplorerWidget::ExplorerWidget(QWidget *parent) : QWidget(parent)
{

    //setting the menu (probably will put it in a another class in the future)
    menu = new Menu(treeWidget);
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

    //Menu connecting :
    connect(menu,SIGNAL(openNewTabSignal()),this,SLOT(openInNewTab()));

}


void ExplorerWidget::addTreeItem(const QFileInfo fileInfo){
    qDebug() << fileInfo.fileName();
    QTreeWidgetItem *item = new QTreeWidgetItem(treeWidget);
    //item->QWidget::contextMenuEvent();
    item->setIcon(0,fileIconProvider->icon(fileInfo));
    item->setText(0, fileInfo.fileName());
    item->setText(1, fileInfo.birthTime().toString());
    if(fileInfo.isFile()){
        item->setData(0,EntryType,1);
        item->setData(2,Qt::DisplayRole,fileInfo.suffix());
    }else if(fileInfo.isDir()){
        item->setData(0,EntryType,0);
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
    treeWidget->sortByColumn(0,Qt::AscendingOrder);
}

void ExplorerWidget::showMenu(const QPoint &pos){
    if(treeWidget->itemAt(pos)==nullptr){
        menu->addAction("This is void");
    }else{
        qDebug() << pos << treeWidget->itemAt(pos)->text(0);
        if(treeWidget->itemAt(pos)->data(0,EntryType).toInt()==1){//if the right-clicked item is a File
            //menu->addAction("Move to new folder");
            menu->setFileOptions();
        }else if(treeWidget->itemAt(pos)->data(0,EntryType).toInt()==0){//if the right-clicked item is a Directory
            //menu->addAction("Open folder in new Tab");
            menu->setDirOptions();
        }
    }

    menu->exec(QCursor::pos());
}

void ExplorerWidget::openInNewTab(){
    qDebug() << "opened in new tab";
    emit openInNewTabSignal("lol");
}

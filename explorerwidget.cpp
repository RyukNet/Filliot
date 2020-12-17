#include "explorerwidget.h"

#include <QDebug>
#include <QDateTime>

const int EntryTypeRole = Qt::UserRole;
const int AbsPathRole = Qt::UserRole+1;

ExplorerWidget::ExplorerWidget(QWidget *parent, QString path) : QWidget(parent)
{
    //setting the layout and widgets to be rendered in the TabView
    vBoxLayout = new QVBoxLayout(this);
    vBoxLayout->setMargin(0);
    treeWidget = new QTreeWidget();
    treeWidget->setFrameShape(QFrame::NoFrame);//just changing the frame of the treeWidget
    vBoxLayout->addWidget(treeWidget);
    treeWidget->setColumnCount(3);
    treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    /***
     * TO DO : Remove Tree indicator in case of list like presentation
    ***/

    menu = new Menu(treeWidget);

    //dir = new QDir(QDir::currentPath());
    /*if(QString::compare("", path))
        dir = new QDir("D:/");
    else dir = new QDir(path);*/
    dir = new QDir(path);
    dir->setFilter(QDir::AllEntries | QDir::NoDot);
    fileIconProvider = new QFileIconProvider();

    updateTreeWidget();//first load
    connect(treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(cdInDirItem(QTreeWidgetItem*)));
    connect(treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showMenu(QPoint)));

    //Menu connecting :
    connect(menu,SIGNAL(openNewTabSignal(QString)),this,SLOT(openInNewTab(QString)));

}

void ExplorerWidget::addTreeItem(const QFileInfo fileInfo){
    QTreeWidgetItem *item = new QTreeWidgetItem(treeWidget);
    //item->QWidget::contextMenuEvent();
    item->setIcon(0,fileIconProvider->icon(fileInfo));
    item->setText(0, fileInfo.fileName());
    item->setText(1, fileInfo.birthTime().toString());
    if(fileInfo.isFile()){
        item->setData(0,EntryTypeRole,1);
        item->setData(2,Qt::DisplayRole,fileInfo.suffix());
        item->setData(0,AbsPathRole,fileInfo.absoluteFilePath());
    }else if(fileInfo.isDir()){
        item->setData(0,EntryTypeRole,0);
        item->setData(2,Qt::DisplayRole,"File folder");
        item->setData(0,AbsPathRole,fileInfo.absoluteFilePath());
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
        //qDebug() << pos << treeWidget->itemAt(pos)->text(0);
        if(treeWidget->itemAt(pos)->data(0,EntryTypeRole).toInt()==1){//if the right-clicked item is a File
            menu->setFileOptions();
        }else if(treeWidget->itemAt(pos)->data(0,EntryTypeRole).toInt()==0){//if the right-clicked item is a Directory
            menu->setAbsPath(treeWidget->itemAt(pos)->data(0,AbsPathRole).toString());
            menu->setDirOptions();
        }
    }

    menu->exec(QCursor::pos());
}

void ExplorerWidget::openInNewTab(QString path){
    //qDebug() << path;
    emit openInNewTabSignal(path);
}

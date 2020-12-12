#include "explorerwidget.h"

#include <QDebug>
#include <QDateTime>

ExplorerWidget::ExplorerWidget(QWidget *parent) : QWidget(parent)
{

    vBoxLayout = new QVBoxLayout(this);
    vBoxLayout->setMargin(0);
    treeWidget = new QTreeWidget();
    treeWidget->setFrameShape(QFrame::NoFrame);

    vBoxLayout->addWidget(treeWidget);

    treeWidget->setColumnCount(3);

    //dir = new QDir(QDir::currentPath());
    dir = new QDir("D:/");
    dir->setFilter(QDir::AllEntries | QDir::NoDot);
    fileIconProvider = new QFileIconProvider();

    updateTreeWidget();
    connect(treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(cdInDirItem(QTreeWidgetItem*)));

}


void ExplorerWidget::addTreeItem(const QFileInfo fileInfo){
    qDebug() << fileInfo.fileName();
    QTreeWidgetItem *item = new QTreeWidgetItem(treeWidget);
    item->setIcon(0,fileIconProvider->icon(fileInfo));
    item->setText(0, fileInfo.fileName());
    item->setText(1, fileInfo.birthTime().toString());
    if(fileInfo.isFile()){
        item->setData(2,Qt::DisplayRole,fileInfo.suffix());
    }else if(fileInfo.isDir()){
        item->setData(2,Qt::DisplayRole,tr("File folder"));
    }
    /**
      TODO: add data in items
      check QT::UserRole + {1|2|...}, QVariant, QMimeDatabase
     **/
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

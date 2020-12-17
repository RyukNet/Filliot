#ifndef EXPLORERWIDGET_H
#define EXPLORERWIDGET_H

#include <QWidget>
#include <QDir>
#include <QFileIconProvider>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include "menu.h"


class ExplorerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ExplorerWidget(QWidget *parent = nullptr, QString path = "/");
    //ExplorerWidget(QWidget *parent = nullptr,const QString path = "/");
private:
    QDir* dir;
    QFileIconProvider *fileIconProvider;

    QVBoxLayout *vBoxLayout;
    QTreeWidget *treeWidget;
    Menu *menu;

    void addTreeItem(const QFileInfo fileInfo);

private slots:
    void cdInDirItem(QTreeWidgetItem *item);
    void updateTreeWidget();
    void showMenu(const QPoint &pos);

    //slots going to mainwindow
    void openInNewTab(QString);

signals:
    void openInNewTabSignal(QString);
};

#endif // EXPLORERWIDGET_H

#ifndef EXPLORERWIDGET_H
#define EXPLORERWIDGET_H

#include <QWidget>
#include <QDir>
#include <QFileIconProvider>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>

class ExplorerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ExplorerWidget(QWidget *parent = nullptr);
private:
    QDir* dir;
    QFileIconProvider *fileIconProvider;

    QVBoxLayout *vBoxLayout;
    QTreeWidget *treeWidget;

    void addTreeItem(const QFileInfo fileInfo);

private slots:
    void cdInDirItem(QTreeWidgetItem *item);
    void updateTreeWidget();
signals:

};

#endif // EXPLORERWIDGET_H

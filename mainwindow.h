#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileIconProvider>
#include <QTreeWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QDir* dir;
    QFileIconProvider *fileIconProvider;

    void addTreeItem(const QFileInfo fileInfo);

private slots:
    void aboutDoubleClick(QTreeWidgetItem *item);
    void updateTreeWidget();

};
#endif // MAINWINDOW_H

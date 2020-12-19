#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileIconProvider>
#include <QTreeWidgetItem>

#include <QFileSystemModel>

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

    QFileSystemModel *fileSysModel;
private slots:
    void openFolderInNewTab(QString);
    void changeTabName(QString);

    void changeCurrentTabPath(QModelIndex index);
};
#endif // MAINWINDOW_H

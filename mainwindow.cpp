#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileSystem.setRootPath(QDir::currentPath());
    ui->treeWidget->QTreeView::setModel(&fileSystem);
}

MainWindow::~MainWindow()
{
    delete ui;
}


#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileInfo>
#include <QDebug>
#include <QTableWidgetItem>
#include <QDateTime>


#include "explorerwidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /***
     * TO ADD: Set the app start-up time according to settings data
     *
    ***/
    ui->setupUi(this);
    ui->splitter->setSizes(QList<int>{300,1000});

    ExplorerWidget *expWidget = new ExplorerWidget();

    ui->tabWidget->addTab(expWidget,"Herro");
}

MainWindow::~MainWindow()
{
    delete ui;
}

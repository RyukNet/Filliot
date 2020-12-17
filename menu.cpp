#include "menu.h"

#include <QDebug>

Menu::Menu(QWidget* parent): QMenu(parent)
{
    AbsPath = "";
    this->addAction("Open");
    this->addAction("Open in new window"); //Directory related
    this->addAction("Open in tab"); //Directory related
    connect(this->actions().at(2),SIGNAL(triggered()),this,SLOT(openInNewTab()));
    this->addSeparator();
    this->addAction("Copy");
    this->addAction("Paste");
    this->addAction("Copy to...");
    this->addAction("Put in new folder...");
    this->addSeparator();
    this->addAction("Copy path");
    this->addSeparator();
    this->addAction("Delete");
    this->addAction("Rename");
    this->addAction("Properties");

}

void Menu::setFileOptions(){
    this->actions().at(1)->setVisible(false);
    this->actions().at(2)->setVisible(false);
}

void Menu::setDirOptions(){
    this->actions().at(1)->setVisible(true);
    this->actions().at(2)->setVisible(true);
}

void Menu::openInNewTab(){
    qDebug() << "Opened !";
    emit openNewTabSignal(AbsPath);
}


void Menu::setAbsPath(const QString path){
    AbsPath = path;
}

QString Menu::absPath(){
    return  AbsPath;
}

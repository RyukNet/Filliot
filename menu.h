#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QMenu>

class Menu : public QMenu
{
    Q_OBJECT
public:
    explicit Menu(QWidget* parent = nullptr);
    void setFileOptions();
    void setDirOptions();
private slots:
    void openInNewTab();

signals:
    void openNewTabSignal();

};

#endif // MENU_H

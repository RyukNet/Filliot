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

    void setAbsPath(const QString path);
    QString absPath();

private :
    QString AbsPath;
private slots:

    void openInNewTab();

signals:
    void openNewTabSignal(QString path);

};

#endif // MENU_H

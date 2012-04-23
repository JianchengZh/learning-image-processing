#ifndef COLORDEPTHQWIDGET_H
#define COLORDEPTHQWIDGET_H

#include <QWidget>
#include "GUI/mainwindow.h"

class   MainWindow;

namespace Ui {
class ColorDepthQwidget;
}

class ColorDepthQwidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ColorDepthQwidget(QWidget *parent, MainController *controller, MainWindow *window);
    ~ColorDepthQwidget();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::ColorDepthQwidget *ui;
    MainController *mainController;
    MainWindow *mainwindow;
};

#endif // COLORDEPTHQWIDGET_H

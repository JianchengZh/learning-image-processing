#ifndef RESIZEQWIDGET_H
#define RESIZEQWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "CONTROLLER/maincontroller.h"

namespace Ui {
class ResizeQwidget;
}

class ResizeQwidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ResizeQwidget(QWidget *parent, MainController *controller);
    ~ResizeQwidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ResizeQwidget *ui;
    MainController *mainController;
};

#endif // RESIZEQWIDGET_H

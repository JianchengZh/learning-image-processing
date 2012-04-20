#ifndef RESIZEQWIDGET_H
#define RESIZEQWIDGET_H

#include <QWidget>

namespace Ui {
class ResizeQwidget;
}

class ResizeQwidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ResizeQwidget(QWidget *parent = 0);
    ~ResizeQwidget();
    
private:
    Ui::ResizeQwidget *ui;
};

#endif // RESIZEQWIDGET_H

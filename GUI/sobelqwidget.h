#ifndef SOBELQWIDGET_H
#define SOBELQWIDGET_H

#include <QWidget>

namespace Ui {
class SobelQwidget;
}

class SobelQwidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SobelQwidget(QWidget *parent = 0);
    ~SobelQwidget();
    
private:
    Ui::SobelQwidget *ui;
};

#endif // SOBELQWIDGET_H

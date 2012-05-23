#ifndef CONVOLUTIONQWIDGET_H
#define CONVOLUTIONQWIDGET_H

#include <QWidget>

namespace Ui {
class ConvolutionQwidget;
}

class ConvolutionQwidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ConvolutionQwidget(QWidget *parent = 0);
    ~ConvolutionQwidget();
    
private:
    Ui::ConvolutionQwidget *ui;
};

#endif // CONVOLUTIONQWIDGET_H

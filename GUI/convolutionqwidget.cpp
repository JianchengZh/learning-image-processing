#include "convolutionqwidget.h"
#include "ui_convolutionqwidget.h"

ConvolutionQwidget::ConvolutionQwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConvolutionQwidget)
{
    ui->setupUi(this);
}

ConvolutionQwidget::~ConvolutionQwidget()
{
    delete ui;
}

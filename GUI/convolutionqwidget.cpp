#include "convolutionqwidget.h"
#include "ui_convolutionqwidget.h"

ConvolutionQwidget::ConvolutionQwidget(QWidget *parent, MainController *controller, MainWindow *window) :
    QWidget(parent),
    ui(new Ui::ConvolutionQwidget)
{
    ui->setupUi(this);
    mainwindow=window;
    mainController=controller;
}

ConvolutionQwidget::~ConvolutionQwidget()
{
    delete ui;
}

#include "colordepthqwidget.h"
#include "ui_colordepthqwidget.h"

ColorDepthQwidget::ColorDepthQwidget(QWidget *parent, MainController *controller, MainWindow *window) :
    QWidget(parent),
    ui(new Ui::ColorDepthQwidget)
{
    ui->setupUi(this);
    mainController=controller;
    mainwindow=window;
}

ColorDepthQwidget::~ColorDepthQwidget()
{
    delete ui;
}

void ColorDepthQwidget::on_pushButton_clicked()
{
    int depth = (int)ui->lcdNumber->value();
    mainwindow->displayResults(mainController->changeColorDepth(depth));
}

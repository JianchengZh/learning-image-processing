#include "resizeqwidget.h"
#include "ui_resizeqwidget.h"

ResizeQwidget::ResizeQwidget(QWidget *parent, MainController *controller, MainWindow *window) :
    QWidget(parent),
    ui(new Ui::ResizeQwidget)
{
    ui->setupUi(this);
    mainController=controller;
    mainwindow=window;
}

ResizeQwidget::~ResizeQwidget()
{
    delete ui;
}

void ResizeQwidget::on_pushButton_clicked()
{
        int density = (int)ui->lcdNumber->value();
        mainwindow->displayResults(mainController->changeSize(density));

}

#include "resizeqwidget.h"
#include "ui_resizeqwidget.h"

ResizeQwidget::ResizeQwidget(QWidget *parent, MainController *controller) :
    QWidget(parent),
    ui(new Ui::ResizeQwidget)
{
    ui->setupUi(this);
    mainController=controller;
}

ResizeQwidget::~ResizeQwidget()
{
    delete ui;
}

void ResizeQwidget::on_pushButton_clicked()
{
        int density = (int)ui->lcdNumber->value();
        mainController->changeSize(density);
}

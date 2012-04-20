#include "resize.h"
#include "ui_resize.h"

Resize::Resize(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Resize)
{
    ui->setupUi(this);
}

Resize::~Resize()
{
    delete ui;
}

void Resize::on_pushButton_clicked()
{

}

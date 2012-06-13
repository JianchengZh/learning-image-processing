#include "sobelqwidget.h"
#include "ui_sobelqwidget.h"

SobelQwidget::SobelQwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SobelQwidget)
{
    ui->setupUi(this);
}

SobelQwidget::~SobelQwidget()
{
    delete ui;
}

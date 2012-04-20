#include "resizeqwidget.h"
#include "ui_resizeqwidget.h"

ResizeQwidget::ResizeQwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResizeQwidget)
{
    ui->setupUi(this);
}

ResizeQwidget::~ResizeQwidget()
{
    delete ui;
}

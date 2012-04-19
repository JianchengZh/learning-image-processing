//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// PGM_PPM_IMAGE_PROCESSING_V2
//
// ARCHIVO: resultwindow.cpp
//
// FECHA INICIACION: Marzo de 2012
//
// AUTORES:
// Gustavo Adolfo Rodriguez         0932979-3743
// gustalibreros@hotmail.com
//
// Edwin Fernando Muñoz             0910398-3743
// edwinfernandomudelgado@hotmail.com
//
// ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION
// UNIVERSIDAD DEL VALLE
//**********************************************************

#include "resultwindow.h"
#include "ui_resultwindow.h"


ResultWindow::ResultWindow(QWidget *parent, QString image) :
    QDialog(parent),
    ui(new Ui::Export)
{
    ui->setupUi(this);
    this->temImageFile=image;
    this->controller= new ResultController(temImageFile);
    showImage();
}

ResultWindow::~ResultWindow()
{
    delete ui;
}

void ResultWindow::showImage(){
    this->qImage= new QImage(temImageFile);
    ui->label_imagen->setPixmap(QPixmap::fromImage(QImage(temImageFile)));
}

void ResultWindow::on_pButton_Save_clicked()
{

    QString filename = QFileDialog::getSaveFileName(this, tr("Save Image"), "../LEARNING_IMAGE_PROCESSING/IMAGES", tr("Images (*.ppm *.pgm)"));
    controller->saveImage(filename);
    this->close();
}

void ResultWindow::on_pushButton_adjust_clicked()
{
    ui->label_imagen->setPixmap(QPixmap::fromImage(this->qImage->scaled(QSize(550,410),Qt::KeepAspectRatio)));
}

void ResultWindow::on_pushButton_normalS_clicked()
{
    ui->label_imagen->setPixmap(QPixmap::fromImage(*this->qImage));
}


//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
//
// FECHA INICIACION: Marzo de 2012
//
// AUTORES:
// Gustavo Adolfo Rodriguez         0932979-3743
// gustalibreros@gmail.com
//
// Edwin Fernando Muñoz             0910398-3743
// edwinfernandomudelgado@gmail.com
//
// Yerminson Doney Gonzalez         0843846-3743
// yermigon@gmail.com
//
// Edgar Andrés Moncada             0832294-3743
// edgarandres29@gmail.com
//
// ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION
// UNIVERSIDAD DEL VALLE
//**********************************************************

#include "structureelementqwidget.h"
#include "ui_structureelementqwidget.h"

StructureElementQwidget::StructureElementQwidget(QWidget *parent, MainController *controller, MainWindow *window) :
    QWidget(parent),
    ui(new Ui::StructureElementQwidget)
{
    ui->setupUi(this);
    mainwindow=window;
    mainController=controller;
    qLineEditMatrix=NULL;
    on_spinBox_valueChanged(3,3);

}

StructureElementQwidget::~StructureElementQwidget()
{
    deleteTable();
    delete ui;
}

void StructureElementQwidget::on_spinBox_valueChanged(int arg1, int arg2)
{
    if (qLineEditMatrix != NULL) {
        deleteTable();
    }

    heigthS = arg1;
    widthS = arg2;
    double widthLineEdit = 30;
    double heightLineEdit = 25;
    double widthTable = widthS * (widthLineEdit + 3);
    double heightTable = heigthS * (heightLineEdit + 3);
    int initialX = (ui->widgetTable->width() - widthTable) / 2;
    int initialY = (ui->widgetTable->height() - heightTable) / 2;


    qLineEditMatrix = new QLineEdit**[heigthS];

    for (int i = 0; i < heigthS; ++i) {
        qLineEditMatrix[i]= new QLineEdit*[widthS];
    }

    QFont font;
    font.setPointSize(10);
    for (int i = 0; i < heigthS; ++i) {
        int x=initialX;
        for (int j = 0; j < widthS; ++j) {
            qLineEditMatrix[i][j] = new QLineEdit(ui->widgetTable);
            qLineEditMatrix[i][j]->setGeometry(QRect(x, initialY, widthLineEdit, heightLineEdit));
            qLineEditMatrix[i][j]->setFont(font);
            qLineEditMatrix[i][j]->setVisible(true);
            x += widthLineEdit + 3;
        }
        initialY += heightLineEdit + 3;
    }
}

void StructureElementQwidget::deleteTable(){

    for (int i = 0; i < heigthS; ++i) {
        for (int j = 0; j < widthS; ++j) {
            delete qLineEditMatrix[i][j];
            qLineEditMatrix[i][j]=0;
        }
        delete qLineEditMatrix[i];
        qLineEditMatrix[i]=0;
    }
    delete qLineEditMatrix;
    qLineEditMatrix=0;
}

void StructureElementQwidget::on_pushButton_clicked(){
    int origenX=1,origenY=1;
    int **kernel = new int*[heigthS];

    for (int i = 0; i < heigthS; ++i) {
        kernel[i]=new int[widthS];
    }

    for (int i = 0; i < heigthS; ++i) {
        for (int j = 0; j < widthS; ++j) {
            kernel[i][j]=qLineEditMatrix[i][j]->text().toInt();
        }
    }

    mainController->morphologicalOperation(kernel,origenX,origenY,heigthS,widthS);
    mainwindow->displayResults(mainController->getQImage());
}

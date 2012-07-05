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

#include <QtGui/QApplication>
#include <QDesktopWidget>
#include "GUI/mainwindow.h"

void center(QWidget & widget)
{
    QRect windowSize = QApplication::desktop() -> frameGeometry();

    int x = (windowSize.width() - widget.frameGeometry().width()) / 2;
    int y = (windowSize.height() - widget.frameGeometry().height()) / 2;

    widget.move(x, y);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    center(w);
    return a.exec();
}


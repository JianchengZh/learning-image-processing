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

#ifndef CUSTOMQLABEL_H
#define CUSTOMQLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QPoint>
#include <QDebug>
#include <QWidget>


class CustomQLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomQLabel(QWidget *parent = 0);
        
public slots:
    
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void drawLine(QPoint start, QPoint end);
    void eraseLine();
    void mousePosition(QPoint position);

private:
    QPoint startPoint, endPoint;
};

#endif // CUSTOMQLABEL_H

#include "customqlabel.h"

CustomQLabel::CustomQLabel(QWidget *parent) :
    QLabel(parent)
{
}

void CustomQLabel::mousePressEvent(QMouseEvent *event){

//    qDebug()<<"Coordenadas: X= "<<event->x()<<" Y= "<<event->y();
    startPoint= QPoint(event->x(), event->y());
    if (this->pixmap()!=0) {
        emit eraseLine();
    }
}

void CustomQLabel::mouseMoveEvent(QMouseEvent *event){

    endPoint= QPoint(event->x(), event->y());
    if (this->pixmap()!=0) {
        emit eraseLine();
        emit drawLine(startPoint, endPoint);
    }

}

void CustomQLabel::mouseReleaseEvent(QMouseEvent *event){

    endPoint= QPoint(event->x(), event->y());

    if (this->pixmap()!=0) {
        emit drawLine(startPoint, endPoint);
    }

}

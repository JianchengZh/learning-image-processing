#include "customqlabel.h"

CustomQLabel::CustomQLabel(QWidget *parent) :
    QLabel(parent)
{
    startPoint = QPoint(-1,-1);
    setMouseTracking(true);
}

void CustomQLabel::mousePressEvent(QMouseEvent *event){

    startPoint= QPoint(event->x(), event->y());
    if (this->pixmap()!=0) {
        emit eraseLine();
    }
}

void CustomQLabel::mouseMoveEvent(QMouseEvent *event){

    endPoint= QPoint(event->x(), event->y());
    emit mousePosition(endPoint);
    if (this->pixmap()!=0 && startPoint!= QPoint(-1,-1)) {
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

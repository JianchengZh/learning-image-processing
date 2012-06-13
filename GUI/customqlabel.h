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

private:
    QPoint startPoint, endPoint;
};

#endif // CUSTOMQLABEL_H

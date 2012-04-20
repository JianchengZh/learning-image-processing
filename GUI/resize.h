#ifndef RESIZE_H
#define RESIZE_H

#include <QWidget>

namespace Ui {
class Resize;
}

class Resize : public QWidget
{
    Q_OBJECT
    
public:
    explicit Resize(QWidget *parent = 0);
    ~Resize();


private slots:
    void on_pushButton_clicked();

private:
    Ui::Resize *ui;
};

#endif // RESIZE_H

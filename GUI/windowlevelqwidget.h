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

#ifndef WINDOWLEVELQWIDGET_H
#define WINDOWLEVELQWIDGET_H

#include <QWidget>
#include "GUI/mainwindow.h"

class   MainWindow;


namespace Ui {
class WindowLevelQWidget;
}

class WindowLevelQWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit WindowLevelQWidget(QWidget *parent, MainController *controller, MainWindow *window);
    ~WindowLevelQWidget();
    
private slots:
    void on_comboBoxPresets_currentIndexChanged(const QString &arg1);

    void on_verticalSliderLevel_valueChanged(int value);

    void on_verticalSliderWindow_valueChanged(int value);

private:
    Ui::WindowLevelQWidget *ui;
    MainController *mainController;
    MainWindow *mainwindow;
};

#endif // WINDOWLEVELQWIDGET_H

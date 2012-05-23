#include "convolutionqwidget.h"
#include "ui_convolutionqwidget.h"

ConvolutionQwidget::ConvolutionQwidget(QWidget *parent, MainController *controller, MainWindow *window) :
    QWidget(parent),
    ui(new Ui::ConvolutionQwidget)
{
    ui->setupUi(this);
    mainwindow=window;
    mainController=controller;
    on_spinBox_valueChanged(3);
}

ConvolutionQwidget::~ConvolutionQwidget()
{
    delete ui;
}

void ConvolutionQwidget::on_spinBox_valueChanged(int arg1)
{
    kernelSize = arg1;
    double widthLineEdit = 30;
    double heightLineEdit = 25;
    double widthTable = kernelSize * (widthLineEdit + 3);
    double heightTable = kernelSize * (heightLineEdit + 3);
    int initialX = (ui->widgetTable->width() - widthTable) / 2;
    int initialY = (ui->widgetTable->height() - heightTable) / 2;
    int x;

    QLineEdit ***lineEditKernel = new QLineEdit**[kernelSize];

    for (int i = 0; i < kernelSize; ++i) {
        lineEditKernel[i]= new QLineEdit*[kernelSize];
    }

    QTextStream (stdout)<<"voy por aqui"<<endl;
    QFont font;
    font.setPointSize(10);
    for (int i = 0; i < kernelSize; ++i) {
        int x=initialX;
        for (int j = 0; j < kernelSize; ++j) {
            lineEditKernel[i][j] = new QLineEdit(ui->widgetTable);
            lineEditKernel[i][j]->setGeometry(QRect(x, initialY, widthLineEdit, heightLineEdit));
            lineEditKernel[i][j]->setFont(font);
            lineEditKernel[i][j]->setVisible(true);
            x += widthLineEdit + 3;
        }
        initialY += heightLineEdit + 3;
    }
}

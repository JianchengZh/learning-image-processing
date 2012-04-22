//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: mainwindow.cpp
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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    mainController= new MainController();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Buttons Events
void MainWindow::on_pButton_LoadImage_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "../LEARNING_IMAGE_PROCESSING/IMAGES", tr("Image Files (*)"));
    if (mainController->loadImage(filename)) {

        // Changes on PushButtons:
        ui->pButton_LoadImage->setEnabled(false);
        ui->pButton__AdjustImageSize->setEnabled(true);
        ui->pButton__NormalSize->setEnabled(true);

        // Changes on labels
        ui->label_Density->setEnabled(true);
        ui->label_Dimensions->setEnabled(true);
        ui->label_ImageType->setEnabled(true);

        // Set text on Labels:
        ui->label_DimensionsValue->setText("W:"+QString::number(mainController->getImage()->getColumnNumber())+
                                           "  H:"+QString::number(mainController->getImage()->getRowNumber()));
        ui->label_DensityValue->setText(QString::number(log2(mainController->getImage()->getColorDensity()+1))+" Bits");
        ui->label_ImageTypeValue->setText(mainController->getImage()->getImageType());

        // Set Image to label_Imagen
        qImage=new QImage(filename);

        // Display Image in Original Size
        on_pButton__NormalSize_clicked();

        if (mainController->getImage()->getImageType().toUpper()=="PGM") {
            QImage *histograma = mainController->generateHistogram();
            ui->label_Histogram->setPixmap(QPixmap::fromImage(histograma->scaled(QSize(250,100), Qt::IgnoreAspectRatio)));
        }

    } else {
        //Falta mostar algo cuando la imagen no pudo ser cargada!!
    }
}

void MainWindow::on_pButton__AdjustImageSize_clicked()
{
    ui->label_Imagen->setGeometry(QRect(0, 0, 733, 550));
    ui->scrollAreaWidgetContents->setGeometry(QRect(0, 0, 733, 550));
    ui->label_Imagen->setPixmap(QPixmap::fromImage(this->qImage->scaled(QSize(733, 550),Qt::KeepAspectRatio)));
}

void MainWindow::on_pButton__NormalSize_clicked()
{
    if(qImage->width()>ui->label_Imagen->width() || qImage->height()>ui->label_Imagen->height()){
        ui->label_Imagen->setGeometry(QRect(0, 0, qImage->width(), qImage->height()));
        ui->scrollAreaWidgetContents->setGeometry(QRect(0, 0, qImage->width(), qImage->height()));
    }
    ui->label_Imagen->setPixmap(QPixmap::fromImage(*qImage));
}

// MenuBar Events

// File Menu
void MainWindow::on_actionNew_Job_triggered()
{
    // Changes on PushButtons:
    ui->pButton_LoadImage->setEnabled(true);
    ui->pButton__AdjustImageSize->setEnabled(false);
    ui->pButton__NormalSize->setEnabled(false);

    // Changes on labels
    ui->label_Density->setEnabled(false);
    ui->label_Dimensions->setEnabled(false);
    ui->label_ImageType->setEnabled(false);

    // changes in the text on Labels:
    ui->label_DensityValue->setText("");
    ui->label_DimensionsValue->setText("");
    ui->label_ImageTypeValue->setText("");

    // Erase Image
    ui->label_Imagen->setPixmap(0);
    ui->label_Histogram->setPixmap(0);

    // delete widget_options
    ui->widget_options->deleteLater();


    mainController->newJob();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

// Edit Menu

// Preprocessing Menu
void MainWindow::on_actionResize_triggered()
{
    if (ui->widget_options->objectName()=="widget_resize") {
        ui->widget_options->deleteLater();
    }
    ui->widget_options = new ResizeQwidget(ui->centralWidget, mainController);
    ui->widget_options->setObjectName(QString::fromUtf8("widget_resize"));
    ui->widget_options->setGeometry(QRect(770, 70, 270, 331));
    ui->widget_options->setVisible(true);

}

// Histogram Menu

// Tomography Menu

// Help Menu
void MainWindow::on_actionAbout_triggered()
{
    DialogAbout about(this);
    about.setModal(true);
    about.exec();
}





// Image Processing
//void MainWindow::on_pButton_PixelDensity_clicked(){
//    ui->label_Messages->setText("Changing the size of the image...");
//    int density = ui->comboBox_size->currentText().left(2).toInt();
//    showResultWindow(mainController->pixelDensityChanged(density));
//    ui->label_Messages->setText("");
//}

//void MainWindow::on_pButton_ColorDensity_clicked(){
//    ui->label_Messages->setText("Changing the Color Density of the image...");
//   // int intensidad = ui->comboBox_color->currentText().left(1).toInt();
//   // showResultWindow(mainController->colorDensityChanged(intensidad));
//    int treshold = ui->lineEdit->text().toInt();
//    ui->label_Messages->setText("");
//}

//void MainWindow::on_pButton_ConvertGrayscale_clicked(){
//    ui->label_Messages->setText("Converting the image to grayscale...");
//    showResultWindow(mainController->convertGrayscale());
//    ui->label_Messages->setText("");
//}

//// OTHER EVENTS
//void MainWindow::showResultWindow(QString imageFile){
//    ResultWindow exportWindow(this, imageFile);
//    exportWindow.setModal(true);
//    exportWindow.exec();
//}

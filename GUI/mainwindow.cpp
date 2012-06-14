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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->widget_options=0;
    displayedImage=0;
    histogramImage=0;
    mainController= new MainController();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//**********************************************************
//**********************************************************
// Buttons Events
//**********************************************************
//**********************************************************
void MainWindow::on_pButton_LoadImage_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "../LEARNING_IMAGE_PROCESSING/IMAGES", tr("Image Files (*)"));
    if (!fileName.isEmpty()){
        if (mainController->loadImage(fileName)) {

            // Changes on PushButtons:
            ui->pButton_LoadImage->setEnabled(false);
            ui->pButton__NormalSize->setEnabled(true);

            //Enable QActions
            ui->actionNew_Job->setEnabled(true);
            ui->actionUndo->setEnabled(true);
            ui->actionResize->setEnabled(true);
            ui->actionChange_Color_Depth->setEnabled(true);
            ui->actionSave->setEnabled(true);

            if (mainController->getImage()->getImageType().toUpper()=="PPM") {
                ui->actionConver_to_GrayScale->setEnabled(true);
                ui->actionEqualization->setEnabled(true);
            }

            if (mainController->getImage()->getImageType().toUpper()=="PGM") {
                ui->actionWeight_Average->setEnabled(true);
                ui->actionAdd->setEnabled(true);
                ui->actionSubstract->setEnabled(true);
                ui->actionMultiply->setEnabled(true);
                ui->actionDivide->setEnabled(true);
                ui->actionThreshold->setEnabled(true);
                ui->actionEqualization->setEnabled(true);
                ui->actionMean->setEnabled(true);
                ui->actionConvolution->setEnabled(true);
                ui->actionGaussiana->setEnabled(true);
                ui->actionStretching->setEnabled(true);
                ui->actionGamma_Correction->setEnabled(true);
                ui->actionNoise_Cleaning_Pixel->setEnabled(true);
                ui->actionNoise_Cleaning_Line->setEnabled(true);
                ui->actionSobel->setEnabled(true);
                ui->actionCanny->setEnabled(true);
            }
            if(mainController->getImage()->getImageType().toUpper()=="DCM"){
                ui->actionWindow_Level->setEnabled(true);
            }


            // Changes on labels
            ui->label_Density->setEnabled(true);
            ui->label_Dimensions->setEnabled(true);
            ui->label_ImageType->setEnabled(true);

            // Set text on Labels with image info
            ui->label_DimensionsValue->setText("W: "+QString::number(mainController->getImage()->getWidth())+"P"+
                                               "  H: "+QString::number(mainController->getImage()->getHeight())+"P");
            ui->label_DensityValue->setText(QString::number(log2(mainController->getImage()->getColorDepth()+1))+" Bits");
            ui->label_ImageTypeValue->setText(mainController->getImage()->getImageType());

            // Set Image to label_Imagen
            displayedImage=mainController->getQImage();

            // Display Image in Original Size
            on_pButton__NormalSize_clicked();
            ShowHistogram();


        } else {
            QMessageBox msgBox(this);
            msgBox.setText("Sorry, but the selected file is not supported");
            msgBox.exec();
            delete mainController;
            mainController=0;
        }
    }
}

void MainWindow::on_pButton__NormalSize_clicked()
{
    // if width and height of the image are bigger than the display Area
    if(displayedImage->width()>ui->scrollAreaWidgetContents->width() && displayedImage->height()>ui->scrollAreaWidgetContents->height()){
        ui->label_Imagen->setGeometry(QRect(0, 0, displayedImage->width(), displayedImage->height()));
        ui->scrollAreaWidgetContents->setGeometry(QRect(0, 0, displayedImage->width(), displayedImage->height()));
    }

    // if just the width is bigger than the display area
    else if (displayedImage->width()>ui->scrollAreaWidgetContents->width()) {
        int yPos = (ui->scrollAreaWidgetContents->height() - displayedImage->height())/2;
        ui->label_Imagen->setGeometry(QRect(0, yPos, displayedImage->width(), displayedImage->height()));
        ui->scrollAreaWidgetContents->setGeometry(QRect(0, 0, displayedImage->width(), ui->scrollAreaWidgetContents->height()));
    }

    // if just the height is bigger than the display area
    else if (displayedImage->height()>ui->scrollAreaWidgetContents->height()) {
        int xPos = (ui->scrollAreaWidgetContents->width() - displayedImage->width())/2;
        ui->label_Imagen->setGeometry(QRect(xPos, 0, displayedImage->width(), displayedImage->height()));
        ui->scrollAreaWidgetContents->setGeometry(QRect(0, 0, ui->scrollAreaWidgetContents->width(), displayedImage->height()));
    }

    // if any of the cases above
    else{
        int xPos = (ui->scrollAreaWidgetContents->width() - displayedImage->width())/2;
        int yPos = (ui->scrollAreaWidgetContents->height() - displayedImage->height())/2;
        ui->label_Imagen->setGeometry(QRect(xPos, yPos, displayedImage->width(), displayedImage->height()));
    }

    ui->label_Imagen->setPixmap(QPixmap::fromImage(*displayedImage));
    pixmapLabelImagen=*ui->label_Imagen->pixmap();

}

//**********************************************************
//**********************************************************
// MenuBar Events
//**********************************************************
//**********************************************************

//**********************************************************
// File Menu
//**********************************************************
void MainWindow::on_actionNew_Job_triggered()
{
    // Changes on PushButtons:
    ui->pButton_LoadImage->setEnabled(true);
    ui->pButton__NormalSize->setEnabled(false);

    //Disable QActions
    ui->actionNew_Job->setEnabled(false);
    ui->actionUndo->setEnabled(false);
    ui->actionResize->setEnabled(false);
    ui->actionChange_Color_Depth->setEnabled(false);
    ui->actionConver_to_GrayScale->setEnabled(false);
    ui->actionThreshold->setEnabled(false);
    ui->actionWeight_Average->setEnabled(false);
    ui->actionAdd->setEnabled(false);
    ui->actionSubstract->setEnabled(false);
    ui->actionMultiply->setEnabled(false);
    ui->actionDivide->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->actionMean->setEnabled(false);
    ui->actionConvolution->setEnabled(false);
    ui->actionGaussiana->setEnabled(false);
    ui->actionWindow_Level->setEnabled(false);
    ui->actionSobel->setEnabled(false);
    ui->actionCanny->setEnabled(false);
    //ui->actionNoise_Cleaning_Line-setEnabled(false);
    //ui->actionNoise_Cleaning_Pixel-setEnabled(false);
    //ui->actionStretching-setEnabled(false);
    //ui->actionGamma_Correction-setEnabled(false);


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
    ui->label_Imagen->setGeometry(QRect(0, 0, 733, 550));
    ui->scrollAreaWidgetContents->setGeometry(QRect(0, 0, 733, 550));

    // delete widget_options
    delete ui->widget_options;
    ui->widget_options=0;

    delete histogramImage;
    histogramImage=0;

    delete displayedImage;
    displayedImage=0;

    delete mainController;
    mainController=0;
    mainController=new MainController();
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Image"),
                                                    QString(getenv("HOME")),
                                                    tr("Image Files (*)"));
    if (!fileName.isEmpty())
        mainController->saveImage(fileName);
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

//**********************************************************
// Edit Menu
//**********************************************************
void MainWindow::on_actionUndo_triggered()
{
    if (mainController->undo()) {
        displayedImage=mainController->getQImage();
        ShowHistogram();
        on_pButton__NormalSize_clicked();
    }else{
        QMessageBox msgBox2(this);
        msgBox2.setText("Sorry, but there is nothing to undo");
        msgBox2.exec();
    }

}

//**********************************************************
// Global Transfomations Menu
//**********************************************************
void MainWindow::on_actionResize_triggered()
{
    if (ui->widget_options!=0) {
        delete ui->widget_options;
        ui->widget_options=0;
    }
    ui->widget_options = new ResizeQwidget(ui->centralWidget, mainController, this);
    ui->widget_options->setGeometry(QRect(770, 70, 270, 331));
    ui->widget_options->setVisible(true);

}

void MainWindow::on_actionChange_Color_Depth_triggered()
{
    if (ui->widget_options!=0) {
        delete ui->widget_options;
        ui->widget_options=0;
    }
    ui->widget_options = new ColorDepthQwidget(ui->centralWidget, mainController, this, log2(mainController->getImage()->getColorDepth()+1));
    ui->widget_options->setGeometry(QRect(770, 70, 270, 331));
    ui->widget_options->setVisible(true);
}

void MainWindow::on_actionConver_to_GrayScale_triggered()
{
    if(mainController->isThereAnUploadedImage()  && mainController->getImage()->getImageType()=="PPM"){
        QMessageBox msgBox(this);
        msgBox.setText("do you want to give the same weight to all color channels?");
        msgBox.setStandardButtons(QMessageBox::Yes| QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int method = msgBox.exec();
        mainController->convertToGrayscale(method);
        displayResults(mainController->getQImage());
        //        ShowHistogram();
    }else {
        QMessageBox msgBox2(this);
        msgBox2.setText("Sorry,Operation not valid");
        msgBox2.setWindowTitle("ERROR");
        msgBox2.exec();
    }
}

void MainWindow::on_actionWeight_Average_triggered()
{
    QErrorMessage *erroMessageDialog = new QErrorMessage(this);
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "../LEARNING_IMAGE_PROCESSING/IMAGES", tr("Image Files (*)"));
    if(filename.right(3).toUpper()=="PGM"){
        bool ok;
        double alpha = QInputDialog::getDouble(this, tr("Sum of Images"),tr("Alpha:"), 0.5, 0, 1, 1, &ok);
        if (ok){
            if (mainController->average(filename, alpha)) {
                displayResults(mainController->getQImage());
                //                ShowHistogram();
            } else {
                erroMessageDialog->showMessage("Imagen no apropiada para realiza dicha operacion");
            }

        }else{
            erroMessageDialog->showMessage("No se ha ingresado ningun valor para Alpha");
        }
    }else{
        erroMessageDialog->showMessage("Formato de imagen no apropiado");
    }
}

void MainWindow::on_actionAdd_triggered()
{
    QErrorMessage *erroMessageDialog = new QErrorMessage(this);
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "../LEARNING_IMAGE_PROCESSING/IMAGES", tr("Image Files (*)"));
    if(filename.right(3).toUpper()=="PGM"){
        if (mainController->add(filename)) {
            displayResults(mainController->getQImage());
            ShowHistogram();
        } else {
            erroMessageDialog->showMessage("Imagen no apropiada para realiza dicha operacion");
        }
    }else{
        erroMessageDialog->showMessage("Formato de imagen no apropiado");
    }
}

void MainWindow::on_actionSubstract_triggered()
{
    QErrorMessage *erroMessageDialog = new QErrorMessage(this);
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "../LEARNING_IMAGE_PROCESSING/IMAGES", tr("Image Files (*)"));
    if(filename.right(3).toUpper()=="PGM"){
        if (mainController->subtract(filename)) {
            displayResults(mainController->getQImage());
            ShowHistogram();
        } else {
            erroMessageDialog->showMessage("Imagen no apropiada para realiza dicha operacion");
        }
    }else{
        erroMessageDialog->showMessage("Formato de imagen no apropiado");
    }
}

void MainWindow::on_actionMultiply_triggered()
{
    QErrorMessage *erroMessageDialog = new QErrorMessage(this);
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "../LEARNING_IMAGE_PROCESSING/IMAGES", tr("Image Files (*)"));
    if(filename.right(3).toUpper()=="PGM"){
        if (mainController->multiply(filename)) {
            displayResults(mainController->getQImage());
            ShowHistogram();
        } else {
            erroMessageDialog->showMessage("Imagen no apropiada para realiza dicha operacion");
        }
    }else{
        erroMessageDialog->showMessage("Formato de imagen no apropiado");
    }
}

void MainWindow::on_actionDivide_triggered()
{
    QErrorMessage *erroMessageDialog = new QErrorMessage(this);
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "../LEARNING_IMAGE_PROCESSING/IMAGES", tr("Image Files (*)"));
    if(filename.right(3).toUpper()=="PGM"){
        if (mainController->divide(filename)) {
            displayResults(mainController->getQImage());
            ShowHistogram();
        } else {
            erroMessageDialog->showMessage("Imagen no apropiada para realiza dicha operacion");
        }
    }else{
        erroMessageDialog->showMessage("Formato de imagen no apropiado");
    }
}

//**********************************************************
// Histogram Menu
//**********************************************************
void MainWindow::on_actionThreshold_triggered()
{
    if (ui->widget_options!=0) {
        delete ui->widget_options;
        ui->widget_options=0;
    }
    ui->widget_options = new ThresholdQwidget(ui->centralWidget, mainController, this);
    ui->widget_options->setGeometry(QRect(770, 70, 270, 331));
    ui->widget_options->setVisible(true);
}

void MainWindow::on_actionEqualization_triggered()
{
    if(mainController->isThereAnUploadedImage()  && mainController->getImage()->getImageType()=="PGM"){
        mainController->equalizateHistogram();
        displayResults(mainController->getQImage());
        ShowHistogram();
    }else {
        QMessageBox msgBox2(this);
        msgBox2.setText("Sorry,Operation not valid");
        msgBox2.setWindowTitle("ERROR");
        msgBox2.exec();
    }
}

//**********************************************************
// Filters Menu
//**********************************************************
void MainWindow::on_actionMean_triggered()
{
    if(mainController->isThereAnUploadedImage()  && mainController->getImage()->getImageType()=="PGM"){

        QStringList items;
        items << tr("3x3") << tr("5x5") << tr("9x9");

        bool ok;
        QString item = QInputDialog::getItem(this, tr("Select Ker"),
                                             tr("Kernel Size:"), items, 0, false, &ok);
        if (ok && !item.isEmpty()){
            if(item=="3x3"){
                mainController->meanFilter(3);
            }else if(item=="5x5"){
                mainController->meanFilter(5);
            }else{
                mainController->meanFilter(9);
            }
            displayResults(mainController->getQImage());
            ShowHistogram();
        }

    }else {
        QMessageBox msgBox2(this);
        msgBox2.setText("Sorry,Operation not valid");
        msgBox2.setWindowTitle("ERROR");
        msgBox2.exec();
    }
}

void MainWindow::on_actionConvolution_triggered()
{
    if (ui->widget_options!=0) {
        delete ui->widget_options;
        ui->widget_options=0;
    }
    ui->widget_options = new ConvolutionQwidget(ui->centralWidget, mainController, this);
    ui->widget_options->setGeometry(QRect(770, 70, 270, 331));
    ui->widget_options->setVisible(true);
}

void MainWindow::on_actionGaussiana_triggered()
{
    if(mainController->isThereAnUploadedImage()  && mainController->getImage()->getImageType()=="PGM"){

        QStringList items;
        items << tr("3x3") << tr("5x5") << tr("9x9");

        bool ok;
        QString item = QInputDialog::getItem(this, tr("Select Ker"),
                                             tr("Kernel Size:"), items, 0, false, &ok);
        if (ok && !item.isEmpty()){
            if(item=="3x3"){
                mainController->gaussianaFilter(1.0,3);
            }else if(item=="5x5"){
                mainController->gaussianaFilter(1.0,5);
            }else{
                mainController->gaussianaFilter(1.0,9);
            }
            displayResults(mainController->getQImage());
            ShowHistogram();
        }

    }else {
        QMessageBox msgBox2(this);
        msgBox2.setText("Sorry,Operation not valid");
        msgBox2.setWindowTitle("ERROR");
        msgBox2.exec();
    }
}

void MainWindow::on_actionNoise_Cleaning_Line_triggered()
{

}

void MainWindow::on_actionNoise_Cleaning_Pixel_triggered()
{

}

//**********************************************************
// Contrast Menu
//**********************************************************
void MainWindow::on_actionGamma_Correction_triggered()
{

}

void MainWindow::on_actionStretching_triggered()
{

}

//**********************************************************
// Edge Detection Menu
//**********************************************************
void MainWindow::on_actionSobel_triggered()
{
    if (ui->widget_options!=0) {
           delete ui->widget_options;
           ui->widget_options=0;
       }
       ui->widget_options = new SobelQwidget(ui->centralWidget, mainController, this);
       ui->widget_options->setGeometry(QRect(770, 70, 270, 331));
       ui->widget_options->setVisible(true);
}

void MainWindow::on_actionCanny_triggered()
{
    int thresholdHigh=200,thresholdDown=160;
    if(mainController->isThereAnUploadedImage()){
        mainController->edgeDetectorCanny(thresholdHigh,thresholdDown);
        displayResults(mainController->getQImage());
        ShowHistogram();
    }else{
        QMessageBox msgBox2(this);
        msgBox2.setText("Sorry,Operation not valid");
        msgBox2.setWindowTitle("ERROR");
        msgBox2.exec();
    }
}

//**********************************************************
// DICOM Menu
//**********************************************************
void MainWindow::on_actionWindow_Level_triggered()
{
    if (ui->widget_options!=0) {
        delete ui->widget_options;
        ui->widget_options=0;
    }
    ui->widget_options = new WindowLevelQWidget(ui->centralWidget, mainController, this);
    ui->widget_options->setGeometry(QRect(770, 70, 270, 331));
    ui->widget_options->setVisible(true);
}

//**********************************************************
// Help Menu
//**********************************************************
void MainWindow::on_actionAbout_triggered()
{
    DialogAbout about(this);
    about.setModal(true);
    about.exec();
}

//**********************************************************
//**********************************************************
// Other Methods
//**********************************************************
//**********************************************************
void MainWindow::displayResults(QImage *result)
{
    displayedImage=result;
    on_pButton__NormalSize_clicked();
    ui->label_DimensionsValue->setText("W: "+QString::number(mainController->getImage()->getWidth())+"P"+
                                       "  H: "+QString::number(mainController->getImage()->getHeight())+"P");
    ui->label_DensityValue->setText(QString::number(log2(mainController->getImage()->getColorDepth()+1))+" Bits");
    ui->label_ImageTypeValue->setText(mainController->getImage()->getImageType());
}

void MainWindow::ShowHistogram(){
    histogramImage = mainController->getHistogramImage();
    ui->label_Histogram->setPixmap(QPixmap::fromImage(histogramImage->scaled(QSize(250,100), Qt::IgnoreAspectRatio)));
}

void MainWindow::on_label_Imagen_drawLine(const QPoint start, const QPoint end)
{
    qDebug()<<"Coordenadas: X1= "<<start.x()<<" Y1= "<<start.y();
    qDebug()<<"Coordenadas: X2= "<<end.x()<<" Y2= "<<end.y();
    QPixmap pixmap (*ui->label_Imagen->pixmap());
    QPainter painter(&pixmap);
    QPen pen(Qt::green, 2, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawLine(start.x(),start.y(),end.x(),end.y());
    ui->label_Imagen->setPixmap(pixmap);
}

void MainWindow::on_label_Imagen_eraseLine()
{
    ui->label_Imagen->setPixmap(pixmapLabelImagen);
}

void MainWindow::on_label_Imagen_mousePosition(const QPoint position)
{
    ui->label_position->setText("X: "+QString::number(position.x())+" Y: "+QString::number(position.y()));
}

void MainWindow::on_horizontalSlider_zoom_sliderMoved(int factor)
{
    if (ui->label_Imagen->pixmap()!=0) {

        double newWidth= ui->label_Imagen->pixmap()->width()*(1+(factor/100));
        double newHeight= ui->label_Imagen->pixmap()->height()*(1+(factor/100));;
        QPixmap scaledPixmap = ui->label_Imagen->pixmap()->scaled(newWidth, newHeight, Qt::KeepAspectRatio);

        // if width and height of the image are bigger than the display Area
        if(scaledPixmap.width()>ui->scrollAreaWidgetContents->width() && scaledPixmap.height()>ui->scrollAreaWidgetContents->height()){
            ui->label_Imagen->setGeometry(QRect(0, 0, scaledPixmap.width(), scaledPixmap.height()));
            ui->scrollAreaWidgetContents->setGeometry(QRect(0, 0, scaledPixmap.width(), scaledPixmap.height()));
        }

        // if just the width is bigger than the display area
        else if (scaledPixmap.width()>ui->scrollAreaWidgetContents->width()) {
            int yPos = (ui->scrollAreaWidgetContents->height() - scaledPixmap.height())/2;
            ui->label_Imagen->setGeometry(QRect(0, yPos, scaledPixmap.width(), scaledPixmap.height()));
            ui->scrollAreaWidgetContents->setGeometry(QRect(0, 0, scaledPixmap.width(), ui->scrollAreaWidgetContents->height()));
        }

        // if just the height is bigger than the display area
        else if (scaledPixmap.height()>ui->scrollAreaWidgetContents->height()) {
            int xPos = (ui->scrollAreaWidgetContents->width() - scaledPixmap.width())/2;
            ui->label_Imagen->setGeometry(QRect(xPos, 0, scaledPixmap.width(), scaledPixmap.height()));
            ui->scrollAreaWidgetContents->setGeometry(QRect(0, 0, ui->scrollAreaWidgetContents->width(), scaledPixmap.height()));
        }

        // if any of the cases above
        else{
            int xPos = (ui->scrollAreaWidgetContents->width() - scaledPixmap.width())/2;
            int yPos = (ui->scrollAreaWidgetContents->height() - scaledPixmap.height())/2;
            ui->label_Imagen->setGeometry(QRect(xPos, yPos, scaledPixmap.width(), displayedImage->height()));
        }

        ui->label_Imagen->setPixmap(scaledPixmap);
        pixmapLabelImagen=*ui->label_Imagen->pixmap();
    }
    else{
        ui->horizontalSlider_zoom->setValue(0);
    }
}

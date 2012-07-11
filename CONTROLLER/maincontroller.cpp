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

#include "maincontroller.h"

MainController::MainController(){
    this->imagen=0;
    this->oldImage=0;

}

MainController::~MainController(){
    delete imagen;
    imagen=0;

    delete oldImage;
    oldImage=0;

}

// LOAD IMAGE
bool MainController::loadImage(QString filename){

    QString fileExtension = filename.section(".",-1);

    if (fileExtension.toUpper() == "PGM") {
        imagen = new ImagenPGM(filename);

        if (imagen->getStatus()) {
            return true;
        }

    } else if (fileExtension.toUpper() == "PPM"){
        imagen = new ImagenPPM(filename);
        if (imagen->getStatus()) {
            return true;
        }
    }

    else{
        imagen = new ImagenDCM(filename.toStdString().c_str());
        if (imagen->getStatus()) {
            return true;
        }
    }
    return false;
}

QImage* MainController::getHistogramImage(){
    return imagen->getHistogramImage();
}

// Image Transfomations
void MainController::changeSize(int density){

    delete oldImage;
    oldImage=0;
    oldImage=imagen;
    imagen=oldImage->changeSize(density);
}

//Contrast
void MainController::gammaCorrection(double r){
    delete oldImage;
    oldImage = 0;
    oldImage = imagen;
    imagen = static_cast<ImagenPGM*>(oldImage)->gammaCorrection(r);
}

void MainController::contrastStretching(){
    delete oldImage;
    oldImage = 0;
    oldImage = imagen;
    imagen = static_cast<ImagenPGM*>(oldImage)->contrastStretching();
}

void MainController::changeColorDepth(int depth){
    QTextStream cout (stdout);

    cout<<"A. Inicio del metodo changeColorDepth en el controlador"<<endl;
    delete oldImage;
    oldImage=0;
    oldImage=imagen;
    cout<<"B. Justo Antes de llamar al metodo changeColorDepth de la clase Imagen"<<endl;
    imagen=oldImage->changeColorDepth(depth);
    imagen->saveImage("temp");
    cout<<"H. Dentro de changeColorDepth - en controlador, despues de exportar "<<endl;
}

void MainController::convertToGrayscale(int method){
    delete oldImage;
    oldImage=imagen;
    imagen=static_cast<ImagenPPM*>(oldImage)->convertToGrayScale(method);
}

bool MainController::average(QString filename, double alpha){

    ImagenPGM *image = new ImagenPGM(filename);

    if (imagen->getHeight()==image->getHeight() && imagen->getWidth()==image->getWidth()) {
        delete oldImage;
        oldImage=imagen;
        GlobalTransformation gt;
        imagen=gt.average(oldImage,static_cast<Image*>(image), alpha);
        //imagen=static_cast<ImagenPGM*>(oldImage)->average(image,alpha);
        return true;
    } else {
        return false;
    }

}

bool MainController::add(QString filename){

    ImagenPGM *image = new ImagenPGM(filename);

    if (imagen->getHeight()==image->getHeight() && imagen->getWidth()==image->getWidth()) {
        delete oldImage;
        oldImage=imagen;
        GlobalTransformation gt;
        imagen=gt.add(oldImage,static_cast<Image*>(image));
        //imagen=static_cast<ImagenPGM*>(oldImage)->add(image);
        return true;
    } else {
        return false;
    }
}

bool MainController::subtract(QString filename){

    ImagenPGM *image = new ImagenPGM(filename);

    if (imagen->getHeight()==image->getHeight() && imagen->getWidth()==image->getWidth()) {
        delete oldImage;
        oldImage=imagen;
        GlobalTransformation gt;
        imagen=gt.subtract(oldImage,static_cast<Image*>(image));
        //imagen=static_cast<ImagenPGM*>(oldImage)->subtract(image);
        return true;
    } else {
        return false;
    }
}

bool MainController::multiply(QString filename){

    ImagenPGM *image = new ImagenPGM(filename);

    if (imagen->getHeight()==image->getHeight() && imagen->getWidth()==image->getWidth()) {
        delete oldImage;
        oldImage=imagen;
        GlobalTransformation gt;
        imagen=gt.multiply(oldImage,static_cast<Image*>(image));
        //imagen=static_cast<ImagenPGM*>(oldImage)->multiply(image);
        return true;
    } else {
        return false;
    }

}

bool MainController::divide(QString filename){

    ImagenPGM *image = new ImagenPGM(filename);

    if (imagen->getHeight()==image->getHeight() && imagen->getWidth()==image->getWidth()) {
        delete oldImage;
        oldImage=imagen;
        GlobalTransformation gt;
        imagen=gt.divide(oldImage,static_cast<Image*>(image));
        //imagen=static_cast<ImagenPGM*>(oldImage)->divide(image);
        //imagen->saveImage("temp");
        return true;
    } else {
        return false;
    }
}

bool MainController::maxOperation(QString filename)
{
    ImagenPGM *image = new ImagenPGM(filename);

        if (imagen->getHeight()==image->getHeight() && imagen->getWidth()==image->getWidth()) {
            delete oldImage;
            oldImage=imagen;
            GlobalTransformation gt;
            imagen=gt.maxOp(oldImage,static_cast<Image*>(image));
            return true;
        } else {
           return false;
        }
}

bool MainController::minOperation(QString filename)
{
    ImagenPGM *image = new ImagenPGM(filename);
        if (imagen->getHeight()==image->getHeight() && imagen->getWidth()==image->getWidth()) {
            delete oldImage;
            oldImage=imagen;
            GlobalTransformation gt;
            imagen=gt.minOp(oldImage,static_cast<Image*>(image));
            return true;
        } else {
           return false;
        }
}

bool MainController::andOperation(QString filename)
{
    ImagenPGM *image = new ImagenPGM(filename);

    if (imagen->getHeight()==image->getHeight() && imagen->getWidth()==image->getWidth()) {
        delete oldImage;
        oldImage=imagen;
        GlobalTransformation gt;
        imagen=gt.binaryOperations(oldImage,static_cast<Image*>(image),GlobalTransformation::And);
        //imagen->saveImage("temp");
        return true;
    } else {
       return false;
    }
}

bool MainController::xorOperation(QString filename)
{
    ImagenPGM *image = new ImagenPGM(filename);

    if (imagen->getHeight()==image->getHeight() && imagen->getWidth()==image->getWidth()) {
        delete oldImage;
        oldImage=imagen;
        GlobalTransformation gt;
        imagen=gt.binaryOperations(oldImage,static_cast<Image*>(image),GlobalTransformation::Xor);
        //imagen->saveImage("temp");
        return true;
    } else {
        return false;
    }
}

void MainController::notOperation()
{
    delete oldImage;
    oldImage=imagen;
    GlobalTransformation gt;
    imagen=gt.unaryOperations(oldImage,GlobalTransformation::Not);

}

bool MainController::orOperation(QString filename)
{
    ImagenPGM *image = new ImagenPGM(filename);
    if (imagen->getHeight()==image->getHeight() && imagen->getWidth()==image->getWidth()) {
        delete oldImage;
        oldImage=imagen;
        GlobalTransformation gt;
        imagen=gt.binaryOperations(oldImage,static_cast<Image*>(image),GlobalTransformation::Or);
        //imagen->saveImage("temp");
        return true;
    } else {
        return false;
    }
}
//geometric operations
void MainController::sacaling(double factorX, double factorY)
{
    delete oldImage;
    oldImage=imagen;
    GeometricOperation gO;
    imagen=gO.scaling(oldImage,factorX,factorY);
}

void MainController::translation(double factorX, double factorY)
{
    delete oldImage;
    oldImage=imagen;
    GeometricOperation gO;
    imagen=gO.translation(oldImage,factorX,factorY);
}

void MainController::rotation(double angle)
{
    delete oldImage;
    oldImage=imagen;
    GeometricOperation gO;
    imagen=gO.rotation(oldImage,angle);
}

void MainController::reflection(bool orientationX)
{
    delete oldImage;
    oldImage=imagen;
    GeometricOperation gO;
    if(orientationX){
        imagen=gO.reflection(oldImage,GeometricOperation::X);
    }else{
        imagen=gO.reflection(oldImage,GeometricOperation::Y);
    }

}

//histogram
void MainController::equalizateHistogram(){
        delete oldImage;
        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->histogramEqualization(oldImage->getHistogram()->calculateEqualization());
}

bool MainController::bimodalSegmentaion(int T){
    if(imagen!=0){
        delete oldImage;
        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->bimodalSegmentaion(T);
        return true;
    }else{
        return false;
    }
}

void MainController::isodataSegmentation(){
    imagen->getHistogram()->ThresholdingByTwoPeaks();
    bimodalSegmentaion(imagen->getHistogram()->ThresholdingByIsodata());
}

void MainController::otsuSegmentation(){
    imagen->getHistogram()->ThresholdingByTwoPeaks();
    bimodalSegmentaion(imagen->getHistogram()->ThresholdingByOtsu());
}

//Filter
void MainController::meanFilter(int size){
    delete oldImage;
    oldImage=imagen;
    Filter f;
    imagen=f.meanFilter(oldImage, size);
    //imagen=static_cast<ImagenPGM*>(oldImage)->meanFilter(size);
}

void MainController::convolutionFilter(int **kernel, int size){
    delete oldImage;
    oldImage=imagen;
    Filter f;
    imagen=f.convolutionFilter(oldImage,kernel,size);
    //imagen=static_cast<ImagenPGM*>(oldImage)->convolutionFilter(kernel,size);
}

void MainController::gaussianaFilter(int size){
    delete oldImage;
    oldImage=imagen;
    Filter f;
    imagen=f.gaussianaFilter(oldImage,size);
    //imagen=static_cast<ImagenPGM*>(oldImage)->gaussianaFilter(size);
}

void MainController::noiseCleaningLine(double delta){
    delete oldImage;
    oldImage=imagen;
    Filter f;
    imagen=f.noiseCleaningLine(oldImage,delta);
    //imagen=static_cast<ImagenPGM*>(oldImage)->noiseCleaningLine(delta);
}

void MainController::noiseCleaningPixel(int delta){
    delete oldImage;
    oldImage=imagen;
    Filter f;
    imagen=f.noiseCleaningPixel(oldImage,delta);
    //imagen=static_cast<ImagenPGM*>(oldImage)->noiseCleaningPixel(delta);
}

//edge Detection

void MainController::edgeDetectionSobel(int position){
    delete oldImage;
    oldImage=imagen;
    imagen=static_cast<ImagenPGM*>(oldImage)->edgeDetectionSobel(position);
}

void MainController::edgeDetectorCanny(int thresholdHigh, int thresholdDown){
    delete oldImage;
    oldImage=imagen;
    EdgeDetector ed;
    imagen=ed.edgeDetectorCanny(oldImage,thresholdHigh,thresholdDown);
}


//Morphological Operation
void MainController::dilateOperation(int** matrixStructuringElement,int origenX,int origenY,int heightS,int widthS){
    delete oldImage;
    oldImage=imagen;
    imagen=static_cast<ImagenPGM*>(oldImage)->dilateOperation(matrixStructuringElement,origenX,origenY,heightS,widthS);
}

void MainController::erosionOperation(int** matrixStructuringElement,int origenX,int origenY,int heightS,int widthS){
    delete oldImage;
    oldImage=imagen;
    imagen=static_cast<ImagenPGM*>(oldImage)->erosionOperation(matrixStructuringElement,origenX,origenY,heightS,widthS);
}

void MainController::openingOperation(int** matrixStructuringElement,int origenX,int origenY,int heightS,int widthS){
    delete oldImage;
    oldImage=imagen;
    imagen=static_cast<ImagenPGM*>(oldImage)->openingOperation(matrixStructuringElement,origenX,origenY,heightS,widthS);
}

void MainController::closingOperation(int** matrixStructuringElement,int origenX,int origenY,int heightS,int widthS){
    delete oldImage;
    oldImage=imagen;
    imagen=static_cast<ImagenPGM*>(oldImage)->closingOperation(matrixStructuringElement,origenX,origenY,heightS,widthS);
}
//segmentation

void MainController::segmentationK_Means(int cluster)
{
    delete oldImage;
    oldImage=imagen;
    Segmentation sg;
    if(static_cast<ImagenPGM*>(oldImage)->getImageType()=="PGM"){
        imagen=sg.kmeansPGM(oldImage,cluster);
    }else{
        imagen=sg.kmeansPPM(oldImage,cluster);
    }

}

void MainController::segmentationRemoveCap()
{
    delete oldImage;
    oldImage=imagen;
    Segmentation sg;
    if(static_cast<ImagenPGM*>(oldImage)->getImageType()=="PGM"){
        imagen=sg.removeCap(oldImage);
    }else{
        //imagen=sg.kmeansPPM(oldImage,cluster);
    }
}

// DICOM
void MainController::applyWindowLevel(int window, int level){

    static_cast<ImagenDCM*>(imagen)->applyWindowLevel(window,level);
}

void MainController::changeFrame(int numFrame)
{
    static_cast<ImagenDCM*>(imagen)->setFrameImage(numFrame);
}

int MainController::getCountFrameFirstImage()
{
   return static_cast<ImagenDCM*>(imagen)->getCountFrameFirstImage()-1;
}

// Getters
Image* MainController::getImage(){
    return imagen;
}

QImage* MainController::getQImage(){
    return imagen->getQImage();
}

// Other Methods
bool MainController::undo(){
    if (oldImage!=0) {
        imagen=oldImage;
        oldImage=0;
        return true;
    }else{
        return false;
    }
}

bool MainController::isThereAnUploadedImage(){
    if(imagen!=0){
        return true;
    }else{
        return false;
    }
}

void MainController::saveImage(QString filename,QString id){
    QString idTemp;
    if(!id.isEmpty()){//si es una imagen dcm no se cambia el tipo
        idTemp = imagen->getIdentification();
        imagen->setImageIdentification(id);
    }
    imagen->saveImage(filename);
    if(!id.isEmpty()){
        imagen->setImageIdentification(idTemp);
    }
}















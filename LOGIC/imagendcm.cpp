//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: image.cpp
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

#include "imagendcm.h"

ImagenDCM::ImagenDCM(const char *fileName){

    dicomImage = new DicomImage(fileName);

    QTextStream cout(stdout);
    if (dicomImage != NULL)
    {
        if (dicomImage->getStatus() == EIS_Normal)
        {
            this->identification="DCM";
            this->comment="";
            this->imageType="DCM";
            this->colorDepth=pow(2,dicomImage->getDepth()-1)-1;
            this->height=dicomImage->getWidth();
            this->width=dicomImage->getHeight();

            //Display information about image


            cout <<"DICOM depth: "<<dicomImage->getDepth()<<endl;
            cout <<"Color Depth: "<<colorDepth<<endl;
            cout<< "frameCount: "<<dicomImage->getFrameCount()<<endl;
            double min, max;
            dicomImage->getMinMaxValues(min, max);
            cout<<"Min Value: "<<min<<endl;
            cout<<"Max Value: "<<max<<endl;

            Uint8 *pixelData = (Uint8 *)(dicomImage->getOutputData(16));
            if (pixelData != NULL)
            {
                //Lookup Table
                lut = new int [colorDepth+1];
                for (int i = 0; i < colorDepth+1; ++i)
                    lut[i]=i;

                matrixImagenP = new int**[height];
                for (int i=0; i < height; i++)
                    matrixImagenP[i]=new int*[width];

                for(int i=0; i<height; i++){
                    for(int j=0; j<width; j++){
                        matrixImagenP[i][j]=&lut[pixelData[(i*width)+j]];
                        QTextStream (stdout)<<*matrixImagenP[i][j]<<" ";
                    }
                    QTextStream (stdout) <<""<<endl;
                }
            }
        } else
            status=false;
    }
    cout<<"TERMINE"<<endl;
}

//Image processing
Image* ImagenDCM::changeSize(int factor){
    return this;
}

Image* ImagenDCM::changeColorDepth(int bits){
    return this;
}

// GUI Display
QImage* ImagenDCM::getQImage(){
    qImage = new QImage(width, height, QImage::Format_RGB32);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            qImage->setPixel(j,i,qRgb(*matrixImagenP[i][j],*matrixImagenP[i][j],*matrixImagenP[i][j]));
        }
    }
    return qImage;
}

//Histogram
QImage* ImagenDCM::getHistogramImage(){

    int **matrix = new int*[height];
    for (int i=0; i < height; i++)
        matrix[i]=new int[width];

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            matrix[i][j]=*matrixImagenP[i][j];
        }
    }
    histogram = new Histogram(height, width, colorDepth, matrix);
    return histogram->getHistogram();
}

Histogram* ImagenDCM::getHistogram(){
    return histogram;
}

// export
void ImagenDCM::saveImage(QString filename){

    if (!filename.contains(".pgm")) {
        filename=filename.section(".",0,0)+".pgm";
    }
    QTextStream (stdout) <<"filename:"<<filename<<endl;
    this->imageType="PGM";
    this->identification="P2";
    QFile temp(filename);
    if(temp.open(QFile::WriteOnly)){
        QTextStream fSalida(&temp);

        fSalida<<identification<<endl;
        fSalida<<comment<<endl;
        fSalida<<width<<" "<<height<<endl;
        fSalida<<colorDepth<<endl;

        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                fSalida<<*matrixImagenP[i][j]<<" ";
            }
            fSalida<<endl;
        }
    }
}



//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: imagenpgm.cpp
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

#include "imagenpgm.h"
ImagenPGM::ImagenPGM(QList<QString> lectura){
    this->identification=lectura.at(0);
    this->comment=lectura.at(1);
    this->columnNumber=lectura.at(2).section(' ',0,0).toInt();
    this->rowNumber=lectura.at(2).section(' ',1,1).toInt();
    this->colorDensity=lectura.at(3).toInt();


    //Lookup Table
    lut = new int [colorDensity+1];
    for (int i = 0; i < colorDensity+1; ++i) {
        lut[i]=i;
    }

    matrixImagenP = new int**[rowNumber];
    for (int i=0; i < rowNumber; i++)
        matrixImagenP[i]=new int*[columnNumber];

    int aux=4;
    for(int i=0; i<rowNumber; i++){
        for(int j=0; j<columnNumber; j++){
            matrixImagenP[i][j]=&lut[lectura[i+j+aux].toInt()];
        }
        aux=aux+columnNumber-1;
    }
}

ImagenPGM::ImagenPGM(QString id, QString coment, int filas, int columnas, int colorD, int **matriz){
    this->identification=id;
    this->comment=coment;
    this->rowNumber=filas;
    this->columnNumber=columnas;
    this->colorDensity=colorD;

    //Lookup Table
    lut = new int [colorDensity+1];
    for (int i = 0; i < colorDensity+1; ++i) {
        lut[i]=i;
    }

    matrixImagenP = new int**[rowNumber];
    for (int i=0; i < rowNumber; i++)
        matrixImagenP[i]=new int*[columnNumber];

    for(int i=0; i<rowNumber; i++){
        for(int j=0; j<columnNumber; j++){
            matrixImagenP[i][j]=&lut[matriz[i][j]];
        }
    }
}

ImagenPGM::ImagenPGM(QString id, QString coment, int filas, int columnas, int colorD, int ***matriz, int *lut){
    this->identification=id;
    this->comment=coment;
    this->rowNumber=filas;
    this->columnNumber=columnas;
    this->colorDensity=colorD;
    this->matrixImagenP=matriz;
    this->lut=lut;
}

//Image processing

ImagenPGM ImagenPGM::changeIntensity(int bits){

    int intensidadNueva=(int)(pow(2,bits)-1);

    int **imagenIntensidad = new int*[rowNumber];
    for (int i=0; i < rowNumber; i++)
        imagenIntensidad[i]=new int[columnNumber];

    int divisor = (colorDensity+1)/(intensidadNueva+1);

    for(int i=0; i<rowNumber; i++){
        for(int j=0; j<columnNumber; j++){
            imagenIntensidad[i][j]=floor(*matrixImagenP[i][j]/divisor);
        }
    }

    return *this;
}

ImagenPGM* ImagenPGM::changeSize(int factor){
    int w=0,h=0,**enlargedImage;
    if (factor>0) {
        w = this->columnNumber*factor;
        h = this->rowNumber*factor;

        enlargedImage = new int*[h];
        for (int i=0; i < h; i++)
            enlargedImage[i]=new int[w];

        for (int i = 0; i <h; ++i) {
            for (int j = 0; j < w; ++j) {
                enlargedImage[i][j]=*(matrixImagenP[(int)floor(i/factor)][(int)floor(j/factor)]);
            }
        }
    } else {
        factor*=-1;
        w = (int)ceil(this->columnNumber/factor);
        h = (int)ceil(this->rowNumber/factor);

        // inicializacion
        enlargedImage = new int*[h];
        for (int i=0; i < h; i++)
            enlargedImage[i]=new int[w];

        // Proceso de reduccion
        for(int i=0; i <h; i++){
            for(int j=0; j<w; j++){
                enlargedImage[i][j]=*(matrixImagenP[i*factor][j*factor]);
            }
        }
    }

    return new ImagenPGM (identification,
                          comment,
                          w,
                          h,
                          colorDensity,
                          enlargedImage);
}

ImagenPGM* ImagenPGM::bimodalSegmentaion(int T){
    for (int i = 0; i < colorDensity+1; ++i) {
        if (lut[i]<T) {
            lut[i]=0;
        } else {
            lut[i]=colorDensity;
        }
    }

    return this;
}

int*** ImagenPGM::getMatrix(){
    return matrixImagenP;
}

void ImagenPGM::exportar(QTextStream &fSalida){

    fSalida<<identification<<endl;
    fSalida<<comment<<endl;
    fSalida<<columnNumber<<" "<<rowNumber<<endl;
    fSalida<<colorDensity<<endl;

    for(int i=0; i<rowNumber; i++){
        for(int j=0; j<columnNumber; j++){
            fSalida<<*matrixImagenP[i][j]<<endl;
        }
    }
}

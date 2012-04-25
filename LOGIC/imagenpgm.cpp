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

//Constructors
ImagenPGM::ImagenPGM(QList<QString> lectura){
    this->identification=lectura.at(0);
    this->comment=lectura.at(1);
    this->width=lectura.at(2).section(' ',0,0).toInt();
    this->height=lectura.at(2).section(' ',1,1).toInt();
    this->colorDepth=lectura.at(3).toInt();
    this->lutSize=colorDepth;
    this->imageType="PGM";


    //Lookup Table
    lut = new int [lutSize+1];
    for (int i = 0; i < lutSize+1; ++i) {
        lut[i]=i;
    }

    matrixImagenP = new int**[height];
    for (int i=0; i < height; i++)
        matrixImagenP[i]=new int*[width];

    int aux=4;
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            matrixImagenP[i][j]=&lut[lectura[i+j+aux].toInt()];
        }
        aux=aux+width-1;
    }
}

ImagenPGM::ImagenPGM(QString id, QString coment, int h, int w, int colorD, int **matrix){
    this->identification=id;
    this->comment=coment;
    this->height=h;
    this->width=w;
    this->colorDepth=colorD;
    this->lutSize=colorD;
    this->imageType="PGM";

    //Lookup Table
    lut = new int [lutSize+1];
    for (int i = 0; i < lutSize+1; ++i) {
        lut[i]=i;
    }

    matrixImagenP = new int**[height];
    for (int i=0; i < height; i++)
        matrixImagenP[i]=new int*[width];

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            matrixImagenP[i][j]=&lut[matrix[i][j]];
        }
    }
}

ImagenPGM::ImagenPGM(QString id, QString coment, int h, int w, int colorD, int ***matrixP, int *lut, int lutSize){
    this->identification=id;
    this->comment=coment;
    this->height=h;
    this->width=w;
    this->colorDepth=colorD;
    this->matrixImagenP=matrixP;
    this->lut=lut;
    this->lutSize=lutSize;
    this->imageType="PGM";
}

//Image processing
Image* ImagenPGM::changeSize(int factor){
    int w=0,h=0,**enlargedImage;
    if (factor>0) {
        w = this->width*factor;
        h = this->height*factor;

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
        w = (int)ceil(this->width/factor);
        h = (int)ceil(this->height/factor);

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
                          colorDepth,
                          enlargedImage);
}

Image* ImagenPGM::changeColorDepth(int bits){

    if((int)(pow(2,bits)-1)<colorDepth){
        int newColorDepth=(int)(pow(2,bits)-1);
        int divisor = (colorDepth+1)/(newColorDepth+1);
        for(int i=0; i<lutSize; i++){
            lut[i]=lut[i]/divisor;
        }
        return new ImagenPGM (identification,
                              comment,
                              height,
                              width,
                              newColorDepth,
                              matrixImagenP,
                              lut,
                              lutSize);

    }else if ((int)(pow(2,bits)-1)>colorDepth) {
        int newColorDepth=(int)(pow(2,bits)-1);
        //int divisor = (newColorDepth+1)/(colorDepth+1);
        for(int i=0; i<lutSize; i++){
            lut[i]=lut[i]*newColorDepth;
        }
        return new ImagenPGM (identification,
                              comment,
                              height,
                              width,
                              newColorDepth,
                              matrixImagenP,
                              lut,
                              lutSize);
    }else{
        return this;
    }

}
Image* ImagenPGM::bimodalSegmentaion(int T){
    for (int i = 0; i < colorDepth+1; ++i) {
        if (lut[i]<T) {
            lut[i]=0;
        } else {
            lut[i]=colorDepth;
        }
    }
    return this;
}

// Getters
int*** ImagenPGM::getMatrix(){
    return matrixImagenP;
}

// export
void ImagenPGM::exportar(QString filename){

    QFile temp(filename+"."+imageType.toLower());
    if(temp.open(QFile::WriteOnly)){
        QTextStream fSalida(&temp);

        fSalida<<identification<<endl;
        fSalida<<comment<<endl;
        fSalida<<width<<" "<<height<<endl;
        fSalida<<colorDepth<<endl;

        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                fSalida<<*matrixImagenP[i][j]<<endl;
            }
        }
    }
}

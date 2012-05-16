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
    this->imageType="PGM";

    //Lookup Table
    lut = new int [colorDepth+1];
    for (int i = 0; i < colorDepth+1; ++i)
        lut[i]=i;

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
    this->imageType="PGM";

    //Lookup Table
    lut = new int [colorDepth+1];
    for (int i = 0; i < colorDepth+1; ++i) {
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

ImagenPGM::ImagenPGM(QString id, QString comment, int h, int w, int colorD, int ***matrixP, int *lut){

    QTextStream (stdout) << "E. Al inicio del constructor de la nueva imagen"<<endl;
    this->identification=id;
    this->comment=comment;
    this->width=w;
    this->height=h;
    this->colorDepth=colorD;
    this->imageType="PGM";

    //Lookup Table
    this->lut = new int [colorDepth+1];
    for (int i = 0; i < colorDepth+1; ++i)
        this->lut[i]=i;
    QTextStream (stdout) << "E1. lookup table ok"<<endl;

    // Matrix of Pointers
    matrixImagenP = new int**[height];
    for (int i=0; i < height; i++)
        matrixImagenP[i]=new int*[width];
    QTextStream (stdout) << "E2. Matriz inicializacion - ok"<<endl;

    QTextStream (stdout) << "F. Antes de llenar la matriz"<<endl;
    for(int i=0; i<height; i++)
        for(int j=0; j<width; j++)
            matrixImagenP[i][j]=&this->lut[*matrixP[i][j]];

    QTextStream (stdout) << "G. Al final del constructor"<<endl;
}

ImagenPGM::~ImagenPGM(){
    for(int i=0; i<height; i++){
        delete matrixImagenP[i];
        matrixImagenP[i]=0;
    }
    delete matrixImagenP;
    matrixImagenP=0;

    delete lut;
    this->lut=0;
}

//Global Transformations
Image* ImagenPGM::changeSize(int factor){

    int w=0;
    int h=0;
    int **resizedMatrix;
    ImagenPGM *resizedImage;

    if (factor>0) {
        w = this->width*factor;
        h = this->height*factor;

        resizedMatrix = new int*[h];
        for (int i=0; i < h; i++)
            resizedMatrix[i]=new int[w];

        for (int i = 0; i <h; ++i) {
            for (int j = 0; j < w; ++j) {
                resizedMatrix[i][j]=*(matrixImagenP[(int)floor(i/factor)][(int)floor(j/factor)]);
            }
        }
        resizedImage = new ImagenPGM (identification,
                                      comment,
                                      w,
                                      h,
                                      colorDepth,
                                      resizedMatrix);

        for (int i=0; i < h; i++)
            delete resizedMatrix[i];
        delete resizedMatrix;

    } else {
        factor*=-1;
        w = (int)ceil(this->width/factor);
        h = (int)ceil(this->height/factor);

        // inicializacion
        resizedMatrix = new int*[h];
        for (int i=0; i < h; i++)
            resizedMatrix[i]=new int[w];

        // Proceso de reduccion
        for(int i=0; i <h; i++){
            for(int j=0; j<w; j++){
                resizedMatrix[i][j]=*(matrixImagenP[i*factor][j*factor]);
            }
        }

        resizedImage = new ImagenPGM (identification,
                                      comment,
                                      w,
                                      h,
                                      colorDepth,
                                      resizedMatrix);

        for (int i=0; i < h; i++)
            delete resizedMatrix[i];
        delete resizedMatrix;

    }
    return resizedImage;
}

Image* ImagenPGM::changeColorDepth(int bits){

    QTextStream (stdout) << "C. Al inicio del metodo changeColorDepth en ImagenPGM"<<endl;
    if((int)(pow(2,bits)-1)<colorDepth){

        int newColorDepth=(int)(pow(2,bits)-1);
        int divisor = (colorDepth+1)/(newColorDepth+1);

        QTextStream (stdout) << "Divisor "<<divisor<<endl;
        for(int i=0; i<colorDepth+1; i++){
            lut[i]=lut[i]/divisor;
            QTextStream (stdout) << "lut["<<i<<"]"<<lut[i]<<endl;
        }

        QTextStream (stdout) << "D. Antes de salir del metodo changeColorDepth en Imagen PGM - Reduccion"<<endl;
        return new ImagenPGM (identification,
                              comment,
                              height,
                              width,
                              newColorDepth,
                              matrixImagenP,
                              lut);

    }else if ((int)(pow(2,bits)-1)>colorDepth) {

        int newColorDepth=(int)(pow(2,bits)-1);
        int divisor = (newColorDepth+1)/(colorDepth+1);
        for(int i=0; i<colorDepth+1; i++){
            lut[i]=lut[i]*divisor;
            QTextStream (stdout) << "lut["<<i<<"]"<<lut[i]<<endl;
        }

        QTextStream (stdout) << "D. Antes de salir del metodo changeColorDepth en Imagen PGM - Aumento"<<endl;
        return new ImagenPGM (identification,
                              comment,
                              height,
                              width,
                              newColorDepth,
                              matrixImagenP,
                              lut);
    }else{
        QTextStream (stdout) << "D. Antes de salir del metodo changeColorDepth en Imagen PGM - IGUAL"<<endl;
        return new ImagenPGM(identification,
                             comment,
                             height,
                             width,
                             colorDepth,
                             matrixImagenP,
                             lut);
    }

}

Image* ImagenPGM::add(ImagenPGM *image, double alpha){

    int **additionMatrix = new int*[height];
    for (int i=0; i < height; i++)
        additionMatrix[i]=new int[width];

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            additionMatrix[i][j]=alpha*(*matrixImagenP[i][j])+(1-alpha)*(*image->getMatrix()[i][j]);
        }
    }

    ImagenPGM *result = new ImagenPGM(identification,comment,height,width,colorDepth,additionMatrix);


    for (int i=0; i < height; i++)
        delete additionMatrix[i];

    delete additionMatrix;

    return result;
}

Image* ImagenPGM::bimodalSegmentaion(int T){
    for (int i = 0; i < colorDepth+1; ++i) {
        if (lut[i]<T) {
            lut[i]=0;
        } else {
            lut[i]=colorDepth;
        }
    }
    return new ImagenPGM(identification, comment, height, width, colorDepth, matrixImagenP, lut);

}

Image* ImagenPGM::histogramEqualization(int *newlut){
    return new ImagenPGM (identification,
                          comment,
                          height,
                          width,
                          colorDepth,
                          matrixImagenP,
                          newlut);
}

// Getters
int*** ImagenPGM::getMatrix(){
    return matrixImagenP;
}

// export
void ImagenPGM::saveImage(QString filename){

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

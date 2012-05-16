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
    for (int i = 0; i < lutSize+1; ++i)
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

ImagenPGM::ImagenPGM(QString id, QString comment, int h, int w, int colorD, int ***matrixP, int *lut, int lutSize){

    this->identification=id;
    this->comment=comment;
    this->width=w;
    this->height=h;
    this->colorDepth=colorD;
    this->lutSize=lutSize;
    this->imageType="PGM";

    //Lookup Table
    this->lut = new int [lutSize+1];
    for (int i = 0; i < lutSize+1; ++i)
        this->lut[i]=lut[i];

    // Matrix of Pointers
    matrixImagenP = new int**[height];

    for (int i=0; i < height; i++)
        matrixImagenP[i]=new int*[width];

    for(int i=0; i<height; i++)
        for(int j=0; j<width; j++)
            matrixImagenP[i][j]=&this->lut[*matrixP[i][j]];

}

ImagenPGM::~ImagenPGM(){

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            matrixImagenP[i][j]=0;
        }
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
  //  QTextStream cout(stdout);

    int newColorDepth=(int)(pow(2,bits)-1);
    //cout<<newColorDepth;

//    double *lutemp = new double[lutSize+1];
//    for (int i = 0; i < lutSize; ++i) {
//        lutemp[i]=0;
//    }
    if(newColorDepth<colorDepth){
        int divisor = (colorDepth+1)/(newColorDepth+1);
      //  cout<<" "<<divisor<<endl;
        for(int i=0; i<lutSize+1; i++){
         //   cout<<" "<<lut[i];
            lut[i]=lut[i]/divisor;
          //  cout<<" "<<lut[i]<<endl;
        }
        return new ImagenPGM (identification,
                              comment,
                              height,
                              width,
                              newColorDepth,
                              matrixImagenP,
                              lut,
                              lutSize);
        delete lut;lut=0;
    }else if (newColorDepth>colorDepth) {
        int divisor = (newColorDepth+1)/(colorDepth+1);
        for(int i=0; i<lutSize+1; i++){
            lut[i]=(lut[i]*divisor)-1;
        }
        //cout<<" "<<divisor<<endl;
        return new ImagenPGM (identification,
                              comment,
                              height,
                              width,
                              newColorDepth,
                              matrixImagenP,
                              lut,
                              lutSize);
        delete lut;lut=0;
    }else{
        return this;
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

Image* ImagenPGM::subtract(ImagenPGM *image, double alpha){

    int **subtractMatrix = new int*[height];
    for (int i=0; i < height; i++)
        subtractMatrix[i]=new int[width];

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            subtractMatrix[i][j]=alpha*(*matrixImagenP[i][j])-(1-alpha)*(*image->getMatrix()[i][j]);
        }
    }

    ImagenPGM *result = new ImagenPGM(identification,comment,height,width,colorDepth,subtractMatrix);


    for (int i=0; i < height; i++)
        delete subtractMatrix[i];

    delete subtractMatrix;

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
    return new ImagenPGM(identification, comment, height, width, colorDepth, matrixImagenP, lut, lutSize);

}

Image* ImagenPGM::histogramEqualization(int *newlut){
    return new ImagenPGM (identification,
                          comment,
                          height,
                          width,
                          colorDepth,
                          matrixImagenP,
                          newlut,
                          lutSize);
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

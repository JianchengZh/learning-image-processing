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
ImagenPGM::ImagenPGM(QString filename){

    ImageFile imageFile(filename);
    if (imageFile.readFile()) {

        this->identification=imageFile.getId();
        this->width=imageFile.getWidth();
        this->height=imageFile.getHeight();
        this->colorDepth=imageFile.getColorDepth();
        this->imageType="PGM";

        int *matrix=imageFile.getMatrix();

        //Lookup Table
        lut = new int [colorDepth+1];
        for (int i = 0; i < colorDepth+1; ++i)
            lut[i]=i;

        matrixImagenP = new int**[height];
        for (int i=0; i < height; i++)
            matrixImagenP[i]=new int*[width];

        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                matrixImagenP[i][j]=&lut[matrix[(i*width)+j]];
            }
        }
        status=true;
    } else {
        status=false;
    }

}

ImagenPGM::ImagenPGM(QString id, int h, int w, int colorD, int **matrix){
    this->identification=id;
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

ImagenPGM::ImagenPGM(QString id, int h, int w, int colorD, int ***matrixP, int *lut){

    QTextStream (stdout) << "E. Al inicio del constructor de la nueva imagen"<<endl;
    this->identification=id;
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
                              height,
                              width,
                              newColorDepth,
                              matrixImagenP,
                              lut);

    }else if ((int)(pow(2,bits)-1)>colorDepth) {

        int newColorDepth=(int)(pow(2,bits)-1);
        for(int i=0; i<colorDepth+1; i++){
            lut[i]=floor((newColorDepth/colorDepth)*lut[i]);
            QTextStream (stdout) << "lut["<<i<<"]"<<lut[i]<<endl;
        }

        QTextStream (stdout) << "D. Antes de salir del metodo changeColorDepth en Imagen PGM - Aumento"<<endl;

        return new ImagenPGM (identification,
                              height,
                              width,
                              newColorDepth,
                              matrixImagenP,
                              lut);
    }else{
        QTextStream (stdout) << "D. Antes de salir del metodo changeColorDepth en Imagen PGM - IGUAL"<<endl;
        return new ImagenPGM(identification,
                             height,
                             width,
                             colorDepth,
                             matrixImagenP,
                             lut);
    }

}

Image* ImagenPGM::average(ImagenPGM *image, double alpha){

    int **averageMatrix = new int*[height];
    for (int i=0; i < height; i++)
        averageMatrix[i]=new int[width];

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            averageMatrix[i][j]=alpha*(*matrixImagenP[i][j])+(1-alpha)*(*image->getMatrix()[i][j]);
        }
    }

    ImagenPGM *result = new ImagenPGM(identification,height,width,colorDepth,averageMatrix);

    for (int i=0; i < height; i++)
        delete averageMatrix[i];

    delete averageMatrix;

    return result;
}

Image* ImagenPGM::add(ImagenPGM *image){

    int **addMatrix = new int*[height];
    for (int i=0; i < height; i++)
        addMatrix[i]=new int[width];
    int sum = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            sum=(*matrixImagenP[i][j])+(*image->getMatrix()[i][j]);
            if (sum<=colorDepth) {
                addMatrix[i][j]=sum;
            } else {
                addMatrix[i][j]=colorDepth;
            }
        }
    }

    ImagenPGM *result = new ImagenPGM(identification,height,width,colorDepth,addMatrix);


    for (int i=0; i < height; i++)
        delete addMatrix[i];

    delete addMatrix;

    return result;
}

Image* ImagenPGM::subtract(ImagenPGM *image){

    int **subtractMatrix = new int*[height];
    for (int i=0; i < height; i++)
        subtractMatrix[i]=new int[width];
    int rest = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            rest=(*matrixImagenP[i][j])-(*image->getMatrix()[i][j]);
            if (rest>=0) {
                subtractMatrix[i][j]=rest;
            } else {
                subtractMatrix[i][j]=colorDepth+1+rest;
            }
        }
    }

    ImagenPGM *result = new ImagenPGM(identification,height,width,colorDepth,subtractMatrix);


    for (int i=0; i < height; i++)
        delete subtractMatrix[i];

    delete subtractMatrix;

    return result;
}

Image* ImagenPGM::multiply(ImagenPGM *image){

    int **multiplyMatrix = new int*[height];
    for (int i=0; i < height; i++)
        multiplyMatrix[i]=new int[width];
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            multiplyMatrix[i][j]=((*matrixImagenP[i][j])*(*image->getMatrix()[i][j]))/colorDepth;
        }
    }

    ImagenPGM *result = new ImagenPGM(identification,height,width,colorDepth,multiplyMatrix);


    for (int i=0; i < height; i++)
        delete multiplyMatrix[i];

    delete multiplyMatrix;

    return result;
}

Image* ImagenPGM::divide(ImagenPGM *image){

    int **divideMatrix = new int*[height];
    for (int i=0; i < height; i++)
        divideMatrix[i]=new int[width];
    QTextStream cout (stdout);
    int div = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            div=((colorDepth+1)*(*matrixImagenP[i][j]))/((*image->getMatrix()[i][j])+1);
            //            if (div<colorDepth+1) {
            divideMatrix[i][j]=div;
            //            } else {
            //                divideMatrix[i][j]=colorDepth;
            //            }
            cout<<divideMatrix[i][j]<<" ";
        }cout<<endl;
    }

    ImagenPGM *result = new ImagenPGM(identification,height,width,colorDepth,divideMatrix);


    for (int i=0; i < height; i++)
        delete divideMatrix[i];

    delete divideMatrix;

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
    return new ImagenPGM(identification, height, width, colorDepth, matrixImagenP, lut);

}

Image* ImagenPGM::histogramEqualization(int *newlut){
    return new ImagenPGM (identification,
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

// GUI Display
void ImagenPGM::generateQImage(){
    QVector<QRgb> colorTable;
    int aux;
    for (int i = 0; i < colorDepth+1; ++i) {
        aux = floor((255/colorDepth)*i);
        colorTable.append(qRgb(aux,aux,aux));
    }

    qImage = new QImage(width, height, QImage::Format_Indexed8);
    qImage->setColorTable(colorTable);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            qImage->setPixel(j,i,*matrixImagenP[i][j]);
        }
    }
}

// Histogram
void ImagenPGM::generateHistogram(){

    int **matrix = new int*[height];
    for (int i=0; i < height; i++)
        matrix[i]=new int[width];

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            matrix[i][j]=*matrixImagenP[i][j];
        }
    }
    histogram = new Histogram(height, width, colorDepth, matrix);

}

// Export
void ImagenPGM::saveImage(QString filename){

    if (!filename.contains(".pgm")) {
        filename=filename+".pgm";
    }

    QFile temp(filename);
    if(temp.open(QFile::WriteOnly)){
        QTextStream fSalida(&temp);

        fSalida<<identification<<endl;
        fSalida<<"#LEARNING IMAGE PROCESSING by GUSTAVO & EDWIN AT UNIVALLE"<<endl;
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

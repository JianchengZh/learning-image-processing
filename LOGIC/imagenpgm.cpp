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

        generateHistogram();
        generateQImage();
        status=true;
    } else {
        status=false;
    }

}

ImagenPGM::ImagenPGM(int h, int w, int colorD, int **matrix){
    this->identification="P2";
    this->height=h;
    this->width=w;
    this->colorDepth=colorD;
    this->imageType="PGM";
    this->status=true;

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
    generateHistogram();
    generateQImage();
}

ImagenPGM::ImagenPGM(int h, int w, int colorD, int ***matrixP, int *lut){

    this->identification="P2";
    this->width=w;
    this->height=h;
    this->colorDepth=colorD;
    this->imageType="PGM";
    this->status=true;

    //Lookup Table
    this->lut = new int [colorDepth+1];
    for (int i = 0; i < colorDepth+1; ++i)
        this->lut[i]=i;

    // Matrix of Pointers
    matrixImagenP = new int**[height];
    for (int i=0; i < height; i++)
        matrixImagenP[i]=new int*[width];

    for(int i=0; i<height; i++)
        for(int j=0; j<width; j++)
            matrixImagenP[i][j]=&this->lut[*matrixP[i][j]];

    generateHistogram();
    generateQImage();
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

//Contrast
Image *ImagenPGM::gammaCorrection(double r){

    if(r<0 || r>3){
        QTextStream (stdout) <<"Error : se encuentra en un rango es invalido! \n";
        return 0;
    }

    if(r==1)
        return this;

    double aux = 0;
    for(int i=0; i<colorDepth+1; i++){
        aux = colorDepth *pow((double)lut[i]/(double)colorDepth,r);
        lut[i]= round(aux);
    }

    return new ImagenPGM(height, width, colorDepth, matrixImagenP, lut);
}

 Image *ImagenPGM::contrastStretching(){


     this->generateHistogram();
     double *colorFrecuency = this->getHistogram()->getColorFrequency();


     int minValue = 0;
     int maxValue = colorDepth;



     for(int i=0; i<colorDepth+1; i++)
         if(colorFrecuency[i]!=0){
             minValue=i;
             break;
         }

     for(int i=colorDepth; i>=0; i--)
         if(colorFrecuency[i]!=0){
             maxValue=i;
             break;
         }
      QTextStream (stdout) <<"valor streching min  "<< colorDepth <<" "<< minValue << "max "<< maxValue<< "\n";
     for(int i=0; i<colorDepth+1; i++){

          lut[i]=(i-minValue)*colorDepth/(maxValue-minValue);
        QTextStream (stdout) <<"valor streching  "<< i <<" "<< lut[i] << "\n";
     }

     return new ImagenPGM(height, width, colorDepth, matrixImagenP, lut);



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
        resizedImage = new ImagenPGM (w, h, colorDepth, resizedMatrix);

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

        resizedImage = new ImagenPGM (w, h, colorDepth, resizedMatrix);

        for (int i=0; i < h; i++)
            delete resizedMatrix[i];
        delete resizedMatrix;

    }
    return resizedImage;
}

Image* ImagenPGM::changeColorDepth(int bits){

    double newColorDepth=(int)(pow(2,bits)-1);
    double aux;
    for(int i=0; i<colorDepth+1; i++){
        aux=qRound((newColorDepth/colorDepth)*lut[i]);
        lut[i]=aux;
    }
    return new ImagenPGM (height, width, newColorDepth, matrixImagenP, lut);
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

    ImagenPGM *result = new ImagenPGM(height, width, colorDepth, averageMatrix);

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

    ImagenPGM *result = new ImagenPGM(height, width, colorDepth, addMatrix);


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

    ImagenPGM *result = new ImagenPGM(height, width, colorDepth, subtractMatrix);


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

    ImagenPGM *result = new ImagenPGM(height, width, colorDepth, multiplyMatrix);


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

    ImagenPGM *result = new ImagenPGM(height, width, colorDepth, divideMatrix);


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
    return new ImagenPGM(height, width, colorDepth, matrixImagenP, lut);

}

Image* ImagenPGM::histogramEqualization(int *newlut){

    for (int i = 0; i < colorDepth+1; ++i) {
        lut[i]=newlut[i];
    }

    return new ImagenPGM (height, width, colorDepth, matrixImagenP, lut);
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

// Filters
Image* ImagenPGM::applyKernel(int **kernel, int kernelSizeX, int kernelSizeY){

    int** resultMatrix = new int*[height];
    for (int i = 0; i < height; ++i) {
        resultMatrix[i] = new int[width];
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            resultMatrix[i][j]=*matrixImagenP[i][j];
        }
    }

    int inicial_position=floor(kernelSizeX/2);
    for (int i = inicial_position; i < height-inicial_position; ++i) {
        for (int j = inicial_position; j < width-inicial_position; ++j) {
            applyKerneltoPixel(i,j,kernel,kernelSizeX,kernelSizeY,resultMatrix);
        }
    }

    ImagenPGM *imageResult = new ImagenPGM (height, width, colorDepth, resultMatrix);

        for (int i = 0; i < height; ++i) {
            delete resultMatrix[i];
            resultMatrix[i]=0;
        }

    delete resultMatrix;
    resultMatrix=0;

    return imageResult;
}

void ImagenPGM::applyKerneltoPixel(int i,int j,int **kernel, int kernelSizeX, int kernelSizeY, int **matrix){

    int ii=0,jj=0,newPixel=0,div=0;
    for (int x = 0; x < kernelSizeX; ++x) {
        ii=(floor(kernelSizeX/2)*-1)+x+i;
        for (int y = 0; y < kernelSizeY; ++y) {
            jj=(floor(kernelSizeY/2)*-1)+y+j;
            newPixel+=*matrixImagenP[ii][jj]*kernel[x][y];
            div+=abs(kernel[x][y]);
            //QTextStream (stdout) <<"newPixel: "<<newPixel;
        }
    }
    int cond=qRound(newPixel/div);
    if(cond>=0&&cond<256)
        matrix[i][j]=cond;
    else if (cond<0)
        matrix[i][j]=0;
    else
        matrix[i][j]=255;
}

Image* ImagenPGM::meanFilter(int kernelSize){

    int **kernel= new int*[kernelSize];
    for (int i = 0; i < kernelSize; ++i) {
        kernel[i]=new int[kernelSize];
    }

    for (int i = 0; i < kernelSize; ++i) {
        for (int j = 0; j < kernelSize; ++j) {
            kernel[i][j]=1;
        }
    }
    return applyKernel(kernel, kernelSize,kernelSize);
}

Image *ImagenPGM::convolutionFilter(int **kernel, int size){
    return applyKernel(kernel,size,size);
}

Image* ImagenPGM::gaussianaFilter(int sigma, int kernelSize){
    int *vectorActual, *vectorAux;
    vectorActual = new int [kernelSize];
    vectorAux = new int [kernelSize];
    for (int i = 0; i < kernelSize; ++i) {
        for (int j = 0; j <=i; ++j) {
            if(i==j){vectorAux[j]=1;}
            else if(j!=0){vectorAux[j]+=vectorActual[i-j];}
        }
        for (int r = 0; r <= i; ++r) {
            vectorActual[r]=vectorAux[r];
        }
    }

    delete vectorAux;
    vectorAux=0;
    //return vectorActual;
    return applyKernel(createKernelFilter(vectorActual,kernelSize),kernelSize,kernelSize);
}

int** ImagenPGM::createKernelFilter(int* vectorKernel, int kernelSize){
   // int kernelSize = (2*r) + 1;
   // double g=0,gmin=2*3.1416*pow(sigma,2);
  //  QTextStream cout (stdout);
  //  int *vectorKernel=kernelGaussiana(kernelSize);

    int **kernel= new int*[kernelSize];
    for (int i = 0; i < kernelSize; ++i) {
        kernel[i]=new int[kernelSize];
    }

    //vectorActual = new int [size];cout<< kernelSize <<" "<<gmin<<" "<<sigma<<endl;
    for (int i = 0; i < kernelSize; ++i) {
        for (int j = 0; j < kernelSize; ++j) {
          //  g=exp(-1*((pow(i,2)+pow(j,2))/(2*pow(sigma,2))));
          //  if (g<gmin) {gmin=g;}
          //  kernel[i][j]=round(g*gmin);
            kernel[i][j]=vectorKernel[i]*vectorKernel[j];
        //    cout<<kernel[i][j]<<" ";
        }//cout<<endl;
    }
    return kernel;
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

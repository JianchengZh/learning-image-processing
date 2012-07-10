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
    //QTextStream (stdout) <<"valor streching min  "<< colorDepth <<" "<< minValue << "max "<< maxValue<< "\n";
    for(int i=0; i<colorDepth+1; i++){

        lut[i]=(i-minValue)*colorDepth/(maxValue-minValue);
        //QTextStream (stdout) <<"valor streching  "<< i <<" "<< lut[i] << "\n";
    }

    return new ImagenPGM(height, width, colorDepth, matrixImagenP, lut);
}

//Segmentation

Image *ImagenPGM::kmeans(int clusters, int iterations){

    Image* image2;

    int centroid[clusters];
    srand(time(NULL));
    //extraer aleatoriamente centroides para cada clase de la imagen
    for(int i=0; i < clusters; i++) {
        centroid[i] = *matrixImagenP[rand()%(width-1)][rand()%(height-1)];
    }

    image2 = clasify(centroid, clusters,iterations);

}

Image *ImagenPGM::clasify(int* centroid, int size , int iterations){



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
int** ImagenPGM::applyKernel(int **kernel, int kernelSizeX, int kernelSizeY){

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
    return resultMatrix;
}

void ImagenPGM::applyKerneltoPixel(int i,int j,int **kernel, int kernelSizeX, int kernelSizeY, int **matrix){

    int ii=0,jj=0,newPixel=0,div=0;
    for (int x = 0; x < kernelSizeX; ++x) {
        ii=(floor(kernelSizeX/2)*-1)+x+i;
        for (int y = 0; y < kernelSizeY; ++y) {
            jj=(floor(kernelSizeY/2)*-1)+y+j;
            newPixel+=*matrixImagenP[ii][jj]*kernel[x][y];
            div+=abs(kernel[x][y]);
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
    //  return applyKernel(kernel, kernelSize,kernelSize);
    ImagenPGM *imageResult = new ImagenPGM (height, width, colorDepth, applyKernel(kernel, kernelSize,kernelSize));
    return imageResult;
}

Image *ImagenPGM::convolutionFilter(int **kernel, int kernelSize){
    //return applyKernel(kernel,size,size);
    ImagenPGM *imageResult = new ImagenPGM (height, width, colorDepth, applyKernel(kernel, kernelSize,kernelSize));
    return imageResult;
}

Image* ImagenPGM::gaussianaFilter(int kernelSize){
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
    ImagenPGM *imageResult = new ImagenPGM (height, width, colorDepth, applyKernel(createKernelFilter(vectorActual,vectorActual,kernelSize),kernelSize,kernelSize));
    return imageResult;
}


Image* ImagenPGM::noiseCleaningLine(double delta){
    int** resultMatrix = new int*[height];
    for (int i = 0; i < height; ++i) {
        resultMatrix[i] = new int[width];
        for (int j = 0; j < width; ++j) {
            resultMatrix[i][j]=*matrixImagenP[i][j];
        }
    }
    for(int i =1; i< height-1; i++){
        for(int j =2; j< width-2; j++){



            int test=*matrixImagenP[i][j], neighbors,sum=0;
            sum+=*matrixImagenP[i][j-1];
            sum+=*matrixImagenP[i][j-2];
            sum+=*matrixImagenP[i][j+1];
            sum+=*matrixImagenP[i][j+2];
            neighbors = qRound(sum/4.0);

            if(fabs(test - neighbors) > delta){
                resultMatrix[i][j]=neighbors;
            }else{
                resultMatrix[i][j]=test;
            }
            int cond=resultMatrix[i][j];
            if(cond>=0&&cond<256)
                resultMatrix[i][j]=cond;
            else if (cond<0)
                resultMatrix[i][j]=0;
            else
                resultMatrix[i][j]=255;
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


Image* ImagenPGM::noiseCleaningPixel(int delta){
    int** resultMatrix = new int*[height];
    for (int i = 0; i < height; ++i) {
        resultMatrix[i] = new int[width];
        for (int j = 0; j < width; ++j) {
            resultMatrix[i][j]=*matrixImagenP[i][j];
        }
    }

    for(int i =1; i< height-1; i++){
        for(int j =1; j< width-1; j++){
            int test=*matrixImagenP[i][j], neighbors,sum=0;
            sum+=*matrixImagenP[i-1][j-1];
            sum+=*matrixImagenP[i-1][j];
            sum+=*matrixImagenP[i-1][j+1];
            sum+=*matrixImagenP[i][j-1];
            sum+=*matrixImagenP[i][j+1];
            sum+=*matrixImagenP[i+1][j-1];
            sum+=*matrixImagenP[i+1][j];
            sum+=*matrixImagenP[i+1][j+1];
            neighbors = qRound(sum/8.0);

            if(fabs(test - neighbors) > delta){
                resultMatrix[i][j]=neighbors;
            }else{
                resultMatrix[i][j]=test;
            }
            int cond=resultMatrix[i][j];
            if(cond>=0&&cond<256)
                resultMatrix[i][j]=cond;
            else if (cond<0)
                resultMatrix[i][j]=0;
            else
                resultMatrix[i][j]=255;
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


int** ImagenPGM::createKernelFilter(int* vectorKerneli,int* vectorKernelj, int kernelSize){
    int **kernel= new int*[kernelSize];
    for (int i = 0; i < kernelSize; ++i) {
        kernel[i]=new int[kernelSize];
    }

    for (int i = 0; i < kernelSize; ++i) {
        for (int j = 0; j < kernelSize; ++j) {
            kernel[i][j]=vectorKerneli[i]*vectorKernelj[j];
        }
    }
    return kernel;
}

//Edge Detection

Image* ImagenPGM::edgeDetectionSobel(int position){
    int kernelSize=3;
    int *vectorKerneli=new int[kernelSize];
    int *vectorKernelj=new int[kernelSize];
    vectorKerneli[0]=-1; vectorKerneli[1]=0; vectorKerneli[2]=1;
    vectorKernelj[0]=1; vectorKernelj[1]=2; vectorKernelj[2]=1;
    ImagenPGM *imageResult;

    resultMatrixI = new int*[height];
    resultMatrixJ = new int*[height];
    for (int i = 0; i < height; ++i) {
        resultMatrixI[i] = new int[width];
        resultMatrixJ[i] = new int[width];
    }
    meanFilter(kernelSize);
    resultMatrixI=applyKernel(createKernelFilter(vectorKernelj,vectorKerneli,kernelSize),kernelSize,kernelSize);
    resultMatrixJ=applyKernel(createKernelFilter(vectorKerneli,vectorKernelj,kernelSize),kernelSize,kernelSize);

    if(position==0){
        imageResult = new ImagenPGM (height, width, colorDepth,resultMatrixI);
    }else if(position==1){
        imageResult = new ImagenPGM (height, width, colorDepth,resultMatrixJ);
    }else if(position==2){
        matrizMagnitud();
        imageResult = new ImagenPGM (height, width, colorDepth,Umbral());

        for (int i = 0; i < height; ++i) {
            delete resultMatrixGradiente[i];resultMatrixGradiente[i]=0;
        }
        delete resultMatrixGradiente; resultMatrixGradiente=0;

    }else{
        matrizMagnitud();
        matrizDirection();
    }

    for (int i = 0; i < height; ++i) {
        delete resultMatrixI[i];resultMatrixI[i]=0;
        delete resultMatrixJ[i];resultMatrixJ[i]=0;
    }

    delete resultMatrixI;resultMatrixI=0;
    delete resultMatrixJ;resultMatrixJ=0;

    return imageResult;
}

void ImagenPGM::matrizMagnitud(){
    maxGradiente=0;
    resultMatrixGradiente = new double*[height];
    for (int i = 0; i < height; ++i) {
        resultMatrixGradiente[i] = new double[width];
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            resultMatrixGradiente[i][j]=sqrt(pow(resultMatrixI[i][j],2)+pow(resultMatrixJ[i][j],2));
            if(maxGradiente<resultMatrixGradiente[i][j])
                maxGradiente=resultMatrixGradiente[i][j];
        }
    }
}

void ImagenPGM::matrizDirection(){
    resultMatrixDirection = new int*[height];
    for (int i = 0; i < height; ++i) {
        resultMatrixDirection[i] = new int[width];
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            resultMatrixDirection[i][j]=discretDegree(atan((double)resultMatrixJ[i][j]/resultMatrixI[i][j]));
        }
    }
}

int** ImagenPGM::Umbral(){
    int** resultMatrixImage=new int*[height];
    for (int i = 0; i < height; ++i) {
        resultMatrixImage[i]= new int[width];
    }

    this->generateHistogram();
    int threshold = this->getHistogram()->ThresholdingByIsodata();

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if(resultMatrixGradiente[i][j]>threshold)
                resultMatrixImage[i][j]=0;
            else
                resultMatrixImage[i][j]=resultMatrixGradiente[i][j];
        }
    }

    return resultMatrixImage;
}

/**
    El detector de bordes basado en Canny:
    * Primero se aplica un filtro gaussiano a la imagen.
    * (No implementado) calculo de los thresholds alto y bajo automaticamente (por ahora se piden estos valores)
    * Luego calculamos los componenetes X y Y del gradiente usando los operadores de Sobel.
      Se calcula la magnitud de dichos componentes y el grado o angulo que forman.
      La magnitud del gradiente deberia ser un double para que no se pierdan valores.
      El grado DEBE de ser un double para que este pueda luego ser discretizado en valores enteros y angulos precisos.
    * Se aplica Non Maximum Suppression a la magnitud del gradiente. Tambien deberia de ser double si la magnitud lo es.
    * Se aplica hysteresis a la matriz con el non maximum Suppression, usando dos thresholds y
      se sigue el borde solo tomando en cuenta el pixel que este 90° en contra de las manecillas del reloj.
      El resultado es 0 si es un borde y 1 si no es un borde;
*/
//const double gX [3][3] ={{-1,-2,-1},{0,0,0},{1,2,1}} , gY [3][3]= {{-1,0,1},{-2,0,2},{-1,0,1}};


Image* ImagenPGM::edgeDetectorCanny(int thresholdHigh, int thresholdsDown){
    double** edgeNonMaximumSuppression = new double*[height];
    int** edgeHysteresis = new int*[height];
    for (int i = 0; i < height; ++i) {
        edgeNonMaximumSuppression[i] = new double[width];
        edgeHysteresis[i] = new int[width];
        for (int j = 0; j < width; ++j) {
            edgeNonMaximumSuppression[i][j]=(double)*matrixImagenP[i][j];
            edgeHysteresis[i][j]=1;
        }
    }

    /*********************************************/
    //Filtro Gaussiano
    //gaussianaFilter(1,1);
    gaussianaFilter(5);
    //Calculo del Gradiente (magnitud y angulo)

    //****Calculo de los componentes usando los operadores de sobel
    /*Image *temp1 = this->edgeDetectionSobel(0);


    ImagenPGM* temp = (static_cast<ImagenPGM*>(temp1));
    int *** dx ;
    dx= (temp->getMatrix());
    //int ** dx=*((ImagenPGM*)(edgeDetectionSobel(0)))->getMatrix();

    temp = (static_cast<ImagenPGM*>(this->edgeDetectionSobel(1)));
    int *** dy ;
    dy = (temp->getMatrix());
    QTextStream (stdout) <<" mag! " << endl << endl << endl << endl;*/

    //****Calculo de la magnitud y angulo del gradiente a partir de lso componentes
    edgeDetectionSobel(3);

    for(int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if(i==0 || j==0 || i==height-1 || j==width-1){// si son los bordes de la imagen completa
                edgeNonMaximumSuppression[i][j]=0;
                edgeHysteresis[i][j]=1;
            }
        }
    }

    //Non Maximum Suppression
    nonMaximumSuppression(edgeNonMaximumSuppression,resultMatrixDirection,resultMatrixGradiente);

    //hysteresis
    hysteresis(edgeHysteresis,edgeNonMaximumSuppression,resultMatrixDirection, thresholdHigh, thresholdsDown);

    /*********************************************/
    ImagenPGM *imageResult = new ImagenPGM (height, width, 1, edgeHysteresis); //OJO SE CAMBIO EL NIVEL DEL COLOR

    for (int i = 0; i < height; ++i) {
        delete edgeNonMaximumSuppression[i]; edgeNonMaximumSuppression[i]=0;
        delete edgeHysteresis[i]; edgeHysteresis[i]=0;
        delete resultMatrixDirection[i]; resultMatrixDirection[i]=0;
        delete resultMatrixGradiente[i]; resultMatrixGradiente[i]=0;

    }
    delete edgeNonMaximumSuppression; edgeNonMaximumSuppression=0;
    delete edgeHysteresis; edgeHysteresis=0;

    delete resultMatrixDirection; resultMatrixDirection=0;
    delete resultMatrixGradiente; resultMatrixGradiente=0;

    return imageResult;
}

/**
    Discretiza los valores del angulo para indicar los angulos posibles que son 8.
*/
int ImagenPGM::discretDegree(double value){
    double degree = (value + PI/2.0) * 180 / PI;

    if(degree<0 || degree > 180){
        QTextStream (stdout) <<"error discret degree! \n";

        //degree = 360 + degree;
    }

    if((degree>= 0 && degree <22.5) ||(degree>=157.5 && degree<=180)){
        return 0;
    }else if(degree>= 22.5 && degree <67.5){
        return 1;
    }else if(degree>= 67.5 && degree <112.5){
        return 2;
    }else if(degree>= 112.5 && degree <157.5){
        return 3;
    }

    //cerr << "no entro discret" << endl;
    return -1;

}

/**
    Se suprimen los valores que sean menores a los dos vecinos que indique la dirección del gradiente, de lo contrario se deja el valor de la magnitud
*/

void ImagenPGM::nonMaximumSuppression(double **edgeNonMaximumSuppression, int** gradientDegreeDiscret, double**gradientMagnitude){

    for(int i = 0 ; i< height;i++ ){
        for(int j = 0 ; j< width;j++ ){

            int orientation = gradientDegreeDiscret[i][j];
            double valueGradient = gradientMagnitude[i][j];
            edgeNonMaximumSuppression[i][j]=gradientMagnitude[i][j];
            switch(orientation){
            case 0:
                if(j==0){
                    if(valueGradient <= gradientMagnitude[i][j+1]){
                        edgeNonMaximumSuppression[i][j]=0;
                    }
                }else if(j == width-1){
                    if(valueGradient <= gradientMagnitude[i][j-1]){
                        edgeNonMaximumSuppression[i][j]=0;
                    }
                }else{
                    if(valueGradient <= gradientMagnitude[i][j+1] || valueGradient <= gradientMagnitude[i][j-1]){
                        edgeNonMaximumSuppression[i][j]=0;
                    }
                }
                break;
            case 1:
                if((i == 0 && j!=0) || (j==0 && i!=0)){
                    if(valueGradient <= gradientMagnitude[i-1][j+1]){
                        edgeNonMaximumSuppression[i][j]=0;
                    }

                }else if((i == height-1 && j!=width-1) || (j==width-1 && i!=height-1)){
                    if(valueGradient <= gradientMagnitude[i+1][j-1]){
                        edgeNonMaximumSuppression[i][j]=0;
                    }
                }else if((j !=0 && i!=0) && (i!=height-1 && j!=width-1)){//no sea las esquinas
                    if(valueGradient <= gradientMagnitude[i+1][j-1] || valueGradient <= gradientMagnitude[i-1][j+1]){
                        edgeNonMaximumSuppression[i][j]=0;

                    }
                }
            case 2:
                if(i==0){
                    if(valueGradient <= gradientMagnitude[i+1][j]){
                        edgeNonMaximumSuppression[i][j]=0;
                    }
                }else if(i == height-1){
                    if(valueGradient <= gradientMagnitude[i-1][j]){
                        edgeNonMaximumSuppression[i][j]=0;
                    }
                }else{
                    if(valueGradient <= gradientMagnitude[i+1][j] || valueGradient <= gradientMagnitude[i-1][j]){
                        edgeNonMaximumSuppression[i][j]=0;
                    }
                }
            case 3:
                if((i == 0 && j!=width-1) || (j==0 && i!=height-1)){
                    if(valueGradient <= gradientMagnitude[i+1][j+1]){
                        edgeNonMaximumSuppression[i][j]=0;
                    }

                }else if((i == height-1 && j!=0) || (j==width-1 && i!=0)){
                    if(valueGradient <= gradientMagnitude[i-1][j-1]){
                        edgeNonMaximumSuppression[i][j]=0;
                    }
                }else if((j !=0 && i!=height-1) && (i!=0 && j!=width-1)){//no sea las esquinas
                    if(valueGradient <= gradientMagnitude[i+1][j+1] || valueGradient <= gradientMagnitude[i-1][j-1]){
                        edgeNonMaximumSuppression[i][j]=0;

                    }
                }
                break;
            }


        }
    }

}
/**
    Se aplica para determinar los bordes de la imagen.
    Primero se buscan los valores que esten por encima del thresholdHigh y
    si es asi se empieza a recorrer en busca de los siguientes puntos que esten por encima del thresholdDown.

*/
void ImagenPGM::hysteresis(int**edgeHysteresis, double **edgeNonMaximumSuppression,int**gradientDegreeDiscret, int thresholdHigh, int thresholdsDown){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width ; j++){
            //QTextStream (stdout) << (edgeNonMaximumSuppression[i][j]/8)<<" \n";

            if((edgeNonMaximumSuppression[i][j])>=(double)thresholdHigh){//OJO AQUI CON LA DIVISION
                edgeFollow(i,j, edgeHysteresis, edgeNonMaximumSuppression,gradientDegreeDiscret,thresholdsDown);
            }
        }
    }
    //0 es borde , 1 no es borde
}

/**
    Metodo que  sigue un borde. Toma el pixel actual que es mayor al threshold y se toma como un borde.
    Luego se mueve a la posicion siguiente (90° respecto angulo gradiente contra manecillas reloj).
    Determina si es mayor por lo menos al thresholdDown y si es asi llama recursivamente a la función.
    La función para si ya lo hemos visitado o no es mayor al thresholdDown.
*/
int ImagenPGM::edgeFollow(int posX, int posY, int **edgeHysteresis, double **edgeNonMaximumSuppression, int **gradientDegreeDiscret, int thresholdsDown){
    if(edgeHysteresis[posX][posY]==1){//si no lo visite
        edgeHysteresis[posX][posY]=0;
        int degree = gradientDegreeDiscret[posX][posY];
        //cout << degree << endl;
        switch(degree){//mover al siguiente punto 90° respecto angulo gradiente contra manecillas reloj
        case 0:
            posY--;
            posX--;
            break;
        case 1:
            posX-=2;
            break;
        case 2:
            posY++;
            posX--;
            break;
        case 3:
            posY+=2;
            break;
        case 4:
            posY++;
            posY++;
            break;
        case 5:
            posX+=2;
            break;
        case 6:
            posX++;
            posY--;
            break;
        case 7:
            posY-=2;
            break;

        }
        //siguiente punto
        //OJO CON LA DIVISION
        if(!(posX<0 || posX>=height) && !(posY<0 || posY>=width) && ((edgeNonMaximumSuppression[posX][posY]) >= (double)thresholdsDown)){//puede interesarme
            if(edgeFollow(posX, posY,edgeHysteresis, edgeNonMaximumSuppression,gradientDegreeDiscret,thresholdsDown)){
                edgeHysteresis[posX][posY]=0;
                return 1;
            }

        }
        return 1;//REVISAR el valor siguiente aun no se ha asignado
    }
    return 0;
}

//Morphological Operation
int** ImagenPGM::matrixMorphological(int** matrixStructuringElement,int origenX,int origenY,int heightS,int widthS,int option){
    int** resultMatrixImage= new int*[height];
    for (int i = 0; i < height; ++i) {
        resultMatrixImage[i]= new int[width];
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (option==0) {
                resultMatrixImage[i][j]=*matrixImagenP[i][j];
            } else {
                resultMatrixImage[i][j]=1;
            }
        }
    }

    int** temporalMSElement= new int*[heightS];
    for (int i = 0; i < heightS; ++i) {
        temporalMSElement[i]=new int[widthS];
    }
    int clave=0;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            clave=0;
            if(*matrixImagenP[i+origenY][j+origenX]==0){
                if(i+origenY<height&&j+origenX<width){
                    for (int x = 0; x < heightS; ++x) {
                        for (int y = 0; y < widthS; ++y) {
                            if(0<=i+(x-origenY)&&i+(x-origenY)<height&&0<=j+(y-origenX)&&j+(y-origenX)<width){
                                if (option==0) {
                                    if(matrixStructuringElement[x][y]==0)
                                        if(resultMatrixImage[i+(x-origenY)][j+(y-origenX)]!=0)
                                            resultMatrixImage[i+(x-origenY)][j+(y-origenX)]=0;
                                } else {
                                    if(*matrixImagenP[i+(x-origenY)][j+(y-origenX)]==matrixStructuringElement[x][y]){
                                        clave++;
                                    }
                                }
                            }
                        }
                    }
                    if(clave==heightS*widthS){
                        for (int x = 0; x < heightS; ++x) {
                            for (int y = 0; y < widthS; ++y) {
                                resultMatrixImage[i+(x-origenY)][j+(y-origenX)]=temporalMSElement[x][y];
                            }
                        }
                        clave=0;
                    }
                }
            }
        }
    }
    return resultMatrixImage;
}

Image* ImagenPGM::dilateOperation(int** matrixStructuringElement,int origenX,int origenY,int heightS,int widthS){

    int** resultMatrixImage = new int*[height];
    for (int i = 0; i < height; ++i) {
        resultMatrixImage[i] = new int[width];
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            resultMatrixImage[i][j]=*matrixImagenP[i][j];
        }
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            //
            if(i+origenY<height&&j+origenX<width)
                if(*matrixImagenP[i+origenY][j+origenX]==0){
                    for (int x = 0; x < heightS; ++x) {
                        for (int y = 0; y < widthS; ++y) {

                            if(matrixStructuringElement[x][y]==0)
                                if(0<=i+(x-origenY)&&i+(x-origenY)<height&&0<=j+(y-origenX)&&j+(y-origenX)<width){
                                    if(resultMatrixImage[i+(x-origenY)][j+(y-origenX)]!=0)//{
                                        resultMatrixImage[i+(x-origenY)][j+(y-origenX)]=0;
                                    // cout<<"("<<i+(x-origenX)<<","<<j+(y-origenY)<<") ";}
                                }//cout<<endl;
                        }
                    }
                }
        }
    }

    ImagenPGM *imageResult = new ImagenPGM (height, width, colorDepth, resultMatrixImage);

    for (int i = 0; i < height; ++i) {
        delete resultMatrixImage[i]; resultMatrixImage[i]=0;
    }   delete resultMatrixImage;resultMatrixImage=0;

    return imageResult;
}

Image* ImagenPGM::erosionOperation(int** matrixStructuringElement,int origenX,int origenY,int heightS,int widthS){

    int** resultMatrixImage = new int*[height];
    for (int i = 0; i < height; ++i) {
        resultMatrixImage[i] = new int[width];
    }

    int** memoryposition = new int*[heightS*widthS];
    for (int i = 0; i < heightS*widthS; ++i) {
        memoryposition[i] = new int[2];
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            resultMatrixImage[i][j]=1;
        }
    }

    int key=0;
    for (int i = origenY; i < height; ++i) {
        for (int j = origenX; j < width; ++j) {
            key=0;
            if(*matrixImagenP[i][j]==0){
                for (int x = 0; x < heightS; ++x) {
                    for (int y = 0; y < widthS; ++y) {
                        if(0<=i+(x-origenY)&&i+(x-origenY)<height&&0<=j+(y-origenX)&&j+(y-origenX)<width)
                            if(*matrixImagenP[i+(x-origenY)][j+(y-origenX)]==matrixStructuringElement[x][y]){
                                resultMatrixImage[i+(x-origenY)][j+(y-origenX)]=0;
                              //  cout<<"("<<i+(x-origenY)<<","<<j+(y-origenX)<<") = "<<*matrixImagenP[i+(x-origenY)][j+(y-origenX)]<<" SM "<<matrixStructuringElement[x][y]<<endl;
                                memoryposition[x+y][0]=i+(x-origenY);
                                memoryposition[x+y][1]=j+(y-origenX);
                                key++;
                            }
                    }
                }
                if(key==heightS*widthS){
                    for (int x = 0; x < heightS; ++x) {
                        for (int y = 0; y < widthS; ++y){
                            for (int z = 0; z <= x+y; ++z) {
                                resultMatrixImage[memoryposition[z][0]][memoryposition[z][1]]=1;
                            }
                        }
                    }
                    key=0;
                }
            }
        }
    }


    ImagenPGM *imageResult = new ImagenPGM (height, width, colorDepth, resultMatrixImage);

    for (int i = 0; i < height; ++i) {
        delete resultMatrixImage[i]; resultMatrixImage[i]=0;
    }   delete resultMatrixImage;resultMatrixImage=0;

    for (int i = 0; i < heightS*widthS; ++i) {
        delete memoryposition[i]; memoryposition[i]= 0;
    }delete memoryposition; memoryposition=0;

    return imageResult;
}

// Export

void ImagenPGM::saveImage(QString filename){

    if (!filename.contains(".pgm")) {
        filename=filename+".pgm";
    };
    ofstream fSalida(filename.toStdString().c_str(), ios::out|ios::binary);
    if(!identification.compare("P2")){
        string id = identification.toStdString();
        fSalida << id << endl;
        fSalida<<"#LEARNING IMAGE PROCESSING by GUSTAVO & EDWIN AT UNIVALLE"<<endl;
        fSalida<<width<<" "<<height<<endl;
        fSalida<<colorDepth<<endl;

        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                fSalida<<*matrixImagenP[i][j]<<" ";
            }
            fSalida<<endl;
        }

    }else if(!identification.compare("P5")){
        fSalida<<identification.toStdString()<<endl;
        fSalida<<"#LEARNING IMAGE PROCESSING by GUSTAVO & EDWIN AT UNIVALLE"<<endl;
        fSalida << width << " " << height << "\n";
        fSalida << colorDepth << "\n";
        unsigned char *image;
        image = (unsigned char *) new unsigned char [this->height*this->width];

        for(int i=0; i<this->height; i++)
            for(int j=0; j<this->width; j++)
                image[i*this->width+j]=(unsigned char)*matrixImagenP[i][j];



        fSalida.write( reinterpret_cast<char *>(image), (this->width*this->height)*sizeof(unsigned char));
        delete [] image;
    }

    fSalida.close();


    /*QFile temp(filename);
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
    }*/


}

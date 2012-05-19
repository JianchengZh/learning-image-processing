//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: imagenppm.cpp
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

#include "imagenppm.h"

//Constructors
ImagenPPM::ImagenPPM(QString filename){

    ImageFile imageFile(filename);
    if (imageFile.readFile()) {

        this->identification=imageFile.getId();
        this->comment="#";
        this->width=imageFile.getWidth();
        this->height=imageFile.getHeight();
        this->colorDepth=imageFile.getColorDepth();
        this->imageType="PPM";

        int *matrix=imageFile.getMatrix();

        matrixRp = new int**[height];
        matrixGp = new int**[height];
        matrixBp = new int**[height];
        for (int i=0; i < height; i++){
            matrixRp[i]=new int*[width];
            matrixGp[i]=new int*[width];
            matrixBp[i]=new int*[width];
        }

        //Lookup Table
        lutR = new int [colorDepth+1];
        lutG = new int [colorDepth+1];
        lutB = new int [colorDepth+1];
        for (int i = 0; i < colorDepth+1; ++i) {
            lutR[i]=i;
            lutG[i]=i;
            lutB[i]=i;
        }

        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                matrixRp[i][j]=&lutR[matrix[(i*width*3)+(j*3)]];
                matrixGp[i][j]=&lutG[matrix[(i*width*3)+(j*3)+1]];
                matrixBp[i][j]=&lutB[matrix[(i*width*3)+(j*3)+2]];
                QTextStream (stdout)<<*matrixRp[i][j]<<" "<<*matrixGp[i][j]<<" "<<*matrixBp[i][j]<<"    ";
            }
            QTextStream (stdout) <<""<<endl;
        }
        status=true;
    } else {
        status=false;
    }
}

ImagenPPM::ImagenPPM(QString id, QString comment, int h, int w, int depth, int **matrizR, int **matrizG, int **matrizB)
{
    this->identification=id;
    this->comment=comment;
    this->height=h;
    this->width=w;
    this->colorDepth=depth;
    this->imageType="PPM";

    //Lookup Table
    lutR = new int [colorDepth+1];
    lutG = new int [colorDepth+1];
    lutB = new int [colorDepth+1];
    for (int i = 0; i < colorDepth+1; ++i) {
        lutR[i]=i;
        lutG[i]=i;
        lutB[i]=i;
    }

    // Matriz Inicialization:
    matrixRp = new int**[height];
    matrixGp = new int**[height];
    matrixBp = new int**[height];
    for (int i=0; i < height; i++){
        matrixRp[i]=new int*[width];
        matrixGp[i]=new int*[width];
        matrixBp[i]=new int*[width];
    }

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            matrixRp[i][j]=&lutR[matrizR[i][j]];
            matrixGp[i][j]=&lutG[matrizG[i][j]];
            matrixBp[i][j]=&lutB[matrizB[i][j]];
        }
    }

}

ImagenPPM::ImagenPPM(QString id, QString comment, int h, int w, int colorD, int ***matrizR, int *lutR, int ***matrizG, int *lutG, int ***matrizB, int *lutB){
    this->identification=id;
    this->comment=comment;
    this->width=w;
    this->height=h;
    this->colorDepth=colorD;
    this->imageType="PPM";

    //Lookup Table
    this->lutR = new int [colorDepth+1];
    this->lutG = new int [colorDepth+1];
    this->lutB = new int [colorDepth+1];
    for (int i = 0; i < colorDepth+1; ++i) {
        this->lutR[i]=lutR[i];
        this->lutG[i]=lutG[i];
        this->lutB[i]=lutB[i];
    }

    // Matrix of Pointers
    matrixRp = new int**[height];
    matrixGp = new int**[height];
    matrixBp = new int**[height];
    for (int i=0; i < height; i++){
        matrixRp[i]=new int*[width];
        matrixGp[i]=new int*[width];
        matrixBp[i]=new int*[width];
    }

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            matrixRp[i][j]=&this->lutR[*matrizR[i][j]];
            matrixGp[i][j]=&this->lutG[*matrizG[i][j]];
            matrixBp[i][j]=&this->lutB[*matrizB[i][j]];
        }
    }
}

ImagenPPM::~ImagenPPM(){

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            matrixRp[i][j]=0;
            matrixGp[i][j]=0;
            matrixBp[i][j]=0;
        }

        delete matrixRp[i];
        matrixRp[i]=0;

        delete matrixGp[i];
        matrixGp[i]=0;

        delete matrixBp[i];
        matrixBp[i]=0;
    }

    delete matrixRp;
    this->matrixRp = 0;

    delete matrixRp;
    this->matrixRp = 0;

    delete matrixRp;
    this->matrixRp = 0;

    delete lutR;
    this->lutR=0;

    delete lutG;
    this->lutG=0;

    delete lutB;
    this->lutB=0;
}

//Image processing
Image* ImagenPPM::changeSize(int factor){

    int newwidth=0,newheight=0;
    int **enlargedR, **enlargedG, **enlargedB;
    ImagenPPM *imageResized;

    if (factor>0) {
        newwidth = this->width*factor;
        newheight = this->height*factor;

        // Initialization
        enlargedR = new int*[newheight];
        enlargedG = new int*[newheight];
        enlargedB = new int*[newheight];
        for (int i=0; i < newheight; i++){
            enlargedR[i]=new int[newwidth];
            enlargedG[i]=new int[newwidth];
            enlargedB[i]=new int[newwidth];
        }

        // Proceso de reduccion
        for (int i = 0; i <newheight; ++i) {
            for (int j = 0; j < newwidth; ++j) {
                enlargedR[i][j]=*(matrixRp[(int)floor(i/factor)][(int)floor(j/factor)]);
                enlargedG[i][j]=*(matrixGp[(int)floor(i/factor)][(int)floor(j/factor)]);
                enlargedB[i][j]=*(matrixBp[(int)floor(i/factor)][(int)floor(j/factor)]);
            }
        }

        imageResized = new ImagenPPM (identification,
                                      comment,
                                      newwidth,
                                      newheight,
                                      colorDepth,
                                      enlargedR,
                                      enlargedG,
                                      enlargedB);

        // Elimination
        for (int i=0; i < newheight; i++){
            delete enlargedR[i];
            delete enlargedG[i];
            delete enlargedB[i];
        }
        delete enlargedR;
        delete enlargedG;
        delete enlargedB;

    }else {
        factor*=-1;
        newwidth = (int)ceil(this->width/factor);
        newheight = (int)ceil(this->height/factor);

        // Initialization
        enlargedR = new int*[newheight];
        enlargedG = new int*[newheight];
        enlargedB = new int*[newheight];
        for (int i=0; i < newheight; i++){
            enlargedR[i]=new int[newwidth];
            enlargedG[i]=new int[newwidth];
            enlargedB[i]=new int[newwidth];
        }

        // Proceso de reduccion
        for(int i=0; i <newheight; i++){
            for(int j=0; j<newwidth; j++){
                enlargedR[i][j]=*(matrixRp[i*factor][j*factor]);
                enlargedG[i][j]=*(matrixGp[i*factor][j*factor]);
                enlargedB[i][j]=*(matrixBp[i*factor][j*factor]);
            }
        }

        imageResized = new ImagenPPM (identification,
                                      comment,
                                      newwidth,
                                      newheight,
                                      colorDepth,
                                      enlargedR,
                                      enlargedG,
                                      enlargedB);

        // Elimination
        for (int i=0; i < newheight; i++){
            delete enlargedR[i];
            delete enlargedG[i];
            delete enlargedB[i];
        }
        delete enlargedR;
        delete enlargedG;
        delete enlargedB;
    }
    return imageResized;
}

Image* ImagenPPM::changeColorDepth(int bits){

    if((int)(pow(2,bits)-1)<colorDepth){

        int newColorDepth=(int)(pow(2,bits)-1);
        int divisor = (colorDepth+1)/(newColorDepth+1);
        for(int i=0; i<colorDepth+1; i++){
            lutR[i]=lutR[i]/divisor;
            lutG[i]=lutG[i]/divisor;
            lutB[i]=lutB[i]/divisor;
        }
        return new ImagenPPM (identification,
                              comment,
                              height,
                              width,
                              newColorDepth,
                              matrixRp,
                              lutR,
                              matrixGp,
                              lutG,
                              matrixBp,
                              lutB);

    }else if ((int)(pow(2,bits)-1)>colorDepth) {

        int newColorDepth=(int)(pow(2,bits)-1);
        int divisor = (newColorDepth+1)/(colorDepth+1);
        for(int i=0; i<colorDepth+1; i++){
            lutR[i]=lutR[i]*divisor;
            lutG[i]=lutG[i]*divisor;
            lutB[i]=lutB[i]*divisor;
        }
        return new ImagenPPM (identification,
                              comment,
                              height,
                              width,
                              newColorDepth,
                              matrixRp,
                              lutR,
                              matrixGp,
                              lutG,
                              matrixBp,
                              lutB);

    }else{
        return this;
    }
}

ImagenPGM* ImagenPPM::convertToGrayScale(int method){

    ImagenPGM *result;

    int **grayScaleMatrix = new int*[height];
    for (int i=0; i < height; i++)
        grayScaleMatrix[i]=new int[width];

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if(method==16384)
                grayScaleMatrix[i][j]=(int)(0.299*matrixRp[i][j][0]+0.587*matrixGp[i][j][0]+0.114*matrixBp[i][j][0]);
            else
                grayScaleMatrix[i][j]=(int)(0.33*matrixRp[i][j][0]+0.33*matrixGp[i][j][0]+0.33*matrixBp[i][j][0]);
        }
    }

    result = new ImagenPGM ("P2",
                            comment,
                            height,
                            width,
                            colorDepth,
                            grayScaleMatrix);

    for (int i=0; i < height; i++)
        delete grayScaleMatrix[i];
    delete grayScaleMatrix;

    return result;

}

// export
void ImagenPPM::saveImage(QString filename){

    if (!filename.contains(".ppm")) {
        filename=filename+".ppm";
    }

    QFile temp(filename);
    if(temp.open(QFile::WriteOnly)){
        QTextStream fSalida(&temp);

        fSalida<<identification<<endl;
        fSalida<<comment<<endl;
        fSalida<<width<<" "<<height<<endl;
        fSalida<<colorDepth<<endl;

        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                fSalida<<*(matrixRp[i][j])<<" "<<*(matrixGp[i][j])<<" "<<*(matrixBp[i][j])<<"    ";
            }
            fSalida<<endl;
        }
    }
}

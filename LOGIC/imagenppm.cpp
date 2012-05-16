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
ImagenPPM::ImagenPPM(QList<QString> lectura){

    this->identification=lectura.at(0);
    this->comment=lectura.at(1);
    this->width=lectura.at(2).section(' ',0,0).toInt();
    this->height=lectura.at(2).section(' ',1,1).toInt();
    this->colorDepth=lectura.at(3).toInt();
    this->lutSize=colorDepth;
    this->imageType="PPM";

    matrixRp = new int**[height];
    matrixGp = new int**[height];
    matrixBp = new int**[height];
    for (int i=0; i < height; i++){
        matrixRp[i]=new int*[width];
        matrixGp[i]=new int*[width];
        matrixBp[i]=new int*[width];
    }

    //Lookup Table
    lutR = new int [lutSize+1];
    lutG = new int [lutSize+1];
    lutB = new int [lutSize+1];
    for (int i = 0; i < lutSize+1; ++i) {
        lutR[i]=i;
        lutG[i]=i;
        lutB[i]=i;
    }

    int aux1=4;
    int aux2=5;
    int aux3=6;
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            matrixRp[i][j]=&lutR[lectura[i+j+aux1].toInt()];
            matrixGp[i][j]=&lutG[lectura[i+j+aux2].toInt()];
            matrixBp[i][j]=&lutB[lectura[i+j+aux3].toInt()];
            aux1=aux1+2;
            aux2=aux2+2;
            aux3=aux3+2;
        }
        aux1=aux1+width-1;
        aux2=aux2+width-1;
        aux3=aux3+width-1;
    }
}

ImagenPPM::ImagenPPM(QString id, QString comment, int h, int w, int depth, int **matrizR, int **matrizG, int **matrizB)
{
    this->identification=id;
    this->comment=comment;
    this->height=h;
    this->width=w;
    this->colorDepth=depth;
    this->lutSize=colorDepth;
    this->imageType="PPM";

    //Lookup Table
    lutR = new int [lutSize+1];
    lutG = new int [lutSize+1];
    lutB = new int [lutSize+1];
    for (int i = 0; i < lutSize+1; ++i) {
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

ImagenPPM::ImagenPPM(QString id, QString comment, int h, int w, int colorD, int ***matrizR, int *lutR, int ***matrizG, int *lutG, int ***matrizB, int *lutB, int lutSize){
    this->identification=id;
    this->comment=comment;
    this->width=w;
    this->height=h;
    this->colorDepth=colorD;
    this->lutSize=lutSize;
    this->imageType="PPM";

    //Lookup Table
    this->lutR = new int [lutSize+1];
    this->lutG = new int [lutSize+1];
    this->lutB = new int [lutSize+1];
    for (int i = 0; i < lutSize+1; ++i) {
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
        for(int i=0; i<lutSize; i++){
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
                              lutB,
                              lutSize);

    }else if ((int)(pow(2,bits)-1)>colorDepth) {

        int newColorDepth=(int)(pow(2,bits)-1);
        int divisor = (newColorDepth+1)/(colorDepth+1);
        for(int i=0; i<lutSize; i++){
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
                              lutB,
                              lutSize);

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

    QFile temp(filename+"."+imageType.toLower());
    if(temp.open(QFile::WriteOnly)){
        QTextStream fSalida(&temp);

        fSalida<<identification<<endl;
        fSalida<<comment<<endl;
        fSalida<<width<<" "<<height<<endl;
        fSalida<<colorDepth<<endl;

        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                fSalida<<*(matrixRp[i][j])<<endl<<*(matrixGp[i][j])<<endl<<*(matrixBp[i][j])<<endl;
            }
        }
    }
}































//ImagenPPM* ImagenPPM::reducirTamano(){

//    int r=2;
//    int nColumnasReducida=width/r;
//    int nFilasReducida=height/r;

//    // inicializacion
//    int **reducidaR = new int*[nFilasReducida];
//    for (int i=0; i < nFilasReducida; i++)
//        reducidaR[i]=new int[nColumnasReducida];

//    int **reducidaG = new int*[nFilasReducida];
//    for (int i=0; i < nFilasReducida; i++)
//        reducidaG[i]=new int[nColumnasReducida];

//    int **reducidaB = new int*[nFilasReducida];
//    for (int i=0; i < nFilasReducida; i++)
//        reducidaB[i]=new int[nColumnasReducida];

//    // Proceso de reduccion
//    for(int i=0; i<nFilasReducida; i++){
//        for(int j=0; j<nColumnasReducida; j++){
//            reducidaR[i][j]=matrizR[i*r][j*r];
//            reducidaG[i][j]=matrizG[i*r][j*r];
//            reducidaB[i][j]=matrizB[i*r][j*r];
//        }
//    }

//    // creacion de nueva imagen reducida

//    return new ImagenPPM (identification,
//                          comment,
//                          nFilasReducida,
//                          nColumnasReducida,
//                          colorDensity,
//                          reducidaR,
//                          reducidaG,
//                          reducidaB);
//}

//ImagenPPM* ImagenPPM::reducirIntensidad(int bits){

//    int intensidadNueva=(int)(pow(2,bits)-1);

//    int **IntensidadR = new int*[height];
//    for (int i=0; i < height; i++)
//        IntensidadR[i]=new int[width];

//    int **IntensidadG = new int*[height];
//    for (int i=0; i < height; i++)
//        IntensidadG[i]=new int[width];

//    int **IntensidadB = new int*[height];
//    for (int i=0; i < height; i++)
//        IntensidadB[i]=new int[width];

//    int divisor = (colorDensity+1)/(intensidadNueva+1);

//    for(int i=0; i<height; i++){
//        for(int j=0; j<width; j++){

//            IntensidadR[i][j]=floor(matrizR[i][j]/divisor);
//            IntensidadG[i][j]=floor(matrizG[i][j]/divisor);
//            IntensidadB[i][j]=floor(matrizB[i][j]/divisor);

//        }
//    }

//    // creacion de nueva imagen intensidad reducida

//    return new ImagenPPM (identification,
//                          comment,
//                          height,
//                          width,
//                          intensidadNueva,
//                          IntensidadR,
//                          IntensidadG,
//                          IntensidadB);

//}

//ImagenPGM* ImagenPPM::convertirGris(int opcion){

//    int **matrizPGM = new int*[height];
//    for (int i=0; i < height; i++)
//        matrizPGM[i]=new int[width];

//    for(int i=0; i<height; i++){
//        for(int j=0; j<width; j++){
//            if(opcion==1)
//                matrizPGM[i][j]=(int)(0.299*matrizR[i][j]+0.587*matrizG[i][j]+0.114*matrizB[i][j]);
//            else
//                matrizPGM[i][j]=(int)(0.33*matrizR[i][j]+0.33*matrizG[i][j]+0.33*matrizB[i][j]);
//        }
//    }

//    ImagenPGM *resultado = new ImagenPGM ("P2",
//                                          comment,
//                                          height,
//                                          width,
//                                          colorDensity,
//                                          matrizPGM);
//    return resultado;
//}

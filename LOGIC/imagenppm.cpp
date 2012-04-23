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

    matrizRp = new int**[height];
    for (int i=0; i < height; i++)
        matrizRp[i]=new int*[width];

    matrizGp = new int**[height];
    for (int i=0; i < height; i++)
        matrizGp[i]=new int*[width];

    matrizBp = new int**[height];
    for (int i=0; i < height; i++)
        matrizBp[i]=new int*[width];

    //Lookup Table
    lutR = new int [lutSize+1];
    for (int i = 0; i < lutSize+1; ++i) {
        lutR[i]=i;
    }
    lutG = new int [lutSize+1];
    for (int i = 0; i < lutSize+1; ++i) {
        lutG[i]=i;
    }
    lutB = new int [lutSize+1];
    for (int i = 0; i < lutSize+1; ++i) {
        lutB[i]=i;
    }

    int aux1=4;
    int aux2=5;
    int aux3=6;
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            matrizRp[i][j]=&lutR[lectura[i+j+aux1].toInt()];
            matrizGp[i][j]=&lutG[lectura[i+j+aux2].toInt()];
            matrizBp[i][j]=&lutB[lectura[i+j+aux3].toInt()];
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
    for (int i = 0; i < lutSize+1; ++i) {
        lutR[i]=i;
    }
    lutG = new int [lutSize+1];
    for (int i = 0; i < lutSize+1; ++i) {
        lutG[i]=i;
    }
    lutB = new int [lutSize+1];
    for (int i = 0; i < lutSize+1; ++i) {
        lutB[i]=i;
    }

    // Matriz Inicialization:
    matrizRp = new int**[height];
    for (int i=0; i < height; i++)
        matrizRp[i]=new int*[width];

    matrizGp = new int**[height];
    for (int i=0; i < height; i++)
        matrizGp[i]=new int*[width];

    matrizBp = new int**[height];
    for (int i=0; i < height; i++)
        matrizBp[i]=new int*[width];

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            matrizRp[i][j]=&lutR[matrizR[i][j]];
        }
    }
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            matrizGp[i][j]=&lutG[matrizG[i][j]];
        }
    }

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            matrizBp[i][j]=&lutB[matrizB[i][j]];
        }
    }
}

ImagenPPM::ImagenPPM(QString id, QString comment, int h, int w, int colorD, int ***matrizR, int *lutR, int ***matrizG, int *lutG, int ***matrizB, int *lutB, int lutSize){
    this->identification=id;
    this->comment=comment;
    this->width=w;
    this->height=h;
    this->colorDepth=colorD;
    this->matrizRp=matrizR;
    this->lutR=lutR;
    this->matrizGp=matrizG;
    this->lutG=lutG;
    this->matrizBp=matrizB;
    this->lutB=lutB;
    this->lutSize=lutSize;

}

//Image processing
Image* ImagenPPM::changeSize(int factor){

    int newwidth=0,newheight=0;
    int **enlargedR, **enlargedG, **enlargedB;

    if (factor>0) {
        newwidth = this->width*factor;
        newheight = this->height*factor;

        enlargedR = new int*[newheight];
        for (int i=0; i < newheight; i++)
            enlargedR[i]=new int[newwidth];

        enlargedG = new int*[newheight];
        for (int i=0; i < newheight; i++)
            enlargedG[i]=new int[newwidth];

        enlargedB = new int*[newheight];
        for (int i=0; i < newheight; i++)
            enlargedB[i]=new int[newwidth];

        for (int i = 0; i <newheight; ++i) {
            for (int j = 0; j < newwidth; ++j) {
                enlargedR[i][j]=*(matrizRp[(int)floor(i/factor)][(int)floor(j/factor)]);
                enlargedG[i][j]=*(matrizGp[(int)floor(i/factor)][(int)floor(j/factor)]);
                enlargedB[i][j]=*(matrizBp[(int)floor(i/factor)][(int)floor(j/factor)]);
            }
        }
    }else {
        factor*=-1;
        newwidth = (int)ceil(this->width/factor);
        newheight = (int)ceil(this->height/factor);

        // inicializacion
        enlargedR = new int*[newheight];
        for (int i=0; i < newheight; i++)
            enlargedR[i]=new int[newwidth];

        enlargedG = new int*[newheight];
        for (int i=0; i < newheight; i++)
            enlargedG[i]=new int[newwidth];

        enlargedB = new int*[newheight];
        for (int i=0; i < newheight; i++)
            enlargedB[i]=new int[newwidth];

        // Proceso de reduccion
        for(int i=0; i <newheight; i++){
            for(int j=0; j<newwidth; j++){
                enlargedR[i][j]=*(matrizRp[i*factor][j*factor]);
                enlargedG[i][j]=*(matrizGp[i*factor][j*factor]);
                enlargedB[i][j]=*(matrizBp[i*factor][j*factor]);
            }
        }
    }

    return new ImagenPPM (identification,
                          comment,
                          newwidth,
                          newheight,
                          colorDepth,
                          enlargedR,
                          enlargedG,
                          enlargedB);
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
                              matrizRp,
                              lutR,
                              matrizGp,
                              lutG,
                              matrizBp,
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
                              matrizRp,
                              lutR,
                              matrizGp,
                              lutG,
                              matrizBp,
                              lutB,
                              lutSize);
    }else{
        return this;
    }

}

ImagenPGM* ImagenPPM::convertToGrayScale(int method){

    int **grayScaleMatrix = new int*[height];
    for (int i=0; i < height; i++)
        grayScaleMatrix[i]=new int[width];

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if(method==6)
                grayScaleMatrix[i][j]=(int)(0.299*matrizRp[i][j][0]+0.587*matrizGp[i][j][0]+0.114*matrizBp[i][j][0]);
            else
                grayScaleMatrix[i][j]=(int)(0.33*matrizRp[i][j][0]+0.33*matrizGp[i][j][0]+0.33*matrizBp[i][j][0]);
        }
    }

    return new ImagenPGM ("P2",
                          comment,
                          height,
                          width,
                          colorDepth,
                          grayScaleMatrix);
}

// Getters

// export
void ImagenPPM::exportar(QString filename){

    QFile temp(filename+"."+imageType.toLower());
    if(temp.open(QFile::WriteOnly)){
        QTextStream fSalida(&temp);

        fSalida<<identification<<endl;
        fSalida<<comment<<endl;
        fSalida<<width<<" "<<height<<endl;
        fSalida<<colorDepth<<endl;

        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                fSalida<<*(matrizRp[i][j])<<endl<<*(matrizGp[i][j])<<endl<<*(matrizBp[i][j])<<endl;
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

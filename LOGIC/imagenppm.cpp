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

ImagenPPM::ImagenPPM(QList<QString> lectura)
{
    identification=lectura.at(0);
    comment=lectura.at(1);
    columnNumber=lectura.at(2).section(' ',0,0).toInt();
    rowNumber=lectura.at(2).section(' ',1,1).toInt();
    colorDensity=lectura.at(3).toInt();

    matrizR = new int*[rowNumber];
    for (int i=0; i < rowNumber; i++)
        matrizR[i]=new int[columnNumber];

    matrizG = new int*[rowNumber];
    for (int i=0; i < rowNumber; i++)
        matrizG[i]=new int[columnNumber];

    matrizB = new int*[rowNumber];
    for (int i=0; i < rowNumber; i++)
        matrizB[i]=new int[columnNumber];

    int aux1=4;
    int aux2=5;
    int aux3=6;
    for(int i=0; i<rowNumber; i++){
        for(int j=0; j<columnNumber; j++){
            matrizR[i][j]=lectura[i+j+aux1].toInt();
            matrizG[i][j]=lectura[i+j+aux2].toInt();
            matrizB[i][j]=lectura[i+j+aux3].toInt();
            aux1=aux1+2;
            aux2=aux2+2;
            aux3=aux3+2;
        }
        aux1=aux1+columnNumber-1;
        aux2=aux2+columnNumber-1;
        aux3=aux3+columnNumber-1;
    }
}

ImagenPPM::ImagenPPM(QString id, QString coment, int filas, int columnas, int intensidad, int **matrizR, int **matrizG, int **matrizB)
{
    this->identification=id;
    this->comment=coment;
    this->rowNumber=filas;
    this->columnNumber=columnas;
    this->colorDensity=intensidad;
    this->matrizR=matrizR;
    this->matrizG=matrizG;
    this->matrizB=matrizB;
}

void ImagenPPM::exportar(QTextStream &fSalida){

    fSalida<<identification<<endl;
    fSalida<<comment<<endl;
    fSalida<<columnNumber<<" "<<rowNumber<<endl;
    fSalida<<colorDensity<<endl;

    for(int i=0; i<rowNumber; i++){
        for(int j=0; j<columnNumber; j++){
            fSalida<<matrizR[i][j]<<endl<<matrizG[i][j]<<endl<<matrizB[i][j]<<endl;
        }
    }
}

ImagenPPM* ImagenPPM::reducirTamano(){

    int r=2;
    int nColumnasReducida=columnNumber/r;
    int nFilasReducida=rowNumber/r;

    // inicializacion
    int **reducidaR = new int*[nFilasReducida];
    for (int i=0; i < nFilasReducida; i++)
        reducidaR[i]=new int[nColumnasReducida];

    int **reducidaG = new int*[nFilasReducida];
    for (int i=0; i < nFilasReducida; i++)
        reducidaG[i]=new int[nColumnasReducida];

    int **reducidaB = new int*[nFilasReducida];
    for (int i=0; i < nFilasReducida; i++)
        reducidaB[i]=new int[nColumnasReducida];

    // Proceso de reduccion
    for(int i=0; i<nFilasReducida; i++){
        for(int j=0; j<nColumnasReducida; j++){
            reducidaR[i][j]=matrizR[i*r][j*r];
            reducidaG[i][j]=matrizG[i*r][j*r];
            reducidaB[i][j]=matrizB[i*r][j*r];
        }
    }

    // creacion de nueva imagen reducida

    ImagenPPM *resultado = new ImagenPPM (identification,
                                          comment,
                                          nFilasReducida,
                                          nColumnasReducida,
                                          colorDensity,
                                          reducidaR,
                                          reducidaG,
                                          reducidaB);

    return resultado;
}

ImagenPPM* ImagenPPM::reducirIntensidad(int bits){

    int intensidadNueva=(int)(pow(2,bits)-1);

    int **IntensidadR = new int*[rowNumber];
    for (int i=0; i < rowNumber; i++)
        IntensidadR[i]=new int[columnNumber];

    int **IntensidadG = new int*[rowNumber];
    for (int i=0; i < rowNumber; i++)
        IntensidadG[i]=new int[columnNumber];

    int **IntensidadB = new int*[rowNumber];
    for (int i=0; i < rowNumber; i++)
        IntensidadB[i]=new int[columnNumber];

    int divisor = (colorDensity+1)/(intensidadNueva+1);

    for(int i=0; i<rowNumber; i++){
        for(int j=0; j<columnNumber; j++){

            IntensidadR[i][j]=floor(matrizR[i][j]/divisor);
            IntensidadG[i][j]=floor(matrizG[i][j]/divisor);
            IntensidadB[i][j]=floor(matrizB[i][j]/divisor);

        }
    }

    // creacion de nueva imagen intensidad reducida

    ImagenPPM *resultado = new ImagenPPM (identification,
                                          comment,
                                          rowNumber,
                                          columnNumber,
                                          intensidadNueva,
                                          IntensidadR,
                                          IntensidadG,
                                          IntensidadB);
    return resultado;
}

ImagenPGM* ImagenPPM::convertirGris(int opcion){

    int **matrizPGM = new int*[rowNumber];
    for (int i=0; i < rowNumber; i++)
        matrizPGM[i]=new int[columnNumber];

    for(int i=0; i<rowNumber; i++){
        for(int j=0; j<columnNumber; j++){
            if(opcion==1)
                matrizPGM[i][j]=(int)(0.299*matrizR[i][j]+0.587*matrizG[i][j]+0.114*matrizB[i][j]);
            else
                matrizPGM[i][j]=(int)(0.33*matrizR[i][j]+0.33*matrizG[i][j]+0.33*matrizB[i][j]);
        }
    }

    ImagenPGM *resultado = new ImagenPGM ("P2",
                                          comment,
                                          rowNumber,
                                          columnNumber,
                                          colorDensity,
                                          matrizPGM);
    return resultado;
}

//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// PGM_PPM_IMAGE_PROCESSING_V2
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
QTextStream cout(stdout);
ImagenPGM::ImagenPGM(QList<QString> lectura){
    this->identification=lectura.at(0);
    this->comment=lectura.at(1);
    this->columnNumber=lectura.at(2).section(' ',0,0).toInt();
    this->rowNumber=lectura.at(2).section(' ',1,1).toInt();
    this->colorDensity=lectura.at(3).toInt();
    cout<<"id "<<identification<<endl;
    matrizImagen = new int*[rowNumber];
    for (int i=0; i < rowNumber; i++)
        matrizImagen[i]=new int[columnNumber];

    int aux=4;
    for(int i=0; i<rowNumber; i++){
        for(int j=0; j<columnNumber; j++){
            matrizImagen[i][j]=lectura[i+j+aux].toInt();
        }
        aux=aux+columnNumber-1;
    }

    //Lookup Table
    lut = new int [colorDensity+1];
    for (int i = 0; i < colorDensity+1; ++i) {
        lut[i]=i;
    }

    matrizImagenP = new int**[rowNumber];
    for (int i=0; i < rowNumber; i++)
        matrizImagenP[i]=new int*[columnNumber];

    aux=0;

    for(int i=0; i<rowNumber; i++){
        for(int j=0; j<columnNumber; j++){
            matrizImagenP[i][j]=&lut[lectura[i+j+aux].toInt()];
            if (*matrizImagenP[i][j]!=matrizImagen[i][j]){
                cout<<"lut"<<&lut[lectura[i+j+aux].toInt()]<<endl;
                cout <<"difiere en "<<i<<" "<<j<<" matrizImagenP "<<*matrizImagenP[i][j]<<" matrizImagen "<<matrizImagen[i][j]<<endl;
            }
            cout <<"--- "<<i<<" "<<j<<" matrizImagenP "<<*matrizImagenP[i][j]<<" matrizImagen "<<matrizImagen[i][j]<<endl;
        }
        aux=aux+columnNumber-1;
    }
    cout<<"entre al constructor 1"<<endl;
}

ImagenPGM::ImagenPGM(QString id, QString coment, int filas, int columnas, int colorD, int **matriz){
    this->identification=id;
    this->comment=coment;
    this->rowNumber=filas;
    this->columnNumber=columnas;
    this->colorDensity=colorD;
    this->matrizImagen=matriz;

    //Lookup Table
    lut = new int [colorDensity+1];
    for (int i = 0; i < colorDensity+1; ++i) {
        lut[i]=i;
    }

    matrizImagenP = new int**[rowNumber];
    for (int i=0; i < rowNumber; i++)
        matrizImagenP[i]=new int*[columnNumber];

    int aux=0;
    for(int i=0; i<rowNumber; i++){
        for(int j=0; j<columnNumber; j++){
            matrizImagenP[i][j]=&lut[matriz[i][j]];
            if (*matrizImagenP[i][j]!=matrizImagen[i][j]){
                cout <<"difiere en "<<i<<" "<<j<<" matrizImagenP "<<*matrizImagenP[i][j]<<" matrizImagen "<<matrizImagen[i][j]<<endl;
            }
        }
        aux=aux+columnNumber-1;
    }
    cout<<"entre al constructor 2"<<endl;
}

ImagenPGM::ImagenPGM(QString id, QString coment, int filas, int columnas, int colorD, int ***matriz, int *lut){
    this->identification=id;
    this->comment=coment;
    this->rowNumber=filas;
    this->columnNumber=columnas;
    this->colorDensity=colorD;
    this->matrizImagenP=matriz;
    this->lut=lut;
}

//Image processing

ImagenPGM* ImagenPGM::reducirTamano(){

    int r=2;
    int nColumnasReducida=columnNumber/r;
    int nFilasReducida=rowNumber/r;

    // inicializacion
    int **imagenReducida = new int*[nFilasReducida];
    for (int i=0; i < nFilasReducida; i++)
        imagenReducida[i]=new int[nColumnasReducida];

    // Proceso de reduccion
    for(int i=0; i<nFilasReducida; i++){
        for(int j=0; j<nColumnasReducida; j++){
            imagenReducida[i][j]=matrizImagen[i*r][j*r];
        }
    }

    // creacion de nueva imagen reducida

    ImagenPGM *resultado = new ImagenPGM (identification,
                                          comment,
                                          nFilasReducida,
                                          nColumnasReducida,
                                          colorDensity,
                                          imagenReducida);

    return resultado;
}

ImagenPGM* ImagenPGM::reducirIntensidad(int bits){

    int intensidadNueva=(int)(pow(2,bits)-1);

    int **imagenIntensidad = new int*[rowNumber];
    for (int i=0; i < rowNumber; i++)
        imagenIntensidad[i]=new int[columnNumber];

    int divisor = (colorDensity+1)/(intensidadNueva+1);

    for(int i=0; i<rowNumber; i++){
        for(int j=0; j<columnNumber; j++){

            imagenIntensidad[i][j]=floor(matrizImagen[i][j]/divisor);

        }
    }

    // creacion de nueva imagen intensidad reducida

    ImagenPGM *resultado = new ImagenPGM (identification,
                                          comment,
                                          rowNumber,
                                          columnNumber,
                                          intensidadNueva,
                                          imagenIntensidad);

    return resultado;
}

ImagenPGM* ImagenPGM::changeSize(int n){
    int w = this->columnNumber*n;
    int h = this->rowNumber*n;

    int **enlargedImage = new int*[h];
    for (int i=0; i < h; i++)
        enlargedImage[i]=new int[w];

    for (int i = 0; i <h; ++i) {
        for (int j = 0; j < w; ++j) {
            enlargedImage[i][j]=*(matrizImagenP[(int)floor(i/n)][(int)floor(j/n)]);
        }
        cout<<endl;
    }
    return new ImagenPGM (identification,
                          comment,
                          w,
                          h,
                          colorDensity,
                          enlargedImage);
}

// Getters:

int ImagenPGM::getColorDensity(){
    return colorDensity;
}

int ImagenPGM::getColumnNumber(){
    return columnNumber;
}

int ImagenPGM::getRowNumber(){
    return rowNumber;
}

int** ImagenPGM::getMatrix(){
    return matrizImagen;
}

void ImagenPGM::exportar(QTextStream &fSalida){

    fSalida<<identification<<endl;
    fSalida<<comment<<endl;
    fSalida<<columnNumber<<" "<<rowNumber<<endl;
    fSalida<<colorDensity<<endl;

    for(int i=0; i<rowNumber; i++){
        for(int j=0; j<columnNumber; j++){
            fSalida<<*matrizImagenP[i][j]<<endl;
        }
    }
}

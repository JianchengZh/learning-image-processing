//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: histogram.cpp
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

#include "histogram.h"

Histogram::Histogram(ImagenPGM *imagen)
{
    int nColumnas=imagen->getColumnNumber();
    int nFilas=imagen->getRowNumber();
    intensidad=imagen->getColorDensity()+1;

    int ***matrizImagen=imagen->getMatrix();
    int totalNumberPixels = nFilas*nColumnas;
    posicion = nColumnas+nFilas;

    relativeFrecuency= new double[intensidad];
    for (int i=0; i < intensidad; i++)
        relativeFrecuency[i]=0;

    for(int i=0; i<nFilas; i++){
        for(int j=0; j<nColumnas; j++){
            relativeFrecuency[*matrizImagen[i][j]]++;
        }
    }
    for (int i=0; i < intensidad; i++){
        relativeFrecuency[i]=(relativeFrecuency[i]/totalNumberPixels)*100;
    }
    generateMatrix();
}

void Histogram::generateMatrix(){
    matrizHistograma = new int*[intensidad];
    for (int i=0; i < intensidad; i++)
        matrizHistograma[i]=new int[intensidad];

    double maxFreq=findMaxRelativeFrecuency();

    for(int i=0; i<intensidad; i++){
        for(int j=0; j<intensidad; j++){
            if(intensidad-i<=((relativeFrecuency[j]*intensidad)/maxFreq)){
                matrizHistograma[i][j]=0;
            }else{
                matrizHistograma[i][j]=1;
            }
        }
    }
}

void Histogram::calculateLocalMaximux(){
    max1=0;max2=0;temp1=0;temp2=0;

    for (int i=1; i < intensidad-1; ++i) {
        //encontrar posicion
        if(relativeFrecuency[i]>relativeFrecuency[i-1]&&relativeFrecuency[i]>relativeFrecuency[i+1]){
            temp2=temp1;
            temp1=pow(max1-i,2)*relativeFrecuency[i];
            if (relativeFrecuency[i]>relativeFrecuency[max1]) {
                max2=max1;
                max1=i;
            }else if((relativeFrecuency[i]>relativeFrecuency[max2])&&(temp1>temp2)){
                max2=i;
            }else if(i-max2>floor(posicion/i)*25){
                max2=i;
            }
        }
    }
}

int Histogram::calculateThresholdIsodata(){
    int umbral = (max1+max2)/2;
    int umbral1=0,umbral2=0;
    int u1=0,u2=0;
    QTextStream cout (stdout);
    for (int i = 0; i < intensidad; ++i) {
        if(relativeFrecuency[i]!=0){
            if(i<umbral){
                u1++;
                umbral1+=relativeFrecuency[i];
            }
            else{
                u2++;
                umbral2+=relativeFrecuency[i];
            }

        }
    }
    u1=umbral1/u1;
    u2=umbral2/u2;
    cout<<max1<<" "<<max2<<" "<<umbral<<" "<<u1<<" "<<u2<<" "<<(u1+u2)/2;
    return((u1+u2)/2);
}

double Histogram::findMaxRelativeFrecuency(){
    QList<double> frequencies;
    for (int i=0; i<intensidad; i++){
        frequencies.append(relativeFrecuency[i]);
    }
    qSort(frequencies.begin(), frequencies.end());
    return frequencies.last();
}

int Histogram::getMax1(){
    return max1;
}

int Histogram::getMax2(){
    return max2;
}

ImagenPGM* Histogram::getHistogram(){
    return new ImagenPGM ("P2","#Histogram", intensidad, intensidad, 1, matrizHistograma);
}

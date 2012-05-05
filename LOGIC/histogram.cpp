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

//    for (int i=0; i < intensidad; i++){
//        relativeFrecuency[i]=(relativeFrecuency[i]/totalNumberPixels)*100;
//    }
    generateMatrix();
}

Histogram::~Histogram(){

    for (int i=0; i < intensidad; i++){
        delete matrizHistograma[i];
        matrizHistograma[i]=0;
    }

    delete matrizHistograma;
    matrizHistograma=0;

    delete relativeFrecuency;
    relativeFrecuency=0;
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

void Histogram::calculateTwoPeaks(){
    max1=0;max2=0;
    int temp1=0, temp2=0;
    //look first peak
    for (int i=1; i < intensidad-1; ++i) {
        if(relativeFrecuency[i]>relativeFrecuency[i-1]&&relativeFrecuency[i]>relativeFrecuency[i+1])
            if (relativeFrecuency[i]>relativeFrecuency[max1]) max1=i;
    }
    //look second peak
    for (int i=1; i < intensidad-1; ++i) {
        if(relativeFrecuency[i]>relativeFrecuency[i-1]&&relativeFrecuency[i]>relativeFrecuency[i+1]){
            temp1=pow(max1-i,2)*relativeFrecuency[i];
            if (temp1>temp2){
                temp2=temp1;
                max2=i;
            }
        }
    }
}

void Histogram::calculatePromedio(){
    umbral = (max1+max2)/2;
    u1=0;u2=0;w1=0;w2=0;
    n1=0;n2=0;
    for (int i = 0; i < intensidad; ++i) {
        if(relativeFrecuency[i]!=0){
            if(i<=umbral) n1+=relativeFrecuency[i];
            else n2+=relativeFrecuency[i];
        }
    }
    for (int i = 0; i < intensidad; ++i) {
        if(relativeFrecuency[i]!=0){
            if(i<=umbral) w1+=relativeFrecuency[i]/n1;
            else w2+=relativeFrecuency[i]/n2;
        }
    }
    for (int i = 0; i < intensidad; ++i) {
        if(relativeFrecuency[i]!=0){
            if(i<=umbral) u1+=(i*(relativeFrecuency[i]/n1))/w1;
            else u2+=(i*(relativeFrecuency[i]/n2))/w2;
        }
    }
}

int Histogram::calculateThresholdIsodata(){
    calculatePromedio();
    return((int)(u1+u2)/2);
}

int Histogram::calculateThresholdOtsu(){
    calculatePromedio();
    double uc = w1*u1+w2*u2;
    double Gin=0,Gzw=w1*pow(u1-uc,2)+w2*pow(u2-uc,2);
    double g1=0,g2=0;

    for (int i = 0; i < intensidad; ++i) {
        if(relativeFrecuency[i]!=0){
            if(i<=umbral) g1+=pow(i-u1,2)*((relativeFrecuency[i])/n1);
            else g2+=pow(i-u2,2)*((relativeFrecuency[i])/n2);
        }
    }
    Gin=w1*g1+w2*g2;
    QTextStream cout(stdout);
    cout<<"Gzw "<<Gzw<<endl;
    cout<<"g1 "<<g1<<endl;
    cout<<"g2 "<<g2<<endl;
    cout<<"Gin "<<Gin<<endl;
//    cout<<"w2 "<<w2<<endl;
//    cout<<"uc "<<uc<<endl;
//    cout<<"u2 "<<u2<<endl;
//    cout<<"u2-uc "<<pow(u2-uc,2)<<endl;
    return((int)Gzw/Gin);
}

double Histogram::findMaxRelativeFrecuency(){
    QList<double> frequencies;
    for (int i=0; i<intensidad; i++){
        frequencies.append(relativeFrecuency[i]);
    }
    qSort(frequencies.begin(), frequencies.end());
    return frequencies.last();
}

int *Histogram::calculeEqualization(){

    int a=0;
    int *discretizedFrecuency = new int[intensidad];
    relativeEqualization = new double[intensidad];

    for (int i=0; i < intensidad; i++){
        discretizedFrecuency[i]=0;
        relativeEqualization[i]=0;
    }
    relativeEqualization[0]=relativeFrecuency[0];
    for (int i = 1; i < intensidad; ++i){
        relativeEqualization[i]+=relativeEqualization[i-1]+relativeFrecuency[i];
    }
    a=relativeEqualization[intensidad-1];
    double redondeo=0;
    for (int i = 0; i < intensidad; ++i) {
        redondeo=((intensidad-1)*relativeEqualization[i])/a;
        redondeo=fmod(redondeo,floor(redondeo));
        if(redondeo>0.5)
            discretizedFrecuency[i]=ceil(((intensidad-1)*relativeEqualization[i])/a);
        else
            discretizedFrecuency[i]=floor(((intensidad-1)*relativeEqualization[i])/a);
    }
    return (discretizedFrecuency);
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

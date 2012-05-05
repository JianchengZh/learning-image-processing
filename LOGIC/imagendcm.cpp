//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: image.cpp
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

#include "imagendcm.h"

ImagenDCM::ImagenDCM(const char *fileName){

    QTextStream cout (stdout);

    dicomImage = new DicomImage(fileName);

    identification="P2";
    comment="";
    imageType="DCM";
    colorDepth=pow(dicomImage->getDepth(),2)-1;
    lutSize=colorDepth;
    height=dicomImage->getWidth();
    width=dicomImage->getHeight();

    cout<<"dicomImage->getWidth()"<<dicomImage->getWidth()<<endl;
    cout<<"dicomImage->getHeight()"<<dicomImage->getHeight()<<endl;
    cout<<"dicomImage->getDepth()"<<dicomImage->getDepth()<<endl;

}

//Image processing
Image* ImagenDCM::changeSize(int factor){
    return this;
}

Image* ImagenDCM::changeColorDepth(int bits){
    return this;
}

// export
void ImagenDCM::exportar(QString filename){

    //    QFile temp(filename+"."+imageType.toLower());
    //    if(temp.open(QFile::WriteOnly)){
    //        QTextStream fSalida(&temp);

    //        fSalida<<identification<<endl;
    //        fSalida<<comment<<endl;
    //        fSalida<<width<<" "<<height<<endl;
    //        fSalida<<colorDepth<<endl;

    //        for(int i=0; i<height; i++){
    //            for(int j=0; j<width; j++){
    //                fSalida<<*matrixImagenP[i][j]<<endl;
    //            }
    //        }
    //    }
}


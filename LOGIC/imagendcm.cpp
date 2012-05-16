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

    dicomImage = new DicomImage(fileName);

    this->identification="DCM";
    this->comment="";
    this->imageType="DCM";
    this->colorDepth=pow(dicomImage->getDepth(),2)-1;
    this->height=dicomImage->getWidth();
    this->width=dicomImage->getHeight();

    QTextStream cout(stdout);
    if (dicomImage != NULL)
    {
        if (dicomImage->getStatus() == EIS_Normal)
        {
            Uint8 *pixelData = (Uint8 *)(dicomImage->getOutputData(8 /* bits per sample */));
            if (pixelData != NULL)
            {
                //Lookup Table
                lut = new int [colorDepth+1];
                for (int i = 0; i < colorDepth+1; ++i)
                    lut[i]=i;

                matrixImagenP = new int**[height];
                for (int i=0; i < height; i++)
                    matrixImagenP[i]=new int*[width];

                for(int i=0; i<height; i++){
                    for(int j=0; j<width; j++){
                        matrixImagenP[i][j]=&lut[pixelData[i+j]];
                        //                        cout<<" matrixImagenP["<<i<<"]["<<j<<"] "<< *matrixImagenP[i][j]<<endl;
                    }
                }
            }
        } else
            cout << "Error: cannot load DICOM image (" << DicomImage::getString(dicomImage->getStatus()) << ")" << endl;
    }
    cout<<"TERMINE"<<endl;
}

//Image processing
Image* ImagenDCM::changeSize(int factor){
    return this;
}

Image* ImagenDCM::changeColorDepth(int bits){
    return this;
}

// export
void ImagenDCM::saveImage(QString filename){

    QTextStream cout(stdout);
    this->imageType="PGM";
    this->identification="P2";

    cout<<"VOY POR AQUI"<<endl;
    QFile temp(filename+"."+imageType.toLower());
    if(temp.open(QFile::WriteOnly)){
        QTextStream fSalida(&temp);

        fSalida<<identification<<endl;
        fSalida<<comment<<endl;
        fSalida<<width<<" "<<height<<endl;
        fSalida<<colorDepth<<endl;

        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                fSalida<<*matrixImagenP[i][j]<<endl;
            }
        }
    }
}


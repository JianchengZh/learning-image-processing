#include "geometricoperation.h"

GeometricOperation::GeometricOperation()
{
}

Image * GeometricOperation::average(Image* img, Image *image, double alpha)
{
    int*** matrixImagenP=static_cast<ImagenPGM*>(img)->getMatrix();
    int height=static_cast<ImagenPGM*>(img)->getHeight(), width=static_cast<ImagenPGM*>(img)->getWidth(), colorDepth=static_cast<ImagenPGM*>(img)->getColorDepth();

    int **averageMatrix = new int*[height];
    for (int i=0; i < height; i++)
        averageMatrix[i]=new int[width];

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            averageMatrix[i][j]=alpha*(*matrixImagenP[i][j])+(1-alpha)*(*static_cast<ImagenPGM*>(image)->getMatrix()[i][j]);
        }
    }

    ImagenPGM *result = new ImagenPGM(height, width, colorDepth, averageMatrix);

    for (int i=0; i < height; i++)
        delete averageMatrix[i];

    delete averageMatrix;

    return result;
}

Image * GeometricOperation::add(Image *img, Image *image)
{
    int*** matrixImagenP=static_cast<ImagenPGM*>(img)->getMatrix();
    int height=static_cast<ImagenPGM*>(img)->getHeight(), width=static_cast<ImagenPGM*>(img)->getWidth(), colorDepth=static_cast<ImagenPGM*>(img)->getColorDepth();

    int **addMatrix = new int*[height];
    for (int i=0; i < height; i++)
        addMatrix[i]=new int[width];
    int sum = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            sum=(*matrixImagenP[i][j])+(*static_cast<ImagenPGM*>(image)->getMatrix()[i][j]);
            if (sum<=colorDepth) {
                addMatrix[i][j]=sum;
            }else {
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

Image * GeometricOperation::subtract(Image *img, Image *image)
{
    int*** matrixImagenP=static_cast<ImagenPGM*>(img)->getMatrix();
    int height=static_cast<ImagenPGM*>(img)->getHeight(), width=static_cast<ImagenPGM*>(img)->getWidth(), colorDepth=static_cast<ImagenPGM*>(img)->getColorDepth();

    int **subtractMatrix = new int*[height];
    for (int i=0; i < height; i++)
        subtractMatrix[i]=new int[width];
    int rest = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            rest=(*matrixImagenP[i][j])-(*static_cast<ImagenPGM*>(image)->getMatrix()[i][j]);
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

Image * GeometricOperation::multiply(Image *img, Image *image)
{
    int*** matrixImagenP=static_cast<ImagenPGM*>(img)->getMatrix();
    int height=static_cast<ImagenPGM*>(img)->getHeight(), width=static_cast<ImagenPGM*>(img)->getWidth(), colorDepth=static_cast<ImagenPGM*>(img)->getColorDepth();

    int **multiplyMatrix = new int*[height];
    for (int i=0; i < height; i++)
        multiplyMatrix[i]=new int[width];
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            multiplyMatrix[i][j]=((*matrixImagenP[i][j])*(*static_cast<ImagenPGM*>(image)->getMatrix()[i][j]))/colorDepth;
        }
    }

    ImagenPGM *result = new ImagenPGM(height, width, colorDepth, multiplyMatrix);


    for (int i=0; i < height; i++)
        delete multiplyMatrix[i];

    delete multiplyMatrix;

    return result;
}

Image * GeometricOperation::divide(Image *img, Image *image)
{
    int*** matrixImagenP=static_cast<ImagenPGM*>(img)->getMatrix();
    int height=static_cast<ImagenPGM*>(img)->getHeight(), width=static_cast<ImagenPGM*>(img)->getWidth(), colorDepth=static_cast<ImagenPGM*>(img)->getColorDepth();

    int **divideMatrix = new int*[height];
    for (int i=0; i < height; i++)
        divideMatrix[i]=new int[width];
    QTextStream cout (stdout);
    int div = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            div=((colorDepth+1)*(*matrixImagenP[i][j]))/((*static_cast<ImagenPGM*>(image)->getMatrix()[i][j])+1);
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

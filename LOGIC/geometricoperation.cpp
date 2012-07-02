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




Image *GeometricOperation::scaling(Image *img, double factorX, double factorY)
{
    int width = img->getWidth();
    int height = img->getHeight();
    int colorDepth = img->getColorDepth();
    int ***matrix = static_cast<ImagenPGM*>(img)->getMatrix();

    int size = 3;

    int *position;

    position = new int[size];
    for(int i=0; i<size;i++)
    {
        position[i] = 1;
    }

    double **matrixScaling = new double*[size];

    for(int i=0;i<size;i++)
        matrixScaling[i] = new double[size];

    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            matrixScaling[i][j] = 0;

    matrixScaling[0][0] = factorX;
    matrixScaling[1][1] = factorY;
    matrixScaling[2][2] = 1;

    int widthNew = round(width*factorY);
    int heightNew = round(height*factorX);

    int **matrixScalingResult = new int*[heightNew];

    for(int i=0;i<heightNew;i++)
        matrixScalingResult[i] = new int[widthNew];

    for(int i=0;i<heightNew;i++)
        for(int j=0;j<widthNew;j++)
            matrixScalingResult[i][j] = 0;


    for(int i=0; i<height; i++)
        for(int j=0; j<width; j++){

            position[0]=j;
            position[1]=i;

            position = multiplyVectorMatrix(position, matrixScaling);

            int x = position[0];
            int y = position[1];

            if(x < widthNew && y < heightNew)
            matrixScalingResult[y][x] = *matrix[i][j];
        }

    delete position;

    for (int i=0; i < size; i++)
        delete matrixScaling[i];

    delete matrixScaling;


    ImagenPGM *result = new ImagenPGM(heightNew,widthNew,colorDepth,matrixScalingResult);

    for (int i=0; i < heightNew; i++)
        delete matrixScalingResult[i];

    delete matrixScalingResult;

    return result;
}



int *GeometricOperation::multiplyVectorMatrix(int *vector, double **matrix)
{

    int size = 3;
    int *positionNew = new int[size];

    for(int i=0; i<size; i++){
        positionNew[i]=(int)(vector[0]*matrix[i][0]+vector[1]*matrix[i][1]+vector[2]*matrix[i][2]);
    }

    return positionNew;

}

#include "geometricoperation.h"

GeometricOperation::GeometricOperation()
{
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

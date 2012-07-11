//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: geometricoperation.cpp
// 
// FECHA: 11.07.12
//
// AUTORES:
// Gustavo Adolfo Rodriguez         0932979-3743
// gustalibreros@gmail.com
//
// Edwin Fernando Muñoz             0910398-3743
// edwinfernandomudelgado@gmail.com
//
// Yerminson Doney Gonzalez         0843846-3743
// yermigon@gmail.com
//
// Edgar Andrés Moncada             0832294-3743
// edgarandres29@gmail.com
//
// ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION
// UNIVERSIDAD DEL VALLE
//**********************************************************



#include "geometricoperation.h"

GeometricOperation::GeometricOperation()
{
}

Image * GeometricOperation::scaling(Image * img,
        double                              factorX,
        double                              factorY)
{
    int     width      = img -> getWidth();
    int     height     = img -> getHeight();
    int     colorDepth = img -> getColorDepth();
    int *** matrix     = static_cast<ImagenPGM *>(img) -> getMatrix();
    int     size       = 3;
    int *   position;

    position = new int[size];

    for (int i = 0; i < size; i++)
    {
        position[i] = 1;
    }

    double ** matrixScaling = new double *[size];

    for (int i = 0; i < size; i++)
    {
        matrixScaling[i] = new double[size];
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrixScaling[i][j] = 0;
        }
    }

    matrixScaling[0][0] = factorX;
    matrixScaling[1][1] = factorY;
    matrixScaling[2][2] = 1;

    int    widthNew            = round(width * factorY);
    int    heightNew           = round(height * factorX);
    int ** matrixScalingResult = new int *[heightNew];

    for (int i = 0; i < heightNew; i++)
    {
        matrixScalingResult[i] = new int[widthNew];
    }

    for (int i = 0; i < heightNew; i++)
    {
        for (int j = 0; j < widthNew; j++)
        {
            matrixScalingResult[i][j] = 0;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            position[0] = j;
            position[1] = i;
            position    = multiplyVectorMatrix(position, matrixScaling);

            int x = position[0];
            int y = position[1];

            if ((x < widthNew) && (y < heightNew))
            {
                matrixScalingResult[y][x] = *matrix[i][j];
            }
        }
    }

    delete position;

    for (int i = 0; i < size; i++)
    {
        delete matrixScaling[i];
    }

    delete matrixScaling;

    ImagenPGM * result = new ImagenPGM(heightNew, widthNew, colorDepth, matrixScalingResult);

    for (int i = 0; i < heightNew; i++)
    {
        delete matrixScalingResult[i];
    }

    delete matrixScalingResult;

    return result;
}

Image * GeometricOperation::translation(Image * img,
        double                                  factorX,
        double                                  factorY)
{
    int     width      = img -> getWidth();
    int     height     = img -> getHeight();
    int     colorDepth = img -> getColorDepth();
    int *** matrix     = static_cast<ImagenPGM *>(img) -> getMatrix();
    int     size       = 3;
    int *   position;

    position = new int[size];

    for (int i = 0; i < size; i++)
    {
        position[i] = 1;
    }

    double ** matrixTranslation = new double *[size];

    for (int i = 0; i < size; i++)
    {
        matrixTranslation[i] = new double[size];
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrixTranslation[i][j] = 0;
        }
    }

    matrixTranslation[0][0] = 1;
    matrixTranslation[1][1] = 1;
    matrixTranslation[0][2] = factorX;
    matrixTranslation[1][2] = factorY;
    matrixTranslation[2][2] = 1;

    int ** matrixTranslationResult = new int *[height];

    for (int i = 0; i < height; i++)
    {
        matrixTranslationResult[i] = new int[width];
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrixTranslationResult[i][j] = 0;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            position[0] = j;
            position[1] = i;
            position    = multiplyVectorMatrix(position, matrixTranslation);

            if (position[1] >= height)
            {
                if (position[0] >= width)
                {
                    matrixTranslationResult[position[1] - height][position[0] - width] = *matrix[i][j];
                }
                else if (position[0] < 0)
                {
                    matrixTranslationResult[position[1] - height][width + position[0]] = *matrix[i][j];
                }
                else
                {
                    matrixTranslationResult[position[1] - height][position[0]] = *matrix[i][j];
                }
            }
            else if (position[0] >= width)
            {
                if (position[1] < 0)
                {
                    matrixTranslationResult[height + position[1]][position[0] - width] = *matrix[i][j];
                }
                else
                {
                    matrixTranslationResult[position[1]][position[0] - width] = *matrix[i][j];
                }
            }
            else if (position[1] < 0)
            {
                if (position[0] < 0)
                {
                    matrixTranslationResult[height + position[1]][width + position[0]] = *matrix[i][j];
                }
                else
                {
                    matrixTranslationResult[height + position[1]][position[0]] = *matrix[i][j];
                }
            }
            else if (position[0] < 0)
            {
                matrixTranslationResult[position[1]][width + position[0]] = *matrix[i][j];
            }
            else
            {
                matrixTranslationResult[position[1]][position[0]] = *matrix[i][j];
            }
        }
    }

    delete position;

    for (int i = 0; i < size; i++)
    {
        delete matrixTranslation[i];
    }

    delete matrixTranslation;

    ImagenPGM * result = new ImagenPGM(height, width, colorDepth, matrixTranslationResult);

    for (int i = 0; i < height; i++)
    {
        delete matrixTranslationResult[i];
    }

    delete matrixTranslationResult;

    return result;
}

Image * GeometricOperation::rotation(Image * img,
        double                               angle)
{
    int     width      = img -> getWidth();
    int     height     = img -> getHeight();
    int     colorDepth = img -> getColorDepth();
    int *** matrix     = static_cast<ImagenPGM *>(img) -> getMatrix();
    int     centerX    = width / 2;
    int     centerY    = height / 2;
    double  sinValue   = sin(angle);
    double  cosValue   = cos(angle);
    int     size       = 3;
    int *   position;

    position = new int[size];

    for (int i = 0; i < size; i++)
    {
        position[i] = 1;
    }

    double ** matrixTranslation = new double *[size];

    for (int i = 0; i < size; i++)
    {
        matrixTranslation[i] = new double[size];
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrixTranslation[i][j] = 0;
        }
    }

    matrixTranslation[0][0] = 1;
    matrixTranslation[1][1] = 1;
    matrixTranslation[2][2] = 1;

    double ** matrixRotation = new double *[size];

    for (int i = 0; i < size; i++)
    {
        matrixRotation[i] = new double[size];
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrixRotation[i][j] = 0;
        }
    }

    // cout << centerX << "    "<< centerY;
    matrixRotation[0][0] = cosValue;
    matrixRotation[0][1] = -sinValue;
    matrixRotation[1][0] = sinValue;
    matrixRotation[1][1] = cosValue;
    matrixRotation[2][2] = 1;

    int ** matrixRotationResult = new int *[height];

    for (int i = 0; i < height; i++)
    {
        matrixRotationResult[i] = new int[width];
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrixRotationResult[i][j] = 0;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrixTranslation[0][2] = -centerX;
            matrixTranslation[1][2] = -centerY;
            position[0]             = j;
            position[1]             = i;

            // Trasladamos al origen
            position = multiplyVectorMatrix(position, matrixTranslation);

            // Rotamos respecto al angulo
            position = multiplyVectorMatrix(position, matrixRotation);

            // cout <<position[0] << " rotacion   "<< position[1];
            matrixTranslation[0][2] = centerX;
            matrixTranslation[1][2] = centerY;
            position                = multiplyVectorMatrix(position, matrixTranslation);

            if ((position[0] < width) && (position[0] >= 0) && (position[1] < height) && (position[1] >= 0))
            {
                matrixRotationResult[position[1]][position[0]] = *matrix[i][j];
            }
        }
    }

    delete position;

    for (int i = 0; i < size; i++)
    {
        delete matrixTranslation[i];
    }

    delete matrixTranslation;

    for (int i = 0; i < size; i++)
    {
        delete matrixRotation[i];
    }

    delete matrixRotation;

    ImagenPGM * result = new ImagenPGM(height, width, colorDepth, matrixRotationResult);

    for (int i = 0; i < height; i++)
    {
        delete matrixRotationResult[i];
    }

    delete matrixRotationResult;

    return result;
}

Image * GeometricOperation::reflection(Image * img,
        GeometricOperation::axis               orientation)
{
    int     width      = img -> getWidth();
    int     height     = img -> getHeight();
    int     colorDepth = img -> getColorDepth();
    int *** matrix     = static_cast<ImagenPGM *>(img) -> getMatrix();
    int     size       = 3;
    int *   position;

    position = new int[size];

    for (int i = 0; i < size; i++)
    {
        position[i] = 1;
    }

    double ** matrixReflection = new double *[size];

    for (int i = 0; i < size; i++)
    {
        matrixReflection[i] = new double[size];
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrixReflection[i][j] = 0;
        }
    }

    if (orientation == GeometricOperation::X)
    {
        matrixReflection[0][0] = -1;
        matrixReflection[1][1] = 1;
        matrixReflection[2][2] = 1;
    }
    else if (orientation == GeometricOperation::Y)
    {
        matrixReflection[0][0] = 1;
        matrixReflection[1][1] = -1;
        matrixReflection[2][2] = 1;
    }

    int ** matrixReflectiongResult = new int *[height];

    for (int i = 0; i < height; i++)
    {
        matrixReflectiongResult[i] = new int[width];
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrixReflectiongResult[i][j] = 0;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            position[0] = j;
            position[1] = i;
            position    = multiplyVectorMatrix(position, matrixReflection);

            int x = position[0];
            int y = position[1];

            if (y < 0)
            {
                matrixReflectiongResult[height + y][x] = *matrix[i][j];
            }
            else if (x < 0)
            {
                matrixReflectiongResult[y][x + width] = *matrix[i][j];
            }
        }
    }

    delete position;

    for (int i = 0; i < size; i++)
    {
        delete matrixReflection[i];
    }

    delete matrixReflection;

    ImagenPGM * result = new ImagenPGM(height, width, colorDepth, matrixReflectiongResult);

    for (int i = 0; i < height; i++)
    {
        delete matrixReflectiongResult[i];
    }

    delete matrixReflectiongResult;

    return result;
}

int * GeometricOperation::multiplyVectorMatrix(int * vector,
        double **                                    matrix)
{
    int   size        = 3;
    int * positionNew = new int[size];

    for (int i = 0; i < size; i++)
    {
        positionNew[i] = (int) (vector[0] * matrix[i][0] + vector[1] * matrix[i][1] + vector[2] * matrix[i][2]);
    }

    return positionNew;
}


//~ Formatted by Jindent --- http://www.jindent.com

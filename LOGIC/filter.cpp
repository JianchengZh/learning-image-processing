//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: filter.cpp
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



#include "filter.h"

Filter::Filter()
{
}

Image * Filter::meanFilter(Image * img,
                           int     kernelSize)
{
    int *** matrixImagenP = static_cast<ImagenPGM *>(img) -> getMatrix();
    int     height        =
        static_cast<ImagenPGM *>(img) ->
             getHeight(), width = static_cast<ImagenPGM *>(img) ->
                  getWidth(), colorDepth = static_cast<ImagenPGM *>(img) -> getColorDepth();
    int ** kernel = new int *[kernelSize];

    for (int i = 0; i < kernelSize; ++i)
    {
        kernel[i] = new int[kernelSize];
    }

    for (int i = 0; i < kernelSize; ++i)
    {
        for (int j = 0; j < kernelSize; ++j)
        {
            kernel[i][j] = 1;
        }
    }

    // return applyKernel(kernel, kernelSize,kernelSize);
    ImagenPGM * imageResult = new ImagenPGM(height, width, colorDepth,
                                  applyKernel(height, width, matrixImagenP, kernel, kernelSize, kernelSize));

    return imageResult;
}

Image * Filter::convolutionFilter(Image * img,
                                  int **  kernel,
                                  int     kernelSize)
{
    int *** matrixImagenP = static_cast<ImagenPGM *>(img) -> getMatrix();
    int     height        =
        static_cast<ImagenPGM *>(img) ->
             getHeight(), width = static_cast<ImagenPGM *>(img) ->
                  getWidth(), colorDepth = static_cast<ImagenPGM *>(img) -> getColorDepth();

    // return applyKernel(kernel,size,size);
    ImagenPGM * imageResult = new ImagenPGM(height, width, colorDepth,
                                  applyKernel(height, width, matrixImagenP, kernel, kernelSize, kernelSize));

    return imageResult;
}

Image * Filter::gaussianaFilter(Image * img,
                                int     kernelSize)
{
    int *** matrixImagenP = static_cast<ImagenPGM *>(img) -> getMatrix();
    int     height        =
        static_cast<ImagenPGM *>(img) ->
             getHeight(), width = static_cast<ImagenPGM *>(img) ->
                  getWidth(), colorDepth = static_cast<ImagenPGM *>(img) -> getColorDepth();
    int * vectorActual, *vectorAux;

    vectorActual = new int[kernelSize];
    vectorAux    = new int[kernelSize];

    for (int i = 0; i < kernelSize; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            if (i == j)
            {
                vectorAux[j] = 1;
            }
            else if (j != 0)
            {
                vectorAux[j] += vectorActual[i - j];
            }
        }

        for (int r = 0; r <= i; ++r)
        {
            vectorActual[r] = vectorAux[r];
        }
    }

    delete vectorAux;

    vectorAux = 0;

    // return vectorActual;
    // return applyKernel(createKernelFilter(vectorActual,vectorActual,kernelSize),kernelSize,kernelSize);
    ImagenPGM * imageResult = new ImagenPGM(height, width, colorDepth,
                                  applyKernel(height, width, matrixImagenP,
                                      createKernelFilter(vectorActual, vectorActual, kernelSize), kernelSize,
                                      kernelSize));

    return imageResult;
}

Image * Filter::noiseCleaningLine(Image * img,
                                  int     delta)
{
    int *** matrixImagenP = static_cast<ImagenPGM *>(img) -> getMatrix();
    int     height        =
        static_cast<ImagenPGM *>(img) ->
             getHeight(), width = static_cast<ImagenPGM *>(img) ->
                  getWidth(), colorDepth = static_cast<ImagenPGM *>(img) -> getColorDepth();
    int ** resultMatrix = new int *[height];

    for (int i = 0; i < height; ++i)
    {
        resultMatrix[i] = new int[width];

        for (int j = 0; j < width; ++j)
        {
            resultMatrix[i][j] = *matrixImagenP[i][j];
        }
    }

    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 2; j < width - 2; j++)
        {
            int test = *matrixImagenP[i][j], neighbors,
                sum  = 0;

            sum       += *matrixImagenP[i][j - 1];
            sum       += *matrixImagenP[i][j - 2];
            sum       += *matrixImagenP[i][j + 1];
            sum       += *matrixImagenP[i][j + 2];
            neighbors = sum / 4.0;

            if (fabs(test - neighbors) > delta)
            {
                resultMatrix[i][j] = neighbors;
            }
            else
            {
                resultMatrix[i][j] = test;
            }

            int cond = resultMatrix[i][j];

            if ((cond >= 0) && (cond < 256))
            {
                resultMatrix[i][j] = cond;
            }
            else if (cond < 0)
            {
                resultMatrix[i][j] = 0;
            }
            else
            {
                resultMatrix[i][j] = 255;
            }
        }
    }

    ImagenPGM * imageResult = new ImagenPGM(height, width, colorDepth, resultMatrix);

    for (int i = 0; i < height; ++i)
    {
        delete resultMatrix[i];

        resultMatrix[i] = 0;
    }

    delete resultMatrix;

    resultMatrix = 0;

    return imageResult;
}

Image * Filter::noiseCleaningPixel(Image * img,
                                   int     delta)
{
    int *** matrixImagenP = static_cast<ImagenPGM *>(img) -> getMatrix();
    int     height        =
        static_cast<ImagenPGM *>(img) ->
             getHeight(), width = static_cast<ImagenPGM *>(img) ->
                  getWidth(), colorDepth = static_cast<ImagenPGM *>(img) -> getColorDepth();
    int ** resultMatrix = new int *[height];

    for (int i = 0; i < height; ++i)
    {
        resultMatrix[i] = new int[width];

        for (int j = 0; j < width; ++j)
        {
            resultMatrix[i][j] = *matrixImagenP[i][j];
        }
    }

    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            int test = *matrixImagenP[i][j], neighbors,
                sum  = 0;

            sum       += *matrixImagenP[i - 1][j - 1];
            sum       += *matrixImagenP[i - 1][j];
            sum       += *matrixImagenP[i - 1][j + 1];
            sum       += *matrixImagenP[i][j - 1];
            sum       += *matrixImagenP[i][j + 1];
            sum       += *matrixImagenP[i + 1][j - 1];
            sum       += *matrixImagenP[i + 1][j];
            sum       += *matrixImagenP[i + 1][j + 1];
            neighbors = qRound(sum / 8.0);

            if (fabs(test - neighbors) > delta)
            {
                resultMatrix[i][j] = neighbors;
            }
            else
            {
                resultMatrix[i][j] = test;
            }

            int cond = resultMatrix[i][j];

            if ((cond >= 0) && (cond < 256))
            {
                resultMatrix[i][j] = cond;
            }
            else if (cond < 0)
            {
                resultMatrix[i][j] = 0;
            }
            else
            {
                resultMatrix[i][j] = 255;
            }
        }
    }

    ImagenPGM * imageResult = new ImagenPGM(height, width, colorDepth, resultMatrix);

    for (int i = 0; i < height; ++i)
    {
        delete resultMatrix[i];

        resultMatrix[i] = 0;
    }

    delete resultMatrix;

    resultMatrix = 0;

    return imageResult;
}


//~ Formatted by Jindent --- http://www.jindent.com

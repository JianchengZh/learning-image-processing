#include "globaltransformation.h"

GlobalTransformation::GlobalTransformation()
{
}

Image *GlobalTransformation::binaryOperations(Image *image1, Image *image2, GlobalTransformation::binaryOperation operation)
{



    if(image1->getHeight() != image2->getHeight() ||
          image1->getWidth()!=image2->getWidth() )
    {
        cerr << "Error la operacion no se puede aplicar a la imagen";
        return image1;
    }


    int height = image1->getHeight();
    int width = image1->getWidth();
    int colorDepth = image1->getColorDepth();



    int ***matrixImage1 = static_cast<ImagenPGM*>(image1)->getMatrix();
    int ***matrixImage2 =  static_cast<ImagenPGM*>(image2)->getMatrix();

    int **binaryMatrix = new int*[height];
    for (int i=0; i < height; i++)
        binaryMatrix[i]=new int[width];

    int valueA;
    int valueB;



    // La operacion escogida fue AND
    if(operation == GlobalTransformation::And)
    {
        for(int i=0; i<height;i++)
        {
            for(int j=0; j<width;j++){

                valueA = *matrixImage1[i][j];
                valueB = *matrixImage2[i][j];
                int value = valueA & valueB;

                if(value>colorDepth){
                    value=colorDepth;
                }else if(value < 0)
                {
                    value += colorDepth;
                }

                binaryMatrix[i][j] = value;
            }

        }

        // La operacion escogida fue OR
    }else if(operation == GlobalTransformation::Or)
    {

        for(int i=0; i<height;i++)
        {
            for(int j=0; j<width;j++)
            {

                valueA = *matrixImage1[i][j];
                valueB = *matrixImage2[i][j];
                int value = valueA | valueB;


                if(value>colorDepth)
                {
                    value=colorDepth;
                }else if(value < 0)
                {
                    value += colorDepth;
                }

                binaryMatrix[i][j] = value;
            }

        }

    }else if(operation == GlobalTransformation::Xor)
    {
        for(int i=0; i<height;i++)
        {
            for(int j=0; j<width;j++){

                valueA = *matrixImage1[i][j];
                valueB = *matrixImage2[i][j];
                int value = valueA ^ valueB;

                if(value>colorDepth){
                    value=colorDepth;
                }else if(value < 0)
                {
                    value += colorDepth;
                }

                binaryMatrix[i][j] = value;
            }
        }


    }

    ImagenPGM *result = new ImagenPGM(height, width, colorDepth, binaryMatrix);



    return result;



}

Image * GlobalTransformation::unaryOperations(Image *image1, GlobalTransformation::unaryOperation operation)
{
    int height = image1->getHeight();
    int width = image1->getWidth();
    int colorDepth = image1->getColorDepth();



    int ***matrixImage1 = static_cast<ImagenPGM*>(image1)->getMatrix();


    int **unaryMatrix = new int*[height];
    for (int i=0; i < height; i++)
        unaryMatrix[i]=new int[width];

    int valueA;




    // La operacion escogida fue NOT
    if(operation == GlobalTransformation::Not)
    {
        for(int i=0; i<height;i++)
        {
            for(int j=0; j<width;j++){

                valueA = *matrixImage1[i][j];
                int value = ~valueA + colorDepth;
                unaryMatrix[i][j] = value;
            }
        }
    }

    ImagenPGM *result = new ImagenPGM(height, width, colorDepth, unaryMatrix);
    return result;

}


Image * GlobalTransformation::average(Image* img, Image *image, double alpha)
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

Image * GlobalTransformation::add(Image *img, Image *image)
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

Image * GlobalTransformation::subtract(Image *img, Image *image)
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

Image * GlobalTransformation::multiply(Image *img, Image *image)
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

Image * GlobalTransformation::divide(Image *img, Image *image)
{
    int*** matrixImagenP=static_cast<ImagenPGM*>(img)->getMatrix();
    int height=static_cast<ImagenPGM*>(img)->getHeight(), width=static_cast<ImagenPGM*>(img)->getWidth(), colorDepth=static_cast<ImagenPGM*>(img)->getColorDepth();

    int **divideMatrix = new int*[height];
    for (int i=0; i < height; i++)
        divideMatrix[i]=new int[width];
    //QTextStream cout (stdout);
    int div = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            div=((colorDepth+1)*(*matrixImagenP[i][j]))/((*static_cast<ImagenPGM*>(image)->getMatrix()[i][j])+1);
            //            if (div<colorDepth+1) {
            divideMatrix[i][j]=div;
            //            } else {
            //                divideMatrix[i][j]=colorDepth;
            //            }
            //cout<<divideMatrix[i][j]<<" ";
        }//cout<<endl;
    }

    ImagenPGM *result = new ImagenPGM(height, width, colorDepth, divideMatrix);


    for (int i=0; i < height; i++)
        delete divideMatrix[i];

    delete divideMatrix;

    return result;
}

Image * GlobalTransformation::maxOp(Image *img, Image *image)
{
    int*** matrixImagenP=static_cast<ImagenPGM*>(img)->getMatrix();
    int height=static_cast<ImagenPGM*>(img)->getHeight(), width=static_cast<ImagenPGM*>(img)->getWidth(), colorDepth=static_cast<ImagenPGM*>(img)->getColorDepth();

    int **addMatrix = new int*[height];
    for (int i=0; i < height; i++)
        addMatrix[i]=new int[width];
    int smaxValue = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            smaxValue= max((*matrixImagenP[i][j]),(*static_cast<ImagenPGM*>(image)->getMatrix()[i][j]));
            if (smaxValue<=colorDepth) {
                addMatrix[i][j]=smaxValue;
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

Image * GlobalTransformation::minOp(Image *img, Image *image)
{
    int*** matrixImagenP=static_cast<ImagenPGM*>(img)->getMatrix();
    int height=static_cast<ImagenPGM*>(img)->getHeight(), width=static_cast<ImagenPGM*>(img)->getWidth(), colorDepth=static_cast<ImagenPGM*>(img)->getColorDepth();

    int **addMatrix = new int*[height];
    for (int i=0; i < height; i++)
        addMatrix[i]=new int[width];
    int minValue = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            minValue= min((*matrixImagenP[i][j]),(*static_cast<ImagenPGM*>(image)->getMatrix()[i][j]));
            if (minValue<=colorDepth) {
                addMatrix[i][j]=minValue;
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



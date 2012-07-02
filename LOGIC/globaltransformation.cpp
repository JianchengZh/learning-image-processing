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

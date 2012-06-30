#include "segmentation.h"
#include <QDebug>

#define eps 1.0E-3
Segmentation::Segmentation()
{

}

Image * Segmentation::kmeans(Image *img, int clusters)
{

    //Calcular el valor de los centroides iniciales de manera aleatoria
    //Se recorre la imagen y se agrupa en el un cluster(grupo) dependiendo del centroide al que mas cercano esten

    //Se calcula el centroide para cada grupo y se tienen presentes los centroides anteriores

    //Se calcula el error es decir la diferencia existente entre los centroides viejos y los nuevos
    int centroid[clusters];
    int  oldCentroid[clusters];
    int ***matrix = static_cast<ImagenPGM*>(img)->getMatrix();
    int width = static_cast<ImagenPGM*>(img)->getWidth();
    int height = static_cast<ImagenPGM*>(img)->getHeight();
    int colorDepth = static_cast<ImagenPGM*>(img)->getColorDepth();
    srand(time(NULL));

    for(int i=0; i < clusters; i++)
    {
        int x = rand()%(height-1);
        int y = rand()%(width-1);
        centroid[i] =*matrix[x][y];
        oldCentroid[i] = 0;
    }

    int label;
    int temp;
    int dist=100000;
    double grayScale[clusters];
    int count[clusters];

    int  labeled[height][width];//matriz de clasificacion
    int tgray = 0;
    bool continuar = true;


    while(continuar) {

        for(int i=0;i<clusters;i++)
        {
            grayScale[i] = 0;
            count[i] = 0;
        }

        for(int i=0; i < height; i++)
        {
            for(int j=0; j< width; j++)
            {

                tgray = *matrix[i][j];
                dist = distance(centroid[0], tgray );
                label = 0;
                for(int k=1; k<clusters; k++)
                {
                    temp = distance(centroid[k], tgray );

                    if( temp < dist) {
                        dist = temp;
                        label = k;

                    }

                }

                count[label]++;
                grayScale[label] += tgray;

                if(equals(centroid,oldCentroid,clusters))
                {
                    labeled[i][j] = label;

                    continuar = false;
                }
            }
        }
        //actualizar centroides
        for(int i=0;i<clusters;i++)
        {
            oldCentroid[i] = centroid[i];

            if(count[i]==0) continue; //no actualizar centroide si no se hay colores que promediar
            centroid[i] = (int)(grayScale[i]/count[i]);




        }




    }

    int **kmeansMatrix = new int*[height];
    for (int i=0; i < height; i++)
        kmeansMatrix[i]=new int[width];

    for(int i=0; i < height; i++) {
        for(int j=0; j < width; j++) {
            kmeansMatrix[i][j] =  centroid[labeled[i][j]];

        }
    }


    ImagenPGM *result = new ImagenPGM(height, width, colorDepth, kmeansMatrix);


    return result;




}

int Segmentation::distance(int x, int y)
{
    return  sqrt((x-y)*(x-y));
}

bool Segmentation::equals(int *centroid, int *oldcentroid, int size)
{
    double total = 0;
    bool equal = false;

    for(int i=0; i<size;i++)
    {
        total += (centroid[i] - oldcentroid[i])*(centroid[i] - oldcentroid[i]);
    }

    total = sqrt(total);


    if(total < eps)
        equal= true;




    return  equal;


}

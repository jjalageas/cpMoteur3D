#include "Filters.h"

int Filters::ConnexityX[8] = {1, -1, 0, 0, 1, 1, -1, -1};
int Filters::ConnexityY[8] = {0, 0, 1, -1, 1, -1, 1, -1};



void Filters::Convolution (ImageMask2d *image, int filterWidth, int filterHeight, double filter[])
{
    Image<float> *data = image->getImageCopy();

    Filters::ApplyConvolution(data, filterWidth, filterHeight, filter);

    int width = image->getWidth();
    int height = image->getHeight();

    for (int i=0 ; i < width * height ; i++)
        image->set(data->get(i), i);
    delete data; data = NULL;
}

void Filters::ConvolutionXY(ImageMask2d *image, int filterWidth, int filterHeight, double filterX[], double filterY[])
{
    Image<float> *convX = image->getImageCopy();
    Image<float> *convY = image->getImageCopy();

    Filters::ApplyConvolution(convX, filterWidth, filterHeight, filterX);
    Filters::ApplyConvolution(convY, filterWidth, filterHeight, filterY);

    int size = image->getWidth() * image->getHeight();

    for (int i=0 ; i < size ; i++)
        image->set(sqrt(pow(convX->get(i), 2.0) + pow(convY->get(i), 2.0)), i);

    delete convX; convX = NULL;
    delete convY; convY = NULL;
}

/* -------------------------------------------------------------------------------------------------
   PUBLIC METHODS
  -------------------------------------------------------------------------------------------------*/

void Filters::ApplyRoutine(ImageMask2d *image, MiList<Filter_t *> *routine)
{
    /*int width=image->getWidth();
    int height=image->getHeight();
    int coeff=0;
    int pourcent=0;*/

    for (int i=0 ; i < routine->size() ; i++)
    {

        MiList<float> *filter = routine->get(i);
        //cout<<"numero filter:"<<(int)filter->get(0)<<endl;
        switch ( (int)filter->get(0) )
        {
        case 0 :
            GaussianSpatial(image, filter->get(1));
            break;        
        case 4 :
            Prewitt(image);
            break;
        case 5 :
            Sobel(image);
            break;
        case 6 :
            Laplacian(image);
            break;
        case 7 :
            //cout<<"Smin Routine:"<<filter->get(1)<<"  Smax Routine"<< filter->get(2)<<endl;
            Bisseuillage(image, filter->get(1), filter->get(2));
            break;       
        case 9 :
            Inversion(image);
            break;        
        case 11 ://Morphologie Binaire
            Erosion(image,  filter->get(1), filter->get(2));
            break;
        case 12 :
           Dilatation(image,  filter->get(1), filter->get(2));
            break;
        case 13 :
            Close(image,  filter->get(1), filter->get(2));
            break;
        case 14 :
            Open(image,  filter->get(1), filter->get(2));
            break;

        }
    }
}

void Filters::ApplyConvolution(Image<float> *image, int filterWidth, int filterHeight, double filter[])
{
    int decalHeight = (filterHeight - 1) / 2;
    int decalWidth = (filterWidth - 1) / 2;
    int width = image->getWidth();
    int height = image->getHeight();
    Image<float> *tmp = new Image<float>(*image);

    for (int j= decalHeight ; j < height - decalHeight ; j++)
    {
        for (int i=decalWidth ; i < width - decalWidth; i++)
        {
            double val = .0;
            for (int k=-decalHeight, q=0 ; k <= decalHeight ; k++, q++)
            {
                for (int l=-decalWidth, p=0 ; l <= decalWidth ; l++, p++)
                {
                    val += tmp->get(i+l, j+k) * filter[q * filterWidth + p];
                }
            }
            image->set(val, i, j);
        }
    }
    delete tmp; tmp = NULL;
}





//*************************************************************************************
//Histogrammes
//*************************************************************************************
float* Filters::MaxandMin(int width, int height, float *in) {
    int size = width * height;
    eassert(size > 0);
    float min = in[0];
    float max = in[0];

    for (int i = 0; i < size; ++i) {
        if (min > in[i])
            min = in[i];
        else if (max < in[i])
            max = in[i];

    }
    float* res = new float[2];

    res[0] = max;
    res[1] = min;
    return res;

}

template<typename T>
T Filters::Min(int width, int height, T *in) {
    int size = width * height;
    eassert(size > 0);
    T min = in[0];

    for (int i = 0; i < size; ++i) {
        if (min > in[i])
            min = in[i];
    }
    return min;
}

template<typename T>
T Filters::Max(int width, int height, T *in) {
    int size = width * height;
    eassert(size > 0);
    T max = in[0];

    for (int i = 0; i < size; ++i) {
        if (max < in[i])
            max = in[i];
    }
    return max;
}

/*float Filter::Min(int width, int height, float *in) {
    int size = width * height;
    eassert(size > 0);
    float min = in[0];

    for (int i = 0; i < size; ++i) {
        if (min > in[i])
            min = in[i];

    }
    return min;
}
float Filter::Max(int width, int height, float *in) {
    int size = width * height;
    eassert(size > 0);
    float max = in[0];

    for (int i = 0; i < size; ++i) {
        if (max < in[i])
            max = in[i];

    }
    return max;
}



int Filter::Max(int width, int height, int *in) {
    int max = -1000000;
    int size = width * height;
    for (int i = 0; i < size; ++i) {
        if (max < in[i])
            max = in[i];

    }
    return max;
}
int Filter::Max(int size, int *in) {
    int max = -1000000;
    for (int i = 0; i < size; ++i) {
        if (max < in[i])
            max = in[i];

    }
    return max;
}
//Permet de calculer l'histogramme cumulé de la classe C

*/


/*---------------------------------------------------------------------------------------------------------------
 Operation math sur l'image
 ---------------------------------------------------------------------------------------------------------------*/

/*
int Filter::Max(int x, int y) {
    return (x > y ? x : y);
}
int Filter::Min(int x, int y) {
    return (x < y ? x : y);
}

float Filter::Max(float x, float y) {
    return (x > y ? x : y);
}
float Filter::Min(float x, float y) {
    return (x < y ? x : y);
}
*/

void Filters::Inversion(ImageMask2d *image)
{
    int width = image->getWidth();
    int height = image->getHeight();
    int size = width * height;
    float max=image->getMaxVal();
    //normalize(width, height, 4096, support);

    for (int i = 0; i < size; ++i){
        float oldValue=image->get(i);
        image->set((float)(max - oldValue), i);

    }
}

//return true si cest les meme false sinon.
bool Filters::compare(ImageMask2d *image,ImageMask2d *image2){

    int width = image->getWidth();
    int height = image->getHeight();



    for (int i=0 ; i < width * height ; i++)
    {
        if(image->get(i)!=image2->get(i))
            return false;
    }
    return true;
}

void Filters::Addition(ImageMask2d *image,ImageMask2d *image2)
{
    int width = image->getWidth();
    int height = image->getHeight();

    Image<bool> *mask = image->getMaskRef();
    Image<bool> *mask2 = image2->getMaskRef();

    for (int i=0 ; i < width * height ; i++) {
        if (mask->get(i)==0 && mask2->get(i)==0)
            mask2->set(0, i);
        else
            mask2->set(1, i);
    }
}

void Filters::soustraction(ImageMask2d *image,ImageMask2d *image2)
{
    int width = image->getWidth();
    int height = image->getHeight();
    Image<bool> *mask = image->getMaskRef();
    Image<bool> *mask2 = image2->getMaskRef();

    for (int i=0 ; i < width * height ; i++) {
        if(mask->get(i)==1 && mask2->get(i)==0)
            mask2->set(1, i);
        else
            mask2->set(0, i);
    }
}

void Filters::Union(ImageMask2d *image,ImageMask2d *image2)
{
    int width = image->getWidth();
    int height = image->getHeight();

    Image<bool> *mask = image->getMaskRef();
    Image<bool> *mask2 = image2->getMaskRef();

    for (int i=0 ; i < width * height ; i++) {
        if(mask->get(i)==1 || mask2->get(i)==1)
            mask2->set(1, i);
        else
            mask2->set(0, i);
    }
}

void Filters::Intersection(ImageMask2d *image,ImageMask2d *image2)
{
    int width = image->getWidth();
    int height = image->getHeight();

    Image<bool> *mask = image->getMaskRef();
    Image<bool> *mask2 = image2->getMaskRef();

    for (int i=0 ; i < width * height ; i++) {
        if(mask->get(i)==1 && mask2->get(i)==1)
            mask2->set(1, i);
        else
            mask2->set(0, i);
    }
}

void Filters::ImageMoinsValue(ImageMask2d *image,int value)
{
    int width = image->getWidth();
    int height = image->getHeight();
    for(int i=0;i<width*height;++i)
        image->set(image->get(i)-value, i);
}



/*---------------------------------------------------------------------------------------------------------------
 Filtres exemple
 ---------------------------------------------------------------------------------------------------------------*/

double Filters::PrewittX[9] = {1, 0, -1, 1, 0, -1, 1, 0, -1};
double Filters::PrewittY[9] = {1, 1, 1, 0, 0, 0, -1, -1, -1};
double Filters::SobelX[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
double Filters::SobelY[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
double Filters::Laplacien[9] = {0, 1, 0, 1, -4, 1, 0, 1, 0};



void Filters::Prewitt(ImageMask2d *image)
{
    Filters::ConvolutionXY(image, 3, 3, PrewittX, PrewittY);
}

void Filters::Sobel(ImageMask2d *image)
{
    Filters::ConvolutionXY(image, 3, 3, SobelX, SobelY);
}

void Filters::Laplacian(ImageMask2d *image)
{
    Filters::Convolution(image, 3, 3, Laplacien);
}


/* -------------------------------------------------------------------------------------------------
BISSEUILLAGE
  -------------------------------------------------------------------------------------------------*/

void Filters::Bisseuillage(ImageMask2d *image, float min, float max)
{
    int width = image->getWidth();
    int height = image->getHeight();

    Image<bool> *mask = image->getMaskRef();

    for (int i=0 ; i < width * height ; i++)
    {
        if ( (image->get(i) < max)
            && (image->get(i) > min) ){
            mask->set(1, i);

        }
        else
            mask->set(0, i);
    }
}

/* -------------------------------------------------------------------------------------------------
   PRE TRAITEMENT
  -------------------------------------------------------------------------------------------------*/

void Filters::GaussianSpatial(ImageMask2d *image, float sigma)
{
    double gaussian[25];
    double sum= 0.0;

    for (int j=-2 ; j <= 2 ; j++)
    {
        for (int i=-2 ; i <= 2 ; i++)
        {
            double val =  exp (- (abs(i) + abs(j)) / (2 * sigma * sigma) );
            gaussian[(j+2) * 5 + (i+2)] = val;
            sum += val;
        }
    }

    for (int i =0 ; i < 25 ; i++)
        gaussian[i] /= sum;

    Filters::Convolution(image, 5, 5, gaussian);
}

/* -------------------------------------------------------------------------------------------------
   MORPHOLOGY binaire
  -------------------------------------------------------------------------------------------------*/

void Filters::Erosion(ImageMask2d *image, int iteration, int connexity)
{
       int width = image->getWidth();
       int height = image->getHeight();
       Image<bool> *mask = image->getMaskRef();

       for (int it=0 ; it < iteration ; it++)
       {
              Image<bool> *copy = new Image<bool>(*mask);

              for (int j=1 ; j < height-1 ; j++)
              {
                     for (int i=1 ; i < width-1 ; i++)
                     {
                            int val = 0;
                            for (int c=0 ; c < connexity ; c++)
                                   val += copy->get(i+Filters::ConnexityX[c], j+Filters::ConnexityY[c]);
                            mask->set((val == connexity) ? 1 : 0, i, j);
                     }
              }
              delete copy;
       }
}

void Filters::Dilatation(ImageMask2d *image, int iteration, int connexity)
{
       int width = image->getWidth();
       int height = image->getHeight();
       Image<bool> *mask = image->getMaskRef();
       for (int it=0 ; it < iteration ; it++)
       {

              Image<bool> *copy = new Image<bool>(*mask);

              for (int j=1 ; j < height-1 ; j++)
              {
                     for (int i=1 ; i < width-1 ; i++)
                     {
                            int val = 0;
                            for (int c=0 ; c < connexity ; c++)
                                   val += copy->get(i+Filters::ConnexityX[c], j+Filters::ConnexityY[c]);


                            mask->set((val > 0) ? 1 : 0, i, j);
                     }
              }
              delete copy;
       }
}



void Filters::Open(ImageMask2d *image, int iteration, int connexity)
{
       for (int i=0 ; i < iteration ; i++)
       {
              Dilatation(image, 1, connexity);
              Erosion(image, 1, connexity);
       }
}

void Filters::Close(ImageMask2d *image, int iteration, int connexity)
{
       for (int i=0 ; i < iteration ; i++)
       {
              Erosion(image, 1, connexity);
              Dilatation(image, 1, connexity);
       }
}

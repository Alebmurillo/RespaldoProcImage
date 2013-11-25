#ifndef OPENIPLIB_OPENCVIMPL_H
#define OPENIPLIB_OPENCVIMPL_H
#include "openimprolib.h"
#include "includes.h"

using namespace std;
/*Inherits from the OpenImProLib*/
class OpenImProLib_OpenCvImpl : public OpenImProLib
{
private:
    int imProThresh2CvThresh(ThresholdType thresholdType);

public:
    OpenImProLib_OpenCvImpl();

    /*
    *The Canny filter detects the edges on an images
    *Calculates the first derivative in the four directions, and applies an hysteresis threshold
    *Hysteresis threshold: Has an Upper and Lower boundary, U and L. If the gradient Gi > U at pixel Pi, then Pi is classified as an edge
    *if  L < Gi < U, and Gi is connected to a Pixel Pj classified as an edge, then Pi is also classified as an edge
    *Otherwise the Pixel Pi is part of the background
    *@param input, input image, should be in grayscale (one channel)
    *@param output, binary image, with one channel. It is an empty pointer, the image is created with 32F, 1 channel format
    *@param limInf, Lower boundary L
    *@param limSup, Upper boundary U
    *@param appertureSize, defines the size of the convolution window. Odd numbers 3, 5 and 7 must be used
    *A smaller window is more sensitive to noise
    *@return Binary Image with the edges white and the rest of the image black
    */
    ImageImPro* filterCanny(ImageImPro* input, double limInf, double limSup, int apertureSize);
    /*
    *The sobel filter is an approximation to a derivative, it can apply first or second order in both coordinates in an image
    *First, the sobel operator applies a gaussian filter, in order to smooth the image
    *Then it calculates the derivative, and umbralizes the image
    *@param input, the input image, could be grayscale or RGB
    *@param output, the output image must have at least 16 bit pixel representation, to avoid overflow
    *@param xOrder, the derivative order for the X axis
    *@param yOrder, the derivative order for the Y axis
    *@param apertureSize, size of the filter window, if the size is 3, the scharr filter is used, less sensitive to noise
    */
    ImageImPro* filterSobel(ImageImPro* input, int xOrder, int yOrder, int apertureSize);
    /*
    *Convolves the gaussian kernel defined in the parameters with the input image
    *Applying this filter to the image results in a blur effect, with the frequency equivalence to a low pass filter, thus reducing
    *noise but also making edges blurrier
    *@param ptrInput, Input image to convolve
    *@param sigmaX, standard deviation of the gaussian bell in the x axis
    *@param sigmaY, standard deviation of the gaussian bell in the y axis
    *@param apertureSize, x and y axis dimension of the convolving window mask
    *@return filtered image
    */
    ImageImPro* filterGauss(ImageImPro* ptrInput, double sigmaX, double sigmaY, int apertureSize);
    /*
    *Applies the non linear bilateral filter to the given image
    *Proposed by Tomasi and Manduchi, the bilateral filter applies a gaussian weighthing function in the space dimension, just as
    *the Gaussian filter, and also applies a gaussian weighting factor for the pixel range, thus minimizing edge blurring
    *@param ptrInput, input image
    *@param winDiameter, convolving window diameter
    *@param sigmaRange, standard deviation of the pixel intensity range gaussian weighthing function
    *@param sigmaSpace , standard deviation of the space L2 distance gaussian weighthing function
    *@return filtered image
    */
    ImageImPro* filterBilateral(ImageImPro* ptrInput, int winDiameter, double sigmaRange, double sigmaSpace);
    /*
    * The threshold operator classifies each pixel on the input image Pi, comparing Pi < threshold, and in the output applyng the type
    * of threshold selected by the user
    *@param input, input image must have ideally a dimmension of 1, otherwise the grayscaled image will be calculated
    *@param output, output image, with the threshold applied, It is an empty pointer, the image is created with 8U, 1 channel format
    *@param limInf, Lower boundary L
    *@param threshold, the threshold checked in every pixel
    *@param maxValue, the maxValue of the output image, assigned according to the type of threshold
    *@param typeThresh, the type of the threshold could be:
    *BINARY_THRESH: Output_i = (Input_i > Thresh) Max:0
    *BINARY_INV_THRESH: Output_i = (Input_i > Thresh) 0:Max
    *TRUNC_THRESH: Output_i = (Input_i > Thresh) M:Input_i
    *TO_ZERO_INV_THRESH: Output_i = (Input_i > Thresh) 0:Input_i
    *TO_ZERO_INV_THRESH: Output_i = (Input_i > Thresh) Input_i:0
    */
    ImageImPro* applyThreshold(ImageImPro* input, double threshold, double maxValue, ThresholdType typeThresh);
    /*
    *Compares the given RGB threshold value to every pixel, and sets a 255 if the value is bigger, and 0 otherwise
    *@param threshold, threshold value
    *@return thresholded image
    */
    ImageImPro* thresholdEqualsRGB(ImageImPro* ptrInput, RGB_VALUE threshold);
    /*
    *Returns a new image with the contoured area defined by the ptrMask
    *@param ptrMask, Mask with objectTag at the pixels values to copy from the ptrInput image to the ptrOutput image
    *@param ptrInput, input image
    *@param objectTag, object's tag
    *@return masked image
    */
    ImageImPro** getCounturedObjectMask(ImageImPro* ptrMask, ImageImPro* ptrInput, int objectMaskTag);
    /*
    *Returns the density function aproximation of the given image, following von Mises definition of probability
    *@param ptrMask, mask of the pixels to take into account for the density function
    *@param layer, to take into account
    */
    vector<float> getDensityFunction(ImageImPro* ptrInput, ImageImPro* ptrMask, int layer);
    double compareHistogram(vector<float> hist1, vector<float> hist2, int mehtod);
    ~OpenImProLib_OpenCvImpl(){}
};

#endif

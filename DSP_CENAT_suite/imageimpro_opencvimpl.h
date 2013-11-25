#ifndef IMAGEIMPRO_OPENCVIMPL_H
#define IMAGEIMPRO_OPENCVIMPL_H
#include "imageimpro.h"
#include "includes.h"
using namespace cv;


class ImageImPro_OpenCvImpl : public ImageImPro {

private:
    /*Pointer to the IplImage used in this implementation*/
    IplImage* ptrImage;
    int depthImPro2Cv(ImageImProDepth depth);
    ImageImProDepth depthCv2ImPro(int depth);
    ImageImProDepth depthMat2ImPro(int depth);
    void cloneImProImage(ImageImPro* ptrImageImPro);
public:
    /*
    *Class constructor
    */
    ImageImPro_OpenCvImpl();
    /*
    *Class constructor
    *@param ptrMat, Mat type object
    */
    ImageImPro_OpenCvImpl(Mat* ptrMat);
    /*
    *Class constructor
    *@param ptrImage, IplImage struct
    */
    ImageImPro_OpenCvImpl(IplImage* ptrImage);
    /*
    *Class constructor
    *@param ptrImage, GpuMat type object
    */
    ImageImPro_OpenCvImpl(GpuMat* ptrMat);
    /*
    *Class constructor
    *@param ptrImage, ImageImPro type object
    */
    ImageImPro_OpenCvImpl(ImageImPro* ptrImageImPro);
    /*
    *Class constructor
    *@param ptrName, path of the image to load
    */
    ImageImPro_OpenCvImpl(char* ptrName);
    /*
    *Class constructor
    *@param size, ImSize struct specifying the image dimensions
    *@param depth, image depth in bits
    *@param channels, number of channels of the image
    */
    ImageImPro_OpenCvImpl(ImSize size, ImageImProDepth depth, int channels);
    /*
    *Converts the image to QImage format
    *@return QImage
    */
    QImage* getQImage();
    /*
    *Converts to the Mat format used in OpenCV
    *@return Mat image
    */
    Mat* getMat();
    /*
    *Converts the image to the GPUMat format
    *@return GPUmat
    */
    GpuMat* getGPUMat();
    /*
    *Converts the image to the IplImage format
    *@return IplImage
    */
    IplImage* getOpenCvImage();
    /*
    *Returns grayScale image
    *@param ImageImPro, new image in grayscale
    *@return, grayscale image
    */
    ImageImPro* getGrayScale();
    /*
    *Returns a HSV image
    *@return ImageImPro, image in HSV
    */
    ImageImPro* getHSV();
    /*
    *Returns the image in the given layer
    *@return ImageImPro with the given layer information
    */
    ImageImPro* getLayer(int layer);
    /*
    *Loads an image from the received path
    *@param ptrName, image name
    */
    void loadImage(char* ptrName);
    /*
    *Creates an image with the given dimensions, depth and number of channels
    *@param size, image dimensions
    *@param depth, image depth struct
    *@param channels, number of channels or matrices
    */
    void createImage(ImSize size, ImageImProDepth depth, int channels);
    /*
    *Returns the image size struct
    *@return ImSize
    */
    ImSize getSize();
    /*
    *Returns the image depth constant
    *@return ImageImProDepth
    */
    ImageImProDepth getDepth();
    /*
    *Returns the number of channels of the image
    *@return number of channels
    */
    int getChannels();
    /*
    *Sets the pixel value in the given x, y coordinates and layer
    *@param x, column value of the image matrix
    *@param y, row value of the image matrix
    *@param value, int value to set
    *@param layer, layer number, starting from 0
    */
    void setPV(int x, int y, int value, int layer = 0);
    /*
    *Gets the pixel value in the given x, y coordinates and layer
    *@param x, column value of the image matrix
    *@param y, row value of the image matrix
    *@param layer, layer number, starting from 0
    *@return value,
    */
    int getPV(int x, int y, int layer = 0);
    /*
    *Gets the pixel value in the given x, y coordinates and layer
    *@param x, column value of the image matrix
    *@param y, row value of the image matrix
    *@param layer, layer number, starting from 0
    *@return value,
    */
    RGB_VALUE getPV_RGB(int x, int y);

    /*
    *Sets the pixel value in the given x, y coordinates and layer
    *@param x, column value of the image matrix
    *@param y, row value of the image matrix
    *@param value, RGB value
    *@param layer, layer number, starting from 0
    */
    void setPV(int x, int y, RGB_VALUE value);    
    /*
    *Shows the given image in a new window
    *@param ptrWinName, window name to display
    */
    void showImageOnWindow(char* ptrWinName);
    /*
    *Shows the given image in a new window, for a while
    *@param ptrWinName, window name to display
    */
    int showImageOnWindow(char* ptrWinName, int framerate);
    QImage* MatToQImage(const Mat& mat);
    /*Class destructor*/
    ~ImageImPro_OpenCvImpl();
};

#endif

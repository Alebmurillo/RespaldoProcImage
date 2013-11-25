#ifndef IMAGE_IMPRO_H
#define IMAGE_IMPRO_H
#include "includes.h"
using namespace::cv;
using namespace::std;
using namespace gpu;

#define R 2
#define G 1
#define B 0
#define WHITE 0
#define BLACK 1
#define FUCSIA 2

/*Image dimensions struct*/
class ImSize{
    public:
        /*Image width in pixels*/
        int width;
        /*Image height in pixels*/
        int height;
        /*Image width and height in pixels */
        ImSize(int width, int height){
            this->width = width;
            this->height = height;
        }
};

/*RGB classic values*/
class RGB_VALUE{
    public:
        int r;
        int g;
        int b;

    RGB_VALUE(int color){
        if(color == WHITE)
            setWhite();
        if(color == BLACK)
            setBlack();
        if(color == FUCSIA)
            setFucsia();
    }

    RGB_VALUE(int r, int g, int b){
        this->r = r;
        this->g = g;
        this->b = b;
    }
    void setWhite(){
        r = 255;
        g = 255;
        b = 255;
    }
    void setBlack(){
        r = 0;
        g = 0;
        b = 0;
    }
    void setFucsia(){
        r = 255;
        g = 0;
        b = 255;
    }
};
/*ImageImPro abstract class or interface, all its methods must be implemented*/
class ImageImPro{
    public:
        /*Enumeration list with classic depth values*/
        enum ImageImProDepth { BIT_8_U, BIT_16_S, BIT_32_F };
        ImageImPro();
        /*
        *Loads an image from the received path
        *@param ptrName, image name
        */
        virtual void loadImage(char* ptrName)=0;
        /*
        *Creates an image with the given dimensions, depth and number of channels
        *@param size, image dimensions
        *@param depth, image depth struct
        *@param channels, number of channels or matrices
        */
        virtual void createImage(ImSize size, ImageImProDepth depth, int channels)=0;
        /*
        *Returns grayScale image
        *@param ImageImPro, new image in grayscale
        *@return, grayscale image
        */
        virtual ImageImPro* getGrayScale() = 0;
        /*
        *Returns a HSV image
        *@return ImageImPro, image in HSV
        */
        virtual ImageImPro* getHSV() = 0;
        /*
        *Returns the image in the given layer
        *@return ImageImPro with the given layer information
        */
        virtual ImageImPro* getLayer(int layer) = 0;
        /*
        *Converts the image to QImage format
        *@return QImage
        */
        virtual QImage* getQImage() = 0;
        /*
        *Converts to the Mat format used in OpenCV
        *@return Mat image
        */
        virtual Mat* getMat() = 0;
        /*
        *Converts the image to the GPUMat format
        *@return GPUmat
        */
        virtual GpuMat* getGPUMat() = 0;
        /*
        *Converts the image to the IplImage format
        *@return IplImage
        */
        virtual IplImage* getOpenCvImage() = 0;
        /*
        *Returns the image size struct
        *@return ImSize
        */
        virtual ImSize getSize() = 0;
        /*
        *Returns the image depth constant
        *@return ImageImProDepth
        */
        virtual ImageImProDepth getDepth() = 0;
        /*
        *Returns the number of channels of the image
        *@return number of channels
        */
        virtual int getChannels() = 0;
        /*
        *Sets the pixel value in the given x, y coordinates and layer
        *@param x, column value of the image matrix
        *@param y, row value of the image matrix
        *@param value, int value to set
        *@param layer, layer number, starting from 0
        */
        virtual void setPV(int x, int y, int value, int layer = 0) = 0;
        /*
        *Sets the pixel value in the given x, y coordinates and layer
        *@param x, column value of the image matrix
        *@param y, row value of the image matrix
        *@param value, RGB value
        *@param layer, layer number, starting from 0
        */
        virtual void setPV(int x, int y, RGB_VALUE value) = 0;
        /*
        *Gets the pixel value in the given x, y coordinates and layer
        *@param x, column value of the image matrix
        *@param y, row value of the image matrix
        *@param layer, layer number, starting from 0
        *@return value,
        */
        virtual int getPV(int x, int y, int layer = 0) = 0;
        /*
        *Gets the pixel value in the given x, y coordinates and layer
        *@param x, column value of the image matrix
        *@param y, row value of the image matrix
        *@param layer, layer number, starting from 0
        *@return value,
        */
        virtual RGB_VALUE getPV_RGB(int x, int y) = 0;
        /*
        *Shows the given image in a new window
        *@param ptrWinName, window name to display
        */
        virtual void showImageOnWindow(char* ptrWinName) = 0;

        /*
        *Shows the given image in a new window, for a while
        *@param ptrWinName, window name to display
        */
        virtual int showImageOnWindow(char* ptrWinName, int framerate) = 0;
        /*
        *Empty destructor must be implemented on the children
        */
        virtual ~ImageImPro(){}

};
#endif

#ifndef HOGDETECTORGPU_H
#define HOGDETECTORGPU_H
#include "imageimpro_opencvimpl.h"
#define PIX_BLOCK_X 32
#define PIX_BLOCK_Y 32
#define PIX_CELL_X 8
#define PIX_CELL_Y 8
#define WIN_X 32
#define WIN_Y 32
//Defines the window overlap, must be a multiple of the block stride
#define WIN_STRIDE_X  8
#define WIN_STRIDE_Y  8
//Coefficient of the window scale increase
#define SCALE_0 1.05
/*
*This class wraps the Histogram of gradients detector implementation on opencv
*The OpenCV implementation is based on the paper written by Dalal & Triggs on 2005
*"Histograms of Oriented Gradients for Human Detection"
*The current implementation uses the CPU
*/

class HOGDetectorCPU{
private:
    /*
    *Performs the HOG detection and returns the original image with bounding rectangles
    *on detected pedestrians
    *@param ptrImage, input image
    *@return image with detected people
    */
    Mat* detectPeople(Mat* ptrImage, double hitThreshold, double groupThreshold);
public:
    /*
    *Default constructor
    */
    HOGDetectorCPU();   
    /*
    *Performs the HOG detection and returns the original image with bounding rectangles
    *on detected pedestrians
    *@param ptrImage, input image
    *@return image with detected people
    */
    ImageImPro* detectPeople(ImageImPro* ptrImage, double hitThreshold, double groupThreshold);


};

#endif

#ifndef BACKGROUNDSEGMENTATORAGMM_H
#define BACKGROUNDSEGMENTATORAGMM_H
#include "backgroundsegmentator.h"
//Default algorithm variables
//Number of initial gaussian mixtures
#define NUM_GAUSSIANS 3
//foreground Region area threshold in pixels
#define FORE_REGION_THRESH 220
//Number of frames used of sample function, objective to adjust the AGMM model
#define HISTORY 100
//Standard deviation forground threshold
#define STD_THRESH 32
//Shadow detection
#define SHADOW_DETECTION false


/*
*This class implements the abstract background segmentation algorithm class
*This implementation is based on the algorithm presented in the paper
*"Improved Adaptive Gaussian Mixture Model for Background Substraction" also known as Adaptive Gaussian Mixture Model segmentator (AGMM)
*This algorithm implements a Gaussian mixture model based background segmentator
*The number of gaussian functions is adaptive, with an initial standard deviation
*/
class BackgroundSegmentatorAGMM : public BackgroundSegmentator{
private:
    /*The opencv background segmentator*/
    cv::BackgroundSubtractorMOG2* ptrBGM2;
    /*
    *From a set of contours returns the rectangles bounding them
    *Additionaly eliminates the smallest areas
    *@param contours, the set of contours to be processed
    *@param threshold, the threshold, in absolute number of pixels used to eliminate small areas
    *@param delta, the additional margin added to the thresholded regions
    *@param size, size of the original image
    */
    list<cv::Rect> getContoursRectangles(std::vector<std::vector<cv::Point> > contours, int delta, int threshold, cv::Mat::MSize size);    
    /*
    *Returns the tracking candidates
    *@param contours, the set of contours to be processed
    *@param threshold, the threshold, in absolute number of pixels used to eliminate small areas
    *@param delta, the additional margin added to the thresholded regions
    *@param size, size of the original image
    */
    list<cv::Rect> getTrackingCandidates(std::vector<std::vector<cv::Point> > contours, int delta, int threshold, cv::Mat::MSize size);
public:
    /*Default constructor, assigns the default values defined in here*/
    BackgroundSegmentatorAGMM();
    /*
    *Class constructor
    *@param history, number of frames used to approximate de Adaptive GMM
    *@param varThreshold, de standard deviance deviation threshold defined to classify a pixel as foreground
    *@param shadowDetection, performs the AGMM on a luminance free space color in order to avoid false positives provoked by shadows
    */
    BackgroundSegmentatorAGMM(int history, float varThreshold, bool bShadowDetection = true);
    /*
    *Abstract method, returns an array of tracking candidates, resulting from the adaptive background segmentation
    *@param ptrInput, input image to be processed, it belongs to a video sequence
    *@param alpha, defines the learning rate, when alpha -> 0, the algorithm learns a pixel as a background more slowly
    *@param delta, defines the additional margin of the segmented rectangles, in order to stick close regions and provide an additional error margin
    *@return list<ImageImPro*>, list of images, each one containing a foreground region
    */
    list<ImageImPro*> substractForegroundMasks(ImageImPro* ptrInput, double alpha, int delta);
    /*
    *Returns the last background image processed
    *@return background image
    */
    ImageImPro* getBackgroundImage();

};

#endif // BACKGROUNDSEGMENTATORAGMM_H

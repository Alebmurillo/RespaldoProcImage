#ifndef BACKGROUNDSEGMETATOR_H
#define BACKGROUNDSEGMETATOR_H
#include "includes.h"
#include "imageimpro_opencvimpl.h"
/*
*This class abstracts the background segmentation algorithms, most of them
*based on gaussian mixture models
*These algorithms model the background as a mixture of gaussians, to latter
*classify each pixel as background if its evaluation on the mixture density function
*falls within a certain standard deviation threshold of the N gaussian functions
*/
class BackgroundSegmentator
{
public:
    /*Default constructor, assigns the default values defined in every implementation*/
    BackgroundSegmentator();
    /*
    *Abstract method, returns an array of tracking candidates, resulting from the adaptive background segmentation
    *@param ptrInput, input image to be processed, it belongs to a video sequence
    *@param alpha, defines the learning rate, when alpha -> 0, the algorithm learns a pixel as a background more slowly
    *@param delta, defines the additional margin of the segmented rectangles, in order to stick close regions and provide an additional error margin
    *@return list<ImageImPro*>, list of images, each one containing a foreground region
    */
    virtual list<ImageImPro*> substractForegroundMasks(ImageImPro* ptrInput, double alpha, int delta) = 0;
    /*
    *Returns the last background image processed
    *@return background image
    */
    virtual ImageImPro* getBackgroundImage() = 0;
};

#endif // BACKGROUNDSEGMETADOR_H

#ifndef VIDEOIMPRO_OPENCVIMPL_H
#define VIDEOIMPRO_OPENCVIMPL_H
#include "imageimpro.h"
#include "imageimpro_opencvimpl.h"
#include "videoimpro.h"

class VideoImPro_OpenCvImpl: public VideoImPro
{
private:    
    double frameRate;

    VideoCapture videoOpenCV;
    VideoWriter outputVideo;
public:
    VideoImPro_OpenCvImpl(int frameRate);
    VideoImPro_OpenCvImpl(char* ptrPath);
    void loadVideo(char* ptrPath);
    void createVideo(char* ptrPath, int frameRate, ImSize vidSize, bool isColor);
    void closeVideo(char* ptrPath, bool videoWrite);
    void writeToVideo(char* ptrName, ImageImPro *ptrInput);
    ImageImPro* getNextFrame();
    ImageImPro* getFrame(int numFrame);
    ImSize getImSize();
    int getNumFrames();    
};

#endif // VIDEOIMPRO_OPENCVIMPL_H

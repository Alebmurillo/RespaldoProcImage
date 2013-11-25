#ifndef VIDEOIMPRO_H
#define VIDEOIMPRO_H
#include "imageimpro.h"
class VideoImPro
{
public:
    VideoImPro();
    virtual void loadVideo(char* ptrName) = 0;
    virtual void writeToVideo(char* ptrName, ImageImPro* ptrInput) = 0;
    virtual ImageImPro* getNextFrame() = 0;
    virtual ImageImPro* getFrame(int numFrame) = 0;
    virtual void createVideo(char* ptrPath, int frameRate, ImSize vidSize, bool isColor) =0;
    virtual void closeVideo(char* ptrPath, bool videoWrite)=0;
    virtual ImSize getImSize() = 0;
    virtual int getNumFrames() = 0;
};

#endif // VIDEOIMPRO_H

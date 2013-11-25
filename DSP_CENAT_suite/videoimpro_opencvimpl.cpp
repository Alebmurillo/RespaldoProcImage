#include "videoimpro_opencvimpl.h"

VideoImPro_OpenCvImpl::VideoImPro_OpenCvImpl(int frameRate){
    this->frameRate = frameRate;
}

VideoImPro_OpenCvImpl::VideoImPro_OpenCvImpl(char *ptrPath){
    this->loadVideo(ptrPath);
}

void VideoImPro_OpenCvImpl::loadVideo(char* ptrPath){
    this->videoOpenCV.open(ptrPath);
    //hacer manejo de excepciones
    if (!videoOpenCV.isOpened()){
           cout  << "Could not open the input video: " << ptrPath << endl;
    }
}

void VideoImPro_OpenCvImpl::createVideo(char* ptrPath, int frameRate, ImSize vidSize, bool isColor){
 this->frameRate = frameRate;
 Size videoSize(vidSize.width, vidSize.height);
 outputVideo.open(ptrPath, -1, this->frameRate, videoSize, isColor);
}
void VideoImPro_OpenCvImpl::closeVideo(char* ptrPath, bool videoWrite){
    if(videoWrite){
     videoOpenCV.release();
    }
    else{
        outputVideo.release();
    }
}


void VideoImPro_OpenCvImpl::writeToVideo(char *ptrPath, ImageImPro* ptrInput){    
    Mat* ptrMatFrame = ptrInput->getMat();
    if(this->outputVideo.isOpened())
        outputVideo << *ptrMatFrame;
}

ImageImPro* VideoImPro_OpenCvImpl::getNextFrame(){
    ImageImPro* ptrFrame = NULL;
    Mat* ptrFrameCv = new Mat();
    bool read = videoOpenCV.read((*ptrFrameCv));
    if(read)
        ptrFrame = new ImageImPro_OpenCvImpl(ptrFrameCv);

    return ptrFrame;
}

int VideoImPro_OpenCvImpl::getNumFrames(){
    int numFrames = 0;

    return numFrames;
}

ImSize VideoImPro_OpenCvImpl::getImSize(){
    ImSize size = ImSize(videoOpenCV.get(CV_CAP_PROP_FRAME_WIDTH), videoOpenCV.get(CV_CAP_PROP_FRAME_HEIGHT));
    return size;
}

ImageImPro* VideoImPro_OpenCvImpl::getFrame(int numFrame){
    ImageImPro* ptrFrame = NULL;
    for ( int i=1;i<numFrame;i++)
    {
        this->getNextFrame();
    }
    ptrFrame =  this->getNextFrame();
    return ptrFrame;
}

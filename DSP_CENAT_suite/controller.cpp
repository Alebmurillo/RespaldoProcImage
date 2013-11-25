#include "controller.h"
#include <time.h>

#include <stdio.h>

#include <iostream>
#include <stdlib.h>
#include <time.h>



Controller::Controller(){
     this->ptrImage = NULL;
    using namespace std;
     this->ptrVideo = NULL;
     this->ptrHogVideo = new HOGDetectorCPU();
     this->ptrLib = new OpenImProLib_OpenCvImpl();     
     this->ptrSegVideo = new BackgroundSegmentatorAGMM();
}

void Controller::loadVideo(char* ptrPath){
    if(this->ptrVideo != NULL){
        delete this->ptrVideo;
    }
    this->ptrVideo = new VideoImPro_OpenCvImpl(ptrPath);
    if(this->ptrVideo == NULL){
        throw ControllerException("Invalid video name");
    }
    ImageImPro* ptrFrame = this->ptrVideo->getNextFrame();
    this->ptrCurrVideoImage = ptrFrame;

}

void Controller::playVideo(){
    ImageImPro* ptrFrame = this->ptrVideo->getNextFrame();
    if(this->ptrCurrVideoImage != NULL){
        delete this->ptrCurrVideoImage;
    }
    this->ptrCurrVideoImage = ptrFrame;
}

void Controller::playVideoHog(QString fileName){
    VideoCapture inputVideo(fileName.toStdString());
    ImageImPro* ptrOut;
    Mat* ptrMat;
    while(inputVideo.grab()){
        ptrMat = new Mat();
        inputVideo >> *ptrMat; // get a new frame from video
        ImageImPro* ptrFrame = new ImageImPro_OpenCvImpl(ptrMat);
        ptrOut = this->ptrHogVideo->detectPeople(ptrFrame, HIT_THRESHOLD, GROUP_THRESHOLD);
        ptrOut->showImageOnWindow("HOG result", 30);
    }
}

void Controller::playVideoSegmented(){    
    cv::Mat frame;
    cv::VideoCapture videoInput("../input/videos/piso.mp4");    
    for(;;){
        videoInput >> frame;
        ImageImPro_OpenCvImpl* ptrFrameImpro = new ImageImPro_OpenCvImpl(&frame);
        list<ImageImPro*> foregrounds = this->ptrSegVideo->substractForegroundMasks(ptrFrameImpro, ALPHA_BACK_SGM_LEARNING, DELTA_RECTANGLES);
        list<ImageImPro*>::iterator iter;
        iter = foregrounds.begin();        
        for(iter = foregrounds.begin(); iter != foregrounds.end(); iter++){
            ImageImPro* ptrCurrent = (ImageImPro*)*iter;
            ptrCurrent->showImageOnWindow("Segmentation result", 30);

        }

    }
}
/*
*Executes the main algorithm's flow
*@param ptrName, image path
*/
void Controller::processVideo(){
     ImageImPro* ptrFrame = this->ptrVideo->getNextFrame();
     while(ptrFrame != NULL){
         list<ImageImPro*> foregrounds = this->ptrSegVideo->substractForegroundMasks(ptrFrame, ALPHA_BACK_SGM_LEARNING, DELTA_RECTANGLES);
         list<ImageImPro*>::iterator iter;
         iter = foregrounds.begin();
         for(iter = foregrounds.begin(); iter != foregrounds.end(); iter++){
             ImageImPro* ptrCurrent = (ImageImPro*)*iter;
             ptrCurrent->showImageOnWindow("Segmentation result", 30);
             ImageImPro* ptrOut = this->ptrHogVideo->detectPeople(ptrCurrent, HIT_THRESHOLD, GROUP_THRESHOLD);
             ptrOut->showImageOnWindow("HOG result", 30);
         }
         ptrFrame = this->ptrVideo->getNextFrame();

     }
}

void Controller::loadImage(char* ptrPath)throw (ControllerException){
    if(this->ptrImage != NULL){
        delete this->ptrImage;
    }
    this->ptrImage = new ImageImPro_OpenCvImpl(ptrPath);
    if(this->ptrImage == NULL){
        throw ControllerException("Invalid image name");
    }

}

void Controller::applyFilterCanny()throw (ControllerException){
    if(this->ptrImage != NULL){
        ImageImPro* ptrImageCanny = this->ptrLib->filterCanny(this->ptrImage, 10, 500, 3);
        delete this->ptrImage;
        ptrImage = ptrImageCanny;
    }
    else{
         throw ControllerException("No image loaded");
    }
 }

void Controller::applyBilateral()throw (ControllerException){
    if(this->ptrImage != NULL){
        ImageImPro* ptrImageBilateralFilter=this->ptrLib->filterBilateral(this->ptrImage, 14, 7, 10 );
        delete this->ptrImage;
        ptrImage = ptrImageBilateralFilter;        
    }
    else{
         throw ControllerException("No image loaded");
    }

}


void Controller::applyFilterSobel()throw (ControllerException){
     if(this->ptrImage != NULL){         
         ImageImPro* ptrImageSobel = this->ptrLib->filterSobel(ptrImage, 1, 1, 3);
         delete this->ptrImage;
         ptrImage = ptrImageSobel;
     }
     else{
         throw ControllerException("No image loaded");
     }
 }

void Controller::applyFilterGauss()throw (ControllerException){
    if(this->ptrImage != NULL){
        ImageImPro* ptrImageGauss = this->ptrLib->filterGauss(this->ptrImage, 0, 0, 11);
        delete this->ptrImage;
        ptrImage = ptrImageGauss;
    }
    else{
        throw ControllerException("No image loaded");
    }

}
void Controller::convertToHSV()throw (ControllerException){
    if(this->ptrImage != NULL){
        ImageImPro* ptrImageHSV = this->ptrImage->getHSV();
        cout<<"hizo la transcripcion RNA"<<endl;
        delete this->ptrImage;
        ptrImage = ptrImageHSV;
    }
    else{
        throw ControllerException("No image loaded");
    }
}

void Controller::applyBinaryThreshold()throw (ControllerException){
     if(this->ptrImage != NULL){        
         ImageImPro* ptrImageBin = this->ptrLib->applyThreshold(this->ptrImage, 100, 255, OpenImProLib::BINARY_THRESH);
         delete this->ptrImage;
         ptrImage = ptrImageBin;
     }
     else{
         throw ControllerException("No image loaded");
     }
 }

 ImageImPro* Controller::getImage(){
    return this->ptrImage;
 }
 ImageImPro* Controller::getVideo(){
    return this->ptrCurrVideoImage;
 }
Controller::~Controller(){
    if(this->ptrImage != NULL)
        delete this->ptrImage;
    if(this->ptrLib != NULL)
        delete this->ptrLib;
}

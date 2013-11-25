#include "hogdetectorcpu.h"
#include <iostream>

using namespace std;

HOGDetectorCPU::HOGDetectorCPU()
{
}

//More eficient version, designed for video processing
Mat* HOGDetectorCPU::detectPeople(Mat* ptrMat, double hitThreshold, double groupThreshold){
   Mat* ptrMatImage = ptrMat;
   vector<float> detector;
   vector<Rect> found;   

   cv::HOGDescriptor cpuHog;
   //Sets the svm trained to detect people
   detector = cv::HOGDescriptor::getDefaultPeopleDetector();
   cpuHog.setSVMDetector(detector);
   Size sizeWinStride(WIN_STRIDE_X, WIN_STRIDE_Y);
   //performs hog detection
   cpuHog.detectMultiScale(*ptrMat, found, hitThreshold, sizeWinStride, Size(32,32), SCALE_0, groupThreshold);
   //groupRectangles(found,1,1000);

   list<Rect> finalRects;
   //Rect intersection = rect1 & rect2;
   for(int i = 0; i < (int)found.size(); ++i){
       Rect current = found[i];
        if(i == 0){
            finalRects.push_front(current);
        }
        else{
            list<Rect>::iterator iter = finalRects.begin();
            //iterates through the found rectangles enclosing the ROI's
            while(iter != finalRects.end() && finalRects.size() > 0){
                Rect pivot =  (Rect)*iter;
                Rect intersection = pivot & current;
                if (intersection.area() > 500)
                {
                    current = pivot | current;
                    finalRects.erase(iter);
                }

                    iter++;

            }
            finalRects.push_front(current);
        }
    }
   list<Rect>::iterator printIterator = finalRects.begin();
   //paints the rectangles in a matrix named mask
   while(printIterator != finalRects.end()){
       Rect currentRect = (Rect)*printIterator;
       rectangle(*ptrMat, currentRect.tl(), currentRect.br(),  CV_RGB(255, 255, 255), 3);
       printIterator++;
   }

   return ptrMatImage;
}


ImageImPro* HOGDetectorCPU::detectPeople(ImageImPro* ptrImage, double hitThreshold, double groupThreshold){
    Mat* ptrMatOut;
    vector<Mat> spl;
    Mat* ptrMat = ptrImage->getMat();
    Mat finalMat;
    split(*ptrMat, spl);
    cvtColor(*ptrMat, *ptrMat, CV_BGR2GRAY);
    ptrMatOut = detectPeople(ptrMat, hitThreshold, groupThreshold);
    spl[0] = *(ptrMatOut);
    spl[1] = *(ptrMatOut);
    spl[2] = *(ptrMatOut);
    merge(spl, finalMat);
    ImageImPro_OpenCvImpl* ptrImageProc = new ImageImPro_OpenCvImpl(ptrMatOut);
    return ptrImageProc;
}


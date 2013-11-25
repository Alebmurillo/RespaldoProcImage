#include "openimprolib_opencvimpl.h"


OpenImProLib_OpenCvImpl::OpenImProLib_OpenCvImpl(){
}

ImageImPro* OpenImProLib_OpenCvImpl::filterBilateral(ImageImPro* ptrInput, int winDiameter, double sigmaRange, double sigmaSpace){
    Mat* ptrMatInput = ptrInput->getMat();
    Mat* ptrMatOutput = ptrInput->getMat();
    bilateralFilter( *ptrMatInput, *ptrMatOutput, winDiameter, sigmaRange, sigmaSpace);
    ImageImPro* ptrOutput = new ImageImPro_OpenCvImpl(ptrMatOutput);
    delete ptrMatInput;
    delete ptrMatOutput;
    return ptrOutput;
}

int OpenImProLib_OpenCvImpl::imProThresh2CvThresh(ThresholdType thresholdType){
    int cvThreshType = -1;
    switch(thresholdType){
           case BINARY_THRESH:
                cvThreshType = CV_THRESH_BINARY;
           break;
           case BINARY_INV_THRESH:
                cvThreshType = CV_THRESH_BINARY_INV;
           break;
           case TRUNC_THRESH:
                cvThreshType = CV_THRESH_TRUNC;
           break;
           case TO_ZERO_THRESH:
                cvThreshType = CV_THRESH_TOZERO;
           break;
           case TO_ZERO_INV_THRESH:
                cvThreshType = CV_THRESH_TOZERO_INV;
           break;
    }
    return cvThreshType;
}

ImageImPro* OpenImProLib_OpenCvImpl::filterCanny(ImageImPro* ptrInput, double limInf, double limSup, int apertureSize){    
    IplImage* ptrInputCv = ptrInput->getOpenCvImage();
    IplImage* ptrOutputCv = cvCreateImage(cvGetSize(ptrInputCv), IPL_DEPTH_8U, 1);
    cvCanny(ptrInputCv, ptrOutputCv, limInf, limSup, apertureSize);
    ImageImPro* ptrOutput = new ImageImPro_OpenCvImpl(ptrOutputCv);    
    cvReleaseImage(&ptrOutputCv);
    cvReleaseImage(&ptrInputCv);
    return ptrOutput;
}

ImageImPro* OpenImProLib_OpenCvImpl::filterGauss(ImageImPro* ptrInput, double sigmaX, double sigmaY, int apertureSize){    
    Size size;
    size.width = apertureSize;
    size.height = apertureSize;
    Mat* ptrMatOutput = new Mat();
    Mat* ptrMatInput = ptrInput->getMat();
    GaussianBlur(*ptrMatInput, *ptrMatOutput, size, sigmaX, sigmaY);
    ImageImPro* ptrOutput = new ImageImPro_OpenCvImpl(ptrMatOutput);    
    delete ptrMatOutput;
    delete ptrMatInput;
    return ptrOutput;
}

ImageImPro* OpenImProLib_OpenCvImpl::applyThreshold(ImageImPro* ptrInput, double threshold, double maxValue, ThresholdType typeThresh){     
     IplImage* ptrCvInput = ptrInput->getOpenCvImage();
     IplImage* ptrCvOutput = cvCreateImage(cvGetSize(ptrCvInput), IPL_DEPTH_8U, 1);
     int cvThresholdType = imProThresh2CvThresh(typeThresh);
     if(ptrInput->getChannels() != 1){
         IplImage* ptrCvInputGray = cvCreateImage(cvSize(ptrCvInput->width, ptrCvInput->height),IPL_DEPTH_8U,1);
         cvCvtColor(ptrCvInput,ptrCvInputGray, CV_RGB2GRAY);
         cvThreshold(ptrCvInputGray, ptrCvOutput, threshold, maxValue, cvThresholdType);
         cvReleaseImage(&ptrCvInputGray);
     }
     else{
        cvThreshold(ptrCvInput, ptrCvOutput, threshold, maxValue, cvThresholdType);
     }
     ImageImPro* ptrOutput = new ImageImPro_OpenCvImpl(ptrCvOutput);
     cvReleaseImage(&ptrCvOutput);
     cvReleaseImage(&ptrCvInput);
     return ptrOutput;
}


ImageImPro* OpenImProLib_OpenCvImpl::filterSobel(ImageImPro* ptrInput, int xOrder, int yOrder, int apertureSize){  
    IplImage* ptrCvInput = ptrInput->getOpenCvImage();
    //buffer for sobel result needing more bits per pixel for the result, then, rescaling is necesary to get it back to 8 bits per pixel
    IplImage* ptrCvTemp = cvCreateImage(cvGetSize(ptrCvInput),IPL_DEPTH_32F,1);
    IplImage* ptrCvOutput = cvCreateImage(cvGetSize(ptrCvInput), IPL_DEPTH_8U, 1);
    if(ptrInput->getChannels() != 1){
        IplImage* ptrCvInputGray = cvCreateImage(cvSize(ptrCvInput->width,ptrCvInput->height),IPL_DEPTH_8U,1);
        cvCvtColor(ptrCvInput,ptrCvInputGray, CV_RGB2GRAY);
        cvSobel(ptrCvInputGray,ptrCvTemp, xOrder, yOrder, apertureSize);
        cvReleaseImage(&ptrCvInputGray);
    }
    else{
        cvSobel(ptrCvInput,ptrCvTemp, xOrder, yOrder, apertureSize);
    }
    cvConvertScaleAbs(ptrCvTemp, ptrCvOutput, 1, 0);
    ImageImPro* ptrOutput = new ImageImPro_OpenCvImpl(ptrCvOutput);
    cvReleaseImage(&ptrCvOutput);
    cvReleaseImage(&ptrCvInput);
    cvReleaseImage(&ptrCvTemp);
    return ptrOutput;
}

ImageImPro* OpenImProLib_OpenCvImpl::thresholdEqualsRGB(ImageImPro* ptrInput, RGB_VALUE threshold){
    ImageImPro* ptrOutput = new ImageImPro_OpenCvImpl(ptrInput->getSize(), ImageImPro::BIT_8_U, 1);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    //thresholds using the flag received to create a mask
    for(int y = 0; y < ptrInput->getSize().height; ++y){
        for(int x = 0; x < ptrInput->getSize().width; ++x){
            unsigned char r = ptrInput->getPV(x, y, R);
            unsigned char g = ptrInput->getPV(x, y, G);
            unsigned char b = ptrInput->getPV(x, y, B);
            if( r == threshold.r && b == threshold.b && g == threshold.g){
                ptrOutput->setPV(x, y, 255);
            }
            else{
                ptrOutput->setPV(x, y, 0);
            }
        }
    }
    Mat* ptrOutputMat = ptrOutput->getMat();
    findContours( *ptrOutputMat, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

      /// Draw contours
    Mat drawing = Mat::zeros( ptrOutputMat->size(), CV_8U);
    int k = 0;
    for( int i = 0; i < contours.size(); i++ ){
        if(i % 2 == 0){
            Scalar color = Scalar(255 - k);
            cout << "Objeto encontrado: " << k << endl;
            k++;
            //-1 to fill the countour
            drawContours( drawing, contours, i, color, -1, 8, hierarchy, 0, Point() );
        }
          /// Show in a window

    }
    delete ptrOutput;
    ptrOutput = new ImageImPro_OpenCvImpl(&drawing);
    //Eliminates the borders marked from the mask, to avoid taking them into account
    for(int y = 0; y < ptrInput->getSize().height; ++y){
        for(int x = 0; x < ptrInput->getSize().width; ++x){
            unsigned char r = ptrInput->getPV(x, y, R);
            unsigned char g = ptrInput->getPV(x, y, G);
            unsigned char b = ptrInput->getPV(x, y, B);
            if( r == threshold.r && b == threshold.b && g == threshold.g){
                ptrOutput->setPV(x, y, 0);
            }
        }
    }

    return ptrOutput;
}

ImageImPro** OpenImProLib_OpenCvImpl::getCounturedObjectMask(ImageImPro* ptrMask, ImageImPro* ptrInput, int objectMaskTag){
    ImageImPro* ptrOutput = NULL;
    ImageImPro* ptrOutputMask = NULL;
    int minX = DBL_MAX;
    int minY = DBL_MAX;
    int maxX = -1;
    int maxY = -1;
    int deltaX, deltaY;
    for(int x = 0; x < ptrInput->getSize().width; ++x ){
        for(int y = 0; y < ptrInput->getSize().height; ++y){
            unsigned char value = ptrMask->getPV(x, y);
            if(value == objectMaskTag){
                if(minX > x)
                    minX = x;
                if(minY > y)
                    minY = y;
                if(maxX < x)
                    maxX = x;
                if(maxY < y)
                    maxY = y;
            }
        }
    }
    deltaX = maxX - minX;
    deltaY = maxY - minY;
    ptrOutput = new ImageImPro_OpenCvImpl(ImSize(deltaX + 1, deltaY + 1), ptrInput->getDepth(), 3);
    ptrOutputMask = new ImageImPro_OpenCvImpl(ImSize(deltaX + 1, deltaY + 1), ptrInput->getDepth(), 1);
    for(int x = 0; x < ptrInput->getSize().width; ++x ){
        for(int y = 0; y < ptrInput->getSize().height; ++y){
            unsigned char value = ptrMask->getPV(x, y);
            if( value == objectMaskTag){
                ptrOutput->setPV(x - minX, y - minY, ptrInput->getPV_RGB(x, y));
                ptrOutputMask->setPV(x - minX, y - minY, 255, 0);
            }
        }
    }
    ImageImPro** ptrArray = (ImageImPro**)malloc(sizeof(ImageImPro*)*2);
    ptrArray[0] = ptrOutput;
    ptrArray[1] = ptrOutputMask;
    return ptrArray;
}

vector<float> OpenImProLib_OpenCvImpl::getDensityFunction(ImageImPro* ptrInput, ImageImPro* ptrMask, int layer){
    vector<float> histogram(180);
    int histSize = 180;

    /// Set the ranges ( for H )
    float range[] = { 0, 180} ;
    const float* histRange = { range };

    Mat h_hist;

    /// Compute the histogram:
    calcHist( ptrInput->getMat(), 1, 0, *(ptrMask->getMat()), h_hist, 1, &histSize, &histRange);//, uniform, accumulate );
    cout << "FILAS MAT HIST" << h_hist.rows << " COLS MAT HIST " << h_hist.cols << endl;
    for(int i = 0; i < h_hist.rows; ++i){
        histogram[i] = h_hist.at<int>(i, 0);
    }

    return histogram;
}

double OpenImProLib_OpenCvImpl::compareHistogram(vector<float> hist1, vector<float> hist2, int method){
    /*InputArray inHist1
    compareHist()*/
    return 0;
}

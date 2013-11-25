#include "backgroundsegmentatoragmm.h"
BackgroundSegmentatorAGMM::BackgroundSegmentatorAGMM(){
    this->ptrBGM2 = new BackgroundSubtractorMOG2(HISTORY, STD_THRESH, SHADOW_DETECTION);
    this->ptrBGM2->set("nmixtures", NUM_GAUSSIANS);
}

BackgroundSegmentatorAGMM::BackgroundSegmentatorAGMM(int history, float varThreshold, bool bShadowDetection){
    ptrBGM2 = new BackgroundSubtractorMOG2(history, varThreshold, bShadowDetection);
}

list<ImageImPro*> BackgroundSegmentatorAGMM::substractForegroundMasks(ImageImPro* ptrInput, double alpha, int delta){
    //list of candidate tracking regions
    list<ImageImPro*> listTrackingCandidatesImages;
    cv::Mat frame, fore;
    std::vector<std::vector<cv::Point> > contours;
    int dilation_type= cv::MORPH_RECT;
    int dilation_size = 0;
    //structuring element used on the openning operation
    cv::Mat element = cv::getStructuringElement( dilation_type,
                                         cv::Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                         cv::Point( dilation_size, dilation_size ) );
    Mat* ptrFrame = ptrInput->getMat();
    frame = *ptrFrame;
    //gets the foreground image with the first candidate regions
    this->ptrBGM2->operator ()(frame, fore, alpha);
    //performs the openning operation
    cv::erode(fore,fore,element);
    cv::dilate(fore,fore,element);
    //searches for the contours in the foreground image
    cv::findContours(fore, contours, CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);
    //returns the rectangles surrounding the candidate regions after an area thresholded
    list<cv::Rect> found= getTrackingCandidates(contours, delta, FORE_REGION_THRESH, frame.size);
    //cropped image contains
    cv::Mat croppedImage;
    list<Rect>::iterator iter = found.begin();
    //iterates through the found rectangles enclosing the ROI's
    while(iter != found.end()){
        Rect current =  (Rect)*iter;
        croppedImage = frame(current);        
        //rectangle(frame, current.tl(), current.br(),  CV_RGB(255, 255, 255), 1);
        //if fails, look here!
        //creates and adds the new image with the corresponding region to the list returned
        ImageImPro* ptrImageImpro = new ImageImPro_OpenCvImpl(&croppedImage);
        listTrackingCandidatesImages.push_back(ptrImageImpro);
        iter++;
    }    
    //frees memory
    delete ptrFrame;
    //returns the images list
    return listTrackingCandidatesImages;
}


list<cv::Rect> BackgroundSegmentatorAGMM::getContoursRectangles(std::vector<std::vector<cv::Point> > contours, int delta, int threshold, cv::Mat::MSize size){
    int index;
    int contours_index;
    std::list<Rect> finalcontours;
    //Analyzes the given contours to extract the bounding rectangles
    for (index = 0;index<contours.size();index++)
    {
        if (contours[index].size()>threshold){
            int y_max=0;
            int y_min=size[0];
            int x_max=0;
            int x_min=size[1];
            //checks the contours corners
            for(contours_index=0;contours_index<contours[index].size();contours_index++){
                if(contours[index][contours_index].y > y_max) y_max=contours[index][contours_index].y;
                if(contours[index][contours_index].x > x_max) x_max=contours[index][contours_index].x;
                if(contours[index][contours_index].y < y_min) y_min=contours[index][contours_index].y;
                if(contours[index][contours_index].x < x_min) x_min=contours[index][contours_index].x;
            }
            //adds the region additional margin
            y_max = y_max + delta;
            y_min = y_min - delta;
            x_max = x_max + delta;
            x_min = x_min - delta ;
            if (y_max > size[0]) y_max = size[0];
            if (x_max > size[1]) x_max = size[1];
            if (y_min < 0) y_min = 0;
            if (x_min < 0) x_min = 0;
            Rect pivot;
            pivot.x = x_min;
            pivot.y = y_min;
            pivot.width = x_max - x_min;
            pivot.height = y_max - y_min;
            finalcontours.push_back(pivot);     
        }
    }   
    //until here we got bigger rectangles
    return finalcontours;
}

list<cv::Rect> BackgroundSegmentatorAGMM::getTrackingCandidates(std::vector<std::vector<cv::Point> > contours, int delta, int threshold, cv::Mat::MSize size){
    std::vector<std::vector<cv::Point> > contoursOfRects;
    list<cv::Rect> finalRects;
    Mat mask =  cv::Mat::zeros(size[0], size[1], CV_8U);
    //processes the given contours in order to obtain the bounding rectangles
    list<cv::Rect> rectsOfContours=  getContoursRectangles( contours, delta, threshold, size);
    list<Rect>::iterator iter = rectsOfContours.begin();
    //paints the rectangles in a matrix named mask
    while(iter != rectsOfContours.end()){
        Rect current = (Rect)*iter;
        rectangle(mask, current.tl(), current.br(),  CV_RGB(255, 255, 255), 3);
        iter++;
    }
    //executes the find contours routine again to find the connected contours
    cv::findContours(mask, contoursOfRects,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    //processes the bounding rectangles of the new contours
    finalRects = getContoursRectangles( contoursOfRects, 0, 0, size);
    return finalRects;
}

ImageImPro* BackgroundSegmentatorAGMM::getBackgroundImage(){

}


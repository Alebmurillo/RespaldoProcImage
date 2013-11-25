#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace std;
using namespace cv;
/*
list<cv::Rect> getContoursRectangles(std::vector<std::vector<cv::Point> > contours, int delta, int threshold, cv::Mat::MSize size){
    int index;
    int contours_index;

    int currentsize= 0;
    std::list<Rect> finalcontours;
    //finalcontours.resize(contours.size());
    for (index = 0;index<contours.size();index++)
    {
        if (contours[index].size()>threshold)
        {
            int y_max=0;
            int y_min=size[0];
            int x_max=0;
            int x_min=size[1];

            for(contours_index=0;contours_index<contours[index].size();contours_index++)
            {
                if(contours[index][contours_index].y > y_max) y_max=contours[index][contours_index].y;
                if(contours[index][contours_index].x > x_max) x_max=contours[index][contours_index].x;
                if(contours[index][contours_index].y < y_min) y_min=contours[index][contours_index].y;
                if(contours[index][contours_index].x < x_min) x_min=contours[index][contours_index].x;
            }
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
            //finalcontours.resize(curr);
          //  currentsize++;
        }
    }
   // cout << currentsize << endl;
    //until here we got bigger rectangles
    return finalcontours;
}

list<cv::Rect> getTrackingCandidates(std::vector<std::vector<cv::Point> > contours, int delta, int threshold, cv::Mat::MSize size){
    std::vector<std::vector<cv::Point> > contoursOfRects;
    list<cv::Rect> finalRects;
    Mat mask =  cv::Mat::zeros(size[0], size[1], CV_8U);
    list<cv::Rect> rectsOfContours=  getContoursRectangles( contours, delta, threshold, size);
    cout << "getTrackingCandidates::rectsOfContours: " << rectsOfContours.size() << endl;
    cout << "getTrackingCandidates::CONTOURS: " << contours.size() << endl;
    cout << "getTrackingCandidates::Size x: " << size[0]<< " size y " << size[1] << endl;
    list<Rect>::iterator iter = rectsOfContours.begin();
    while(iter != rectsOfContours.end()){
        Rect current = (Rect)*iter;
        rectangle(mask, current.tl(), current.br(),  CV_RGB(255, 255, 255), 3);
        iter++;
    }
    cv::findContours(mask, contoursOfRects,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    finalRects = getContoursRectangles( contoursOfRects, 0, 0, size);
    return finalRects;
}

int main(int argc, char *argv[]){
    cv::Mat frame;
    cv::Mat back;
    cv::Mat fore;
    cv::VideoCapture cap("../input/videos/piso.mp4");
    cv::BackgroundSubtractorMOG2 bg(100, 32, true);
    bg.set("nmixtures", 3);
    std::vector<std::vector<cv::Point> > contours;
    int dilation_type= cv::MORPH_RECT;
    int dilation_size = 0;
    cv::Mat element = cv::getStructuringElement( dilation_type,
                                         cv::Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                         cv::Point( dilation_size, dilation_size ) );
    cv::namedWindow("Frame");
    for(;;){
        cap >> frame;
        bg.operator ()(frame,fore,0.000001);
        bg.getBackgroundImage(back);
        cv::erode(fore,fore,element);
        cv::dilate(fore,fore,element);
        cv::findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);
        int delta = 10;
        int threshold = 220;

        list<cv::Rect> found= getTrackingCandidates(contours, delta, threshold, frame.size);
        cv::Mat croppedImage;
        list<Rect>::iterator iter = found.begin();
        while(iter != found.end()){
            Rect current =  (Rect)*iter;
            //croppedImage = frame(current);
            //cv::imshow("Frame",croppedImage);
            if(cv::waitKey(30) >= 0) break;
            rectangle(frame, current.tl(), current.br(),  CV_RGB(0, 255, 0), 1);
            iter++;
        }
       // cv::imshow("Frame",fore);
       // if(cv::waitKey(30) >= 0) break;
        std::cout<<"Found elements: "<< found.size() << endl;
    }
    return 0;
}


*/
#include <QApplication>
#include "mainwindow.h"




int main(int argc, char *argv[]){
   // UnitTestsOCV_OCL::testOCV_OCL_2();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    //return 0;
}

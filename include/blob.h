#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>


#ifndef BLOB_H


typedef struct{
    float velX;
    float velY;
    float velZ;
} linV_t;

typedef struct {
    float divergence;
    float curl;
}vectorField_t;


class OpticalFlow {
    public:
        OpticalFlow(cv::VideoCapture cap);
        void initFeatures(cv::Mat& old_frame, cv::Mat& old_gray, cv::Mat& mask);
        int calcFlow(cv::Mat& old_gray, cv::Mat& mask);
        int calcDivCurl();
        // void calcCurl();
    private:
        cv::VideoCapture cap;
        std::vector<cv::Point2f> p0, p1;
        cv::Mat vel;
        std::vector<cv::Point2f> dp;
        double meanDiv;
        double meanCurl;


};


#endif
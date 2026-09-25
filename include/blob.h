#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <mavlink/common/mavlink.h>


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
        void initVideo();
        void opticalFlow();
    private:
        cv::VideoCapture cap_;
        cv::Mat vel_;
        
};


#endif
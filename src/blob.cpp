#include <iostream>
#include "../include/blob.h"

using namespace cv;
using namespace std;


OpticalFlow::OpticalFlow(
        cv::VideoCapture cap
    ){
        this->cap = cap;
        cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    }

void OpticalFlow::initFeatures(cv::Mat& old_frame, cv::Mat& old_gray, cv::Mat& mask){
    cap >> old_frame;
    cvtColor(old_frame, old_gray, COLOR_BGR2GRAY);
    goodFeaturesToTrack(old_gray, p0, 150, 0.03, 4, Mat(), 3, false, 0.04);
 
    // Create a mask image for drawing purposes
    mask = Mat::zeros(old_frame.size(), old_frame.type());
}

int OpticalFlow::calcFlow(cv::Mat& old_gray, cv::Mat& mask){
    
    Mat frame, frame_gray;
        cap >> frame;
        if (frame.empty())
            return EXIT_FAILURE;
        cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
        // calculate optical flow
        vector<uchar> status;
        vector<float> err;
        TermCriteria criteria = TermCriteria((TermCriteria::COUNT) + (TermCriteria::EPS), 10, 0.03);
        calcOpticalFlowPyrLK(old_gray, frame_gray, p0, p1, status, err, Size(15,15), 2, criteria);
        vector<cv::Point2f> good_new;
        // vector<cv::Point2f> dp;

        Mat img;
        add(frame, mask, img);

        for(uint i = 0; i < p0.size(); i++)
        {
            // Select good points
            if(status[i] == 1) {
                good_new.push_back(p1.at(i));
                // draw the tracks
                dp.push_back(p1.at(i) - p0.at(i));
                
                circle(img, p0[i], 5, Scalar(0,0,255), -1);
                circle(img, p1[i], 5, Scalar(0,255,0), -1);
            }
            // std::cout << dp.at(i) << std::endl;
        }

        calcDivCurl();
        // calcCurl();
        
        
        imshow("Frame", img);
        int keyboard = waitKey(30);
        if (keyboard == 'q' || keyboard == 27)
            return EXIT_FAILURE;
        // Now update the previous frame and previous points
        old_gray = frame_gray.clone();
        p0 = good_new;

    return 0;
}

int OpticalFlow::calcDivCurl(){
    cv::Mat flow(dp);
    std::cout << dp.back() << std::endl;
    if (dp.empty()) {
    std::cerr << "Error: Input flow matrix 'dp' is empty!" << std::endl;
    return EXIT_FAILURE; // or handle error accordingly
    }

    cv::Mat ch[2];
    cv::split(flow, ch);                                    // ch[0] = Vx, ch[1] = Vy

    cv::Mat dVx_dx, dVy_dy, dVy_dx, dVx_dy;

    cv::Sobel(ch[0], dVx_dx, CV_32F, 1, 0, 1, 0.5);         // ksize=1 → [-1 0 1], scale 0.5
    cv::Sobel(ch[1], dVy_dy, CV_32F, 0, 1, 1, 0.5);
    cv::Sobel(ch[1], dVy_dx, CV_32F, 1, 0, 1, 0.5);
    cv::Sobel(ch[0], dVx_dy, CV_32F, 0, 1, 1, 0.5);

    cv::Mat div  = dVx_dx + dVy_dy;
    cv::Mat curl = dVy_dx - dVx_dy;

    meanDiv = cv::mean(div)[0];
    meanCurl = cv::mean(curl)[0];

    std::cout<< "Average Divergance: "<< meanDiv << std::endl;
    std::cout<< "Average Curl: "<< meanCurl << std::endl;


    return EXIT_SUCCESS;
}

    


// int main(int argc, char **argv)
// {



//     VideoCapture capture(0);
//     if (!capture.isOpened()){
//         //error in opening the video input
//         cerr << "Unable to open file!" << endl;
//         return 0;
//     }

//     OpticalFlow flow(capture);
//     std::cout << "Class initiated" << std::endl;

//     Mat oldGray, oldFrame, mask;

//     flow.initFeatures(oldFrame, oldGray, mask);
//     std::cout<<"Features Initialized"<<endl;

//     while(true){
//         flow.calcFlow(oldGray, mask);
//     }


    // Create some random colors
    // vector<Scalar> colors;
    // RNG rng;
    // for(int i = 0; i < 100; i++)
    // {
    //     int r = rng.uniform(0, 256);
    //     int g = rng.uniform(0, 256);
    //     int b = rng.uniform(0, 256);
    //     colors.push_back(Scalar(r,g,b));
    // }
    // Mat old_frame, old_gray;
    // vector<Point2f> p0, p1;
    // // Take first frame and find corners in it
    // capture >> old_frame;
    // cvtColor(old_frame, old_gray, COLOR_BGR2GRAY);
    // goodFeaturesToTrack(old_gray, p0, 100, 0.3, 7, Mat(), 7, false, 0.04);
    // // Create a mask image for drawing purposes
    // Mat mask = Mat::zeros(old_frame.size(), old_frame.type());
    // while(true){
        
    // }

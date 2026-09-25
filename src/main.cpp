#include "../include/mav.h"
#include "../include/blob.h"
// #include <c_uart_interface_example/serial_port.h>


int main(void){
    // Serial_Port port("/dev/ttyS0", 921600);
    // Autopilot_Interface horus(&port);
    // horus.read_messages();

    cv::VideoCapture capture(0);
    if (!capture.isOpened()){
        //error in opening the video input
        std::cerr << "Unable to open file!" << std::endl;
        return 0;
    }

    OpticalFlow flow(capture);

    cv::Mat oldFrame, oldGray, mask;

    flow.initFeatures(oldFrame, oldGray, mask);
    std::cout << "Features collected" <<std::endl;

    while(true){
        flow.calcFlow(oldGray, mask);
    }

}
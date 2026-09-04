#include <mavlink/common/mavlink.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

int openSerial(std::string path, int baudrate);

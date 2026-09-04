#include "../include/mav.h"


int openSerial(std::string path, int baudrate){
    
    struct termios tty;
    int fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);

    if (fd == -1){
        std::cout  << "Failed to open serial port" <<std::endl;;
        return -1;
    }
    if(tcgetattr(fd, &tty) < 0)
    {
        return -1;
    }

    cfsetospeed(&tty, (speed_t)baudrate);
    cfsetispeed(&tty, (speed_t)baudrate);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~PARENB;
    tty.c_cflag |= CSTOPB;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;
    if(tcsetattr(fd, TCSANOW, &tty))
    {
        return -1;
    }

    return fd;
}

int main(void){
    std::string port = "/dev/ttyS0";
    int baudrate = 921600;
    int serfd = openSerial(port, baudrate);
    if (serfd < 0){
        return EXIT_FAILURE;
    }else{
        std::cout<<"connection success"<<std::endl;;
    }


}
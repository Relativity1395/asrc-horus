#include "../include/mav.h"
#include "../include/blob.h"
// #include <c_uart_interface_example/serial_port.h>


int main(void){
    Serial_Port port("/dev/ttyS0", 921600);
    Autopilot_Interface horus(&port);

    horus.read_messages();
}
#ifndef SIM_ON
#include "main.h"

#include "lwip.h"
#endif
#include<iostream>
#include "ST-LIB.hpp"

int main(void) {
    int id = FDCAN::inscribe(FDCAN::fdcan1); 
    //STLIB::start();
    std::cout << "id" <<id<< endl;
    //std::string data = "Hello2";
    //FDCAN::transmit(id, 0x123, data.c_str(), FDCAN::DLC::BYTES_16);
    while (1) {
        /*FDCAN::Packet packet;
        FDCAN::read(id, &packet);
        std::cout << packet.rx_data.data() << endl;
        std::cout << packet.identifier << endl;
        std::cout << packet.data_length << endl;
        */
        //STLIB::update();
    }
}

void Error_Handler(void) {
    ErrorHandler("HAL error handler triggered");
    while (1) {
    }
}
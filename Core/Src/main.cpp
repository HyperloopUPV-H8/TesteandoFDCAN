#ifndef SIM_ON
#include "main.h"

#include "lwip.h"
#endif
#include<iostream>
#include "ST-LIB.hpp"

int main(void) {
    SharedMemory::start("sim_tests","state_machine__tests");
    int id = FDCAN::inscribe(FDCAN::fdcan1); 
    STLIB::start();
    std::string data = "Hello2";
   
    while (1) {
        bool test = FDCAN::transmit(id, 0x123, data.c_str(), FDCAN::DLC::BYTES_16);
        std::cout << test << endl;
        
        /*FDCAN::Packet packet;
        FDCAN::read(id, &packet);
        std::cout << packet.rx_data.data() << endl;
        std::cout << packet.identifier << endl;
        std::cout << packet.data_length << endl;
        */
        std::this_thread::sleep_for(std::chrono::seconds(1));
        STLIB::update();
    }
}

void Error_Handler(void) {
    ErrorHandler("HAL error handler triggered");
    while (1) {
    }
}
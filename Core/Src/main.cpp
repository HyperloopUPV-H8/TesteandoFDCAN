#ifndef SIM_ON
#include "main.h"

#include "lwip.h"
#endif
#include<iostream>
#include <thread>
#include "ST-LIB.hpp"



/*void r_thread(int id) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    while (1) {
        FDCAN::Packet packet;
        std::cout << "Reading data" << endl;
        bool test = FDCAN::read(id, &packet);
        std::cout << "data read" << endl;
        if (test) {
            std::cout << "Received data: " << packet.rx_data.data() << endl;
            std::cout << "Identifier: " << packet.identifier << endl;
            std::cout << "Data length: " << packet.data_length << endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
    }
}
*/
int main(void) {
    SharedMemory::start("gpio__blinking_led","state_machine__blinking_led");
    int id = FDCAN::inscribe(FDCAN::fdcan1); 
    STLIB::start();
    //std::string data = "Hello2";
    //std::thread read_thread(r_thread,id);
    while (1) {
        //bool test = FDCAN::transmit(id, 1, data.c_str(), FDCAN::DLC::BYTES_6);
        //std::cout <<endl<< test << endl;
        
        FDCAN::Packet packet;
        //bool test = FDCAN::read(id, &packet);
        FDCAN::read(id, &packet);
        for(uint8_t i = 0; i < packet.data_length; i++){
            std::cout << /*uint16_t*/(packet.rx_data[i])<< " ";
        }
        
        std::cout <<endl<<  packet.identifier << endl;
        std::cout << packet.data_length << endl;
        //std::cout<<endl<<test<<endl;
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
        STLIB::update();
    }
    //read_thread.join();
}

void Error_Handler(void) {
    ErrorHandler("HAL error handler triggered");
    while (1) {
    }
}
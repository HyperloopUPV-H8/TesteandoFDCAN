#ifndef SIM_ON
#include "main.h"

#include "lwip.h"
#endif
#include<iostream>
#include <thread>
#include "ST-LIB.hpp"


int main1(){
#ifdef SIM_ON
    SharedMemory::start("gpio__blinking_led","state_machine__blinking_led");
#endif
    int id = FDCAN::inscribe(FDCAN::fdcan1); 
    std::string data = "Hello2";
    STLIB::start();
    Time::register_low_precision_alarm(500,[&](){
        FDCAN::transmit(id, 1, data.c_str(), FDCAN::DLC::BYTES_6);
    });
    FDCAN::Packet packet;
    Time::register_low_precision_alarm(500,[&](){
        FDCAN::read(id, &packet);
    });
    while(1){
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        STLIB::update();
    }
    }



int main2(){
#ifdef SIM_ON
    SharedMemory::start("gpio__blinking_led","state_machine__blinking_led");
#endif
    enum state_id{
        connecting =0,
        operational =1,
    };
    PinState led_state = PinState::OFF;
    uint8_t id = DigitalInput::inscribe(PA1);
    STLIB::start();
    StateMachine state_machine(connecting);
    state_machine.add_state(operational);
    state_machine.add_transition(connecting, operational, [&](){
        return led_state;

    });
    state_machine.add_low_precision_cyclic_action([&](){
        led_state = DigitalInput::read_pin_state(id);
    }, std::chrono::milliseconds(1000), {connnecting, operational});
    while(1){
        STLIB::update();
        state_machine.check_transitions();
        
    }
    }
int main(){
    main1();
    //main2();
}


void Error_Handler(void) {
    ErrorHandler("HAL error handler triggered");
    while (1) {
    }
}
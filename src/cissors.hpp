#include <iostream>
#include <thread>
#include "serialib.h"

bool serial_ready = false;
unsigned short serial_time;
serialib serial_connection;
std::string serial_port;
std::thread serial_thread;
bool serial_modified = true;
unsigned char cissorPos = 0;
unsigned char cissorForce = 0;
double cissorMovement = 0;

void setForce(double amount)
{
    cissorForce = amount;
    serial_modified = true;
    return;
}

double getMovement()
{
    return cissorMovement;
}

double getAngle()
{
    return cissorPos;
}

void serial_startConnection()
{
    serial_ready = false;
    while (serial_connection.openDevice(serial_port.c_str(), 9600) != 1);
    serial_ready = true;
    while (serial_ready)
    {
        if (serial_modified)
        {
            serial_modified = false;
            serial_connection.writeBytes(&cissorForce, 1);
        }
        unsigned char state = 0;
        serial_connection.readBytes(&state, 1, 5, 0);
        if (state <= 174)
        {
            double res = (state - 87) / 87.0;
            cissorMovement = (res == -1) ? cissorMovement : res;
        } else cissorPos = state - 176;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void serial_start(std::string p) {
    serial_port = p;
    serial_time = 0;
    serial_thread = std::thread(serial_startConnection);
}
void serial_stop() {
    serial_ready = false;
    serial_thread.join();
    serial_connection.closeDevice();
}
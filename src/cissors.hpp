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

void setForce(double amount)
{
    cissorForce = amount;
    serial_modified = true;
    return;
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
        serial_connection.readBytes(&cissorPos, 1, 25, 0);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
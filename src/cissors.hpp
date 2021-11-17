#include <iostream>

void setForce(double amount)
{
    std::cout << "Setting cissors force to " << amount << std::endl;
    return;
}

double getAngle()
{
    double val = 62.1;
    std::cout << "Sending cissors angle (" << val << ")" << std::endl;
    return val;
}
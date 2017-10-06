#include <string>
#include <sstream>
#include "Robot.h"
#include "serialib.h"

using namespace std;

Robot::Robot()
{
    port.Open(SERIAL_PORT, SERIAL_BAUDRATE);
    sleep(4);
}

void Robot::sendOrder(char c)
{
    cout << "c= " << c << endl;
    port.WriteChar(c);
}




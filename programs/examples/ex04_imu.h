#include "mbed.h"
#include "crazyflie.h"
#include "USBSerial.h"

// Define serial object
USBSerial serial;

// Define IMU sensor object
MPU9250 imu(IMU_SDA,IMU_SCL);

// Main program
int main() 
{
    // Initialize IMU sensor object
    imu.init();
    // Print IMU readings every 0.1s
    while(1)
    {
        imu.read();
        serial.printf("Gyro   [rad/s]: %6.2f %6.2f %6.2f   |   ", imu.gx, imu.gy, imu.gz);
        serial.printf("Accel  [m/s^2]: %6.2f %6.2f %6.2f \n", imu.ax, imu.ay, imu.az);
        wait(0.1);
    }
}
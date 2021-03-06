#ifndef mpu9250_h
#define mpu9250_h
 
#include "mbed.h"
 
// Device I2C bus address (shift 1 bit left because mbed utilizes 8-bit addresses and not 7-bit)
#define MPU9250_ADDRESS 0b1101001 << 1

// Device identity register address
#define WHO_AM_I        0x75
// Auxiliary I2C configuration register address
#define INT_PIN_CFG     0x37

// Accelerometer configuration registers addresses
#define ACC_CONFIG_1    0x1C
#define ACC_CONFIG_2    0x1D
// Accelerometer data register addresses
#define ACC_XOUT_H      0x3B
#define ACC_XOUT_L      0x3C
#define ACC_YOUT_H      0x3D
#define ACC_YOUT_L      0x3E
#define ACC_ZOUT_H      0x3F
#define ACC_ZOUT_L      0x40
 
// Gyroscope configuration registers addresses
#define GYR_CONFIG      0x1B
// Accelerometer data register addresses
#define GYR_XOUT_H      0x43
#define GYR_XOUT_L      0x44
#define GYR_YOUT_H      0x45
#define GYR_YOUT_L      0x46
#define GYR_ZOUT_H      0x47
#define GYR_ZOUT_L      0x48
 
// Accelerometer full-scale ranges
enum acc_range
{
    ACC_RANGE_2G = 0b00, 
    ACC_RANGE_4G = 0b01,
    ACC_RANGE_8G = 0b10, 
    ACC_RANGE_16G = 0b11 
};
 
// Gyroscope full-scale ranges
enum gyr_range
{
    GYR_RANGE_250DPS = 0b00,   
    GYR_RANGE_500DPS = 0b01,  
    GYR_RANGE_1000DPS = 0b10,  
    GYR_RANGE_2000DPS = 0b11 
};
 
// MPU9250 (IMU sensor) class
class MPU9250
{
    public:
        // Class constructor
        MPU9250(PinName sda, PinName scl);
        // Initialize sensor
        bool init();
        // Read accelerometer and gyroscope data
        void read();
        // Accelerometer data in x, y and z axis [m/s^2]
        float ax, ay, az;
        // Gyroscope data in x, y and z axis [rad/s]
        float gx, gy, gz;
    private:    
        // Setup accelerometer configurations (full-scale range)
        void init_acc(acc_range a_range = ACC_RANGE_16G);
        // Setup gyroscope  configurations (full-scale range)
        void init_gyr(gyr_range g_range = GYR_RANGE_2000DPS);
        // Read accelerometer data
        void read_acc();
        // Read gyroscope data
        void read_gyr();          
        // Accelerometer resolution [m/s^2 / bit]
        float a_res;
        // Gyroscope resolution [rad/s / bit]
        float g_res;
        // I2C bus
        I2C i2c;    
        // Read data from register on given I2C bus address
        uint8_t read_reg(uint8_t add, uint8_t reg);  
        // Write data into register on given I2C bus address
        void write_reg(uint8_t add, uint8_t reg, uint8_t data);
};
 
#endif
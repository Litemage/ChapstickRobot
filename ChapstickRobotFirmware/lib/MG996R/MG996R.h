/*
    Wrapper for MG996R Servos, to enforce both using the ESP32Servo library to interact with the devices PWM properly
    as well as setting correct values for the max and min duty cycle of these particular servos.

    These servos run off of a duty cycle range of [500, 2500] microseconds
*/

#pragma once

#include <Arduino.h>
#include <ESP32Servo.h>

class MG996R{
    public:
        MG996R() = delete;
        /// @brief Construct a new MG996R servo
        /// @param pin The PWM pin to attach to servo
        MG996R(int pin);

        /// @brief Write position to motor
        /*
            If value is less than minimum pulse width (500) this will be treated as an angle in degrees
            If value is above minimum pulse width, it is treated as a value in microseconds
            See ESP32Servo.cpp for more details
        */
        /// @param value Value in degrees or microseconds
        void write(int value);
    private:
        Servo m_servo; ///> The servo object
};
/*
    This defines a custom library for the HW-095 motor driver module based off of the 
    L298N IC. Should work with most ESP32 based development board
*/

#pragma once

#include <Arduino.h>

/// @brief Holds information about generic dc motor
struct Motor {
    bool inverted = false;
};

/// @brief Describes pins connected to HW-095 module
struct ControllerPins{
  u_int8_t en_a;
  u_int8_t in_1;
  u_int8_t in_2;

  u_int8_t in_3;
  u_int8_t in_4;
  u_int8_t en_b;
};

/// @brief Describes PWM settings used for controlling motor speed
struct L298N_PWMSettings{
    u_int8_t AChannel;
    u_int8_t BChannel;
    u_int32_t freq; // frequency is in HZ
    u_int32_t resolution; // Resolution is in bits
};

class HW_095_L298N{
    public:
        HW_095_L298N() = delete;

        /// @brief Constructs a HW-095 module object
        /// @param pins ControllerPins reference, containing pin definitions for controller
        /// @param pwmSettings Settings regarding PWM for motor control
        HW_095_L298N(const ControllerPins &pins, L298N_PWMSettings pwmSettings);

        Motor m_motorA; ///> Motor object attached to B channel
        Motor m_motorB; ///> Motor object attached to B channel

        /// @brief "Free running" motor stop, cuts motor power, and coasts to stop
        void CoastStop();
        /// @brief "Fast stop" of motors, as documented in the L298N datasheet
        void FastStop();
        /// @brief Drive the A channel at specified duty cycle
        /// @param speed A number in the range [0, PWM RESOLUTION], determines speed
        void DriveA(u_int8_t speed);
        /// @brief Drive the B channel at specified duty cycle
        /// @param speed A number in the range [0, PWM RESOLUTION], determines speed
        void DriveB(u_int8_t speed);
        /// @brief Same as DriveA, but in reverse
        /// @param speed A number in the range [0, PWM RESOLUTION], determines speed
        void ReverseDriveA(u_int8_t speed);
        /// @brief Same as DriveB, but in reverse
        /// @param speed A number in the range [0, PWM RESOLUTION], determines speed
        void ReverseDriveB(u_int8_t speed);
    private:
        ControllerPins m_pins; ///> Pins for communicating with HW-095 module based on the L298N motor driver
        L298N_PWMSettings m_pwmSettings; ///> Settings of the PWM channels that govern motor speed

};

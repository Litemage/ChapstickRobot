/*
    Contains constant values used throughout the application
*/

#pragma once

#include <WString.h>
#include <IPAddress.h>
#include "HW_095_L298N.h"
#include <vector>

/* ----------------------------- OTHER CONSTANTS ---------------------------- */

namespace Constants{
    namespace DriveConstants
    {
        constexpr ControllerPins controllerPins = ControllerPins{27, 32, 33, 25, 26, 14};
        constexpr double DefaultDriveSpeed = 0.5;
        constexpr double SlowDriveSpeed = 0.3;
    } // namespace Drivetrain

    namespace PWMSettings
    {
        // channel 0 for A
        // Channel 1 for B
        // 100hz frequency
        // 8-bit resolution
        constexpr L298N_PWMSettings controllerSettings = L298N_PWMSettings{2, 3, 100, 8};
        constexpr unsigned char clawChannel = 1;
        constexpr unsigned char elevatorChannel = 2;
    } // namespace PWMSettings


    namespace Claw
    {
        constexpr int pos_close = 500; // in micro seconds
        constexpr int pos_open = 1200; // in micro seconds
        constexpr int pin = 23;
    } // namespace Claw

    namespace Elevator
    {
        constexpr int pos_up = 1000; // in micro seconds
        constexpr int pos_down = 2000; // in micro seconds
        constexpr int pin = 19;
    } // namespace Elevator

    namespace MQTT
    {
        const String clientID = "CHAPSTICKROBOT"; // The clientID to connect with
        const IPAddress broker(127, 0, 0, 1); // IP address of MQTT broker
        const u_int16_t brokerPort = 1883; // Port the broker is running off of (1883 is default)
        const std::vector<String> topics{"CHAPSTER"}; // A vector of topics to subscribe to
    } // namespace MQTT

    namespace WIFI
    {
        const String ssid = "..."; // Fill in with SSID
        const String pass = "..."; // Fill in with Password
    } // namespace WIFI
}
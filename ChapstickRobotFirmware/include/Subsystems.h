/*
    Subsystems abstract the interaction with hardware, and allow easier interaction with robot
    Each critical part of the robot has it's own subsystem, i.e, drivetrain, claw, elevator.

    It should be noted that the corresponding source file for this header requires "Constants.h" to run,
    as critical position information is contained there
*/

#pragma once

#include <Arduino.h>
#include <Constants.h>
#include <MG996R.h>
#include "HW_095_L298N.h"

/* -------------------------- DRIVETRAIN SUBSYSTEM -------------------------- */

/// @brief Drivetrain subsystem
class Sub_DriveTrain{
    public:
        Sub_DriveTrain() = delete;
        Sub_DriveTrain(ControllerPins pins, L298N_PWMSettings pwmSettings);

        /// @brief Drives both tracks of drivetrain equally
        /// @param speed Percent motor output [-1, 1]
        void Drive(double speed);

        /// @brief Controls the drivetrain's motors
        /// @param leftSpeed Percent motor speed [-1, 1]
        /// @param rightSpeed Percent motor speed [-1, 1]
        void Drive(double leftSpeed, double rightSpeed);

        /*
        This function was experimental, and does not work fantastically, and if this robot is
        ever reproduced, it would have to be re-calculated, and even then this method of control
        is mediocre at it's best, and was only accurate up to about 40-50 cm
        */
        /// @brief Drive a distance (in cm) (BLOCKING)
        /// @param speed // Given from -1.0 to 1.0, negative speed represents reverse
        /// @param distance // Given in cm
        void DriveDistance(double speed, u_int32_t distance);

        /// @brief Drives at a set speed for a set time (BLOCKING)
        /// @param speed The speed to drive [-1, 1]
        /// @param timeDelay The delay before the drivetrain is stopped
        void DriveDelay(double speed, int32_t timeDelay);

        /// @brief Turns drivetrain CW, speed is -1 thru 1 inclusive, though the bounds [0, 1] is suggested
        /// @param speed 
        void TurnCW(double speed);

        /// @brief Turns drivetrain CCW
        /// @param speed [-1, 1] but [0, 1] is suggested
        void TurnCCW(double speed);

        /// @brief Stops the drivetrain, using the "fast stop" function from the controller
        void StopDrivetrain();

        /// @brief Stops the drivetrain using the "coast stop" function from the controller class
        void CoastStop();

        /// @brief Gets the motor time to run to get to 10cm given the speed and distance
        /// @param speed Percent speed [-1, 1] of drivetrain
        /// @param distance Distance to travel (cm) (effective to about 50cm depending on tuning)
        /// @return The time (in ms) to run motors to get to distance (cm) given speed (motor percent output)
        u_int32_t GetDistanceDelay(double speed, u_int32_t distance) const;
    private:
        HW_095_L298N m_controller; ///> L298N motor control module
};

/* --------------------------- ELEVATOR SUBSYSTEM --------------------------- */

/// @brief Elevator Subsystem
class Sub_Elevator{
    public:
        Sub_Elevator() = delete;
        /// @brief Constructs an elevator subsystem
        /// @param servoPin 
        Sub_Elevator(const int &servoPin);

        /// @brief Puts elevator to "up" position (BLOCKING)
        void ElevatorUp();

        /// @brief Moves elevator to "down" position (dependent on constants) (BLOCKING)
        void ElevatorDown();
        
        /// @brief Sets elevator either up or down
        /// @param position The position to set the elevator to. "true" is up, "false" is down
        void ElevatorSetPosition(bool position);

        /// @brief Non-Blocking call to set the elevator to the "up" position
        void Async_ElevatorUp();

        /// @brief Non-Blocking call to set the elevator to the "down" position
        void Async_ElevatorDown();

        /// @brief Non-Blocking, sets the elevator's position
        /// @param position The position to set the elevator to. "true" is up, "false" is down
        void Async_ElevatorSetPosition(bool position);
    private:
        MG996R m_servo; ///> Servo for elevator system
};

/* ----------------------------- CLAW SUBSYSTEM ----------------------------- */

/// @brief Claw Subsystem
class Sub_Claw{
    public:
        Sub_Claw() = delete;
        /// @brief Constructs a claw subsystem
        /// @param servoPin 
        Sub_Claw(const int &servoPin);

        /// @brief Opens the claw (BLOCKING)
        void ClawOpen();

        /// @brief Closes the claw (BLOCKING)
        void ClawClose();

        /// @brief Sets the position of the claw (BLOCKING)
        /// @param position The position to set the claw to. "true" is open, "false" is closed
        void ClawSetPosition(bool position);

        /// @brief Non-Blocking call to open the claw
        void Async_ClawOpen();

        /// @brief Non-Blocking call to close the claw
        void Async_ClawClose();

        /// @brief Non-Blocking call to set the claw's position
        /// @param position The position to set the claw to. "true" is open, "false" is closed1
        void Async_ClawSetPosition(bool position);
    private:
        MG996R m_servo; ///> Servo for claw system
};
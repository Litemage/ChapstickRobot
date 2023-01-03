/*
    Data classes that take in a ChapsterCommand, and then process it into a specific command with the data in the payload

    NOTE: future revisions of this software could include some better inheritance, these classes could be extensions of a base class
    because of the extreme similarities between all of them. This was not implemented here for time's sake, and was out of this project's intended scope.
    Adding this base class could also improve the functionality of the Commander class, as it's command processing could be more Object-Oriented
*/

#pragma once

#include <Arduino.h>
#include "ChapsterCommand.h"

/// @brief DriveDistance command data class
class DriveDistance{
    public:
        DriveDistance() = delete;
        /// @brief Constructs a new DriveDistance command
        /// @param cmd ChapsterCommand to parse command data from
        DriveDistance(const ChapsterCommand& cmd) : m_direction{DirectionFromCmd(cmd)}, m_distance{DistanceFromCmd(cmd)}{}

        /// @brief Exposes direction as read from command
        /// @return Direction to drive
        bool GetDirection(){
            return m_direction;
        }

        /// @brief Exposes the distance member
        /// @return distance (cm) for robot to travel
        u_int16_t GetDistance(){
            return m_distance;
        }

        /// @brief Dumps command details to serial
        void DumpCommand(){
            Serial.println("---Drive Distance Command Dump---");
            Serial.print("Distance: ");
            Serial.println((u_int8_t)GetDistance());
            Serial.print("Direction: ");
            Serial.println((u_int8_t)GetDirection());
            Serial.println("---------------------------------");
        }

    private:

        // Two static functions are used for getting information from message through constructor ONLY
        
        /// @brief Gets the distance to drive from a ChapsterCommand object
        /// @param cmd The ChapsterCommand object to parse data from
        /// @return Distance, in cm, to drive
        static u_int16_t DistanceFromCmd(const ChapsterCommand& cmd){
            u_int16_t distance;
            memcpy(&distance, cmd.GetPayload().cbegin().base() + 1, sizeof(distance));
            return distance;
        }

        /// @brief Gets the direction to drive from a ChapsterCommand object
        /// @param cmd The ChapsterCommand object to parse data from
        /// @return Direction (true=forward false=backward) to drive
        static u_int8_t DirectionFromCmd(const ChapsterCommand& cmd){
            u_int8_t direction;
            memcpy(&direction, cmd.GetPayload().begin().base(), sizeof(direction));
            return direction;
        }

        const u_int8_t m_direction; ///> Direction to drive
        const u_int16_t m_distance; ///> Distance to drive (cm)
};

/// @brief Data class for a SetSpeed command
class SetSpeed{
    public:
        SetSpeed() = delete;
        /// @brief Constructs a new SetSpeed command
        /// @param cmd ChapsterCommand object to parse data from
        SetSpeed(const ChapsterCommand& cmd) : m_direction{GetDirectionFromCmd(cmd)}, m_percentSpeed{GetSpeedFromCmd(cmd)}{}

        /// @brief Exposes drive direction member
        /// @return The direction to drive (true=forward false=backwards)
        bool GetDirection(){
            return m_direction;
        }

        /// @brief Exposes the drive speed member
        /// @return Percent motor output [-1, 1] to drive with
        double GetSpeed(){
            return m_percentSpeed;
        }

    private:

        /// @brief Gets the drive direction from a ChapsterCommand object
        /// @param cmd ChapsterCommand to parse data from
        /// @return Direction for drivetrain to drive (true=forward, false=backwards)
        static bool GetDirectionFromCmd(const ChapsterCommand& cmd){
            u_int8_t direction;
            memcpy(&direction, cmd.GetPayload().cbegin().base(), sizeof(direction));
            // return 1 by default if direction is ill-formed
            if(direction != 0 && direction != 1){
                return true;
            } else {
                return direction;
            }
        }

        /// @brief Gets the drive speed in percent motor output from a ChapsterCommand object
        /// @param cmd ChapsterCommand object to parse data from
        /// @return The percent motor output [-1, 1] to apply to drivetrain when executing command
        static double GetSpeedFromCmd(const ChapsterCommand& cmd){
            u_int8_t rawSpeed;
            memcpy(&rawSpeed, cmd.GetPayload().cbegin().base()+1, sizeof(rawSpeed));

            // Guard against invalid values
            if (rawSpeed > 100 || rawSpeed < 0){
                rawSpeed = 0;
            }

            return (double)(0.01 * rawSpeed);
        }

        bool m_direction; ///> Direction to drive (true=forward, false=backward)
        double m_percentSpeed; ///> Percent output of motors to drive with
};

/// @brief Data class for containing a SetTurn command
class SetTurn{
    public:
        SetTurn() = delete;
        /// @brief Constructs a new SetTurn command
        /// @param cmd ChapsterCommand object to parse data from
        SetTurn(const ChapsterCommand& cmd) : m_directon{GetDirectionFromCmd(cmd)}{}

        /// @brief Exposes the rotational drive direction
        /// @return The turn direction, either false for counter-clockwise or true for clockwise
        bool GetDirection(){
            return m_directon;
        }

    private:

        /// @brief Gets the direction to turn from a ChapsterCommand object
        /// @param cmd ChapsterCommand object to parse data from
        /// @return The direction of turning, either false for counter-clockwise or true for clockwise
        static bool GetDirectionFromCmd(const ChapsterCommand& cmd){
            u_int8_t direction;
            memcpy(&direction, cmd.GetPayload().cbegin().base(), sizeof(direction));
            return direction;
        }

        bool m_directon; ///> Direction of turning, either false for counter-clockwise or true for clockwise
};

/// @brief Data class for containing a ClawPosition command
class ClawPosition{
    public:
        ClawPosition() = delete;
        /// @brief construct a new ClawPosition command
        /// @param cmd The ChapsterCommand to parse data from
        ClawPosition(const ChapsterCommand& cmd) : m_posRequest{RequestedPosFromCommand(cmd)}{}

        /// @brief Exposes the position request member
        /// @return The requested position to move the claw to. false for close, true for open
        bool GetPositionRequest(){
            return m_posRequest;
        }

    private:

        /// @brief Gets the requested position for claw to move to from ChapsterCommand object
        /// @param cmd The ChapsterCommand object to parse data from
        /// @return The requested position of the claw, false for close, true for open
        static bool RequestedPosFromCommand(const ChapsterCommand& cmd){
            bool position;
            memcpy(&position, cmd.GetPayload().cbegin().base(), sizeof(position));
            return position;
        }

        bool m_posRequest; ///> Requested position of claw
};

/// @brief Data class for containing a ElevatorPosition class
class ElevatorPosition{
    public:
        ElevatorPosition() = delete;
        /// @brief Constructs a new ElevatorPosition command
        /// @param cmd The ChapsterCommand object to parse data from
        ElevatorPosition(const ChapsterCommand& cmd) : m_posRequest{RequestedPosFromCommand(cmd)}{}

        /// @brief Exposes the requested position member
        /// @return The requested position of the elevator either true for up, or false for down
        bool GetPositionRequest(){
            return m_posRequest;
        }

    private:

        /// @brief Gets the requested position from a ChapsterCommand object
        /// @param cmd The ChapsterCommand to parse data from
        /// @return The requested position of the elevator either true for up, or false for down
        bool RequestedPosFromCommand(const ChapsterCommand& cmd){
            bool position;
            memcpy(&position, cmd.GetPayload().begin().base(), sizeof(position));
            return position;
        }

        bool m_posRequest; ///> The requested position of the elevator either true for up, or false for down
};
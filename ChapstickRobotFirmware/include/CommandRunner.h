/*
    CommandRunner is responsible for executing commands received and passed as ChapsterCommands
    Thus far, the class only serves to run commands through the function "ProcessCommand"
*/

#pragma once

#include "Subsystems.h"
#include "ChapsterCommand.h"

class CommandRunner{
    public:
        CommandRunner() = delete;
        /// @brief Construct a new CommandRunner
        /// @param drivetrain Reference to drivetrain
        /// @param claw Reference to claw
        /// @param elevator Reference to elevator
        CommandRunner(Sub_DriveTrain& drivetrain, Sub_Claw& claw, Sub_Elevator& elevator);

        /// @brief Takes in command data, constructs the proper command, then runs it
        /// @param commandData ChapsterCommand object containing command data
        void ProcessCommand(const ChapsterCommand& commandData);

    private:
        Sub_DriveTrain& m_drivetrain; ///> Reference to drivetrain subsystem
        Sub_Claw& m_claw; ///> Reference to claw subsystem
        Sub_Elevator& m_elevator; ///> Reference to elevator subsystem
};
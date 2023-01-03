#include "CommandRunner.h"
#include "Commands.h"

typedef unsigned char u_char;

CommandRunner::CommandRunner(Sub_DriveTrain& drivetrain, Sub_Claw& claw, Sub_Elevator& elevator): m_drivetrain{drivetrain}, m_claw{claw}, m_elevator{elevator}{}

void CommandRunner::ProcessCommand(const ChapsterCommand& commandData){
    const u_int8_t headerID = commandData.GetHeaderID();

    switch (headerID)
    {
        case 10: // Drive distance command
            {
                Serial.println("[CommandRunner]> Received DriveDistance command. ID: 10 (0x0A)");
                // Construct a drive distance command
                DriveDistance driveDisCmd(commandData);
                //NOTE: Just use 0.4 speed right now for this command, as it is the most reliable
                double speed = Constants::DriveConstants::DefaultDriveSpeed;
                if (!driveDisCmd.GetDirection()){
                    speed*=-1;
                }
                m_drivetrain.DriveDistance(speed, driveDisCmd.GetDistance());
            }
            break;
        
        case 11:
            {
                Serial.println("<[CommandRunner]> Received SetSpeed command. ID: 11 (0x0B)");
                // Construct set speed
                SetSpeed setSpeedCmd(commandData);
                // Set the drivetrain speed based on the direction
                if (setSpeedCmd.GetSpeed() == 0){
                    m_drivetrain.StopDrivetrain();
                    break;
                }
                if (setSpeedCmd.GetDirection()){
                    m_drivetrain.Drive(setSpeedCmd.GetSpeed());
                } else {
                    m_drivetrain.Drive(-setSpeedCmd.GetSpeed());
                }
            }
            break;
        
        case 12:
            {
                Serial.println("<[CommandRunner]> Received SetTurn command. ID: 12 (0x0C)");
                // Construct set turn
                SetTurn setTurnCmd(commandData);
                if (setTurnCmd.GetDirection()){
                    m_drivetrain.TurnCW(0.8);
                } else {
                    m_drivetrain.TurnCCW(0.8);
                }
            }
            break;

        case 15:
            {
                Serial.println("[CommandRunner]> Received ClawPosition command.ID: 15 (0x0F)");
                // Construct command data
                ClawPosition clawPosCmd(commandData);
                // set the claw position based off of data
                m_claw.ClawSetPosition(clawPosCmd.GetPositionRequest());
            }
            break;

        case 16:
            {
                Serial.println("[CommandRunner]> Received ElevatorPosition command.ID: 16 (0x10)");
                // Construct elevator command data
                ElevatorPosition elevPositionCommand(commandData);
                // Set elevator pos to requested pos
                m_elevator.ElevatorSetPosition(elevPositionCommand.GetPositionRequest());
            }
            break;
        case 160: // Retrieve command
            {
                Serial.println("[CommandRunner]> Received Retrieve command.ID: 160 (0xA0)");
                m_claw.ClawOpen();
                m_elevator.ElevatorDown();
                m_drivetrain.DriveDelay(Constants::DriveConstants::DefaultDriveSpeed, 630);

                delay(500);

                // Slow drive
                m_drivetrain.DriveDelay(Constants::DriveConstants::SlowDriveSpeed, 700);

                // Grab the chap stick
                m_claw.ClawClose();
                m_elevator.ElevatorUp();

                // Drive back
                m_drivetrain.DriveDelay(-Constants::DriveConstants::DefaultDriveSpeed, 850);
            }
            break;
        case 161: // Place command
            {
                Serial.println("[CommandRunner]> Received PickUp command.ID: 161 (0xA1)");
                m_drivetrain.DriveDelay(Constants::DriveConstants::DefaultDriveSpeed, 900);
                m_elevator.ElevatorDown();
                delay(300);
                m_claw.ClawOpen();

                // Drive slowly back
                m_drivetrain.DriveDelay(-Constants::DriveConstants::SlowDriveSpeed, 800);

                // raise effectors
                m_claw.Async_ClawClose();
                m_elevator.Async_ElevatorUp();

                // Drive back
                m_drivetrain.DriveDelay(-Constants::DriveConstants::DefaultDriveSpeed, 650);
            }
            break;
    
        default:
            break;

    }
}
#include "Subsystems.h"

/* -------------------------- DRIVETRAIN SUBSYSTEM -------------------------- */

Sub_DriveTrain::Sub_DriveTrain(ControllerPins pins, L298N_PWMSettings pwmSettings) : m_controller{pins, pwmSettings}{

  // Construct controller to be used with drivetrain
  m_controller.CoastStop();
}


void Sub_DriveTrain::Drive(double speed){
  Drive(speed, speed);
}

void Sub_DriveTrain::Drive(double leftSpeed, double rightSpeed){

  // If out of bounds, just coast
  if ((leftSpeed < -1 || leftSpeed > 1) || (rightSpeed < -1 || rightSpeed > 1)){
    m_controller.CoastStop();
    return;
  }

  // Scale left duty cycle by left speed input
  int leftDuty = pow(2, Constants::PWMSettings::controllerSettings.resolution) - 1; 
  leftDuty *= leftSpeed; 

  // Scale right duty cycle by right speed input
  int rightDuty = pow(2, Constants::PWMSettings::controllerSettings.resolution) - 1; 
  rightDuty *= rightSpeed; 

  // Drive left motor
  if (leftSpeed == 0){
    m_controller.CoastStop();
  } else if (leftSpeed > 0){
    m_controller.DriveA((u_int8_t)abs(leftDuty));
  } else if (leftSpeed < 0){
    m_controller.ReverseDriveA((u_int8_t)abs(leftDuty));
  }

  // Drive right motor
  if (rightSpeed == 0){
    m_controller.CoastStop();
  } else if (rightSpeed > 0){
    m_controller.DriveB((u_int8_t)abs(rightDuty));
  } else if (rightSpeed < 0){
    m_controller.ReverseDriveB((u_int8_t)abs(rightDuty));
  }
}

void Sub_DriveTrain::DriveDistance(double speed, u_int32_t distance){
  Drive(speed);
  delay(GetDistanceDelay(speed, distance));
  StopDrivetrain();
}

void Sub_DriveTrain::DriveDelay(double speed, int32_t timeDelay){
  Drive(speed);
  delay(timeDelay);
  StopDrivetrain();
}

void Sub_DriveTrain::TurnCW(double speed){
  Drive(-speed, speed); // Because Channel A drives the right motor on robot, and B the left
}

void Sub_DriveTrain::TurnCCW(double speed){
  Drive(speed, -speed); // See CW for details
}

void Sub_DriveTrain::StopDrivetrain(){
  m_controller.FastStop();
}

void Sub_DriveTrain::CoastStop(){
  m_controller.CoastStop();
}

u_int32_t Sub_DriveTrain::GetDistanceDelay(double speed, u_int32_t distance) const{
  // Calculate delay for 30cm
  double cmDelay = (speed * -902.976 + 1338.99) / 30;
  // Make delay for given distance
  return (u_int32_t)((double)distance * cmDelay);
}

/* --------------------------- ELEVATOR SUBSYSTEM --------------------------- */

Sub_Elevator::Sub_Elevator(const int &servoPin) : m_servo(servoPin){}

void Sub_Elevator::ElevatorUp(){
  m_servo.write(Constants::Elevator::pos_up);
  delay(300);
}

void Sub_Elevator::ElevatorDown(){
  m_servo.write(Constants::Elevator::pos_down);
  delay(300);
}

void Sub_Elevator::ElevatorSetPosition(bool position){
  position ? ElevatorUp() : ElevatorDown();
}

void Sub_Elevator::Async_ElevatorUp(){
  m_servo.write(Constants::Elevator::pos_up);
}

void Sub_Elevator::Async_ElevatorDown(){
  m_servo.write(Constants::Elevator::pos_down);
}

void Sub_Elevator::Async_ElevatorSetPosition(bool position){
  position ? Async_ElevatorUp() : Async_ElevatorDown();
}

/* ----------------------------- CLAW SUBSYSTEM ----------------------------- */

Sub_Claw::Sub_Claw(const int &servoPin) : m_servo(servoPin){}

void Sub_Claw::ClawOpen(){
  m_servo.write(Constants::Claw::pos_open);
  delay(500);
}

void Sub_Claw::ClawClose(){
  m_servo.write(Constants::Claw::pos_close);
  delay(500);
}

void Sub_Claw::ClawSetPosition(bool position){
    position? ClawOpen() : ClawClose();
}

void Sub_Claw::Async_ClawOpen(){
  m_servo.write(Constants::Claw::pos_open);
}

void Sub_Claw::Async_ClawClose(){
  m_servo.write(Constants::Claw::pos_close);
}

void Sub_Claw::Async_ClawSetPosition(bool position){
  position ? Async_ClawOpen() : Async_ClawClose();
}
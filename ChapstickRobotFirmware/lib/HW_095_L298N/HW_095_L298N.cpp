#include "HW_095_L298N.h"

/* ------------------------- HW_095_L298N MEMBER FUNCTIONS ------------------------- */

HW_095_L298N::HW_095_L298N(const ControllerPins &pins, L298N_PWMSettings pwmSettings){
  m_pins = pins; 
  m_pwmSettings = pwmSettings;
  // Configure pins
  pinMode(pins.in_1, OUTPUT);
  pinMode(pins.in_2, OUTPUT);
  pinMode(pins.in_3, OUTPUT);
  pinMode(pins.in_4, OUTPUT);

  ledcSetup(m_pwmSettings.AChannel, m_pwmSettings.freq, m_pwmSettings.resolution);
  ledcSetup(m_pwmSettings.BChannel, m_pwmSettings.freq, m_pwmSettings.resolution);

  ledcAttachPin(m_pins.en_a, m_pwmSettings.AChannel);
  ledcAttachPin(m_pins.en_b, m_pwmSettings.BChannel);

}

void HW_095_L298N::DriveA(u_int8_t speed){
  if (m_motorA.inverted){
    digitalWrite(m_pins.in_1, LOW);
    digitalWrite(m_pins.in_2, HIGH);
  } else {
    digitalWrite(m_pins.in_1, HIGH);
    digitalWrite(m_pins.in_2, LOW);
  }

  ledcWrite(m_pwmSettings.AChannel, speed);
}

void HW_095_L298N::DriveB(u_int8_t speed){
  if (m_motorB.inverted){
    digitalWrite(m_pins.in_3, LOW);
    digitalWrite(m_pins.in_4, HIGH);
  } else {
    digitalWrite(m_pins.in_3, HIGH);
    digitalWrite(m_pins.in_4, LOW);
  }

  ledcWrite(m_pwmSettings.BChannel, speed);
}

void HW_095_L298N::ReverseDriveA(u_int8_t speed){
  if (m_motorA.inverted){
    digitalWrite(m_pins.in_1, HIGH);
    digitalWrite(m_pins.in_2, LOW);
  } else {
    digitalWrite(m_pins.in_1, LOW);
    digitalWrite(m_pins.in_2, HIGH);
  }

  ledcWrite(m_pwmSettings.AChannel, speed);
}

void HW_095_L298N::ReverseDriveB(u_int8_t speed){
  if (m_motorB.inverted){
    digitalWrite(m_pins.in_3, HIGH);
    digitalWrite(m_pins.in_4, LOW);
  } else {
    digitalWrite(m_pins.in_3, LOW);
    digitalWrite(m_pins.in_4, HIGH);
  }

  ledcWrite(m_pwmSettings.BChannel, speed);
}


void HW_095_L298N::CoastStop(){
  // Set enable pins low
  ledcWrite(m_pwmSettings.AChannel, 0);
  ledcWrite(m_pwmSettings.BChannel, 0);

  // Set h-bridge pins low
  digitalWrite(m_pins.in_1, LOW);
  digitalWrite(m_pins.in_2, LOW);
  digitalWrite(m_pins.in_3, LOW);
  digitalWrite(m_pins.in_4, LOW);
}

void HW_095_L298N::FastStop(){
  ledcWrite(m_pwmSettings.AChannel, m_pwmSettings.resolution);
  ledcWrite(m_pwmSettings.BChannel, m_pwmSettings.resolution);

  digitalWrite(m_pins.in_1, LOW);
  digitalWrite(m_pins.in_2, LOW);
  digitalWrite(m_pins.in_3, LOW);
  digitalWrite(m_pins.in_4, LOW);
}

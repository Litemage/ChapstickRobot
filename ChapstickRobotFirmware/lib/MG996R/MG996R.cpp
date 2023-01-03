#include <MG996R.h>

MG996R::MG996R(int pin){
  m_servo.attach(pin, 500, 2500);
}

void MG996R::write(int value){
  m_servo.write(value);
}

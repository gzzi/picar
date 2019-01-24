
#include <cstdint>
#include "motor.hpp"

Motor::~Motor()
{
  ApplyMode(OutMode::STOP);
}

Motor::Motor(unsigned pin_in1, unsigned pin_in2, unsigned pin_pwm):
  m_in1(pin_in1),
  m_in2(pin_in2),
  m_pwm(pin_pwm)
{
  m_in1.Init(GPIO::Direction::OUT);
  m_in2.Init(GPIO::Direction::OUT);
  m_pwm.Init();
  ApplyMode(OutMode::STOP);
}

void Motor::SetTork(int16_t tork)
{
  if(tork == 0) {
    ApplyMode(OutMode::OPEN);
  }
  else if(tork > 0) {
    ApplyMode(OutMode::CW);
    m_pwm.Write(tork*2);
  }
  else {
    ApplyMode(OutMode::CCW);
    if(tork == INT16_MIN)
      tork++;
    tork = -tork;
    m_pwm.Write(tork*2);
  }
}

void Motor::ApplyMode(OutMode mode)
{
  switch(mode)
  {
  case OutMode::STOP:
    m_in1.Write(false);
    m_in2.Write(false);
    m_pwm.Write(UINT16_MAX);
    break;

  case OutMode::OPEN:
    m_in1.Write(true);
    m_in2.Write(true);
    break;

  case OutMode::CW:
    m_in1.Write(true);
    m_in2.Write(false);
    break;

  case OutMode::CCW:
    m_in1.Write(false);
    m_in2.Write(true);
    break;
  }
}

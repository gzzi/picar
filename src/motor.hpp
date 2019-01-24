
#ifndef MOTOR_HPP
#define MOTOR_HPP

#include "gpio.hpp"
#include "pwm.hpp"

class Motor
{
private:
  GPIO m_in1;
  GPIO m_in2;
  PWM m_pwm;

  enum class OutMode
  {
    STOP,
    CW,
    CCW,
    OPEN
  };

  void ApplyMode(OutMode mode);

public:

  virtual ~Motor();

  Motor() = delete;
  Motor(Motor const&) = delete;
  Motor(Motor &&) = default;

  Motor(unsigned pin_in1, unsigned pin_in2, unsigned pin_wiring_pi_pwm);

  void SetTork(int16_t tork); // >0 CW, <0 CCW
};

#endif

#include <iostream>
#include <wiringPi.h>
#include <pwm.hpp>

PWM::PWM(unsigned wiringpi_pin_nbr) : m_number(wiringpi_pin_nbr)
{

}

PWM::~PWM()
{

}

bool PWM::Init()
{
  static bool wpi_setup = false;
  int ret;

  if(!wpi_setup) {
    
    ret = wiringPiSetup();
    if(ret == -1) {
      std::cerr << "Failed to init wiringPi" << std::endl;
      return false;
    }

    //pwmSetRange(1024);
    pwmSetClock(512);
    wpi_setup = true;
  }
  pinMode(m_number, PWM_OUTPUT);
}

void PWM::Write(uint16_t val)
{
  pwmWrite(m_number, val>>6);
}



#ifndef CAR_H
#define CAR_H

#include "motor.hpp"
#include <cstdint>

class Car
{
private:
  Motor & m_left;
  Motor & m_right;

  int16_t m_tork;
  int16_t m_direction_tork;

  void ApplyTork();
  
public:
  Car(Motor & left, Motor & right);

  void SetTork(int16_t tork);
  void SetDirection(int16_t direction);
};

#endif

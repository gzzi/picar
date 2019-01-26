
#include "car.hpp"
#include <limits>       // std::numeric_limits

template<typename Tout, typename Tin>
Tout saturate(Tin val) {
  return std::min(std::max(val, (Tin)std::numeric_limits<Tout>::min()), (Tin)std::numeric_limits<Tout>::max());
}

Car::Car(Motor & left, Motor & right)
  : m_left(left), m_right(right),
    m_tork(0), m_direction_tork(0)
{

}

void Car::ApplyTork()
{
  int32_t left_tork;
  int32_t right_tork;

  left_tork = m_tork;
  left_tork = -left_tork;
  left_tork -= m_direction_tork;
  left_tork = saturate<int16_t, int32_t>(left_tork);
  m_left.SetTork(left_tork);

  right_tork = m_tork;
  right_tork -= m_direction_tork;
  right_tork = saturate<int16_t, int32_t>(right_tork);
  m_right.SetTork(right_tork);
}

void Car::SetTork(int16_t tork)
{
  m_tork = tork;
  ApplyTork();
}

void Car::SetDirection(int16_t direction)
{
  m_direction_tork = direction;
  ApplyTork();
}
  
  
  

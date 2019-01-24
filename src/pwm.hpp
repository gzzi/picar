
#ifndef PWM_H
#define PWM_H

#include <cstdint>

class PWM
{
private:
  const unsigned m_number;

public:
  virtual ~PWM();

  PWM() = delete;
  PWM(PWM const&) = delete;
  PWM(PWM &&) = default;

  PWM(unsigned wiringpi_pin_nbr);
  bool Init();
  void Write(uint16_t val);
};

#endif

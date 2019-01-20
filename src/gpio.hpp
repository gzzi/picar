
#ifndef GPIO_HPP
#define GPIO_HPP

#include <string>
#include <fstream>

class GPIO
{
private:
  const unsigned m_number;
  std::string m_path;
  std::ofstream m_value;
  bool m_active_low;

  bool Unexport(bool force=false);

public:
  enum class Direction
  {
    IN,
    OUT
  };

  virtual ~GPIO();

  GPIO() = delete;
  GPIO(GPIO const&) = delete;
  GPIO(GPIO &&) = default;

  GPIO(unsigned bcm_pin_nbr);
  bool Init(Direction pin_dir, bool active_low=false);
  void Write(bool val);
};

#endif

#include <fstream>
#include <iostream>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "gpio.hpp"

GPIO::GPIO(unsigned bcm_pin_nbr): m_number(bcm_pin_nbr)
{
}

GPIO::~GPIO()
{
  Unexport();
}

bool GPIO::Init(Direction pin_dir, bool active_low)
{
  const char* pin_export_path = "/sys/class/gpio/export";
  std::ofstream pin_export(pin_export_path);

  Unexport(true);
  
  if(pin_export) {
    pin_export << m_number << std::endl;
  }
  if(pin_export.bad()) {
    std::cerr << "Error export: " << errno << " " << strerror(errno) << std::endl;
    return false;
  }

  m_path = "/sys/class/gpio/gpio";
  m_path += std::to_string(m_number);

  std::string dir_path(m_path);
  dir_path += "/direction";
  std::ofstream dir;

  do
  {
    dir.open(dir_path);
    usleep(1000); // because of bug github.com/raspberrypi/linux/issues/553
  } while(dir.fail());
  
  if(dir) {
    if(pin_dir == Direction::IN)
      dir << "in" << std::endl;
    else
      dir << "out" << std::endl;
  }
  if(dir.bad()) {
    std::cerr << "Error set dir: " << errno << " " << strerror(errno) << std::endl;
    return false;
  }

  std::string value_path(m_path);
  value_path += "/value";
  do
  {
    m_value.open(value_path);
    usleep(1000); // because of bug github.com/raspberrypi/linux/issues/553
  } while(m_value.fail());

  m_active_low = active_low;
  return true;
}

bool GPIO::Unexport(bool force)
{
  if(m_path.empty() && !force) {
    return false;
  }

  const char* pin_unexport_path = "/sys/class/gpio/unexport";
  std::ofstream pin_unexport(pin_unexport_path);

  m_value.close();
  
  if(pin_unexport) {
    pin_unexport << m_number << std::endl;
  }
  if(pin_unexport.bad() && !force) {
    std::cerr << "Error unexport: " << errno << " " << strerror(errno) << std::endl;
    return false;
  }
  return true;
}

void GPIO::Write(bool val)
{
  m_value << (val != m_active_low? "1" : "0") << std::endl;
  if(m_value.bad()) {
    std::cerr << "Error write: " << errno << " " << strerror(errno) << std::endl;
  }
}


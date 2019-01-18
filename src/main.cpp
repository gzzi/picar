
#include <iostream>
#include <unistd.h>
#include "joystick/joystick.hh"
#include "src/gpio.hpp"


int main(int argc, char** argv) {
  const char* js_path = "/dev/input/js0";
  Joystick joystick(js_path);
  if (!joystick.isFound())
  {
    std::cerr << "open " << js_path << " failed" << std::endl;
    exit(1);
  }

  GPIO led(10);
  if(!led.Init(GPIO::Direction::OUT, true))
  {
    std::cerr << "open led failed (root?)" << std::endl;
    exit(1);
  }

  while (true)
  {
    // Restrict rate
    usleep(1000);

    // Attempt to sample an event from the joystick
    JoystickEvent event;
    if (joystick.sample(&event))
    {
      if (event.isButton())
      {
        printf("Button %u is %s\n",
        event.number,
        event.value == 0 ? "up" : "down");

        if(event.number==12) { // triangle
          led.Write(event.value == 0);
        }
      }
      else if (event.isAxis())
      {
        //printf("Axis %u is at position %d\n", event.number, event.value);
      }
    }
  }
  return 0;
}


#include <iostream>
#include <unistd.h>
#include "joystick/joystick.hh"
#include "src/gpio.hpp"
#include "src/motor.hpp"

typedef enum
{
  UP = 0,
  DOWN = 1
}EVENT;

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

  GPIO standby(9);
  if(!standby.Init(GPIO::Direction::OUT, true))
  {
    std::cerr << "open led failed (root?)" << std::endl;
    exit(1);
  }
  standby.Write(false);

  Motor left(19, 26, 12);
  Motor right(6, 5, 13);

  bool exit_loop = false;
  do
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
        event.value == EVENT::UP ? "up" : "down");

        switch(event.number)
	{
	case 12: // triangle
	  led.Write(event.value == EVENT::UP);
	  break;

	case 13: // round
	  exit_loop = event.value;
	  break;

	case 9: // forward gachette
	case 4: // forward
	case 14: // cross
	  if(event.value == EVENT::UP) {
	    left.SetTork(0);
	    right.SetTork(0);
	  }
	  else {
	    left.SetTork(-1);
	    right.SetTork(1);
	  }
	  break;

	case 15: // square -> reverse
	  if(event.value == EVENT::UP) {
	    left.SetTork(0);
	    right.SetTork(0);
	  }
	  else {
	    left.SetTork(1);
	    right.SetTork(-1);
	  }
	  break;
	}
      }
      else if (event.isAxis())
      {
        //printf("Axis %u is at position %d\n", event.number, event.value);
      }
    }
  }while(! exit_loop );
  return 0;
}

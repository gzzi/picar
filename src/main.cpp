
#include <iostream>
#include <unistd.h>
#include "joystick/joystick.hh"
#include "src/gpio.hpp"
#include "src/car.hpp"

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

  Motor _left(26, 19, 26);
  Motor _right(6, 5, 23);
  Car car(_left, _right);

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

	//case 9: // forward gachette
        case 4: // forward
        case 14: // cross
          if(event.value == EVENT::UP) {
            car.SetTork(0);
          }
          else {
	    car.SetTork(INT16_MAX);
          }
          break;

        case 15: // square -> reverse
          if(event.value == EVENT::UP) {
            car.SetTork(0);
          }
          else {
            car.SetTork(INT16_MIN);
          }
          break;
        }
      }
      else if (event.isAxis())
      {
        //printf("Axis %u is at position %d\n", event.number, event.value);

	if(event.number==13) { // right gachette
	  printf("Axis %u is at position %d\n", event.number, event.value);
	  int16_t tork = event.value;

	  // convert from -32k..32k to 0..32k
	  tork >>= 1;
	  tork += INT16_MAX / 2;

	  car.SetTork(tork);
	}
	else if(event.number==0) {
	  car.SetDirection(event.value);
	}
      }
    }
  }while(! exit_loop );
  return 0;
}

cmake_minimum_required(VERSION 3.6)

project(picar)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable( picar

  joystick/joystick.cc

  src/main.cpp
  src/gpio.cpp
  src/pwm.cpp 
  src/motor.cpp
  src/car.cpp
)

target_include_directories( picar
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries( picar
  wiringPi
)

cmake_minimum_required(VERSION 3.5)

project(Sound-generator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("usr/include/ncursesw/")
include_directories("usr/include/SFML/")
link_directories("usr/lib/x86_64-linux-gnu")

add_executable(Sound-generator main.cpp sound_generator.h sound_generator.cpp run.h run.cpp encoder.cpp encoder.h packetsender.cpp packetsender.h ackreceiver.cpp ackreceiver.h)

target_link_libraries(Sound-generator libsfml-audio.so libsfml-system.so -lncurses)

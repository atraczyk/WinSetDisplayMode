cmake_minimum_required(VERSION 3.0)

project(ChangeResolution)

add_executable(ChangeResolution main.cpp)

target_link_libraries(ChangeResolution PRIVATE user32 gdi32)
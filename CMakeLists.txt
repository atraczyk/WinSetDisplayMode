cmake_minimum_required(VERSION 3.0)

project(WinSetDisplayMode)

add_executable(WinSetDisplayMode main.cpp)

target_link_libraries(WinSetDisplayMode PRIVATE user32 gdi32)
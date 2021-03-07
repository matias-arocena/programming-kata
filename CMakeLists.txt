cmake_minimum_required(VERSION 2.8.12)
project(ProgrammingKata)

add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(main ${CMAKE_BINARY_DIR}/../tests/main.cpp)
target_link_libraries(main ${CONAN_LIBS})

add_executable(computer-graphics-test 
  ${CMAKE_BINARY_DIR}/../tests/computer-graphics-test.cpp
  ${CMAKE_BINARY_DIR}/../computer-graphics/Vector.cpp
  ${CMAKE_BINARY_DIR}/../computer-graphics/Vector.h)

target_link_libraries(computer-graphics-test ${CONAN_LIBS})

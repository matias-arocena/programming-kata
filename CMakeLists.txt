cmake_minimum_required(VERSION 3.7)
project(ProgrammingKata)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(main ${CMAKE_BINARY_DIR}/../tests/main.cpp)
target_link_libraries(main ${CONAN_LIBS})

add_executable(computer-graphics-test 
  ${CMAKE_BINARY_DIR}/../tests/computer-graphics-test.cpp
  ${CMAKE_BINARY_DIR}/../computer-graphics/Vector.cpp
  ${CMAKE_BINARY_DIR}/../computer-graphics/Vector.h)

target_link_libraries(computer-graphics-test ${CONAN_LIBS})

set(SDL2_DIR ${CMAKE_BINARY_DIR}/../lib/SDL2-2.0.14)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(emptySDL 
  ${CMAKE_BINARY_DIR}/../computer-graphics/emptySDL.cpp)
target_link_libraries(emptySDL ${SDL2_LIBRARIES} ${CONAN_LIBS})

add_executable(firstPolygon 
  ${CMAKE_BINARY_DIR}/../computer-graphics/firstPolygon.cpp)
target_link_libraries(firstPolygon ${SDL2_LIBRARIES} ${CONAN_LIBS})

add_executable(colorPolygon 
  ${CMAKE_BINARY_DIR}/../computer-graphics/colorPolygon.cpp)
target_link_libraries(colorPolygon ${SDL2_LIBRARIES} ${CONAN_LIBS})

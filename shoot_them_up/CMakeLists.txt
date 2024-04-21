cmake_minimum_required(VERSION 3.29)

project("ShootThemUp")

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_executable(ShootThemUp ${SOURCES})

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2_image REQUIRED)

target_link_libraries(ShootThemUp PRIVATE SDL2::SDL2 SDL2_image)
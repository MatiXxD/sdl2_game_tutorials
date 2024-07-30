cmake_minimum_required(VERSION 3.16)
project("ShootThemUp")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)
add_executable(ShootThemUp 
    src/main.cpp
    src/game.cpp
    src/screen.cpp
    src/player.cpp
    src/bullet.cpp
    src/enemy.cpp
    src/game_utility.cpp
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

target_include_directories(ShootThemUp
    PUBLIC ${SDL2_INCLUDE_DIRS}
    PUBLIC ${SDL2IMAGE_INCLUDE_DIRS}
)

target_link_libraries(ShootThemUp PUBLIC ${SDL2_LIBRARIES} SDL2_image::SDL2_image)

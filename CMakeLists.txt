cmake_minimum_required(VERSION 3.16)

project(Pac_man LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt automatic tools
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt 6
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Recommended Qt setup
qt_standard_project_setup()

# Your executable
add_executable(Pac_man
        main.cpp
        Player.h
        Player.cpp
        Map.h
        map.cpp
        Collectible.h
        Collectible.cpp
        Game.h
        Game.cpp
        Enemy.h
        Enemy.cpp
        MovingEntity.h
        MovingEntity.cpp
)

# Link Qt libraries
target_link_libraries(Pac_man
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)
cmake_minimum_required(VERSION 3.16) # Qt needs at least this
project(Satlin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)   # Auto-generate meta-object code
set(CMAKE_AUTORCC ON)   # Auto-process .qrc resource files
set(CMAKE_AUTOUIC ON)   # Auto-process .ui files

# Find Qt6 Widgets module
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Add the executable
add_executable(Satlin
        main.cpp
        MasterWindow.cpp
        MasterWindow.h
        Constants.h
        # add more .cpp or .ui files here
)

# Link Qt6 Widgets library
target_link_libraries(Satlin Qt6::Widgets)

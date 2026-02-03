cmake_minimum_required(VERSION 3.16)
project(Satlin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable Qt's automatic features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find required Qt6 modules
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Explicitly list all source files
add_executable(Satlin
        main.cpp
        MasterWindow.cpp
        MasterWindow.h
        Constants.h
        ClipBoardUI.cpp
        ClipBoardUI.h
        ItemWidget.cpp
        ItemWidget.h
        EmojiGenerator.cpp
        EmojiGenerator.h
        EmojiBoardUI.cpp   # Fixed typo: previously 'EmojiBoardUI.cpp'
        EmojiBoardUI.h     # Fixed typo: previously 'EmojiBoardUI.h'
        TextManagerInterface.cpp
        TextManagerInterface.h
        ImageManagerInterface.cpp
        ImageManagerInterface.h
        EmojiWidget.cpp
        EmojiWidget.h
        TextEditor.cpp
        TextEditor.h
        IconManager.cpp
        IconManager.h
)

# Link against Qt modules
target_link_libraries(Satlin PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

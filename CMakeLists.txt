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

# Group source files by category
set(UI_SOURCES
        Ui/MasterWindow.cpp
        Ui/MasterWindow.h
        Ui/ClipBoardUI.cpp
        Ui/ClipBoardUI.h
        Ui/EmojiBoardUI.cpp
        Ui/EmojiBoardUI.h
        Ui/TextEditor.cpp
        Ui/TextEditor.h
)

set(WIDGET_SOURCES
        Widgets/ItemWidget.cpp
        Widgets/ItemWidget.h
        Widgets/EmojiWidget.cpp
        Widgets/EmojiWidget.h
)

set(MANAGER_SOURCES
        ManagerSources/TextManagerInterface.cpp
        ManagerSources/TextManagerInterface.h
        ManagerSources/ImageManagerInterface.cpp
        ManagerSources/ImageManagerInterface.h
        ManagerSources/IconManager.cpp
        ManagerSources/IconManager.h
)

set(UTIL_SOURCES
        Util/EmojiGenerator.cpp
        Util/EmojiGenerator.h
        Util/Constants.h
)

# Combine all sources
add_executable(Satlin
        main.cpp
        ${UI_SOURCES}
        ${WIDGET_SOURCES}
        ${MANAGER_SOURCES}
        ${UTIL_SOURCES}
        Resources/resources.qrc
)

# Link against Qt modules
target_link_libraries(Satlin PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

# Optional: Organize files in IDE (Visual Studio, Xcode, etc.)
source_group("UI" FILES ${UI_SOURCES})
source_group("Widgets" FILES ${WIDGET_SOURCES})
source_group("Managers" FILES ${MANAGER_SOURCES})
source_group("Utils" FILES ${UTIL_SOURCES})
source_group("Resources" FILES Resources/resources.qrc)
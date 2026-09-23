cmake_minimum_required(VERSION 3.16)
project(Satlin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Multimedia)
find_package(SQLite3 REQUIRED)

set(UI_SOURCES
        Ui/MasterWindow.cpp
        Ui/MasterWindow.h
        Ui/ClipBoardInterface.cpp
        Ui/ClipBoardInterface.h
        Ui/EmojiPanelInterface.cpp
        Ui/EmojiPanelInterface.h
        Ui/TextEditor.cpp
        Ui/TextEditor.h
)

set(WIDGET_SOURCES
        Widgets/ItemWidget.cpp
        Widgets/ItemWidget.h
        Widgets/EmojiWidget.cpp
        Widgets/EmojiWidget.h
        Widgets/ImageWidget.cpp
        Widgets/ImageWidget.h
        Widgets/AudioWidget.cpp
        Widgets/AudioWidget.h
        Widgets/AudioCard.cpp
        Widgets/AudioCard.h
        Widgets/TextWidget.cpp
        Widgets/TextWidget.h
)

set(MANAGER_SOURCES
        ManagerSources/TextManagerInterface.cpp
        ManagerSources/TextManagerInterface.h
        ManagerSources/ImageManagerInterface.cpp
        ManagerSources/ImageManagerInterface.h
        ManagerSources/IconManager.cpp
        ManagerSources/IconManager.h
        ManagerSources/AudioManagerInterface.cpp
        ManagerSources/AudioManagerInterface.h
        ManagerSources/ItemManagerInterface.cpp
        ManagerSources/ItemManagerInterface.h
)

set(UTIL_SOURCES
        Util/EmojiGenerator.cpp
        Util/EmojiGenerator.h
        Util/Constants.h
        Util/MimeDataAnalyzer.cpp
        Util/MimeDataAnalyzer.h
        Util/HashGenerator.cpp
        Util/HashGenerator.h
        Util/ItemRepository.cpp
        Util/ItemRepository.h
        Util/DataModels.h
        CustomWidgets/RegularButton.cpp
        CustomWidgets/RegularButton.h
        Util/ToolKit.h
        Util/DatabaseConnectivityCheckerThread.cpp
        Util/DatabaseConnectivityCheckerThread.h
)

add_executable(Satlin
        main.cpp
        ${UI_SOURCES}
        ${WIDGET_SOURCES}
        ${MANAGER_SOURCES}
        ${UTIL_SOURCES}
        Resources/resources.qrc
)

target_link_libraries(Satlin PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Multimedia
        SQLite::SQLite3
)

# Ensures include paths are correctly registered across all OS/package managers
target_include_directories(Satlin PRIVATE ${SQLite3_INCLUDE_DIRS})

source_group("UI" FILES ${UI_SOURCES})
source_group("Widgets" FILES ${WIDGET_SOURCES})
source_group("Managers" FILES ${MANAGER_SOURCES})
source_group("Utils" FILES ${UTIL_SOURCES})
source_group("Resources" FILES Resources/resources.qrc)
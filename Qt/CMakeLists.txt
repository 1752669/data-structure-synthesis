cmake_minimum_required(VERSION 3.8)
project(Hello)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH C:\\Qt\\Qt5.13.0\\5.13.0\\mingw73_64\\lib\\cmake) #这里需要填入自己安装的路径


find_package(Qt5Widgets)
find_package( Qt5Core)
find_package( Qt5Gui)

set(UI_FILES)

set(RC_FILES)

set(QRC_FILES)

set(SOURCE_FILES main.cpp)

add_executable(Hello  main.cpp random.h Game.h Circles.h MyCircle.h MainWindow.h)

target_link_libraries(Hello Qt5::Widgets)

qt5_use_modules(Hello Core Widgets Gui)
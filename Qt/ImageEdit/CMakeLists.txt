set(CMAKE_TOOLCHAIN_FILE "D:/lib/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CXX_FLAGS -m64)

cmake_minimum_required(VERSION 3.5)

project(ImageEdit LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenCV CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
add_executable(ImageEdit
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
)

target_link_libraries(ImageEdit PRIVATE Eigen3::Eigen)
target_link_libraries(ImageEdit PRIVATE numeric multiview opencv_sfm opencv_world)
target_link_libraries(ImageEdit PRIVATE Qt5::Widgets)

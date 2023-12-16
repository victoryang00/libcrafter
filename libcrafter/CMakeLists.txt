cmake_minimum_required(VERSION 3.22)
project(MVVM LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)


file(GLOB_RECURSE SOURCE_FILES crafter/*/*.cpp crafter/*.cpp)
add_library(crafter ${SOURCE_FILES})
include_directories(crafter crafter/Utils crafter/Protocols crafter/ProtoSource crafter/Fields)

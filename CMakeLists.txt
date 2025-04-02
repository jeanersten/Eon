cmake_minimum_required(VERSION 3.28)

project(Eon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_SHARED_LIBS OFF)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>/bin)

add_subdirectory(
  vendor/SFML
)

add_executable(Eon
  source/Main.cpp
  source/Game.cpp
  source/Entity.cpp
)

target_include_directories(Eon PRIVATE
  vendor/SFML/include
)

target_link_libraries(Eon PRIVATE
  sfml-system
  sfml-window
  sfml-graphics
)

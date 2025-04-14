cmake_minimum_required(VERSION 3.28)

project(Eon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_SHARED_LIBS ON)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/$<CONFIG>/bin")
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})


add_subdirectory(
  vendor/SFML
)

add_executable(Eon
  source/Utils.cpp
  source/Main.cpp
  source/Game.cpp
  source/Entity.cpp
  source/EntityManager.cpp
  source/Components.cpp
)

target_include_directories(Eon PRIVATE
  vendor/SFML/include
)

target_link_libraries(Eon PRIVATE
  SFML::System
  SFML::Window
  SFML::Graphics
)

foreach(SFML_LIB System Window Graphics)
  add_custom_command(TARGET Eon POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:SFML::${SFML_LIB}>"
    "$<TARGET_FILE_DIR:Eon>"
  )
endforeach()

add_custom_command(TARGET Eon POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  "${ASSETS_DIR}"
  "${OUTPUT_DIR}/assets"
)

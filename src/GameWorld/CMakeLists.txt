cmake_minimum_required(VERSION 3.16)

add_library(
  GameWorld
  STATIC
  GameWorld.hpp
  GameWorld.cpp
)

target_link_libraries(
  GameWorld
  Environments
  Plants
  Seeds
  Zombies
)

target_include_directories(
  GameWorld
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/Framework/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
  ${CMAKE_SOURCE_DIR}/src/GameObject/Environments
  ${CMAKE_SOURCE_DIR}/src/GameObject/Plants
  ${CMAKE_SOURCE_DIR}/src/GameObject/Seeds
  ${CMAKE_SOURCE_DIR}/src/GameObject/Zombies
)

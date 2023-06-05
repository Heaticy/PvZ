cmake_minimum_required(VERSION 3.16)

add_subdirectory(Environments)
add_subdirectory(Plants)
add_subdirectory(Seeds)
add_subdirectory(Zombies)
add_subdirectory(FlyingObject)
target_include_directories(Plants PUBLIC ../Framework)
target_link_libraries(Plants PUBLIC Framework GameWorld)
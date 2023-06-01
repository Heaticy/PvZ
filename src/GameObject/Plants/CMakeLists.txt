add_library(Plants SHARED Plants.hpp Plants.cpp)
target_include_directories(Plants PUBLIC ../../Framework ../../GameWorld)
target_link_libraries(Plants PUBLIC Framework Gameworld)
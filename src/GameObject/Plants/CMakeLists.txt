add_library(Plants STATIC Plants.hpp Plants.cpp)
target_include_directories(Plants PUBLIC ../../Framework ../../GameWorld ../FlyingObject)
target_link_libraries(Plants PUBLIC Framework GameWorld FlyingObject Environments)
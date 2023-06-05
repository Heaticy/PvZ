add_library(FlyingObject STATIC FlyingObject.hpp FlyingObject.cpp)
target_include_directories(FlyingObject PUBLIC ../../Framework ../../GameWorld)
target_link_libraries(FlyingObject PUBLIC Framework GameWorld)
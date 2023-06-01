add_library(Zombies SHARED Zombies.hpp Zombies.cpp)
target_include_directories(Zombies PUBLIC ../../Framework ../../GameWorld)
target_link_libraries(Zombies PUBLIC Framework)
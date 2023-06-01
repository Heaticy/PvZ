add_library(Environments STATIC Environments.hpp Environments.cpp)
target_include_directories(Environments PUBLIC ../../Framework ../../GameWorld)
target_link_libraries(Environments PUBLIC Framework GameWorld)
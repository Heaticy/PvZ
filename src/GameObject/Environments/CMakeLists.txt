add_library(Environments SHARED Environments.hpp Environments.cpp)
target_include_directories(Environments PUBLIC ../../Framework ../../GameWorld)
target_link_libraries(Environments PUBLIC Framework)
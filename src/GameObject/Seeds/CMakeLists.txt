add_library(Seeds STATIC Seeds.hpp Seeds.cpp)
target_include_directories(Seeds PUBLIC ../../Framework ../../GameWorld)
target_link_libraries(Seeds PUBLIC Framework GameWorld Plants)
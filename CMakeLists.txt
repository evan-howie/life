cmake_minimum_required(VERSION 3.0)
project(life)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# add libraries
include_directories(include)
add_library(grid src/grid.cpp)

set_target_properties(grid PROPERTIES
  CXX_STANDARD 11  # or 14, 17, 20 depending on your needs
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
)

# Include your source files
add_executable(life src/main.cpp)
add_executable(life_editor src/editor.cpp)

# Link SFML libraries
target_link_libraries(life sfml-graphics sfml-audio grid)
target_link_libraries(life_editor sfml-graphics sfml-audio grid)

cmake_minimum_required(VERSION 3.27.7)
project(raytracer VERSION 1.0.0)

find_package(SDL2 REQUIRED)
 
find_package(Eigen3 REQUIRED)
add_executable(raytracer 
    src/main.cpp    
    src/shapes.cpp
    )



target_include_directories(raytracer PRIVATE dependencies)
target_link_libraries(${PROJECT_NAME} SDL2 Eigen3::Eigen)


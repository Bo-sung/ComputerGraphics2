cmake_minimum_required(VERSION 3.8)

project(Chapter1_HelloTriangle)

file(GLOB_RECURSE SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Since the packages are found in the root CMakeLists.txt, 
# we just need to link them here.
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm glfw unofficial::gl3w::gl3w)

cmake_minimum_required(VERSION 3.24)

set(PROJECT_NAME opengl_project)
set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME})
add_executable(${PROJECT_NAME} src/main.cpp)

set(WINDOW_NAME "Hello, OpenGL!")
set(WINDOW_WIDTH 1600)
set(WINDOW_HIGHT 900)

include(CPM.cmake)
CPMAddPackage("gh:gabime/spdlog#v1.x")
CPMAddPackage("gh:glfw/glfw#3.3.3")
CPMAddPackage("gh:Dav1dde/glad#v0.1.34")
CPMAddPackage("gh:g-truc/glm#0.9.9.8")
CPMAddPackage(
  NAME stb
  GITHUB_REPOSITORY nothings/stb
  GIT_TAG HEAD
)

if (stb_ADDED)
  add_library(stb INTERFACE IMPORTED)
  target_include_directories(stb INTERFACE "${stb_SOURCE_DIR}")
endif()

target_link_libraries(
  ${PROJECT_NAME}
  
  gdi32
  spdlog::spdlog
  glfw
  glad
  glm
  stb
  )


target_compile_definitions(${PROJECT_NAME}
# ABC = EFG 처럼 띄어쓰기 하지말것 ABC=EFG로 작성
  PUBLIC WINDOW_NAME="${WINDOW_NAME}"
  PUBLIC WINDOW_WIDTH=${WINDOW_WIDTH}
  PUBLIC WINDOW_HIGHT=${WINDOW_HIGHT}
)
cmake_minimum_required(VERSION 3.10)
project(tp2 VERSION 2021.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)
message(STATUS "OPENGL_gl_LIBRARY: ${OPENGL_gl_LIBRARY}")

if(MSVC)
    set(GLUT_ROOT_PATH "${CMAKE_SOURCE_DIR}/freeglut")
    message(STATUS "GLUT_ROOT_PATH: ${GLUT_ROOT_PATH}")
endif()
find_package(GLUT REQUIRED)
message(STATUS "GLUT_FOUND: ${GLUT_FOUND}")
message(STATUS "GLUT_INCLUDE_DIR: ${GLUT_INCLUDE_DIR}")
message(STATUS "GLUT_LIBRARIES: ${GLUT_LIBRARIES}")

if(APPLE)
  add_definitions(-Wno-deprecated-declarations)
endif()  


add_executable(main src/main.cpp)
#target_include_directories(main PUBLIC ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})
#target_link_libraries(main PUBLIC ${OPENGL_opengl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARIES})
target_link_libraries(main OpenGL::GL OpenGL::GLU GLUT::GLUT)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(main PRIVATE -Wall -Wextra -pedantic -Wno-comment)
endif()
if(MSVC)
    target_compile_definitions(main PUBLIC -DNOMINMAX)
endif()

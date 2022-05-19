
aux_source_directory(. CPP_FILES)

add_executable(main ${CPP_FILES})

find_package(OpenGL REQUIRED)
message(STATUS "OPENGL_gl_LIBRARY: ${OPENGL_gl_LIBRARY}")

find_package(glfw3 REQUIRED)
message(STATUS "GLFW3_LIBRARIES: ${GLFW3_LIBRARIES}")

if(APPLE)
  add_definitions(-Wno-deprecated-declarations)
endif()

target_link_libraries(main OpenGL::GL OpenGL::GLU glfw)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(main PRIVATE -Wall -Wextra -pedantic -Wno-comment)
endif()
if(MSVC)
    target_compile_definitions(main PUBLIC -DNOMINMAX)
endif()

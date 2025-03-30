cmake_minimum_required(VERSION 3.30)
project(learnOpenGl)

set(CMAKE_CXX_STANDARD 20)

add_executable(learnOpenGl main.cpp glutils.cpp)

include_directories(
        /opt/homebrew/Cellar/glew/2.2.0_1/include/
        /opt/homebrew/Cellar/glfw/3.4/include/
        /opt/homebrew/Cellar/glm/1.0.1/include/
)

link_directories(
        /opt/homebrew/Cellar/glew/2.2.0_1/lib
        /opt/homebrew/Cellar/glfw/3.4/lib
        /opt/homebrew/Cellar/glm/1.0.1/lib
)

target_link_libraries(learnOpenGl
        /opt/homebrew/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib
        /opt/homebrew/Cellar/glfw/3.4/lib/libglfw.3.dylib
)

if (APPLE)
    target_link_libraries(learnOpenGl "-framework OpenGL")
    target_link_libraries(learnOpenGl "-framework GLUT")
endif()

message(STATUS "GLEW include dirs: /opt/homebrew/Cellar/glew/2.2.0_1/include/GL")
message(STATUS "GLEW libraries: /opt/homebrew/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib")
message(STATUS "GLFW include dirs: /opt/homebrew/Cellar/glfw/3.4/include/GLFW")
message(STATUS "GLFW libraries: /opt/homebrew/Cellar/glfw/3.4/lib/libglfw.3.dylib")
cmake_minimum_required(VERSION 3.7)
project(Euler-Operations)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa -framework OpenGL -framework IOKit")

set(SOURCE_FILES src/main.hpp src/main.cpp 
src/TopologicalOperation.hpp src/TopologicalOperation.cpp 
src/camera.hpp src/camera.cpp 
src/controller.hpp src/controller.cpp 
src/shader.hpp src/shader.cpp
src/DrawOperation.hpp src/DrawOperation.cpp )

add_executable(Euler-Operations ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} glut)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} GLU)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} GLEW)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} glfw3)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} GL)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} dl)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} X11)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Xrandr)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Xi)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Xxf86vm)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Xinerama)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Xcursor)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} pthread)

cmake_minimum_required(VERSION 3.10)
project(code)

set(CMAKE_CXX_STANDARD 11)
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
IF(APPLE)
    include_directories(/usr/X11R6/include/)
    link_directories(/usr/X11R6/lib)
    SET(EXTRA_LIBS GL X11 Xrender Xtst Xcomposite Xfixes GLU glut)
ELSE()
    include_directories( ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    SET(EXTRA_LIBS X11 Xrender Xtst Xcomposite Xfixes)
ENDIF()

add_executable(code src/main.cpp src/mrmCfgParser.cpp inc/mrmCfgParser.h src/mrmMouse.cpp inc/mrmMouse.h src/mrmCursor.cpp inc/mrmCursor.h src/mrmScreen.cpp inc/mrmScreen.h src/mrmOSCursor.cpp inc/mrmOSCursor.h src/mrmMultiRemoteMouse.cpp inc/mrmMultiRemoteMouse.h src/mrmUDPClient.cpp inc/mrmUDPClient.h src/mrmUDPServer.cpp inc/mrmUDPServer.h src/mrmMiceControl.cpp inc/mrmMiceControl.h src/mrmCursorControl.cpp inc/mrmCursorControl.h inc/osinput.h)
target_link_libraries(code ${EXTRA_LIBS} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} nlohmann_json::nlohmann_json)


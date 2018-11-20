cmake_minimum_required(VERSION 3.10)
project(code)

set(CMAKE_CXX_STANDARD 11)
find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS})
IF(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
ENDIF()
add_executable(code src/main.cpp src/mmClient.cpp inc/mmClient.h src/mmCursorCtrl.cpp inc/mmCursorCtrl.h src/mmRealMouseCtrl.cpp inc/mmRealMouseCtrl.h src/mmServer.cpp inc/mmServer.h src/mmVirtualMouseCtrl.cpp inc/mmVirtualMouseCtrl.h src/multimouse.cpp inc/multimouse.h src/mmThreadsafeQueue.cpp inc/mmThreadsafeQueue.h src/mmCursor.cpp inc/mmCursor.h)

target_link_libraries(code ${OPENGL_LIBRARIES} X11 Xrender)
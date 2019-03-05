SET(execName test_ocv)
CMAKE_MINIMUM_REQUIRED(VERSION 2.4)
PROJECT(${execName})

SET(EXECUTABLE_OUTPUT_PATH ".")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
#specify opencv directory
SET(OpenCV_DIR /opt/bus_face_id/opencv-3.4.5/build)
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

IF(NOT WIN32)
    add_definitions(-Wno-format-extra-args)
    SET(SPECIAL_OS_LIBS "pthread" "X11")
ENDIF()

include_directories(${OPENCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

link_directories(${OpenCV_LIBRARY_DIRS})

FILE(GLOB_RECURSE SRC_FILES src/*.cc src/*.cpp)
FILE(GLOB_RECURSE HDR_FILES include/*.h)

ADD_EXECUTABLE(${execName} ${HDR_FILES} ${SRC_FILES})
add_definitions(-std=c++11 -g -O3)

TARGET_LINK_LIBRARIES(${execName}
                        ${SPECIAL_OS_LIBS}
                        ${OpenCV_LIBRARIES}
                    )
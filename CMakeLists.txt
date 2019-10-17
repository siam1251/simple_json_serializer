cmake_minimum_required(VERSION 2.8.12)

include_directories(${OPENCV_INCL_PATH})
link_directories(${OPENCV_LIB_PATH})
MESSAGE(STATUS "opencv lib path: " ${OPENCV_LIB_PATH})
MESSAGE(STATUS "android lib name: " ${ANDROID_LIB})
link_directories(${FACE_DETECT_LIB_PATH})
link_directories(${TENSORFLOW_LIB_PATH})
MESSAGE(STATUS "tensorflow lib path: " ${TENSORFLOW_LIB_PATH})
MESSAGE(STATUS "tensorflow lib path: " ${TENSORFLOW_LIB_PATH} "/" ${TENSORFLOW_LIB_NAME})

link_directories(${DDK_LIB_PATH})
set(LIB_NAME "JsonSerializer")
set(log_dir ${SYSROOT}/usr/lib)
MESSAGE(STATUS "lod dir: " ${log_dir})
link_directories(log_dir)

file(GLOB HEADERS "*.h")
file(GLOB SOURCES "*.cpp")

MESSAGE(STATUS "project name: " ${PROJECT_NAME})

if(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
  find_library(ANDROID_LOG_LIB log)
  add_library(${LIB_NAME} ${SOURCES} ${HEADERS})
  
  target_link_libraries(${LIB_NAME} log opencv_video opencv_imgproc opencv_core)
  # target_link_libraries(${LIB_NAME} DetectBasedTracker HVisionLib facedetector opencv_video opencv_imgproc opencv_core)
else()
  add_library(${LIB_NAME} STATIC ${SOURCES} ${HEADERS})
  target_link_libraries(${LIB_NAME} ${OPENCV_WORLD_LIB} ${TENSORFLOW_LIB_NAME})
  #add_executable(main ${HEADERS} ${SOURCES})

endif()

target_include_directories(${LIB_NAME} BEFORE PUBLIC ${OPENCV_INCL_PATH} ${log_dir})
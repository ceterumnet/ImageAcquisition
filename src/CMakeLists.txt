cmake_minimum_required (VERSION 2.8.1)
cmake_policy(SET CMP0015 NEW)

project(ImageAcquisition)

set(PIXINSIGHT64 "C:/PCL64/bin" CACHE PATH "PixInsight 64bit bin")
set(PCL_SDK_HOME "c:/PCL-SDK" CACHE PATH "PixInsight SDK")

set(CMAKE_USER_MAKE_RULES_OVERRIDE
  ${CMAKE_CURRENT_SOURCE_DIR}/c_flag_overrides.cmake)
set(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX
  ${CMAKE_CURRENT_SOURCE_DIR}/cxx_flag_overrides.cmake)

include_directories(${PCL_SDK_HOME}/include)
include_directories(icons)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB all_SOURCES "*.cpp" "*.c")
file(GLOB all_HEADERS "*.hpp" "*.h")

source_group("headers" FILES ${all_HEADERS})

add_library(ImageAcquisition-pxm SHARED ${all_SOURCES} ${all_HEADERS})

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
  message("detected 64 bit build")
  set(IS_64 true)
endif()

if(WIN32 AND IS_64)
  add_custom_command(TARGET ImageAcquisition-pxm POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ImageAcquisition-pxm> ${PIXINSIGHT64}
    )
  message("Generating Build for Win64")
  add_definitions(-D__PCL_WINDOWS -D_ITERATOR_DEBUG_LEVEL=0)
  target_link_libraries(ImageAcquisition-pxm ${PCL_SDK_HOME}/lib/windows/vc10/x86_64/PCL-pxi.lib)
elseif(APPLE)
  add_definitions(-D__PCL_APPLE -D_ITERATOR_DEBUG_LEVEL=0)
  target_link_libraries(ImageAcquisition-pxm ${PCL_SDK_HOME}/lib/macosx/x86/libPCL-pxi.a)
elseif(UNIX)
  message("Linux build")
  add_definitions(-D__PCL_LINUX -D_ITERATOR_DEBUG_LEVEL=0)
  add_custom_command(TARGET ImageAcquisition-pxm POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ImageAcquisition-pxm> ${PIXINSIGHT64}
    )

  target_link_libraries(ImageAcquisition-pxm ${PCL_SDK_HOME}/lib/linux/x64/libPCL-pxi.a)
endif()


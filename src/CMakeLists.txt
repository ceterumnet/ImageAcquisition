cmake_minimum_required (VERSION 2.8.1)
cmake_policy(SET CMP0015 NEW)

project(ImageAcquisition)

set(PIXINSIGHT32 "G:/PixInsight32/bin" CACHE PATH "PixInsight 32bit bin")
set(PCL_SDK_HOME "c:/PCL-SDK" CACHE PATH "PixInsight SDK")

set(CMAKE_USER_MAKE_RULES_OVERRIDE
   ${CMAKE_CURRENT_SOURCE_DIR}/c_flag_overrides.cmake)
set(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX
   ${CMAKE_CURRENT_SOURCE_DIR}/cxx_flag_overrides.cmake)



include_directories(${PCL_SDK_HOME}/include)
include_directories(icons)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB all_SOURCES "*.cpp" "*.c")

#source_group("lua-pst" FILES ${pst_SOURCES})

add_library(ImageAcquisition-pxm SHARED ${all_SOURCES})

add_custom_command(TARGET ImageAcquisition-pxm POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ImageAcquisition-pxm> ${PIXINSIGHT32}
)

if(WIN32)
	add_definitions(-D__PCL_WINDOWS -D_ITERATOR_DEBUG_LEVEL=0)
	target_link_libraries(ImageAcquisition-pxm ${PCL_SDK_HOME}/lib/windows/x86/vc10/PCL-pxi.lib)

elseif(APPLE)
	
elseif(LINUX)
endif()


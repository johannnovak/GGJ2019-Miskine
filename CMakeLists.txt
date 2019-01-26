cmake_minimum_required(VERSION 3.12)

project(GGJ2019)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)

# Warnings
if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_SCL_SECURE_NO_WARNINGS") # use /wd4996 instead ?
else (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif (MSVC)

# Find shine Engine libraries
if(SHINE_INTERNAL)
	find_package(ShSDK REQUIRED ShCore StubUserSystem ShEntryPoint NO_MODULE)
else(SHINE_INTERNAL)
	find_package(ShSDK REQUIRED ShCore StubUserSystem ShEntryPoint)
endif(SHINE_INTERNAL)

# Include some cmake helpers
include(cmake/Master.cmake)
include(cmake/TargetBuildSAAS.cmake)

ConfigureShineSAAS()

add_subdirectory(src)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "Game")

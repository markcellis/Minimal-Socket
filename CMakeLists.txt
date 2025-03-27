cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
if(WIN32)
# The X-KeyPad StremDeck plugin needs a MD library while the X-KeyPad plugin needs an MT
if(MD)
	set(CMAKE_CXX_FLAGS_RELEASE "/MD")
	set(CMAKE_CXX_FLAGS_DEBUG "/MDd")
else()
	set(CMAKE_CXX_FLAGS_RELEASE "/MT")
	set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
endif()

endif(WIN32)

project(MinimalCppSocket)

option(LIB_OPT "Compile shared libraries (ON) or static (OFF)" OFF)
add_subdirectory(src)

option(BUILD_MinimalCppSocket_SAMPLES "Build the samples showing how to use Minimal Cpp Socket" ON)
if(BUILD_MinimalCppSocket_SAMPLES)
    add_subdirectory(samples)
endif()

option(BUILD_MinimalCppSocket_TESTS "" OFF)
if(BUILD_MinimalCppSocket_TESTS)
    add_subdirectory(tests)
endif()

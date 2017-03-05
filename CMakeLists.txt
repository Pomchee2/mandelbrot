cmake_minimum_required(VERSION 3.0)
project(mandelbrot)

#####################################
# Directory structure macros
#####################################

# Set pencil root dir
set(MANDELBROT_ROOT_DIR ${PROJECT_SOURCE_DIR})

# Source directory
set(MANDELBROT_SRC_DIR ${MANDELBROT_ROOT_DIR}/src)
# Dependencies directory (GLFW, compiled libs etc...)
set(MANDELBROT_DEP_DIR ${MANDELBROT_ROOT_DIR}/deps)

# Directories for static libraries
set(MANDELBROT_LIB_DIR ${MANDELBROT_DEP_DIR}/lib})
set(MANDELBROT_INCLUDE_DIR ${MANDELBROT_DEP_DIR}/include})

#####################################

# Set SRCS macro - place source files you want to compile here (.cpp or .c, not .h or .hpp)

set(MANDELBROT_SRCS
  ${MANDELBROT_SRC_DIR}/main.cpp
  ${MANDELBROT_SRC_DIR}/generator.cpp
  ${MANDELBROT_SRC_DIR}/renderer.cpp
  )

add_executable(mandelbrot ${MANDELBROT_SRCS})

target_include_directories(mandelbrot PUBLIC ${MANDELBROT_SRC_DIR})


#####################################
# Dependencies
#####################################

# OpenGL ############################


# GLFW ##############################
set (GLFW_BUILD_EXAMLES OFF)
set (GLFW_BUILD_TESTS OFF)
set (GLFW_BUILD_DOCS OFF)
# Make sure GLFW doesn't build vulkan
set (GLFW_VULKAN_STATIC OFF)
add_subdirectory(${MANDELBROT_DEP_DIR}/glfw)
target_link_libraries(mandelbrot glfw)
target_include_directories(mandelbrot PUBLIC ${MANDELBROT_DEP_DIR}/glfw/include)


#####################################
# COMPILER FLAGS
#####################################
if(MSVC)
  SET_TARGET_PROPERTIES(mandelbrot
    PROPERTIES COMPILE_FLAGS "/W4 /Wall")

  target_link_libraries(mandelbrot opengl32 gdi32)
elseif(CMAKE_COMPILER_IS_GNUCXX)
  SET_TARGET_PROPERTIES(mandelbrot
    PROPERTIES COMPILER_FLAGS "-Wall -Wpedantic -g -std=c++11")
  target_link_libraries(mandelbrot GL)
endif()

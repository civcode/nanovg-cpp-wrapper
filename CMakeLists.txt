cmake_minimum_required(VERSION 3.16)

project(nanovg)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmax-errors=5")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfatal-errors -fmax-errors=5")

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_BUILD_TYPE debug)

add_definitions(-DNANOVG_GL3)
add_definitions(-DNANOVG_USE_GLEW)
#add_definitions(-DDEMO_MSAA)


if (WIN32)
    list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/dep/glfw-3.3.7-mingw-bin/glfw-3.3.7/lib/cmake)
endif (WIN32)

find_package(glfw3 REQUIRED CONFIG)
find_package(OpenGL REQUIRED)

if (UNIX)
    find_package(GLEW REQUIRED)
    find_package(TBB REQUIRED)
endif (UNIX)

include_directories(
    ${OPENGL_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/dep/nanovg/src
    ${PROJECT_SOURCE_DIR}/dep/nanovg/example
    ${PROJECT_SOURCE_DIR}/dep
    ${PROJECT_SOURCE_DIR}/include
)

if (WIN32)
    include_directories(
        ${PROJECT_SOURCE_DIR}/dep/glew-2.1.0-mingw-bin/glew-2.1.0/include
    )
endif (WIN32)

set(nanovg_SRC
    ${PROJECT_SOURCE_DIR}/dep/nanovg/src/nanovg.c
    ${PROJECT_SOURCE_DIR}/dep/nanovg/src/nanovg_gl.c
    ${PROJECT_SOURCE_DIR}/dep/nanovg/src/nanovg_gl_utils.c
    ${PROJECT_SOURCE_DIR}/dep/nanovg/example/perf.c
    ${PROJECT_SOURCE_DIR}/dep/nanovg/example/demo.c
)

file(GLOB project_SRC
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/ci_nanovg.cpp
)

set(SOURCES 
    ${nanovg_SRC}
    ${project_SRC}
)

add_library(nanovg_lib STATIC
    ${nanovg_SRC}
)

target_link_libraries(nanovg_lib glfw)

add_executable(nanovg src/main.cpp ${project_SRC})

if (UNIX)
    target_link_libraries(nanovg nanovg_lib OpenGL::GL GLEW::GLEW TBB::tbb glfw ${CMAKE_DL_LIBS})
endif (UNIX)

if (WIN32)
    file(COPY ${CMAKE_SOURCE_DIR}/dep/glew-2.1.0-mingw-bin/glew-2.1.0/lib/glew32.dll DESTINATION ${CMAKE_SOURCE_DIR}/build)
    target_link_libraries(nanovg nanovg_lib OpenGL::GL glfw ${CMAKE_DL_LIBS} ${CMAKE_SOURCE_DIR}/dep/glew-2.1.0-mingw-bin/glew-2.1.0/lib/libglew32.dll.a)
endif (WIN32)

target_compile_features(nanovg PUBLIC cxx_std_17)
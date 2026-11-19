cmake_minimum_required(VERSION 3.25)

project(
    RayTracer
    VERSION 0.1.0
    DESCRIPTION "A student ray tracer project"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    lodepng
    GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
    GIT_TAG 7b2893e35891c0c85bee5595caafaf3c2044b409
)

FetchContent_MakeAvailable(lodepng)

add_library(lodepng STATIC ${lodepng_SOURCE_DIR}/lodepng.cpp)
target_include_directories(lodepng PUBLIC ${lodepng_SOURCE_DIR})

add_library(project_warnings INTERFACE)

if(MSVC)
    target_compile_options(project_warnings INTERFACE /W4 /permissive-)
else()
    target_compile_options(project_warnings INTERFACE -Wall -Wextra -Wpedantic)
endif()

add_library(raytracer_core
    src/colour/colour.cpp
    src/geometry/ray.cpp
    src/geometry/sphere.cpp
    src/image/image.cpp
    src/math/vector.cpp
    src/render/camera.cpp
    src/render/trace.cpp
)

target_include_directories(raytracer_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_link_libraries(raytracer_core PRIVATE lodepng project_warnings)

add_executable(raytracer
    src/main.cpp
)

target_link_libraries(raytracer
    PRIVATE
        project_warnings
        raytracer_core
)

add_custom_target(start
    COMMAND $<TARGET_FILE:raytracer>
    DEPENDS raytracer
    USES_TERMINAL
    COMMENT "Running raytracer"
)

include(CTest)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

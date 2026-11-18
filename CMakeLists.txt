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
    src/math/vector.cpp
    src/render/camera.cpp
    src/render/trace.cpp
)

target_include_directories(raytracer_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_link_libraries(raytracer_core PRIVATE project_warnings)

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

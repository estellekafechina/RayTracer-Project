include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.16.1
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(Catch2)

add_executable(raytracer_tests
    colour/test_colour.cpp
    geometry/test_ray.cpp
    geometry/test_sphere.cpp
    image/test_image.cpp
    material/test_material.cpp
    math/test_vector.cpp
    output/test_png_saver.cpp
    render/test_camera.cpp
    render/test_trace.cpp
    test_helpers.cpp
)

target_include_directories(raytracer_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(raytracer_tests
    PRIVATE
        Catch2::Catch2WithMain
        lodepng
        project_warnings
        raytracer_core
)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(raytracer_tests)

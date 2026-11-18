include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.16.1
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(Catch2)

add_executable(raytracer_tests
    greeting_test.cpp
    test_vector.cpp
)

target_link_libraries(raytracer_tests
    PRIVATE
        Catch2::Catch2WithMain
        project_warnings
        raytracer_core
)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(raytracer_tests)

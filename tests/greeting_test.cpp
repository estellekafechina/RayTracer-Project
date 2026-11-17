#include "raytracer/greeting.hpp"

#include <catch2/catch_test_macros.hpp>

#include <string_view>

TEST_CASE("The demo has a stable greeting", "[greeting]") {
    REQUIRE(raytracer::greeting() == std::string_view{"Hello, World!"});
}

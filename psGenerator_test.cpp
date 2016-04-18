#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "psGenerator.h"
#include <iostream>
#include <vector>


TEST_CASE("Test make circle of r=50") {
    Circle testCirc(50);
    REQUIRE(testCirc.boundingWidth == 100);
    REQUIRE(testCirc.boundingHeight == 100);
}

TEST_CASE("Test Scaled") {
    Circle testCirc(50);
    Scaled testEllipse(&testCirc, 2, 1);
    REQUIRE(testEllipse.boundingWidth == 200);
    REQUIRE(testEllipse.boundingHeight == 100);
}

TEST_CASE("Test Rotate") {
    Circle testCirc(50);
    Scaled testEllipse(&testCirc, 2, 1);
    Rotate testRotateOdd(&testEllipse, 90);

    REQUIRE(testRotateOdd.boundingWidth == 100);
    REQUIRE(testRotateOdd.boundingHeight == 200);
    Rotate testRotateEven(&testEllipse, 180);
    REQUIRE(testRotateEven.boundingWidth == 200);
    REQUIRE(testRotateEven.boundingHeight == 100);
}

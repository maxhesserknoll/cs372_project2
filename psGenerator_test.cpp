#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "psGenerator.h"


TEST_CASE("Test Cicle") {
    Circle testCirc(50);
    
    REQUIRE(testCirc.boundingWidth == 100);
    REQUIRE(testCirc.boundingHeight == 100);
    REQUIRE(testCirc.toString(360,360) ==
            "gsave\n"
            "360.000000 360.000000 translate\n"
            "50.000000\n"
            "/radius 1 index def\n"
            "newpath\n"
            "0 0 radius 0 360 arc stroke\n"
            "grestore\n");
}

TEST_CASE("Test Polygon") {
    Polygon testPolyOdd(3,15);
    
    Polygon testPolyEvenNotDiv4(6,30.5);
    
    Polygon testPolyEvenDiv4(8,55.5);
    
    
    REQUIRE(testPolyOdd.boundingWidth == 15);
    REQUIRE(testPolyOdd.boundingHeight == 12.99038105676658);
    
    REQUIRE(testPolyEvenNotDiv4.boundingWidth == 61.000000000000014);
    REQUIRE(testPolyEvenNotDiv4.boundingHeight == 52.827549630850768);
    
    REQUIRE(testPolyEvenDiv4.boundingWidth == 133.98885271170676);
    REQUIRE(testPolyEvenDiv4.boundingHeight == 133.98885271170676);
    
    
    REQUIRE(testPolyOdd.toString(360,360) ==
            "gsave\n"
            "360.000000 360.000000 translate\n"
            "newpath\n0 0 moveto\n"
            "7.500000 -4.330127 moveto\n"
            "0.000000 8.660254 lineto\n"
            "-7.500000 -4.330127 lineto\n"
            "closepath\n"
            "stroke\n"
            "grestore\n");
    
    REQUIRE(testPolyEvenNotDiv4.toString(360, 360) ==
            "gsave\n"
            "360.000000 360.000000 translate\n"
            "newpath\n"
            "0 0 moveto\n"
            "15.250000 -26.413775 moveto\n"
            "30.500000 -0.000000 lineto\n"
            "15.250000 26.413775 lineto\n"
            "-15.250000 26.413775 lineto\n"
            "-30.500000 0.000000 lineto\n"
            "-15.250000 -26.413775 lineto\n"
            "closepath\n"
            "stroke\n"
            "grestore\n");
    
    REQUIRE(testPolyEvenDiv4.toString(360, 360) ==
            "gsave\n"
            "360.000000 360.000000 translate\n"
            "newpath\n"
            "0 0 moveto\n"
            "27.750000 -66.994426 moveto\n"
            "66.994426 -27.750000 lineto\n"
            "66.994426 27.750000 lineto\n"
            "27.750000 66.994426 lineto\n"
            "-27.750000 66.994426 lineto\n"
            "-66.994426 27.750000 lineto\n"
            "-66.994426 -27.750000 lineto\n"
            "-27.750000 -66.994426 lineto\n"
            "closepath\n"
            "stroke\n"
            "grestore\n");

}

TEST_CASE("Test Spacer") {
    Spacer testSpacer(100,144.4);
    
    REQUIRE(testSpacer.boundingWidth == 100);
    REQUIRE(testSpacer.boundingHeight == 144.40000000000001);
    
    REQUIRE(testSpacer.toString(360, 360) == "");
}

TEST_CASE("Test Rectangle") {
    Rectangle testRect(100, 144.4);
    
    REQUIRE(testRect.boundingWidth == 100);
    REQUIRE(testRect.boundingHeight == 144.40000000000001);
    
    REQUIRE(testRect.toString(360, 360) ==
            "gsave\n"
            "360.000000 360.000000 translate\n"
            "newpath\n"
            "-50.000000 -72.200000 moveto\n"
            "0 144.400000 rlineto\n"
            "100.000000 0 rlineto\n"
            "0 -144.400000 rlineto\n"
            "closepath stroke\n"
            "grestore\n");
}

TEST_CASE("Test Square") {
    Square testSquare(56.7);
    
    REQUIRE(testSquare.boundingWidth == 56.700000000000017);
    REQUIRE(testSquare.boundingHeight == 56.700000000000017);
    
    REQUIRE(testSquare.toString(360, 360) ==
            "gsave\n"
            "360.000000 360.000000 translate\n"
            "newpath\n"
            "0 0 moveto\n"
            "28.350000 -28.350000 moveto\n"
            "28.350000 28.350000 lineto\n"
            "-28.350000 28.350000 lineto\n"
            "-28.350000 -28.350000 lineto\n"
            "closepath\n"
            "stroke\n"
            "grestore\n");
}
    
TEST_CASE("Test Triangle") {
    Triangle testTriangle(300.123);
    
    REQUIRE(testTriangle.boundingWidth == 300.12299999999999);
    REQUIRE(testTriangle.boundingHeight == 259.91414225999711);
    
    REQUIRE(testTriangle.toString(360, 360) ==
            "gsave\n"
            "360.000000 360.000000 translate\n"
            "newpath\n"
            "0 0 moveto\n"
            "150.061500 -86.638047 moveto\n"
            "0.000000 173.276095 lineto\n"
            "-150.061500 -86.638047 lineto\n"
            "closepath\n"
            "stroke\n"
            "grestore\n");
}

TEST_CASE("Test Trapezoid") {
    Trapezoid testTrap(55, 44, 21.2);
    
    REQUIRE(testTrap.boundingWidth == 55);
    REQUIRE(testTrap.boundingHeight == 21.199999999999999);
    
    REQUIRE(testTrap.toString(360, 360) ==
            "gsave\n"
            "360.000000 360.000000 translate\n"
            "55.000000 44.000000 21.200000\n"
            "/topside 1 index def\n"
            "/bottomside 2 index def\n"
            "/hieght 3 index def\n"
            "newpath\n"
            "0 0 moveto\n"
            "bottomside 2  div\n"
            "hieght -2 div\n"
            "moveto\n"
            "bottomside -2 div\n"
            "hieght -2 div\n"
            "lineto\n"
            "topside -2 div\n"
            "hieght 2 div\n"
            "lineto\n"
            "topside 2 div\n"
            "hieght 2 div\n"
            "lineto\n"
            "closepath\n"
            "stroke\n"
            "grestore\n");
}

TEST_CASE("Test FiftyShades") {
    FiftyShades testFS(88.90);
    
    REQUIRE(testFS.boundingWidth == 88.900000000000006);
    REQUIRE(testFS.boundingHeight == 88.900000000000006);
    
    REQUIRE(testFS.toString(360, 360) ==
            "gsave\n"
            "360.000000 360.000000 translate\n"
            "88.900000\n"
            "/size 1 index def\n"
            "/50size size 50 div def\n"
            "size -2 div size -2 div translate\n"
            "newpath\n"
            "0 0 moveto\n"
            "50 -1 0{\n"
                "0 0 moveto\n"
                "dup\n"
                "dup\n"
                ".02 mul\n"
                "setgray\n"
                "dup\n"
                "50size mul\n"
                "0 lineto\n"
                "50size mul\n"
                "size lineto\n"
                "0 size lineto\n"
                "closepath\n"
                "fill\n"
                "stroke\n"
            "}for\n"
            "0 0 moveto\n"
            "0 size lineto\n"
            "size size lineto\n"
            "size 0 lineto\n"
            "closepath\n"
            "stroke\n"
            "grestore\n");
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

TEST_CASE("Test Layered") {
}

TEST_CASE("Test Vertical") {
}

TEST_CASE("Test Horizontal") {
}

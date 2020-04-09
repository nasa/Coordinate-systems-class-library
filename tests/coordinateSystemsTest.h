/**
 * @brief Coordinate systems class library tester definition.
 * @file coordinateSystemsTest.h
 * @version 19.09
 * @date September 24, 2019
 * @details Class for testing the coordinate systems class library
 * 
 * Version History:
 * Version 0.0 on December 5, 2013
 * Version 1.0 on January 13, 2014
 * Version 19.09 on September 24, 2019
 */

#ifndef COORDINATESYSTEMSTEST_H
#define	COORDINATESYSTEMSTEST_H

#include <cppunit/extensions/HelperMacros.h>

//WGS84
#define sma 6378137.0 //Earth elipsoid semi-major axis in meters
#define ecc2 0.00669437999014 //Earth elipsoid eccentricity squared
#define tol 0.01 //tolerance for testing positoin equivalence (meters)

class coordinateSystemsTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(coordinateSystemsTest);

    CPPUNIT_TEST(testAER);
    CPPUNIT_TEST(testAERToECF);
    CPPUNIT_TEST(testAERToECFThrow);
    CPPUNIT_TEST(testAERToENU);
    CPPUNIT_TEST(testAERToLLA);
    CPPUNIT_TEST(testAERToLLAThrow);
    CPPUNIT_TEST(testAERToDCA);
    CPPUNIT_TEST(testDCA);
    CPPUNIT_TEST(testGetHeading);
    CPPUNIT_TEST(testSetHeading);
    CPPUNIT_TEST(testDCAToECF);
    CPPUNIT_TEST(testDCAToECFThrow);
    CPPUNIT_TEST(testDCAToENU);
    CPPUNIT_TEST(testDCAToLLA);
    CPPUNIT_TEST(testDCAToLLAThrow);
    CPPUNIT_TEST(testDCAToAER);
    CPPUNIT_TEST(testGetOrigin);
    CPPUNIT_TEST(testSetOrigin);
    CPPUNIT_TEST(testECFToAER);
    CPPUNIT_TEST(testECFToDCA);
    CPPUNIT_TEST(testECFToENU);
    CPPUNIT_TEST(testECFToLLA);
    CPPUNIT_TEST(testECFToLLAPolar);
    CPPUNIT_TEST(testECFToLLAZeroX);
    CPPUNIT_TEST(testENU);
    CPPUNIT_TEST(testENUToAER);
    CPPUNIT_TEST(testENUToDCA);
    CPPUNIT_TEST(testENUToECF);
    CPPUNIT_TEST(testENUToECFThrow);
    CPPUNIT_TEST(testENUToLLA);
    CPPUNIT_TEST(testENUToLLAThrow);
    CPPUNIT_TEST(testGetMagnitude);
    CPPUNIT_TEST(testGetPosition);
    CPPUNIT_TEST(testPositionVector);
    CPPUNIT_TEST(testSetPosition);
    CPPUNIT_TEST(testLLAGetMagnitude);
    CPPUNIT_TEST(testLLAToAER);
    CPPUNIT_TEST(testLLAToDCA);
    CPPUNIT_TEST(testLLAToECF);
    CPPUNIT_TEST(testLLAToENU);

    CPPUNIT_TEST_SUITE_END();

public:
    coordinateSystemsTest();
    virtual ~coordinateSystemsTest();
    void setUp();
    void tearDown();

private:
    double _first, _second, _third;
    double _X, _Y, _Z;
    double _east, _north, _up;
    double _downRange, _crossRange, _above;
    double _latitude, _longitude, _altitude;
    double _heading;
    double _azimuth, _elevation, _range;
    void testAER();
    void testAERToECF();
    void testAERToECFThrow();
    void testAERToENU();
    void testAERToLLA();
    void testAERToLLAThrow();
    void testAERToDCA();
    void testDCA();
    void testGetHeading();
    void testSetHeading();
    void testDCAToECF();
    void testDCAToECFThrow();
    void testDCAToENU();
    void testDCAToLLA();
    void testDCAToLLAThrow();
    void testDCAToAER();
    void testGetOrigin();
    void testSetOrigin();
    void testECFToAER();
    void testECFToDCA();
    void testECFToENU();
    void testECFToLLA();
    void testECFToLLAPolar();
    void testECFToLLAZeroX();
    void testENU();
    void testENUToAER();
    void testENUToDCA();
    void testENUToECF();
    void testENUToECFThrow();
    void testENUToLLA();
    void testENUToLLAThrow();
    void testGetMagnitude();
    void testGetPosition();
    void testPositionVector();
    void testSetPosition();
    void testLLAGetMagnitude();
    void testLLAToAER();
    void testLLAToDCA();
    void testLLAToECF();
    void testLLAToENU();
};

#endif	/* COORDINATESYSTEMSTEST_H */


/**
 * @brief Coordinate systems class library tester implementation.
 * @file coordinateSystemsTest.cpp
 * @version 19.09
 * @date September 24, 2019
 * @details Class for testing the coordinate systems class library
 * 
 * Version History:
 * Version 0.0 on December 5, 2013
 * Version 1.0 on January 13, 2014
 * Version 19.09 on September 24, 2019
 */

#include <math.h>
#include "coordinateSystemsTest.h"
#include "include/coordinateSystems.h"

using namespace coordinateSystems;

CPPUNIT_TEST_SUITE_REGISTRATION(coordinateSystemsTest);

coordinateSystemsTest::coordinateSystemsTest() {
}

coordinateSystemsTest::~coordinateSystemsTest() {
}

void coordinateSystemsTest::setUp() {
    _first = 1.11;
    _second = 2.22;
    _third = 3.33;
    _X = sma+1000;
    _Y = 2000;
    _Z = 300.0;
    _east = 1111.11;
    _north = 222.22;
    _up = 333.33;
    _downRange = 1111.11;
    _crossRange = 222.22;
    _above = 333.33;
    _latitude = 10.0;
    _longitude = 20.0;
    _altitude = 30.0;
    _heading = 55.5;
    _azimuth = 45.0;
    _elevation = 30.0;
    _range = 555.55;
}

void coordinateSystemsTest::tearDown() {
}

void coordinateSystemsTest::testAER() {
    LLA _origin(_latitude,_longitude,_altitude);
    AER AER1(_origin);
    AER AER2(_azimuth, _elevation, _range, _origin, _heading);
    AER AER3(_azimuth, _elevation, _range, _latitude, _longitude, _altitude, _heading);
    AER AER4;
    AER AER5(_azimuth, _elevation, _range, _heading);
    AER AER6(_origin,_heading);
    
    CPPUNIT_ASSERT_EQUAL(0.0,AER1.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,AER1.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,AER1.getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(_latitude,AER1.getOrigin().getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_longitude,AER1.getOrigin().getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_altitude,AER1.getOrigin().getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,AER1.getHeading());
   
    CPPUNIT_ASSERT_EQUAL(_azimuth,AER2.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_elevation,AER2.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_range,AER2.getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(_latitude,AER2.getOrigin().getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_longitude,AER2.getOrigin().getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_altitude,AER2.getOrigin().getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(_heading,AER2.getHeading());
    
    CPPUNIT_ASSERT_EQUAL(_azimuth,AER3.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_elevation,AER3.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_range,AER3.getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(_latitude,AER3.getOrigin().getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_longitude,AER3.getOrigin().getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_altitude,AER3.getOrigin().getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(_heading,AER3.getHeading());
    
    CPPUNIT_ASSERT_EQUAL(0.0,AER4.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,AER4.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,AER4.getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,AER4.getHeading());
    
    CPPUNIT_ASSERT_EQUAL(_azimuth,AER5.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_elevation,AER5.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_range,AER5.getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(_heading,AER5.getHeading());

    CPPUNIT_ASSERT_EQUAL(0.0,AER6.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,AER6.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,AER6.getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(_latitude,AER6.getOrigin().getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_longitude,AER6.getOrigin().getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_altitude,AER6.getOrigin().getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(_heading,AER6.getHeading());
}

void coordinateSystemsTest::testAERToECF() {
    AER AER1(0, 90, _range, 0.0, 0.0, 0.0, 0.0);
    
    ECF result1 = AER1.toECF();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(sma+_range,result1.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,result1.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,result1.getThirdCoordinate(),tol);
    
    AER1.setFirstCoordinate(_azimuth);
    AER1.setSecondCoordinate(_elevation);
    AER1.setOrigin(_latitude, _longitude, _altitude);
    AER1.setHeading(_heading);
    AER result2 = AER1.toECF().toAER(_latitude, _longitude, _altitude, _heading);
    
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_azimuth,result2.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_elevation,result2.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_range,result2.getThirdCoordinate(),tol);
}

void coordinateSystemsTest::testAERToECFThrow(){
    AER AER1(1.0,2.0,3.0);
    CPPUNIT_ASSERT_THROW(AER1.toECF(),std::exception);
}

void coordinateSystemsTest::testAERToENU() {
    AER AER1(0.0, 0.0, _range);
    
    ENU result1 = AER1.toENU();
    CPPUNIT_ASSERT_EQUAL(0.0,result1.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_range,result1.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,result1.getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,result1.getOrigin().getFirstCoordinate());
    
    AER1.setFirstCoordinate(90.0);
    result1 = AER1.toENU();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_range,result1.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,result1.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,result1.getThirdCoordinate(),tol);
    
    AER1.setHeading(90.0);
    result1 = AER1.toENU();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,result1.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-_range,result1.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,result1.getThirdCoordinate(),tol);
    
    AER1.setFirstCoordinate(_azimuth);
    AER1.setSecondCoordinate(_elevation);
    AER1.setOrigin(_latitude, _longitude, _altitude);    
    AER1.setHeading(_heading);
    AER result2 = AER1.toENU().toAER(_heading);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_azimuth,result2.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_elevation,result2.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_range,result2.getThirdCoordinate(),tol);
    CPPUNIT_ASSERT_EQUAL(_latitude,result2.getOrigin().getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_longitude,result2.getOrigin().getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_altitude,result2.getOrigin().getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(_heading,result2.getHeading());
}

void coordinateSystemsTest::testAERToLLA() {
    AER AER1(0.0,0.0,0.0,_latitude, _longitude, _altitude);
    LLA result1 = AER1.toLLA();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_latitude,result1.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_longitude,result1.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_altitude,result1.getThirdCoordinate(),tol);

    AER1.setPosition(_azimuth, _elevation, _range);
    AER1.setHeading(_heading);
    
    AER result2 = AER1.toLLA().toAER(_latitude, _longitude, _altitude, _heading);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_azimuth,result2.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_elevation,result2.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_range,result2.getThirdCoordinate(),tol);
}

void coordinateSystemsTest::testAERToLLAThrow(){
    AER AER1(1.0,2.0,3.0);
    CPPUNIT_ASSERT_THROW(AER1.toLLA(),std::exception);
}

void coordinateSystemsTest::testAERToDCA(){
    AER AER1(0.0,0.0,_range);
    DCA result = AER1.toDCA();
    CPPUNIT_ASSERT_EQUAL(_range,result.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,result.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,result.getThirdCoordinate());
    
    AER1.setFirstCoordinate(90.0);
    result = AER1.toDCA();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,result.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-_range,result.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,result.getThirdCoordinate(),tol);
    
    AER1.setPosition(_azimuth, _elevation,_range);
    AER result2 = AER1.toDCA().toAER();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_azimuth,result2.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_elevation,result2.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_range,result2.getThirdCoordinate(),tol);
}

void coordinateSystemsTest::testDCA() {
    LLA _origin(_latitude,_longitude,_altitude);
    DCA DCA1(_origin);
    DCA DCA2(_downRange, _crossRange, _above, _origin, _heading);
    DCA DCA3(_downRange, _crossRange, _above, _latitude, _longitude, _altitude, _heading);
    DCA DCA4;
    DCA DCA5(_downRange, _crossRange, _above, _heading);
    DCA DCA6(_origin,_heading);
    
    CPPUNIT_ASSERT_EQUAL(0.0,DCA1.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,DCA1.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,DCA1.getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(_latitude,DCA1.getOrigin().getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_longitude,DCA1.getOrigin().getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_altitude,DCA1.getOrigin().getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,DCA1.getHeading());
   
    CPPUNIT_ASSERT_EQUAL(_downRange,DCA2.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_crossRange,DCA2.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_above,DCA2.getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(_latitude,DCA2.getOrigin().getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_longitude,DCA2.getOrigin().getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_altitude,DCA2.getOrigin().getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(_heading,DCA2.getHeading());
    
    CPPUNIT_ASSERT_EQUAL(_downRange,DCA3.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_crossRange,DCA3.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_above,DCA3.getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(_latitude,DCA3.getOrigin().getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_longitude,DCA3.getOrigin().getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_altitude,DCA3.getOrigin().getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(_heading,DCA3.getHeading());
    
    CPPUNIT_ASSERT_EQUAL(0.0,DCA4.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,DCA4.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,DCA4.getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,DCA4.getHeading());
    
    CPPUNIT_ASSERT_EQUAL(_downRange,DCA5.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_crossRange,DCA5.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_above,DCA5.getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(_heading,DCA5.getHeading());

    CPPUNIT_ASSERT_EQUAL(0.0,DCA6.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,DCA6.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,DCA6.getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(_latitude,DCA6.getOrigin().getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_longitude,DCA6.getOrigin().getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_altitude,DCA6.getOrigin().getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(_heading,DCA6.getHeading());
}


void coordinateSystemsTest::testGetHeading() {
    DCA dCA;
    AER aER;
    double result;
    
    result = dCA.getHeading();
    CPPUNIT_ASSERT_EQUAL(result,0.0);
    result = aER.getHeading();
    CPPUNIT_ASSERT_EQUAL(result,0.0);
}

void coordinateSystemsTest::testSetHeading() {
    DCA dCA;
    AER aER;
    double result;
    
    dCA.setHeading(_heading);
    aER.setHeading(_heading);
    
    result = dCA.getHeading();
    CPPUNIT_ASSERT_EQUAL(_heading,result);
    result = aER.getHeading();
    CPPUNIT_ASSERT_EQUAL(_heading,result);
}

void coordinateSystemsTest::testDCAToECF() {
    DCA DCA1(_downRange, _crossRange, _above, 0.0, 0.0, 0.0, 0.0);
    
    ECF result1 = DCA1.toECF();
    CPPUNIT_ASSERT_EQUAL(sma+_above,result1.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(-_crossRange,result1.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_downRange,result1.getThirdCoordinate());
    
    DCA1.setOrigin(_latitude, _longitude, _altitude);
    DCA1.setHeading(_heading);
    DCA result2 = DCA1.toECF().toDCA(_latitude, _longitude, _altitude, _heading);
    
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_downRange,result2.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_crossRange,result2.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_above,result2.getThirdCoordinate(),tol);
}

void coordinateSystemsTest::testDCAToECFThrow(){
    DCA DCA1(1.0,2.0,3.0);
    CPPUNIT_ASSERT_THROW(DCA1.toECF(),std::exception);
}

void coordinateSystemsTest::testDCAToENU() {
    DCA DCA1(_downRange, _crossRange, _above);
    
    ENU result1 = DCA1.toENU();
    CPPUNIT_ASSERT_EQUAL(-_crossRange,result1.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_downRange,result1.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_above,result1.getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,result1.getOrigin().getFirstCoordinate());
    
    DCA1.setOrigin(_latitude, _longitude, _altitude);
    DCA1.setHeading(90.0);
    result1 = DCA1.toENU();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_downRange,result1.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_crossRange,result1.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_above,result1.getThirdCoordinate(),tol);
    CPPUNIT_ASSERT_EQUAL(_latitude,result1.getOrigin().getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_longitude,result1.getOrigin().getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_altitude,result1.getOrigin().getThirdCoordinate());
    
    DCA1.setHeading(_heading);
    DCA result2 = DCA1.toENU().toDCA(_heading);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_downRange,result2.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_crossRange,result2.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_above,result2.getThirdCoordinate(),tol);
    CPPUNIT_ASSERT_EQUAL(_latitude,result2.getOrigin().getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_longitude,result2.getOrigin().getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_altitude,result2.getOrigin().getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(_heading,result2.getHeading());
}

void coordinateSystemsTest::testDCAToLLA() {
    DCA DCA1(0.0,0.0,0.0,_latitude, _longitude, _altitude);
    LLA result1 = DCA1.toLLA();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_latitude,result1.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_longitude,result1.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_altitude,result1.getThirdCoordinate(),tol);

    DCA1.setPosition(_downRange, _crossRange, _above);
    DCA1.setHeading(_heading);
    
    DCA result2 = DCA1.toLLA().toDCA(_latitude, _longitude, _altitude, _heading);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_downRange,result2.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_crossRange,result2.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_above,result2.getThirdCoordinate(),tol);
}

void coordinateSystemsTest::testDCAToLLAThrow(){
    DCA DCA1(1.0,2.0,3.0);
    CPPUNIT_ASSERT_THROW(DCA1.toLLA(),std::exception);
}

void coordinateSystemsTest::testDCAToAER(){
    DCA DCA1(0.0,0.0,0.0);
    AER result1 = DCA1.toAER();
    CPPUNIT_ASSERT_EQUAL(0.0,result1.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,result1.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,result1.getThirdCoordinate());
    
    DCA1.setPosition(0.0, 0.0, _above);
    result1 = DCA1.toAER();
    CPPUNIT_ASSERT_EQUAL(0.0,result1.getFirstCoordinate());
    CPPUNIT_ASSERT_DOUBLES_EQUAL(90.0,result1.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_EQUAL(_above,result1.getThirdCoordinate());
    
    DCA1.setPosition(0.0, 0.0, -_above);
    result1 = DCA1.toAER();
    CPPUNIT_ASSERT_EQUAL(0.0,result1.getFirstCoordinate());
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-90.0,result1.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_EQUAL(_above,result1.getThirdCoordinate());
    
    DCA1.setPosition(_downRange, _crossRange, _above);
    DCA result2 = DCA1.toAER().toDCA();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_downRange,result2.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_crossRange,result2.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_above,result2.getThirdCoordinate(),tol);
}

void coordinateSystemsTest::testGetOrigin() {
    ENU ENU1;
    LLA result = ENU1.getOrigin();
    CPPUNIT_ASSERT_EQUAL(0.0,result.getFirstCoordinate());
}

void coordinateSystemsTest::testSetOrigin() {
    LLA _origin(_latitude,_longitude,_altitude);
    ENU ENU1;
    ENU1.setOrigin(_origin);
    LLA result = ENU1.getOrigin();
    CPPUNIT_ASSERT_EQUAL(_latitude,result.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_longitude,result.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_altitude,result.getThirdCoordinate());
}

void coordinateSystemsTest::testECFToAER() {
    ECF ECF1(_X, _Y, _Z);
    LLA _origin(_latitude,_longitude,_altitude);
    
    ECF result = ECF1.toAER(_origin, _heading).toECF();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_X,result.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_Y,result.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_Z,result.getThirdCoordinate(),tol);
    
    result = ECF1.toAER(_latitude, _longitude, _altitude, _heading).toECF();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_X,result.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_Y,result.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_Z,result.getThirdCoordinate(),tol);
}

void coordinateSystemsTest::testECFToDCA() {
    ECF ECF1(_X, _Y, _Z);
    LLA _origin(_latitude,_longitude,_altitude);
    
    ECF result = ECF1.toDCA(_origin, _heading).toECF();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_X,result.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_Y,result.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_Z,result.getThirdCoordinate(),tol);
    
    result = ECF1.toDCA(_latitude, _longitude, _altitude, _heading).toECF();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_X,result.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_Y,result.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_Z,result.getThirdCoordinate(),tol);
}

void coordinateSystemsTest::testECFToENU() {
    ECF ECF1(_X, _Y, _Z);
    LLA _origin(_latitude,_longitude,_altitude);
    
    ECF result = ECF1.toENU(_origin).toECF();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_X,result.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_Y,result.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_Z,result.getThirdCoordinate(),tol);
    
    result = ECF1.toENU(_latitude, _longitude, _altitude).toECF();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_X,result.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_Y,result.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_Z,result.getThirdCoordinate(),tol);
}

void coordinateSystemsTest::testECFToLLA() {
    ECF ECF1(sma,0.0,0.0);
    LLA result1 = ECF1.toLLA();
    CPPUNIT_ASSERT_EQUAL(0.0,result1.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,result1.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,result1.getThirdCoordinate());
    
    ECF1.setPosition(_X, _Y, _Z);
    ECF result2 = ECF1.toLLA().toECF();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_X,result2.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_Y,result2.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_Z,result2.getThirdCoordinate(),tol);
}

void coordinateSystemsTest::testECFToLLAPolar() {
    double b = sqrt(pow(sma,2)*(1-ecc2));
    ECF ECF1(0.0,0.0,b);
    LLA result1 = ECF1.toLLA();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(90.0,result1.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_EQUAL(0.0,result1.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,result1.getThirdCoordinate());
    
    ECF1.setThirdCoordinate(-b-300.0);
    result1 = ECF1.toLLA();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-90.0,result1.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_EQUAL(0.0,result1.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(300.0,result1.getThirdCoordinate());
}

void coordinateSystemsTest::testECFToLLAZeroX() {
    ECF ECF1(0.0,sma,0.0);
    LLA result1 = ECF1.toLLA();
    CPPUNIT_ASSERT_EQUAL(0.0,result1.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(90.0,result1.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,result1.getThirdCoordinate());
    
    ECF1.setPosition(0.0,-sma-300.0,0.0);
    result1 = ECF1.toLLA();
    CPPUNIT_ASSERT_EQUAL(0.0,result1.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(-90.0,result1.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(300.0,result1.getThirdCoordinate());
}

void coordinateSystemsTest::testENU() {
    LLA _origin(_latitude,_longitude,_altitude);
    ENU ENU1(_origin);
    ENU ENU2(_east, _north, _up, _origin);
    ENU ENU3(_east, _north, _up, _latitude, _longitude, _altitude);
    
    CPPUNIT_ASSERT_EQUAL(_latitude,ENU1.getOrigin().getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_longitude,ENU1.getOrigin().getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_altitude,ENU1.getOrigin().getThirdCoordinate());
   
    CPPUNIT_ASSERT_EQUAL(_east,ENU2.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_north,ENU2.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_up,ENU2.getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(_latitude,ENU2.getOrigin().getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_longitude,ENU2.getOrigin().getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_altitude,ENU2.getOrigin().getThirdCoordinate());
    
    CPPUNIT_ASSERT_EQUAL(_east,ENU3.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_north,ENU3.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_up,ENU3.getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(_latitude,ENU3.getOrigin().getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_longitude,ENU3.getOrigin().getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_altitude,ENU3.getOrigin().getThirdCoordinate());
}

void coordinateSystemsTest::testENUToAER() {
    ENU ENU1(_east, _north, _up);
    ENU1.setOrigin(_latitude, _longitude, _altitude);
    
    ENU result2 = ENU1.toAER(_heading).toENU();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_east,result2.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_north,result2.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_up,result2.getThirdCoordinate(),tol);
    CPPUNIT_ASSERT_EQUAL(_latitude,result2.getOrigin().getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_longitude,result2.getOrigin().getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_altitude,result2.getOrigin().getThirdCoordinate());
}

void coordinateSystemsTest::testENUToDCA() {
    ENU ENU1(_east, _north, _up);
    
    DCA result1 = ENU1.toDCA(0.0);
    CPPUNIT_ASSERT_EQUAL(_north,result1.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(-_east,result1.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_up,result1.getThirdCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,result1.getOrigin().getFirstCoordinate());
    
    ENU1.setOrigin(_latitude, _longitude, _altitude);
    result1 = ENU1.toDCA(90.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_east,result1.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_north,result1.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_up,result1.getThirdCoordinate(),tol);
    CPPUNIT_ASSERT_EQUAL(_latitude,result1.getOrigin().getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_longitude,result1.getOrigin().getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_altitude,result1.getOrigin().getThirdCoordinate());
    
    ENU result2 = ENU1.toDCA(_heading).toENU();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_east,result2.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_north,result2.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_up,result2.getThirdCoordinate(),tol);
    CPPUNIT_ASSERT_EQUAL(_latitude,result2.getOrigin().getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_longitude,result2.getOrigin().getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_altitude,result2.getOrigin().getThirdCoordinate());
}

void coordinateSystemsTest::testENUToECF() {
    ENU ENU1(_east, _north, _up, 0.0, 0.0, 0.0);
    
    ECF result1 = ENU1.toECF();
    CPPUNIT_ASSERT_EQUAL(sma+_up,result1.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_east,result1.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_north,result1.getThirdCoordinate());
    
    ENU1.setOrigin(_latitude, _longitude, _altitude);
    ENU result2 = ENU1.toECF().toENU(_latitude, _longitude, _altitude);
    
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_east,result2.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_north,result2.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_up,result2.getThirdCoordinate(),tol);
}

void coordinateSystemsTest::testENUToECFThrow() {
    ENU ENU1(1.0,2.0,3.0);
    CPPUNIT_ASSERT_THROW(ENU1.toECF(),std::exception);
}


void coordinateSystemsTest::testENUToLLA() {
    ENU ENU1(0.0,0.0,0.0,_latitude, _longitude, _altitude);
    
    LLA result1 = ENU1.toLLA();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_latitude,result1.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_longitude,result1.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_altitude,result1.getThirdCoordinate(),tol);
    
    ENU1.setPosition(_east, _north, _up);
    ENU result2 = ENU1.toLLA().toENU(_latitude, _longitude, _altitude);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_east,result2.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_north,result2.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_up,result2.getThirdCoordinate(),tol);
}

void coordinateSystemsTest::testENUToLLAThrow() {
    ENU ENU1(1.0,2.0,3.0);
    CPPUNIT_ASSERT_THROW(ENU1.toLLA(),std::exception);
}

void coordinateSystemsTest::testGetMagnitude() {
    Cartesian _positionVector(6,2,3);
    double result = _positionVector.getMagnitude();
    CPPUNIT_ASSERT_EQUAL(result,7.0);
    
    Spherical P1(_azimuth,_elevation,_range);
    result = P1.getMagnitude();
    CPPUNIT_ASSERT_EQUAL(result,_range);
    
    AER AER1(_azimuth,_elevation,_range);
    result = AER1.getMagnitude();
    CPPUNIT_ASSERT_EQUAL(result,_range);
}

void coordinateSystemsTest::testGetPosition() {
    Cartesian _positionVector(_first, _second, _third);
    std::vector<double> result = _positionVector.getPosition();
    CPPUNIT_ASSERT_EQUAL(_first,result.at(0));
    CPPUNIT_ASSERT_EQUAL(_second,result.at(1));
    CPPUNIT_ASSERT_EQUAL(_third,result.at(2));
}

void coordinateSystemsTest::testPositionVector() {
    Cartesian _positionVector(_first, _second, _third);
    Cartesian P1;

    //test default constructor
    CPPUNIT_ASSERT_EQUAL(P1.getFirstCoordinate(),0.0);
        
    //test gets
    CPPUNIT_ASSERT_EQUAL(_first,_positionVector.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_second,_positionVector.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_third,_positionVector.getThirdCoordinate());
    
    //test sets
    P1.setFirstCoordinate(_first);
    CPPUNIT_ASSERT_EQUAL(_first,P1.getFirstCoordinate());
    P1.setSecondCoordinate(_second);
    CPPUNIT_ASSERT_EQUAL(_second,P1.getSecondCoordinate());
    P1.setThirdCoordinate(_third);
    CPPUNIT_ASSERT_EQUAL(_third,P1.getThirdCoordinate());
}

void coordinateSystemsTest::testSetPosition() {
    Cartesian _positionVector;
    _positionVector.setPosition(_first, _second, _third);
    CPPUNIT_ASSERT_EQUAL(_first,_positionVector.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(_second,_positionVector.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(_third,_positionVector.getThirdCoordinate());
}

void coordinateSystemsTest::testLLAGetMagnitude() {
    LLA lLA;
    double result = lLA.getMagnitude();
    
    //earth radius equator
    CPPUNIT_ASSERT_EQUAL(result,sma);
}

void coordinateSystemsTest::testLLAToAER() {
    double locationLat = 15;
    double locationLon = 15;
    double locationAlt = 55.0;
    
    LLA LLA1(_latitude, _longitude, _altitude);
    
    //test zero result
    AER result1 = LLA1.toAER(_latitude, _longitude, _altitude,0.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,result1.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,result1.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,result1.getThirdCoordinate(),tol);

    LLA _origin(_latitude, _longitude, _altitude);    
    LLA1.setPosition(locationLat,locationLon,locationAlt);
    LLA result2 = LLA1.toAER(_origin,_heading).toLLA();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(locationLat,result2.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(locationLon,result2.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(locationAlt,result2.getThirdCoordinate(),tol);
}

void coordinateSystemsTest::testLLAToDCA() {
    double locationLat = 15;
    double locationLon = 15;
    double locationAlt = 55.0;
    
    LLA LLA1(_latitude, _longitude, _altitude);
    
    //test zero result
    DCA result1 = LLA1.toDCA(_latitude, _longitude, _altitude,0.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,result1.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,result1.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,result1.getThirdCoordinate(),tol);

    LLA _origin(_latitude, _longitude, _altitude);    
    LLA1.setPosition(locationLat,locationLon,locationAlt);
    LLA result2 = LLA1.toDCA(_origin,_heading).toLLA();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(locationLat,result2.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(locationLon,result2.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(locationAlt,result2.getThirdCoordinate(),tol);
}

void coordinateSystemsTest::testLLAToECF() {
    LLA LLA1;
    ECF result = LLA1.toECF();
    CPPUNIT_ASSERT_EQUAL(sma,result.getFirstCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,result.getSecondCoordinate());
    CPPUNIT_ASSERT_EQUAL(0.0,result.getThirdCoordinate());
    
    LLA1.setPosition(_latitude, _longitude, _altitude);
    LLA result2 = LLA1.toECF().toLLA();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_latitude,result2.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_longitude,result2.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_altitude,result2.getThirdCoordinate(),tol);
}

void coordinateSystemsTest::testLLAToENU() {
    double locationLat = 15;
    double locationLon = 15;
    double locationAlt = 55.0;
    
    LLA LLA1(_latitude, _longitude, _altitude);
    
    //test zero result
    ENU result1 = LLA1.toENU(_latitude, _longitude, _altitude);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,result1.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,result1.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,result1.getThirdCoordinate(),tol);
    
    LLA _origin(_latitude, _longitude, _altitude);    
    LLA1.setPosition(locationLat,locationLon,locationAlt);
    LLA result2 = LLA1.toENU(_origin).toLLA();
    CPPUNIT_ASSERT_DOUBLES_EQUAL(locationLat,result2.getFirstCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(locationLon,result2.getSecondCoordinate(),tol);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(locationAlt,result2.getThirdCoordinate(),tol);
}
/**
 * @brief Coordinate systems class library definition.
 * @file coordinateSystems.h
 * @version 19.09
 * @date September 24, 2019
 * @details Library of classes representing various coordinate systems and
 * providing the transformations between them. Coordinate systems represented
 * are: East-North-Up (ENU), Downrange-Crossrange-Above (DCA), Latitude-
 * Longitude-Altitude (LLA), Earth-Centered-Fixed (ECF), and Azimuth-Elevation-
 * Range (AER).
 * 
 * Version History:
 * Version 0.0 on December 5, 2013
 * Version 1.0 on January 13, 2014
 * Version 1.4 on June 6, 2014
 * Version 19.09 on September 24, 2019
 */

/**
 * Notices: Copyright 2020 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration. All
 * Rights Reserved.
 * 
 * Disclaimers:
 * No Warranty: THE SUBJECT SOFTWARE IS PROVIDED "AS IS" WITHOUT
 * ANY WARRANTY OF ANY KIND, EITHER EXPRESSED, IMPLIED, OR STATUTORY, INCLUDING,
 * BUT NOT LIMITED TO, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL CONFORM TO
 * SPECIFICATIONS, ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, OR FREEDOM FROM INFRINGEMENT, ANY WARRANTY THAT THE
 * SUBJECT SOFTWARE WILL BE ERROR FREE, OR ANY WARRANTY THAT DOCUMENTATION, IF
 * PROVIDED, WILL CONFORM TO THE SUBJECT SOFTWARE. THIS AGREEMENT DOES NOT, IN
 * ANY MANNER, CONSTITUTE AN ENDORSEMENT BY GOVERNMENT AGENCY OR ANY PRIOR
 * RECIPIENT OF ANY RESULTS, RESULTING DESIGNS, HARDWARE, SOFTWARE PRODUCTS OR
 * ANY OTHER APPLICATIONS RESULTING FROM USE OF THE SUBJECT SOFTWARE.  FURTHER,
 * GOVERNMENT AGENCY DISCLAIMS ALL WARRANTIES AND LIABILITIES REGARDING
 * THIRD-PARTY SOFTWARE, IF PRESENT IN THE ORIGINAL SOFTWARE, AND DISTRIBUTES IT
 * "AS IS."
 * 
 * Waiver and Indemnity: RECIPIENT AGREES TO WAIVE ANY AND ALL CLAIMS AGAINST
 * THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS, AS WELL AS
 * ANY PRIOR RECIPIENT.  IF RECIPIENT'S USE OF THE SUBJECT SOFTWARE RESULTS IN
 * ANY LIABILITIES, DEMANDS, DAMAGES, EXPENSES OR LOSSES ARISING FROM SUCH USE,
 * INCLUDING ANY DAMAGES FROM PRODUCTS BASED ON, OR RESULTING FROM, RECIPIENT'S
 * USE OF THE SUBJECT SOFTWARE, RECIPIENT SHALL INDEMNIFY AND HOLD HARMLESS THE
 * UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS, AS WELL AS ANY
 * PRIOR RECIPIENT, TO THE EXTENT PERMITTED BY LAW.  RECIPIENT'S SOLE REMEDY FOR
 * ANY SUCH MATTER SHALL BE THE IMMEDIATE, UNILATERAL TERMINATION OF THIS
 * AGREEMENT.
 */

#ifndef COORDINATESYSTEMS_H
#define	COORDINATESYSTEMS_H

#include <stdexcept>
#include <vector>

namespace coordinateSystems {

#define PI 3.14159265359
#define rad2deg 180/PI
#define deg2rad PI/180

class positionVector; //forward declaration of class positionVector
class Cartesian; //forward declaration of class positionVector
class Spherical; //forward declaration of class positionVector
class earthCentered; //forward declaration of class earthCentered
class earthFixed; //forward declaration of class earthFixed
class ENU; //forward declaration of class ENU
class DCA; //forward declaration of class DCA
class LLA; //forward declaration of class LLA
class ECF; //forward declaration of class ECF
class AER; //forward declaration of class AER

/**
 *  @brief Position vector abstract base class.
*/
class positionVector {
public:
/**
 *  @brief Coordinate system constructor.
 *  @param  _first:  first coordinate (optional, default  = 0.0).
 *  @param  _second: second coordinate (optional, default  = 0.0).
 *  @param  _third:  third coordinate (optional, default  = 0.0).
 *  @return class instance.
 *
 *  Creates an instance of the coordinate system class and sets the position
 *  vector coordinates in the coordinate system.
*/
    positionVector(double _first = 0.0, double _second = 0.0, double _third = 0.0);
    virtual ~positionVector();
/**
 *  @brief Set the coordinates.
 *  @param  _first:  first coordinate.
 *  @param  _second: second coordinate.
 *  @param  _third:  third coordinate.
 *  @return nothing
 *
 *  This sets the position vector coordinates in the coordinate system.
*/
    void setPosition(double _first, double _second, double _third);
/**
 *  @brief Set the first coordinate.
 *  @param  _first:  first coordinate.
 *  @return nothing
 *
 *  This sets the position vector first coordinate in the coordinate system.
*/
    void setFirstCoordinate(double _first);
/**
 *  @brief Set the second coordinate.
 *  @param  _second:  second coordinate.
 *  @return nothing
 *
 *  This sets the position vector second coordinate in the coordinate system.
*/
    void setSecondCoordinate(double _second);
/**
 *  @brief Set the third coordinate.
 *  @param  _third:  third coordinate.
 *  @return nothing
 *
 *  This sets the position vector first coordinate in the coordinate system.
*/
    void setThirdCoordinate(double _third);

/**
 *  @brief Get the coordinates.
 *  @return a vector of 3 double values for the position vector coordinates.
 *
 *  This gets the position vector coordinates from the coordinate system.
*/
    std::vector<double> getPosition(void);
/**
 *  @brief Get the first coordinate.
 *  @return first coordinate.
 *
 *  This gets the position vector first coordinate from the coordinate system.
*/
    double getFirstCoordinate(void);
/**
 *  @brief Get the second coordinate.
 *  @return second coordinate.
 *
 *  This gets the position vector second coordinate from the coordinate system.
*/
    double getSecondCoordinate(void);
/**
 *  @brief Get the third coordinate.
 *  @return third coordinate.
 *
 *  This gets the position vector third coordinate from the coordinate system.
*/
    double getThirdCoordinate(void);
/**
 *  @brief Get the magnitude of the position vector.
 *  @return vector magnitude.
*/
    virtual double getMagnitude(void) = 0; // declare pure virtual function for abstract class
protected:
    double x, y, z;
};

/**
 *  @brief Cartesian coordinate system base class.
*/
class Cartesian: public positionVector {
public:
/**
 *  @brief Coordinate system constructor.
 *  @param  _first:  first coordinate (optional, default  = 0.0).
 *  @param  _second: second coordinate (optional, default  = 0.0).
 *  @param  _third:  third coordinate (optional, default  = 0.0).
 *  @return class instance.
 *
 *  Creates an instance of the coordinate system class and sets the position
 *  vector coordinates in the coordinate system.
*/
    Cartesian(double _first = 0.0, double _second = 0.0, double _third = 0.0);
    virtual ~Cartesian();
/**
 *  @brief Get the magnitude of the position vector.
 *  @return vector magnitude.
*/
    double getMagnitude(void);
};

/**
 *  @brief Spherical coordinate system base class.
*/
class Spherical: public positionVector {
public:
/**
 *  @brief Coordinate system constructor.
 *  @param  _first:  first coordinate (optional, default  = 0.0).
 *  @param  _second: second coordinate (optional, default  = 0.0).
 *  @param  _third:  third coordinate (optional, default  = 0.0).
 *  @return class instance.
 *
 *  Creates an instance of the coordinate system class and sets the position
 *  vector coordinates in the coordinate system.
*/
    Spherical(double _first = 0.0, double _second = 0.0, double _third = 0.0);
    virtual ~Spherical();
/**
 *  @brief Get the magnitude of the position vector.
 *  @return vector magnitude.
*/
    virtual double getMagnitude(void);
};

/**
 * @brief Abstract base class for Earth-centered coordinate systems.
 * 
 * Provides bases for Earth-Centered-Fixed (ECF) and Latitude-Longitude-
 * Altitude (LLA) coordinate frames.
*/
class earthCentered {
public:
    earthCentered();
    virtual ~earthCentered();
    virtual ENU toENU(LLA _origin) = 0; // declare pure virtual function for abstract class
    virtual ENU toENU(double _latitude, double _longitude, double _altitude) = 0; // declare pure virtual function for abstract class
    virtual DCA toDCA(LLA _origin, double _heading) = 0; // declare pure virtual function for abstract class
    virtual DCA toDCA(double _latitude, double _longitude, double _altitude, double _heading) = 0; // declare pure virtual function for abstract class
    virtual AER toAER(LLA _origin, double _heading) = 0; // declare pure virtual function for abstract class
    virtual AER toAER(double _latitude, double _longitude, double _altitude, double _heading) = 0; // declare pure virtual function for abstract class
protected:
    //WGS84
    static const double a = 6378137.0; //Earth elipsoid semi-major axis in meters
    static const double e2 = 0.00669437999014; //Earth elipsoid eccentricity squared
    static const double latTol = 0.00001; //tolerance for latitude convergence
};

/**
 * @brief Earth-Centered-Fixed (ECF) Cartesian coordinate system.
*/
class ECF: public Cartesian, public earthCentered {
public:
/**
 *  @brief Coordinate system constructor.
 *  @param  _X: X coordinate in meters (optional, default  = 0.0).
 *  @param  _Y: Y coordinate in meters (optional, default  = 0.0).
 *  @param  _Z: Z coordinate in meters (optional, default  = 0.0).
 *  @return class instance.
 *
 *  Creates an instance of the coordinate system class and sets the position
 *  vector coordinates in the coordinate system.
*/
    ECF (double _X = 0.0, double _Y = 0.0, double _Z = 0.0);
    virtual ~ECF();
/**
 * @brief Coordinate conversion to East-North_Up (ENU) system.
 * @param _origin: Defines origin for ENU frame (instance of LLA).
 * @return Instance of ENU.
 */
    ENU toENU(LLA _origin);
/**
 * @brief Coordinate conversion to East-North_Up (ENU) system.
 * @param _latitude: Latitude of the ENU frame origin in degrees.
 * @param _longitude: Longitude of the ENU frame origin in degrees.
 * @param _altitude: Altitude of the ENU frame origin above a reference datum
 * in meters
 * @return Instance of ENU.
 */
    ENU toENU(double _latitude, double _longitude, double _altitude);
/**
 * @brief Coordinate conversion to DownRange-CrossRange-Above (DCA) system.
 * @param _origin: Defines origin for DCA frame (instance of LLA).
 * @param _heading: Heading of the DCA frame measured from True North in degrees.
 * @return Instance of DCA.
 */
    DCA toDCA(LLA _origin, double _heading = 0.0);
/**
 * @brief Coordinate conversion to DownRange-CrossRange-Above (DCA) system.
 * @param _latitude: Latitude of the DCA frame origin in degrees.
 * @param _longitude: Longitude of the DCA frame origin in degrees.
 * @param _altitude: Altitude of the DCA frame origin above a reference datum
 * in meters
 * @param _heading: Heading of the DCA frame measured from True North in degrees.
 * @return Instance of DCA.
 */
    DCA toDCA(double _latitude, double _longitude, double _altitude, double _heading = 0.0);
/**
 * @brief Coordinate conversion to Azimuth-Elevation-Range (AER) system.
 * @param _origin: Defines origin for AER frame (instance of LLA).
 * @param _heading: Heading of the AER frame measured from True North in degrees.
 * @return Instance of AER.
 */
    AER toAER(LLA _origin, double _heading = 0.0);
/**
 * @brief Coordinate conversion to Azimuth-Elevation-Range (AER) system.
 * @param _latitude: Latitude of the AER frame origin in degrees.
 * @param _longitude: Longitude of the AER frame origin in degrees.
 * @param _altitude: Altitude of the AER frame origin above a reference datum
 * in meters
 * @param _heading: Heading of the AER frame measured from True North in degrees.
 * @return Instance of AER.
 */
    AER toAER(double _latitude, double _longitude, double _altitude, double _heading = 0.0);
/**
 * @brief Coordinate conversion to Latitude-Longitude-Altitude (LLA) system.
 * @return Instance of LLA.
 */
    LLA toLLA(void);
};

/**
*  @brief Latitude-Longitude-Altitude (LLA) spherical coordinate system.
*/
class LLA: public Spherical, public earthCentered {
public:
/**
 *  @brief Coordinate system constructor.
 *  @param  _latitude: Latitude in degrees (optional, default  = 0.0).
 *  @param  _longitude: Longitude in degrees (optional, default  = 0.0).
 *  @param  _altitude: Altitude above reference datum in meters (optional, default  = 0.0).
 *  @return class instance.
 *
 *  Creates an instance of the coordinate system class and sets the position
 *  vector coordinates in the coordinate system.
*/
    LLA (double _latitude = 0.0, double _longitude = 0.0, double _altitude = 0.0);
    virtual ~LLA();
/**
 * @brief overrides position vector magnitude
 * @return ECF position magnitude
 * 
 * For spherical coordinates, magnitude is the third component (i.e. radius)
 * For LLA, the third component is altitude above a reference datum, so
 * magnitude is really measured from the center of the Earth.
 */
    double getMagnitude(void);
/**
 * @brief Coordinate conversion to East-North_Up (ENU) system.
 * @param _origin: Defines origin for ENU frame (instance of LLA).
 * @return Instance of ENU.
 */
    ENU toENU(LLA _origin);
/**
 * @brief Coordinate conversion to East-North_Up (ENU) system.
 * @param _latitude: Latitude of the ENU frame origin in degrees.
 * @param _longitude: Longitude of the ENU frame origin in degrees.
 * @param _altitude: Altitude of the ENU frame origin above a reference datum
 * in meters
 * @return Instance of ENU.
 */
    ENU toENU(double _latitude, double _longitude, double _altitude);
/**
 * @brief Coordinate conversion to DownRange-CrossRange-Above (DCA) system.
 * @param _origin: Defines origin for DCA frame (instance of LLA).
 * @param _heading: Heading of the DCA frame measured from True North in degrees.
 * @return Instance of DCA.
 */
    DCA toDCA(LLA _origin, double _heading = 0.0);
/**
 * @brief Coordinate conversion to DownRange-CrossRange-Above (DCA) system.
 * @param _latitude: Latitude of the DCA frame origin in degrees.
 * @param _longitude: Longitude of the DCA frame origin in degrees.
 * @param _altitude: Altitude of the DCA frame origin above a reference datum
 * in meters
 * @param _heading: Heading of the DCA frame measured from True North in degrees.
 * @return Instance of DCA.
 */
    DCA toDCA(double _latitude, double _longitude, double _altitude, double _heading = 0.0);
/**
 * @brief Coordinate conversion to Azimuth-Elevation-Range (AER) system.
 * @param _origin: Defines origin for AER frame (instance of LLA).
 * @param _heading: Heading of the AER frame measured from True North in degrees.
 * @return Instance of AER.
 */
    AER toAER(LLA _origin, double _heading = 0.0);
/**
 * @brief Coordinate conversion to Azimuth-Elevation-Range (AER) system.
 * @param _latitude: Latitude of the AER frame origin in degrees.
 * @param _longitude: Longitude of the AER frame origin in degrees.
 * @param _altitude: Altitude of the AER frame origin above a reference datum
 * in meters
 * @param _heading: Heading of the AER frame measured from True North in degrees.
 * @return Instance of AER.
 */
    AER toAER(double _latitude, double _longitude, double _altitude, double _heading = 0.0);
/**
 * @brief Coordinate conversion to Earth-Centered-Fixed (ECF) system.
 * @return Instance of ECF.
 */
    ECF toECF(void);
};

/**
 * @brief Abstract base class for Earth fixed coordinate frames.
 * 
 * Earth-fixed meaning on, above, or below the Earth surface and rotating
 *    with the Earth.
 * NOT Earth Centered
 * Have an origin defined by LLA
 * Have a heading that is only made public in children classes needing it.
 * 
*/
class earthFixed {
public:
    earthFixed ();
    earthFixed (LLA _origin, double _heading = 0.0);
    earthFixed (double _latitude, double _longitude, double _altitude, double _heading = 0.0);
    virtual ~earthFixed();
/**
 * @brief Sets the origin of the Earth-fixed coordinate system.
 * @param _origin: Defines origin for coordinate frame (instance of LLA).
 * @return Nothing.
 */
    void setOrigin(LLA _origin);
/**
 * @brief Sets the origin of the Earth-fixed coordinate system.
 * @param _latitude: Latitude of the Earth-Fixed frame origin in degrees.
 * @param _longitude: Longitude of the Earth-Fixed frame origin in degrees.
 * @param _altitude: Altitude of the Earth-fixed frame origin above a reference
 * datum in meters.
 * @return Nothing.
 */
    void setOrigin(double _latitude, double _longitude, double _altitude);
/**
 * @brief Gets the origin of the Earth-fixed coordinate system.
 * @return Instance of LLA.
 */
    LLA getOrigin(void);
    virtual ECF toECF(void) = 0; // declare pure virtual function for abstract class
    virtual LLA toLLA(void) = 0; // declare pure virtual function for abstract class
protected:
    LLA origin;
    bool originSet;
    double heading;
/**
 * @brief Sets the true heading of the earth fixed coordinate system.
 * @param _heading: Heading of the earth fixed frame measured from True North
 * in degrees.
 * @return Nothing.
 */
    void setHeading(double _heading);
/**
 * @brief Gets the true heading of the earth fixed coordinate system.
 * @return Heading of the earth fixed frame measured from True North in degrees.
 */
    double getHeading(void);
};

/**
 * @brief East-North-Up (ENU) Cartesian coordinate system.
 * 
 * This is an Earth-Fixed frame, meaning on, above, or below the Earth surface
 * and rotating with the Earth.
 * NOT Earth-centered.
 * Has an origin defined by LLA.
*/
class ENU: public Cartesian, public earthFixed {
public:
/**
 * @brief Coordinate system constructor.
 * @param _east: East coordinate in meters (optional, default  = 0.0).
 * @param _north: North coordinate in meters (optional, default  = 0.0).
 * @param _up: Up coordinate in meters (optional, default  = 0.0).
 * @return class instance.
 *
 *  Creates an instance of the coordinate system class and sets the position
 *  vector coordinates in the coordinate system.
 */
    ENU (double _east = 0.0, double _north = 0.0, double _up = 0.0);
/**
 * @brief Coordinate system constructor.
 * @param _origin: Defines origin for coordinate frame (instance of LLA).
 * @return class instance.
 * 
 *  Creates an instance of the coordinate system class and sets the origin of
 *  the coordinate system. Sets the default position vector [0.0, 0.0, 0.0].
 */
    ENU (LLA _origin);
/**
 * @brief Coordinate system constructor.
 * @param _east: East coordinate in meters.
 * @param _north: North coordinate in meters.
 * @param _up: Up coordinate in meters.
 * @param _origin: Defines origin for coordinate frame (instance of LLA).
 * @return class instance.
 * 
 *  Creates an instance of the coordinate system class, sets the position
 *  vector coordinates in the coordinate system, and sets the origin of the
 *  coordinate system.
 */
    ENU (double _east, double _north, double _up, LLA _origin);
/**
 * @brief Coordinate system constructor.
 * @param _east: East coordinate in meters.
 * @param _north: North coordinate in meters.
 * @param _up: Up coordinate in meters.
 * @param _latitude: Latitude of the Earth-Fixed frame origin in degrees.
 * @param _longitude: Longitude of the Earth-Fixed frame origin in degrees.
 * @param _altitude: Altitude of the Earth-fixed frame origin above a reference
 * datum in meters.
 * @return class instance.
 * 
 *  Creates an instance of the coordinate system class, sets the position
 *  vector coordinates in the coordinate system, and sets the origin of the
 *  coordinate system.
 */
    ENU (double _east, double _north, double _up, double _latitude, double _longitude, double _altitude);
    virtual ~ENU();
/**
 * @brief Coordinate conversion to Earth-Centered-Fixed (ECF) system.
 * @return Instance of ECF.
 * 
 * Throws a standard runtime exception if the origin is not set.
 */
    ECF toECF(void) throw (std::exception);
/**
 * @brief Coordinate conversion to Latitude-Longitude-Altitude (LLA) system.
 * @return Instance of LLA.
 * 
 * Throws a standard runtime exception if the origin is not set.
 */
    LLA toLLA(void) throw (std::exception);
/**
 * @brief Coordinate conversion to DownRange-CrossRange-Above (DCA) system.
 * @param _heading: Heading of the DCA frame measured from True North in degrees.
 * @return Instance of DCA.
 */
    DCA toDCA(double _heading);
/**
 * @brief Coordinate conversion to Azimuth-Elevation-Range (AER) system.
 * @param _heading: Heading of the AER frame measured from True North in degrees.
 * @return Instance of AER.
 */
    AER toAER(double _heading);
};

/**
 * @brief DownRange-CrossRange-Above (DCA) Cartesian coordinate system.
 * 
 * This is an Earth-Fixed frame, meaning on, above, or below the Earth surface
 * and rotating with the Earth.
 * NOT Earth-centered.
 * Has an origin defined by LLA.
 * Has a down range heading measured from True North.
*/
class DCA: public Cartesian, public earthFixed {
public:
/**
 * @brief Coordinate system constructor.
 * @param _downRange: DownRange coordinate in meters (optional, default  = 0.0).
 * @param _crossRange: CrossRange coordinate in meters (optional, default  = 0.0).
 * @param _above: Above coordinate in meters (optional, default  = 0.0).
 * @param _heading: Heading of the DCA frame measured from True North in degrees.
 * (optional, default  = 0.0).
 * @return class instance.
 *
 *  Creates an instance of the coordinate system class and sets the position
 *  vector coordinates in the coordinate system.
 */
    DCA (double _downRange = 0.0, double _crossRange = 0.0, double _above = 0.0, double _heading = 0.0);
/**
 * @brief Coordinate system constructor.
 * @param _origin: Defines origin for coordinate frame (instance of LLA).
 * @param _heading: Heading of the DCA frame measured from True North in degrees.
 * (optional, default  = 0.0).
 * @return class instance.
 * 
 *  Creates an instance of the coordinate system class and sets the origin of
 *  the coordinate system. Sets the default position vector [0.0, 0.0, 0.0].
 */
    DCA (LLA _origin, double _heading = 0.0);
/**
 * @brief Coordinate system constructor.
 * @param _downRange: DownRange coordinate in meters.
 * @param _crossRange: CrossRange coordinate in meters.
 * @param _above: Above coordinate in meters.
 * @param _origin: Defines origin for coordinate frame (instance of LLA).
 * @param _heading: Heading of the DCA frame measured from True North in degrees.
 * (optional, default  = 0.0).
 * @return class instance.
 * 
 *  Creates an instance of the coordinate system class, sets the position
 *  vector coordinates in the coordinate system, sets the origin of the
 *  coordinate system, and the true heading of the DownRange direction.
 */
    DCA (double _downRange, double _crossRange, double _above, LLA _origin, double _heading = 0.0);
/**
 * @brief Coordinate system constructor.
 * @param _downRange: DownRange coordinate in meters.
 * @param _crossRange: CrossRange coordinate in meters.
 * @param _above: Above coordinate in meters.
 * @param _latitude: Latitude of the Earth-Fixed frame origin in degrees.
 * @param _longitude: Longitude of the Earth-Fixed frame origin in degrees.
 * @param _altitude: Altitude of the Earth-fixed frame origin above a reference
 * datum in meters.
 * @param _heading: Heading of the DCA frame measured from True North in degrees.
 * (optional, default  = 0.0).
 * @return class instance.
 * 
 *  Creates an instance of the coordinate system class, sets the position
 *  vector coordinates in the coordinate system, sets the origin of the
 *  coordinate system, and the true heading of the DownRange direction.
 */
    DCA (double _downRange, double _crossRange, double _above, double _latitude, double _longitude, double _altitude, double _heading = 0.0);
    virtual ~DCA();
/**
 * @brief Use inherited setHeading(heading) method from earthFixed class as a
 * public method.
 */
    using earthFixed::setHeading;
/**
 * @brief Use inherited getHeading() method from earthFixed class as a public
 * method.
 */
    using earthFixed::getHeading;
/**
 * @brief Coordinate conversion to Earth-Centered-Fixed (ECF) system.
 * @return Instance of ECF.
 * 
 * Throws a standard runtime exception if the origin is not set.
 */
    ECF toECF(void) throw (std::exception);
/**
 * @brief Coordinate conversion to Latitude-Longitude-Altitude (LLA) system.
 * @return Instance of LLA.
 * 
 * Throws a standard runtime exception if the origin is not set.
 */
    LLA toLLA(void) throw (std::exception);
/**
 * @brief Coordinate conversion to East_North-Up (ENU) system.
 * @return Instance of ENU.
 */
    ENU toENU(void);
/**
 * @brief Coordinate conversion to Azimuth-Elevation-Range (AER) system.
 * @return Instance of AER.
 */
    AER toAER(void);
};

/**
 * @brief Azimuth-Elevation-Range (AER) spherical coordinate system.
 * 
 * This is an Earth-Fixed frame, meaning on, above, or below the Earth surface
 * and rotating with the Earth.
 * NOT Earth-centered.
 * Has an origin defined by LLA.
*/
class AER: public Spherical, public earthFixed {
public:
/**
 * @brief Coordinate system constructor.
 * @param _azimuth: Azimuth angle in degrees (optional, default  = 0.0).
 * @param _elevation: Elevation angle in degrees (optional, default  = 0.0).
 * @param _range: Range coordinate in meters (optional, default  = 0.0).
 * @param _heading: Heading of the AER frame measured from True North in degrees.
 * (optional, default  = 0.0).
 * @return class instance.
 *
 *  Creates an instance of the coordinate system class and sets the position
 *  vector coordinates in the coordinate system.
 */
    AER (double _azimuth = 0.0, double _elevation = 0.0, double _range = 0.0, double _heading = 0.0);
/**
 * @brief Coordinate system constructor.
 * @param _origin: Defines origin for coordinate frame (instance of LLA).
 * @param _heading: Heading of the AER frame measured from True North in degrees.
 * (optional, default  = 0.0).
 * @return class instance.
 * 
 *  Creates an instance of the coordinate system class and sets the origin of
 *  the coordinate system. Sets the default position vector [0.0, 0.0, 0.0].
 */
    AER (LLA _origin, double _heading = 0.0);
/**
 * @brief Coordinate system constructor.
 * @param _azimuth: Azimuth angle in degrees.
 * @param _elevation: Elevation angle in degrees.
 * @param _range: Range coordinate in meters.
 * @param _origin: Defines origin for coordinate frame (instance of LLA).
 * @param _heading: Heading of the AER frame measured from True North in degrees.
 * (optional, default  = 0.0).
 * @return class instance.
 * 
 *  Creates an instance of the coordinate system class, sets the position
 *  vector coordinates in the coordinate system, sets the origin of the
 *  coordinate system, and the true heading of the DownRange direction.
 */
    AER (double _azimuth, double _elevation, double _range, LLA _origin, double _heading = 0.0);
/**
 * @brief Coordinate system constructor.
 * @param _azimuth: Azimuth angle in degrees.
 * @param _elevation: Elevation angle in degrees.
 * @param _range: Range coordinate in meters.
 * @param _latitude: Latitude of the Earth-Fixed frame origin in degrees.
 * @param _longitude: Longitude of the Earth-Fixed frame origin in degrees.
 * @param _altitude: Altitude of the Earth-fixed frame origin above a reference
 * datum in meters.
 * @param _heading: Heading of the AER frame measured from True North in degrees.
 * (optional, default  = 0.0).
 * @return class instance.
 * 
 *  Creates an instance of the coordinate system class, sets the position
 *  vector coordinates in the coordinate system, sets the origin of the
 *  coordinate system, and the true heading of the DownRange direction.
 */
    AER (double _azimuth, double _elevation, double _range, double _latitude, double _longitude, double _altitude, double _heading = 0.0);
    virtual ~AER();
/**
 * @brief Use inherited setHeading(heading) method from earthFixed class as a
 * public method.
 */
    using earthFixed::setHeading;
/**
 * @brief Use inherited getHeading() method from earthFixed class as a public
 * method.
 */
    using earthFixed::getHeading;
/**
 * @brief Coordinate conversion to Earth-Centered-Fixed (ECF) system.
 * @return Instance of ECF.
 * 
 * Throws a standard runtime exception if the origin is not set.
 */
    ECF toECF(void) throw (std::exception);
/**
 * @brief Coordinate conversion to Latitude-Longitude-Altitude (LLA) system.
 * @return Instance of LLA.
 * 
 * Throws a standard runtime exception if the origin is not set.
 */
    LLA toLLA(void) throw (std::exception);
/**
 * @brief Coordinate conversion to East_North-Up (ENU) system.
 * @return Instance of ENU.
 */
    ENU toENU(void);
/**
 * @brief Coordinate conversion to DownRange-CrossRange-Above (DCA) system.
 * @return Instance of DCA.
 */
    DCA toDCA(void);
};
}
#endif	/* COORDINATESYSTEMS_H */

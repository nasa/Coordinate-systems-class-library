/**
 * @brief Coordinate systems class library implementation.
 * @file coordinateSystems.cpp
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

#include <math.h>
#include "coordinateSystems.h"

using namespace coordinateSystems;

/***** positionVector *********************************************************/
positionVector::positionVector(double first, double second, double third) {
    this->setPosition(first,second,third);
}
positionVector::~positionVector() {
}
void positionVector::setPosition(double first, double second, double third) {
    x = first;
    y = second;
    z = third;
}
void positionVector::setFirstCoordinate(double first){
    x = first;
}
void positionVector::setSecondCoordinate(double second){
    y = second;
}
void positionVector::setThirdCoordinate(double third){
    z = third;
}
std::vector<double> positionVector::getPosition(){
    std::vector<double> position;
    
    position.push_back(x);
    position.push_back(y);
    position.push_back(z);
    
    return position;
}
double positionVector::getFirstCoordinate(){
    return x;
}
double positionVector::getSecondCoordinate(){
    return y;
}
double positionVector::getThirdCoordinate(){
    return z;
}
/***** Cartesian **************************************************************/
Cartesian::Cartesian(double first, double second, double third) : positionVector(first,second,third){
}
Cartesian::~Cartesian() {
}
double Cartesian::getMagnitude(){
    return sqrt(pow(x,2)+pow(y,2)+pow(z,2));
}
/***** Spherical **************************************************************/
Spherical::Spherical(double first, double second, double third) : positionVector(first,second,third){
}
Spherical::~Spherical() {
}
double Spherical::getMagnitude(){
    return z;
}
/***** earthCentered **********************************************************/
earthCentered::earthCentered(){
}
earthCentered::~earthCentered(){
}
/***** ECF ********************************************************************/
ECF::ECF(double X, double Y, double Z) : Cartesian(X,Y,Z), earthCentered(){
}
ECF::~ECF() {
}
ENU ECF::toENU(LLA origin){
    double east, north, up;
    double dx, dy, dz;
    double lat, lon;
    
    ECF originECF = origin.toECF();
    dx = x-originECF.getFirstCoordinate();
    dy = y-originECF.getSecondCoordinate();
    dz = z-originECF.getThirdCoordinate();
    lat = origin.getFirstCoordinate()*deg2rad;
    lon = origin.getSecondCoordinate()*deg2rad;    
 
    east = -dx*sin(lon) + dy*cos(lon);
    north = -dx*sin(lat)*cos(lon) - dy*sin(lat)*sin(lon) + dz*cos(lat);
    up =  dx*cos(lat)*cos(lon) + dy*cos(lat)*sin(lon) + dz*sin(lat);
    
    return ENU(east,north,up,origin);
}
ENU ECF::toENU(double latitude, double longitude, double altitude){
    LLA latLonAlt(latitude,longitude,altitude);
    return this->toENU(latLonAlt);
}
DCA ECF::toDCA(LLA origin, double heading){
    return this->toENU(origin).toDCA(heading);
}
DCA ECF::toDCA(double latitude, double longitude, double altitude, double heading){
    return this->toENU(latitude,longitude,altitude).toDCA(heading);
}
AER ECF::toAER(LLA origin, double heading){
    return this->toDCA(origin,heading).toAER();
}
AER ECF::toAER(double latitude, double longitude, double altitude, double heading){
    return this->toDCA(latitude,longitude,altitude,heading).toAER();
}
LLA ECF::toLLA(){
    double p = sqrt(pow(x,2)+pow(y,2));
    double lat,N;
    double latitude, longitude, altitude;
    
    if (p == 0) {
        longitude = 0.0; //undefined longitude
        latitude = (z > 0) ? PI/2 : -PI/2; //at the poles
        altitude = fabs(z) - sqrt(pow(a,2)*(1-e2)); // h = z - b;
    } else {      
        if (x == 0) {
            longitude = (y > 0) ? PI/2 : -PI/2;
        } else {
            longitude = atan2(y,x);
        }

        latitude = atan2(z,p); //initial guess for latitude
        do {
            lat = latitude;
            N = a / sqrt(1-e2*pow(sin(latitude),2));
            altitude = p / cos(latitude) - N;
            latitude = atan(z / (p*(1-e2*N / (N+altitude))));
        } while (fabs(lat-latitude) > latTol);

        //recompute altitude once latitude converges
        N = a / sqrt(1-e2*pow(sin(latitude),2));
        altitude = p / cos(latitude) - N;
    }
    
    return LLA(latitude*rad2deg,longitude*rad2deg,altitude);
}
/***** LLA ********************************************************************/
LLA::LLA (double latitude, double longitude, double altitude) :
Spherical(latitude,longitude,altitude), earthCentered(){
}
LLA::~LLA() {
}
double LLA::getMagnitude(){
    return this->toECF().getMagnitude();
}
ENU LLA::toENU(LLA origin){
    return this->toECF().toENU(origin);
}
ENU LLA::toENU(double latitude, double longitude, double altitude){
    return this->toECF().toENU(latitude,longitude,altitude);
}
DCA LLA::toDCA(LLA origin, double heading){
    return this->toECF().toDCA(origin,heading);
}
DCA LLA::toDCA(double latitude, double longitude, double altitude, double heading){
    return this->toECF().toDCA(latitude,longitude,altitude,heading);
}
AER LLA::toAER(LLA origin, double heading){
    return this->toDCA(origin,heading).toAER();
}
AER LLA::toAER(double latitude, double longitude, double altitude, double heading){
    return this->toDCA(latitude,longitude,altitude,heading).toAER();
}
ECF LLA::toECF(){
    double X, Y, Z;
    double N = a / sqrt(1-e2*pow(sin(x*deg2rad),2));
    X = (N + z)*cos(x*deg2rad)*cos(y*deg2rad);
    Y = (N + z)*cos(x*deg2rad)*sin(y*deg2rad);
    Z = (N*(1-e2) + z)*sin(x*deg2rad);
    return ECF(X,Y,Z);
}
/***** earthFixed *************************************************************/
earthFixed::earthFixed(){
    origin = LLA();
    originSet = false;
    heading = 0.0;
}
earthFixed::earthFixed(LLA latLonAlt, double h) {
    origin = latLonAlt;
    originSet = true;
    heading = h;
}
earthFixed::earthFixed(double latitude, double longitude, double altitude, double h) :
origin(latitude,longitude,altitude){
    originSet = true;
    heading = h;
}
earthFixed::~earthFixed() {
}
void earthFixed::setOrigin(LLA latLonAlt){
    origin = latLonAlt;
    originSet = true;
}
void earthFixed::setOrigin(double latitude, double longitude, double altitude){
    origin = LLA(latitude,longitude,altitude);
    originSet = true;
}
LLA earthFixed::getOrigin(){
    return origin;
}
void earthFixed::setHeading(double h){
    heading = h;
}
double earthFixed::getHeading(){
    return heading;
}
/***** ENU ********************************************************************/
ENU::ENU(double east, double north, double up) : Cartesian(east,north,up), earthFixed(){
}
ENU::ENU(LLA origin) : Cartesian(), earthFixed(origin){
}
ENU::ENU(double east, double north, double up, LLA origin) : Cartesian(east,north,up), earthFixed(origin){
}
ENU::ENU(double east, double north, double up, double latitude, double longitude, double altitude) :
Cartesian(east,north,up), earthFixed(latitude,longitude,altitude){
}
ENU::~ENU(){
}
ECF ENU::toECF() throw (std::exception){
    double X, Y, Z;
    double lat, lon;
    
    if (!originSet){
        throw std::runtime_error("Cannot convert to ECF, origin not set.");
    }
    
    ECF originECF = origin.toECF();
    lat = origin.getFirstCoordinate()*deg2rad;
    lon = origin.getSecondCoordinate()*deg2rad;
    
    X = -x*sin(lon) - y*sin(lat)*cos(lon) + z*cos(lat)*cos(lon) + originECF.getFirstCoordinate();
    Y =  x*cos(lon) - y*sin(lat)*sin(lon) + z*cos(lat)*sin(lon) + originECF.getSecondCoordinate();
    Z =  y*cos(lat) + z*sin(lat) + originECF.getThirdCoordinate();
    
    return ECF(X,Y,Z);
}
LLA ENU::toLLA() throw (std::exception){
    if (!originSet){
        throw std::runtime_error("Cannot convert to ECF, origin not set.");
    }
    return this->toECF().toLLA();
}
DCA ENU::toDCA(double h){
    double downRange, crossRange, above;
    downRange = x*sin(h*deg2rad) + y*cos(h*deg2rad);;
    crossRange = -x*cos(h*deg2rad) + y*sin(h*deg2rad);;
    above = z;

    DCA result(downRange,crossRange,above);
    result.setHeading(h);
    if (originSet){
        result.setOrigin(origin);
    }
    return result;
}
AER ENU::toAER(double h) {
    return this->toDCA(h).toAER();
}
/***** DCA ********************************************************************/
DCA::DCA(double downRange, double crossRange, double above, double h) :
Cartesian(downRange,crossRange,above), earthFixed(){
    heading = h;
}
DCA::DCA(LLA origin, double h) : Cartesian(), earthFixed(origin,h){
}
DCA::DCA(double downRange, double crossRange, double above, LLA origin, double h) :
Cartesian(downRange,crossRange,above), earthFixed(origin,h){
}
DCA::DCA(double downRange, double crossRange, double above, double latitude, double longitude, double altitude, double h) :
Cartesian(downRange,crossRange,above), earthFixed(latitude,longitude,altitude,h){
}
DCA::~DCA() {
}
ECF DCA::toECF() throw (std::exception){
    if (!originSet){
        throw std::runtime_error("Cannot convert to ECF, origin not set.");
    }
    return this->toENU().toECF();
}
LLA DCA::toLLA() throw (std::exception){
    if (!originSet){
        throw std::runtime_error("Cannot convert to ECF, origin not set.");
    }
    return this->toECF().toLLA();
}
ENU DCA::toENU(){
    double east, north, up;
    east = x*sin(heading*deg2rad) - y*cos(heading*deg2rad);
    north = x*cos(heading*deg2rad) + y*sin(heading*deg2rad);
    up = z;
    if (originSet){
        return ENU(east,north,up,origin);
    } else {
        return ENU(east,north,up);
    }
}
AER DCA::toAER(){
    double azimuth, elevation, range;
    double p = sqrt(pow(x,2)+pow(y,2));
    
    range = this->getMagnitude();
    if (range == 0) {
        azimuth = 0.0; //undefined azimuth
        elevation = 0.0; //undefined elevation
    } else if (p == 0) {
        azimuth = 0.0; //undefined azimuth
        elevation = (z > 0) ? PI/2 : -PI/2; //vertical
    } else {
        azimuth = atan2(-y,x);
        elevation = atan2(z,p);
    }
    if (originSet){
        return AER(azimuth*rad2deg,elevation*rad2deg,range,origin,heading);
    } else {
        return AER(azimuth*rad2deg,elevation*rad2deg,range,heading);
    }
}
/***** AER ********************************************************************/
AER::AER(double azimuth, double elevation, double range, double h) : 
Spherical(azimuth,elevation,range), earthFixed() {
    heading = h;
}
AER::AER(LLA origin, double h) : Spherical(), earthFixed(origin,h){
}
AER::AER(double azimuth, double elevation, double range, LLA origin, double h) :
Spherical(azimuth,elevation,range), earthFixed(origin,h){
}
AER::AER(double azimuth, double elevation, double range, double latitude, double longitude, double altitude, double h) :
Spherical(azimuth,elevation,range), earthFixed(latitude,longitude,altitude,h){
}
AER::~AER() {
}
ECF AER::toECF() throw (std::exception){
    if (!originSet){
        throw std::runtime_error("Cannot convert to ECF, origin not set.");
    }
    return this->toENU().toECF();
}
LLA AER::toLLA() throw (std::exception){
    if (!originSet){
        throw std::runtime_error("Cannot convert to ECF, origin not set.");
    }
    return this->toECF().toLLA();
}
ENU AER::toENU(){
    return this->toDCA().toENU();
}
DCA AER::toDCA(){
    double downRange, crossRange, above;
    downRange = z*cos(x*deg2rad)*cos(y*deg2rad);
    crossRange = -z*sin(x*deg2rad)*cos(y*deg2rad);
    above = z*sin(y*deg2rad);
    if (originSet){
        return DCA(downRange,crossRange,above,origin,heading);
    } else {
        return DCA(downRange,crossRange,above,heading);
    }
}

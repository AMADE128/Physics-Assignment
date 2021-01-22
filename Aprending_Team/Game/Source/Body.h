#pragma once
#include "p2Point.h"

#define RADTODEG 57.29577958f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) PIXELS_PER_METER * m)
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

enum class BodyType
{

};

enum class BodyClass
{

};

enum class BodyState
{

};

class Body
{
public:


private:

	
};
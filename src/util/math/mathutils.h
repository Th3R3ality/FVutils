#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <optional>

#include "vec.h"
#include "matrix.h"

#define RAD2DEG 180.0 / M_PI;
#define DEG2RAD M_PI / 180.0;

namespace mathutils
{
	std::optional<ivec2> Project( fvec3 point );
	std::optional<ivec2> WorldToScreen( fvec3 point, matrix modelView, matrix projection, int screenWidth, int screenHeight );


	float wrapAngleTo180( float angle );
	fvec2 vec_wrapAngleTo180( fvec2 angle );
	float coterminal( float angle );
	fvec3 crossProduct( fvec3 p1, fvec3 p2 );
	//float shortestDistance( fvec3 p, fvec3 a, fvec3 b );
	fvec2 getAngles( fvec3 pos1, fvec3 pos2 );


	float radiantsToDeg( float x );
	float degToRadiants( float x );
}


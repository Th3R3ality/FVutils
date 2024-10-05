#include "mathutils.h"

#include <cmath>

namespace mathutils
{
	fvec4 Multiply(fvec4 v, matrix m) {
		return fvec4{
			v.x * m.m00 + v.y * m.m10 + v.z * m.m20 + v.w * m.m30,
			v.x * m.m01 + v.y * m.m11 + v.z * m.m21 + v.w * m.m31,
			v.x * m.m02 + v.y * m.m12 + v.z * m.m22 + v.w * m.m32,
			v.x * m.m03 + v.y * m.m13 + v.z * m.m23 + v.w * m.m33
		};
	}


	std::optional<ivec2> WorldToScreen( fvec3 point, matrix modelView, matrix projection, int screenWidth, int screenHeight )
	{

		fvec4 csp = ( ( fvec4{ point.x, point.y, point.z, 1.0f } * modelView ) * projection );

		// ndc = Native Device Coordinate
		fvec3 ndc{
			csp.x / csp.w,
			csp.y / csp.w,
			csp.z / csp.w
		};

		if ( ndc.z > 1 && ndc.z < 1.15 )
		{
			return ivec2(
				(int)( ( ( ndc.x + 1.0f ) / 2.0f ) * ( ( float )screenWidth ) ),
				(int)( ( ( 1.0f - ndc.y ) / 2.0f ) * ( ( float )screenHeight ) ) );
		}

		return std::nullopt;
	}

	float wrapAngleTo180( float angle )
	{
		angle = std::fmod( angle, 360.0f );
		if ( angle >= 180.0f )
		{
			angle -= 360.0f;
		}

		if ( angle < -180.0f )
		{
			angle += 360.0f;
		}

		return angle;
	}

	fvec2 vec_wrapAngleTo180( fvec2 angle )
	{
		return fvec2{
			wrapAngleTo180( angle.x ),
			wrapAngleTo180( angle.y ),
		};
	}

	float coterminal( float angle )
	{
		return std::fmod( angle, 180 ) < 0 ? angle + 170 : angle;
	}

	fvec3 crossProduct( fvec3 v1, fvec3 v2 )
	{
		return fvec3{
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
		};
	}

	//float shortestDistance( Vector3 p, Vector3 a, Vector3 b )
	//{

	//	Vector3 ab{ b.x - a.x, b.y - a.y, b.z - a.z };
	//	Vector3 cp = crossProduct(
	//		Vector3{ p.x - a.x, p.y - a.y, p.z - a.z },
	//		ab
	//	);

	//	return magnitude( cp ) / magnitude( ab );
	//}

	fvec2 getAngles( fvec3 pos, fvec3 pos1 )
	{
		double d_x = pos1.x - pos.x;
		double d_y = pos1.y - pos.y;
		double d_z = pos1.z - pos.z;

		double hypothenuse = sqrt( d_x * d_x + d_z * d_z );
		float yaw = radiantsToDeg( atan2( d_z, d_x ) ) - 90.f;
		float pitch = radiantsToDeg( -atan2( d_y, hypothenuse ) );

		return fvec2( yaw, pitch );
	}

	float radiantsToDeg( float x )
	{
		return x * 180.f / M_PI;
	}

	float degToRadiants( float x )
	{
		return x * M_PI / 180.f;
	}


}
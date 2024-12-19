#pragma once
#include "../../imgui/imgui.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>


#include "matrix.h"

template <class T>
struct vec3;

template <class T>
struct vec2
{
	T x, y;

	constexpr vec2() { x = 0; y = 0; }
	constexpr vec2( const T& v ) { x = v; y = v; }
	constexpr vec2( const T& a, const T& b ) { x = a; y = b; }
	constexpr vec2( const T* a ) { x = a[ 0 ]; y = a[ 1 ]; }
	constexpr vec2( const vec3<T> v ) { x = v.x; y = v.y; }

	//constexpr vec2(const float(*a)[2]) { x = a[0]; y = a[1];  }
#ifdef IMGUI_API
	constexpr vec2( const ImVec2 b ) { x = static_cast< T >( b.x ); y = static_cast< T >( b.y ); };
#endif
	vec2 operator+( const vec2& v ) const { return { x + v.x, y + v.y }; }
	vec2 operator-( const vec2& v ) const { return { x - v.x, y - v.y }; }
	vec2 operator*( const vec2& v ) const { return { x * v.x, y * v.y }; }
	vec2 operator/( const vec2& v ) const { return { x / v.x, y / v.y }; }
	void operator=( const vec2& v ) { x = v.x; y = v.y; }

	vec2 operator+( const T& v ) const { return { x + v, y + v }; }
	vec2 operator-( const T& v ) const { return { x - v, y - v }; }
	vec2 operator*( const T& v ) const { return { x * v, y * v }; }
	vec2 operator/( const T& v ) const { return { x / v, y / v }; }

	vec2 operator+=( const vec2& v ) { return { x += v.x, y += v.y }; }
	vec2 operator-=( const vec2& v ) { return { x -= v.x, y -= v.y }; }
	vec2 operator*=( const vec2& v ) { return { x *= v.x, y *= v.y }; }
	vec2 operator/=( const vec2& v ) { return { x /= v.x, y /= v.y }; }
	bool operator==( const vec2& v ) const { return  x == v.x && y == v.y; }
	bool operator!=( const vec2& v ) const { return  x != v.x || y != v.y; }

	vec2 operator+=( const T& v ) { return { x += v, y += v }; }
	vec2 operator-=( const T& v ) { return { x -= v, y -= v }; }
	vec2 operator*=( const T& v ) { return { x *= v, y *= v }; }
	vec2 operator/=( const T& v ) { return { x /= v, y /= v }; }

#ifdef IMGUI_API
	operator ImVec2() { return ImVec2( ( float )x, ( float )y ); };
	operator ImVec2() const { return ImVec2( ( float )x, ( float )y ); };
#endif

	operator vec2<int>() { return { ( int )x, ( int )y }; }
	operator vec2<float>() { return { ( float )x, ( float )y }; }

	T& operator[]( const int index ) const
	{
		return ( ( T* )&x )[ index ];
	}

	T sum() const noexcept
	{
		return x + y;
	}
	float mag() const
	{
		return sqrtf( x * x + y * y );
	}
	T magsq() const
	{ //magnitude squared
		return ( x * x + y * y );
	}
	float dot( const vec2& vec ) const
	{
		return x * vec.x + y * vec.y;
	}
	float normalize()
	{
		const float length = this->mag();
		float ilength;

		if ( length )
		{
			ilength = 1 / length;
			this->x *= ilength;
			this->y *= ilength;
		}

		return length;
	}
	float dist( const vec2& vec ) const
	{
		const vec2 sub = *this - vec;
		return sub.mag();
	}
	vec2 inverse() const
	{
		return { -x, -y };
	}
	void clamp( const T min, const T max )
	{
		if ( x < min )		x = min;
		else if ( x > max )	x = max;

		if ( y < min )		y = min;
		else if ( y > max )	y = max;
	}
	//expects radians
	vec2 fromAngle( float angle )
	{
		return { cos( angle ), sin( angle ) };
	}

};

using ivec2 = vec2<int>;
using fvec2 = vec2<float>;

template <class T>
struct vec3
{

	T x, y, z;

	constexpr vec3() { x = 0; y = 0, z = 0; }
	constexpr vec3( const T& v ) { x = v; y = v, z = v; }
	constexpr vec3( const T& a, const T& b, const T& c ) { x = a; y = b, z = c; }
	constexpr vec3( const float( *a )[ 3 ] ) { x = a[ 0 ]; y = a[ 1 ], z = a[ 2 ]; }
	constexpr vec3( const float* a ) { x = a[ 0 ]; y = a[ 1 ], z = a[ 2 ]; }

	//constexpr explicit vec3(const vec3<int>& v) { x = (int)v.x, y = (int)v.y; }

	vec3 operator+( const vec3& v ) const { return { x + v.x, y + v.y, z + v.z }; }
	vec3 operator-( const vec3& v ) const { return { x - v.x, y - v.y, z - v.z }; }
	vec3 operator*( const vec3& v ) const { return { x * v.x, y * v.y, z * v.z }; }
	vec3 operator/( const vec3& v ) const { return { x / v.x, y / v.y, z / v.z }; }
	void operator=( const vec3& v ) { x = v.x; y = v.y, z = v.z; }
	void operator=( const T* v ) { x = v[ 0 ]; y = v[ 1 ], z = v[ 2 ]; }

	vec3 operator+( const T& v ) const { return { x + v, y + v, z + v }; }
	vec3 operator-( const T& v ) const { return { x - v, y - v, z - v }; }
	vec3 operator*( const T& v ) const { return { x * v, y * v, z * v }; }
	vec3 operator/( const T& v ) const { return { x / v, y / v, z / v }; }

	vec3 operator+=( const vec3& v ) { return { x += v.x, y += v.y, z += v.z }; }
	vec3 operator-=( const vec3& v ) { return { x -= v.x, y -= v.y, z -= v.z }; }
	vec3 operator*=( const vec3& v ) { return { x *= v.x, y *= v.y, z *= v.z }; }
	vec3 operator/=( const vec3& v ) { return { x /= v.x, y /= v.y, z /= v.z }; }
	bool operator==( const vec3& v ) const { return  x == v.x && y == v.y && z == v.z; }
	bool operator!=( const vec3& v ) const { return  x != v.x || y != v.y || z != v.z; }

	vec3 operator+=( const T& v ) { return { x += v, y += v, z += v }; }
	vec3 operator-=( const T& v ) { return { x -= v, y -= v, z -= v }; }
	vec3 operator*=( const T& v ) { return { x *= v, y *= v, z *= v }; }
	vec3 operator/=( const T& v ) { return { x /= v, y /= v, z /= v }; }

	operator vec3<int>() { return { ( int )x, ( int )y, ( int )z }; }
	operator vec3<float>() { return { ( float )x, ( float )y, ( float )z }; }

	operator float* ( ) { return &x; }
	operator int* ( ) { return &x; }

	T& operator[]( const int index ) const
	{
		return ( ( T* )&x )[ index ];
	}

	T sum() const noexcept
	{
		return x + y + z;
	}
	float mag() const noexcept
	{
		return sqrtf( x * x + y * y + z * z );
	}
	T magsq() const noexcept
	{ //magnitude squared
		return ( x * x + y * y + z * z );
	}
	float dot( const vec3& vec ) const noexcept
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}
	float normalize() noexcept
	{
		const float length = this->mag();
		float ilength;

		if ( length )
		{
			ilength = 1 / length;
			this->x *= ilength;
			this->y *= ilength;
			this->z *= ilength;
		}

		return length;
	}
	float dist( const vec3& vec ) const noexcept
	{
		const vec3 sub = *this - vec;
		return sub.mag();
	}
	vec3 inverse() const noexcept
	{
		return { -x, -y, -z };
	}
	vec3 abs() const noexcept
	{
		return { std::abs( x ), std::abs( y ), std::abs( z ) };
	}
	void clamp( const T min, const T max ) noexcept
	{
		if ( x < min )		x = min;
		else if ( x > max )	x = max;

		if ( y < min )		y = min;
		else if ( y > max )	y = max;

		if ( z < min )		z = min;
		else if ( z > max )	z = max;
	}
	vec3 cross(const vec3& other) const noexcept
	{
		//
		// ay az	ax az	ax ay
		// by bz	bx bz	bx by
		//
		// (ay * bz) - (az * by),
		// (ax * bz) - (az * bx),
		// (ax * by) - (ay * bx)
		//

		return vec3{
			( this->y * other.z ) - ( this->z * other.y ),
			( this->x * other.z ) - ( this->z * other.x ),
			( this->x * other.y ) - ( this->y * other.x )
		};
	}

	vec3 toangles() const noexcept
	{
		float forward;
		float yaw, pitch;

		if ( y == 0 && x == 0 )
		{
			yaw = 0;
			if ( z > 0 )
			{
				pitch = 90;
			}
			else
			{
				pitch = 270;
			}
		}
		else
		{
			if ( x )
			{
				yaw = ( atan2( y, x ) * 180 / 3.14159265358979323846f );
			}
			else if ( y > 0 )
			{
				yaw = 90;
			}
			else
			{
				yaw = 270;
			}
			//if (yaw < 0) {
			//	yaw += 360;
			//}

			forward = sqrt( x * x + y * y );
			pitch = ( atan2( z, forward ) * 180 / 3.14159265358979323846f );
			if ( pitch < 0 )
			{
				pitch += 360;
			}
		}

		return vec3( -pitch, yaw, 0 );
	}
	vec3 toforward() const noexcept
	{
		float angle;
		static float sp, sy, cp, cy;
		// static to help MS compiler fp bugs

		angle = y * ( 3.14159265358979323846f * 2 / 360 );
		sy = sin( angle );
		cy = cos( angle );

		angle = x * ( 3.14159265358979323846f * 2 / 360 );
		sp = sin( angle );
		cp = cos( angle );

		return vec3( cp * cy, cp * sy, -sp );

	}
	vec3 toright() const noexcept
	{
		float angle;
		static float sr, cr, sp, sy, cp, cy;
		// static to help MS compiler fp bugs

		angle = y * ( 3.14159265358979323846f * 2 / 360 );
		sy = sin( angle );
		cy = cos( angle );

		angle = x * ( 3.14159265358979323846f * 2 / 360 );
		sp = sin( angle );
		cp = cos( angle );

		angle = z * ( 3.14159265358979323846f * 2 / 360 );
		sr = sin( angle );
		cr = cos( angle );

		return vec3( ( -1 * sr * sp * cy + -1 * cr * -sy ), ( -1 * sr * sp * sy + -1 * cr * cy ), -1 * sr * cp );

	}
	vec3 toup() const noexcept
	{
		float angle;
		static float sr, cr, sp, sy, cp, cy;
		// static to help MS compiler fp bugs

		angle = y * ( 3.14159265358979323846f * 2 / 360 );
		sy = sin( angle );
		cy = cos( angle );

		angle = x * ( 3.14159265358979323846f * 2 / 360 );
		sp = sin( angle );
		cp = cos( angle );

		angle = z * ( 3.14159265358979323846f * 2 / 360 );
		sr = sin( angle );
		cr = cos( angle );

		return vec3( ( cr * sp * cy + -sr * -sy ), ( cr * sp * sy + -sr * cy ), cr * cp );

	}


};

using ivec3 = vec3<int>;
using fvec3 = vec3<float>;

template <class T>
struct vec4
{

	T x, y, z, w;

	constexpr vec4() { x = 0; y = 0, z = 0; w = 0; }
	constexpr vec4( const T& v ) { x = v; y = v, z = v; w = v; }
	constexpr vec4( const T& a, const T& b, const T& c, const T& d ) { x = a; y = b, z = c; w = d; }
	constexpr vec4( const float* a ) { x = a[ 0 ]; y = a[ 1 ], z = a[ 2 ]; w = a[ 3 ]; };


	vec4 operator+( const vec4& v ) const { return { x + v.x, y + v.y, z + v.z, w + v.w, }; }
	vec4 operator-( const vec4& v ) const { return { x - v.x, y - v.y, z - v.z, w - v.w, }; }
	vec4 operator*( const vec4& v ) const { return { x * v.x, y * v.y, z * v.z, w * v.w, }; }
	vec4 operator/( const vec4& v ) const { return { x / v.x, y / v.y, z / v.z, w / v.w, }; }
	void operator=( const vec4& v ) { x = v.x; y = v.y, z = v.z; w = v.w; }
	void operator=( const T* v ) { x = v[ 0 ]; y = v[ 1 ], z = v[ 2 ]; w = v[ 3 ]; }

	vec4 operator+( const T& v ) const { return { x + v, y + v, z + v, w + v }; }
	vec4 operator-( const T& v ) const { return { x - v, y - v, z - v, w - v }; }
	vec4 operator*( const T& v ) const { return { x * v, y * v, z * v, w * v }; }
	vec4 operator/( const T& v ) const { return { x / v, y / v, z / v, w / v }; }

	vec4 operator+=( const vec4& v ) { return { x += v.x, y += v.y, z += v.z, w += v.w }; }
	vec4 operator-=( const vec4& v ) { return { x -= v.x, y -= v.y, z -= v.z, w -= v.w }; }
	vec4 operator*=( const vec4& v ) { return { x *= v.x, y *= v.y, z *= v.z, w *= v.w }; }
	vec4 operator/=( const vec4& v ) { return { x /= v.x, y /= v.y, z /= v.z, w /= v.w }; }
	bool operator==( const vec4& v ) const { return  x == v.x && y == v.y && z == v.z && w == v.w; }
	bool operator!=( const vec4& v ) const { return  x != v.x || y != v.y || z != v.z || w != v.w; }

	vec4 operator+=( const T& v ) { return { x += v, y += v, z += v, w += v }; }
	vec4 operator-=( const T& v ) { return { x -= v, y -= v, z -= v, w -= v }; }
	vec4 operator*=( const T& v ) { return { x *= v, y *= v, z *= v, w *= v }; }
	vec4 operator/=( const T& v ) { return { x /= v, y /= v, z /= v, w /= v }; }

	operator vec4<int>() { return { ( int )x, ( int )y, ( int )z, ( int )w }; }
	operator vec4<float>() { return { ( float )x, ( float )y, ( float )z, ( float )w }; }

	operator float* ( ) { return &x; }
	operator int* ( ) { return &x; }

	vec4 operator* ( const matrix m ) const
	{
		return vec4{
			x * m.m00 + y * m.m10 + z * m.m20 + w * m.m30,
			x * m.m01 + y * m.m11 + z * m.m21 + w * m.m31,
			x * m.m02 + y * m.m12 + z * m.m22 + w * m.m32,
			x * m.m03 + y * m.m13 + z * m.m23 + w * m.m33
		};
	}

	T& operator[]( const int index ) const
	{
		return ( ( T* )&x )[ index ];
	}

	T sum() const noexcept
	{
		return x + y + z + w;
	}
	float mag() const noexcept
	{
		return sqrtf( x * x + y * y + z * z + w * w );
	}
	T magsq() const noexcept
	{ //magnitude squared
		return ( x * x + y * y + z * z + w * w );
	}
	float dot( const vec4& vec ) const noexcept
	{
		return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
	}
	float normalize() noexcept
	{
		const float length = this->mag();
		float ilength;

		if ( length )
		{
			ilength = 1 / length;
			this->x *= ilength;
			this->y *= ilength;
			this->z *= ilength;
			this->w *= ilength;
		}

		return length;
	}
	float dist( const vec4& vec ) const noexcept
	{
		const vec4 sub = *this - vec;
		return sub.mag();
	}
	vec4 inverse() const noexcept
	{
		return { -x, -y, -z, -w };
	}
	vec4 abs() const noexcept
	{
		return { std::abs( x ), std::abs( y ), std::abs( z ), std::abs( w ) };
	}
	void clamp( const T min, const T max ) noexcept
	{
		if ( x < min )		x = min;
		else if ( x > max )	x = max;

		if ( y < min )		y = min;
		else if ( y > max )	y = max;

		if ( z < min )		z = min;
		else if ( z > max )	z = max;

		if ( w < min )		w = min;
		else if ( w > max )	w = max;
	}
};


using ivec4 = vec4<int>;
using fvec4 = vec4<float>;
#pragma once
#include "../imgui/imgui.h"

struct Color
{
	union
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		};
		struct
		{
			float r;
			float g;
			float b;
			float a;
		} rgba = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

	constexpr Color() :
		rgba( { 0,0,0,0 } )
	{}

	constexpr Color( float f ) :
		rgba( { f,f,f,f } )
	{}

	constexpr Color( int i )
	{
		float f = static_cast< float >( i );
		rgba = { f,f,f,f };
	}

	constexpr Color( float r, float g, float b, float a = 1.f ) :
		rgba( { r,g,b,a } )
	{}
	constexpr Color( Color& c) :
		r(c.r), g(c.g), b(c.b), a(c.a)
	{}
	constexpr Color( Color&& c) :
		r(c.r), g(c.g), b(c.b), a(c.a)
	{}

	Color( const char* hex )
	{
		auto&& c = hex2rgba( hex );
		r = c.r;
		g = c.g;
		b = c.b;
		a = c.a;
	}


	constexpr Color( const ImColor color ) { auto& col = color.Value; r = col.x; g = col.y; b = col.z; a = col.w; };
	operator ImColor() { return ImColor( r, g, b, a ); };
	operator ImVec4() const { return ImVec4( r, g, b, a ); }



	static Color hex2rgba( const char* hex );
};
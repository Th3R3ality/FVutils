#pragma once
#include "rendering.h"

inline void AddTextShadow( ImDrawList* drawlist, const ImVec2& pos, ImColor col, const char* text_begin, const char* text_end = NULL )
{
	ImColor shadowCol;
	ImVec4 colParts = col;
	colParts.x -= 100; colParts.x = colParts.x > 0 ? colParts.x : 0;
	colParts.y -= 100; colParts.y = colParts.y > 0 ? colParts.y : 0;
	colParts.z -= 100; colParts.z = colParts.z > 0 ? colParts.z : 0;

	shadowCol = colParts;
	drawlist->AddText( ImVec2(pos.x + 1, pos.y + 1), shadowCol, text_begin, text_end);
	drawlist->AddText( pos, col, text_begin, text_end );
}
#pragma once

#include <gl/GL.h>
#include "../util/math/vec.h"
#include "../util/Color.h"

inline void glColor4f( Color col )
{
	glColor4f( col.r, col.g, col.b, col.a );
}
inline void glVertex3f( fvec3 vec )
{
	glVertex3f( vec.x, vec.y, vec.z );
}
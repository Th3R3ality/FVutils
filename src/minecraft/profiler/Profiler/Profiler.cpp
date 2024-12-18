#include "Profiler.h"
#include <lang/String.h>

MAKE_INITIALISER( Profiler );

std::string Profiler::getNameOfLastSection(bool noderef)
{
	String Str = (jstring)TLSENV->CallObjectMethod( instance, Profiler::methodIDs[ "getNameOfLastSection" ] );

	if ( noderef )
		Str.noDeref = true;
	return Str.ToString();
}

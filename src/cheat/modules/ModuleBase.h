#pragma once
#include "Modules.h"
#include "../../util/initialiser_type.h"



#define MODULE_STRUCTOR(klass) \
klass ( INITIALISER_TYPE ) { modules::moduleInitialisers.push_back( &Initialise ); }

class ModuleBase
{
public:
	static bool initialised;

	static void Initialise() {};

	ModuleBase() = default;

	ModuleBase( INITIALISER_TYPE )
	{
		modules::moduleInitialisers.push_back( &Initialise );
	}
};
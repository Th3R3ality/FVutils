#include "Modules.h"
#include "Combat/Clicker.h"
#include "Render/Esp.h"

#define INIT(klass) klass __ ## klass ## _initialiser = klass ( INITIALISER_TYPE{} )

INIT( Clicker );
INIT( Esp );

void modules::Init()
{
	for ( auto&& fn : moduleInitialisers )
	{
		fn();
	}
}
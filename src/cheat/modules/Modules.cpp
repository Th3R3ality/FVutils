#include "Modules.h"
#include "Clicker/Clicker.h"

#define INIT(klass) klass __ ## klass ## _initialiser = klass ( INITIALISER_TYPE{} )

INIT( Clicker );

//inline Clicker __Clicker_initialiser = Clicker( INITIALISER_TYPE{} );

void modules::Init()
{
	for ( auto&& fn : moduleInitialisers )
	{
		fn();
	}
}
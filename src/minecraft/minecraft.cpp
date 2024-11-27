#include "minecraft.h"

MAKE_INITIALISER( Minecraft );
jobject Minecraft::staticInstance = 0;


#define VALIDATE_OBJECT(klass, objectVar, field) \
jobject __ ## klass ## objectVar = TLSENV->GetObjectField( Minecraft::staticInstance, Minecraft::fieldIDs[ field ] ); \
if ( !__ ## klass ## objectVar ) \
{ \
	minecraft::## objectVar = nullptr; \
	return false; \
} \
if ( minecraft::## objectVar == nullptr || !TLSENV->IsSameObject(__ ## klass ## objectVar, minecraft::##objectVar ->instance) ) \
{ \
	if ( minecraft::##objectVar != nullptr && minecraft::##objectVar ->instance && minecraft::##objectVar ->noDeref == true ) \
		{minecraft::##objectVar ->Deref();} \
 \
	minecraft::##objectVar = std::make_unique< klass >( __ ## klass ## objectVar ); \
	minecraft::##objectVar ->MakeGlobal(); \
	minecraft::##objectVar ->noDeref = true; \
} \
else \
{ /*TLSENV->DeleteLocalRef( __ ## klass ## objectVar );*/ }

namespace minecraft
{
	bool ValidateObjects()
	{
		VALIDATE_OBJECT( EntityPlayerSP, localPlayer, "thePlayer" );
		VALIDATE_OBJECT( WorldClient, world, "theWorld" );
		VALIDATE_OBJECT( Timer, timer, "timer" );
		VALIDATE_OBJECT( RenderManager, renderManager, "renderManager" );

		return true;
	}
}
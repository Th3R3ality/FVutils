#include "hooks.h"
#include "../minecraft/minecraft.h"
#include "../cache/cache.h"

namespace hooks
{
	void jhk_runGameLoop( HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel )
	{
		JNIEnv* env = thread->get_env();
		if ( !TlsSetValue( java::envTlsIndex, env ) )
		{
			printf("TlsSetValue error"); 
			return;
		}

		printf( "runGameLoop\n" );
		
		//jobject theWorld = env->GetObjectField( Minecraft::staticInstance, Minecraft::fieldIDs[ "theWorld" ] );

		//if ( theWorld )
		//{
		//	jobject playerEntitiesObject = env->GetObjectField( theWorld, World::fieldIDs[ "playerEntities" ] );
		//	
		//	
		//	if (playerEntitiesObject)
		//		env->DeleteLocalRef( playerEntitiesObject );
		//	
		//	env->DeleteLocalRef( theWorld );
		//}

		//jobject worldClientInstance = TLSENV->GetObjectField( Minecraft::staticInstance, Minecraft::fieldIDs[ "theWorld" ] );
		//if ( !worldClientInstance )
		//{
		//	minecraft::world = nullptr;
		//	return;
		//}
		//if ( minecraft::world == nullptr || !TLSENV->IsSameObject(worldClientInstance, minecraft::world->instance) )
		//{
		//	if ( minecraft::world != nullptr && minecraft::world->instance && minecraft::world->noDeref == true )
		//		minecraft::world->Deref();

		//	minecraft::world = std::make_unique<WorldClient>( worldClientInstance );
		//	minecraft::world->MakeGlobal();
		//	minecraft::world->noDeref = true;
		//}
		//else
		//	TLSENV->DeleteLocalRef( worldClientInstance );


		if ( ( minecraft::objectsAreValid = minecraft::ValidateObjects() ) )
		{
			cache::UpdateCache();
		}
	}
}
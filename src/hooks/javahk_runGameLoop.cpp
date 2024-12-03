#include "hooks.h"
#include "../minecraft/minecraft.h"
#include "../cache/cache.h"
#include "../global.h"
#include <lang/Class.h>

namespace hooks
{
	void javahk_runGameLoop( HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel )
	{
		if ( global::glUnhookWant )
			return;

		JNIEnv* env = thread->get_env();
		if ( !TlsSetValue( java::envTlsIndex, env ) )
		{
			printf("TlsSetValue error"); 
			return;
		}


		if ( ( minecraft::objectsAreValid = minecraft::ValidateObjects() ) )
		{
			//cache::UpdateCache();

			for ( int i = 0; i < 2; i++ )
			{
				List playerList = TLSENV->GetObjectField( minecraft::world->instance, World::fieldIDs[ "playerEntities" ] );
				if ( playerList.instance == nullptr )
				{
					printf( "playerList NULL\n" );
					continue;
				}

				jobjectArray playerArray = playerList.toArray();
				if ( playerArray == nullptr )
				{
					printf( "playerArray NULL\n" );
					continue;
				}

				jsize length = TLSENV->GetArrayLength( playerArray );

				for ( jsize idx = 0; idx < length; idx++ )
				{
					EntityPlayer entityPlayer = TLSENV->GetObjectArrayElement( playerArray, idx );

					if ( entityPlayer.instance == nullptr )
					{
						printf( "entityPlayer NULL\n" );
						continue;
					}

					
					jfloat health = entityPlayer.getHealth();
					String str = entityPlayer.getName();
					if ( str.instance == nullptr )
					{
						printf( "str NULL\n" );
						continue;
					}
					std::string a = str.ToString();
					//std::cout << str.ToString() << std::endl;
					//printf( "Health: %f\n", health );

				}

				TLSENV->DeleteLocalRef( playerArray );
			}


			//if ( playerArray == nullptr ) return;

			//jsize length = TLSENV->GetArrayLength( playerArray );

			//for ( jsize idx = 0; idx < length; idx++ )
			//{
			//	EntityPlayer entityPlayer = TLSENV->GetObjectArrayElement( playerArray, idx );
			//	if ( entityPlayer.instance )
			//	{
			//		//Class klass = TLSENV->GetObjectClass( entityPlayer.instance );

			//		//String name = klass.getName();
			//		//std::cout << name.ToString() << "\n";

			//		std::cout << "  health: " << entityPlayer.getHealth() << "\n";
			//	}
			//}

			//TLSENV->DeleteLocalRef( playerArray );


			//cache::UpdateCache();

		}
	}
}
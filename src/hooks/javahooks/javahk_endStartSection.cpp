#include "../hooks.h"
#include "../../global.h"
#include "../../minecraft/entity/EntityPlayer/EntityPlayer.h"
#include "../../minecraft/minecraft.h"
#include <lang/String.h>

namespace hooks
{
	void javahk_endStartSection( HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel )
	{
		if ( global::glUnhookWant )
			return;

		JNIEnv* env = thread->get_env();

		if ( !TlsSetValue( java::envTlsIndex, env ) )
		{
			printf("TlsSetValue error");
			return;
		}

		// param 0, instance
		jobject profiler = JavaHook::get_jobject_param_at( frame, 0 );

		// param 1, String
		String Str = JavaHook::get_jobject_param_at( frame, 1 );
		Str.noDeref = true;

		std::string str = Str.ToString();
		if ( str.compare( "sound" ) == 0 )
		{
			printf( "endStartSection: %s\n", str.c_str());

			if ( ( minecraft::objectsAreValid = minecraft::ValidateObjects() ) )
			{
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
						fvec3 pos = entityPlayer.GetPos();
						std::cout << a << " : " << health << " :"" x" << pos.x <<" y" << pos.y <<" z" << pos.z << std::endl;
						//printf( "Health: %f\n", health );

					}

					TLSENV->DeleteLocalRef( playerArray );
				}
			}
		}	
	}
}
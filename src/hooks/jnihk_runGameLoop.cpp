#include "hooks.h"
#include <iostream>

#include "../minecraft/minecraft.h"
#include "../cache/cache.h"
#include "../global.h"

JNIEXPORT void JNICALL hooks::jnihk_runGameLoop( JNIEnv* env, jobject instance )
{
	if ( global::glUnhookWant )
		return;

	if ( !TlsSetValue( java::envTlsIndex, env ) )
	{
		printf( "TlsSetValue error" );
		return;
	}

	//std::cout << "Target::sayHello HOOK CALLED!" << std::endl;
	//std::cout << "Calling original method..." << std::endl;

	try
	{
		env->CallNonvirtualVoidMethod( instance, Minecraft::klass, __orig_mid_jnihk_runGameLoop );

		if ( env->ExceptionCheck() )
		{
			printf( "runGameLoop: env exception\n" );
			return;
		}
	}
	catch (std::exception e) {
		printf( "runGameLoop: try/catch exception\n" );
		return;
	}

	if ( ( minecraft::objectsAreValid = minecraft::ValidateObjects() ) )
	{
		cache::UpdateCache();


		//List playerList = TLSENV->GetObjectField( minecraft::world->instance, World::fieldIDs[ "playerEntities" ] );
		//if ( playerList.instance == nullptr )
		//{
		//	printf( "playerList NULL\n" );
		//	return;
		//}

		//jobjectArray playerArray = playerList.toArray();
		//if ( playerArray == nullptr )
		//{
		//	printf( "playerArray NULL\n" );
		//	return;
		//}

		//jsize length = TLSENV->GetArrayLength( playerArray );

		//for ( jsize idx = 0; idx < length; idx++ )
		//{
		//	EntityPlayer entityPlayer = TLSENV->GetObjectArrayElement( playerArray, idx );

		//	if ( entityPlayer.instance == nullptr )
		//	{
		//		printf( "entityPlayer NULL\n" );
		//		continue;
		//	}


		//	jfloat health = entityPlayer.getHealth();
		//	String str = entityPlayer.getName();
		//	if ( str.instance == nullptr )
		//	{
		//		printf( "str NULL\n" );
		//		continue;
		//	}
		//	std::string a = str.ToString();
		//	std::cout << str.ToString() << std::endl;
		//	printf( "Health: %f\n", health );

		//	fvec3 pos = entityPlayer.GetPos();

		//	printf( "pos: %f, %f, %f\n", pos.x, pos.y, pos.z );
		//}

		//TLSENV->DeleteLocalRef( playerArray );




	}
}
#include "hooks.h"
#include "../minecraft/client/renderer/entity/Render/Render.h"
#include "../minecraft/client/renderer/entity/RenderPlayer/RenderPlayer.h"
#include "../minecraft/entity/Entity/Entity.h"
#include "../java/lang/String.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <lang/Class.h>

namespace hooks
{
	void jhk_renderName( HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel )
	{
		JNIEnv* env = thread->get_env();

		if ( !TlsSetValue( java::envTlsIndex, env ) )
		{
			printf("TlsSetValue error"); 
			return;
		}
		//printf("renderName thread %d: lpvData=%lx\n", GetCurrentThreadId(), env);
		//java::TestTLS();

		jobject instance = JavaHook::get_jobject_param_at( frame, 0 );

		//(Lnet/minecraft/entity/Entity;DDD)V
		jobject _entity = JavaHook::get_jobject_param_at( frame, 1 );


		Class klass = env->GetObjectClass( _entity );
		klass.noDeref = true;

		String str = klass.getName( env );
		str.noDeref = true;


		//klass.Deref();

		//if ( env->IsInstanceOf( instance, RenderPlayer::klass ) )
		//{
		//	printf( "PLAYER!\n" );
		//	RenderPlayer p = instance;
		//	p.noDeref = true;
		//	
		//}
		//else
		//{
		//	printf( "NOT PLAYER :(\n" );
		//}

		//net.minecraft.client.renderer.entity.RenderPlayer
		//net.minecraft.client.entity.EntityOtherPlayerMP

		//printf( "renderName | %s\n", klassStr.ToString().c_str());


		//klassStr.Deref();
		//String Str = JavaHook::get_jobject_param_at( frame, 6 );
		//std::string str = Str.ToString();


		//str = str;

		//std::stringstream ss;
		//ss << std::hex << std::setfill( '0' );
		//for ( int i = 0; i < str.length(); i++ )
		//{
		//	ss << std::setw( 2 ) << static_cast< unsigned >(str.at(i));
		//}

		//str = str + ": " + ss.str() + "\n";
	}
}
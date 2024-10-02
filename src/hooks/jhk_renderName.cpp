#include "hooks.h"
#include "../minecraft/client/renderer/entity/Render/Render.h"
#include "../minecraft/client/renderer/entity/RenderPlayer/RenderPlayer.h"
#include "../minecraft/entity/Entity/Entity.h"
#include "../java/lang/String.h"

#include <iostream>
#include <sstream>
#include <iomanip>

namespace hooks
{
	void jhk_renderName( HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel )
	{
		JNIEnv* env = thread->get_env();

		jobject instance = JavaHook::get_jobject_param_at( frame, 0 );

		//(Lnet/minecraft/entity/Entity;DDD)V
		jobject _entity = JavaHook::get_jobject_param_at( frame, 1 );


		jclass klass = env->GetObjectClass( _entity );

		static jclass ccls = env->FindClass("java/lang/Class");
		static jmethodID mid_getName = env->GetMethodID(ccls, "getName", "()Ljava/lang/String;");
		String klassStr = env->CallObjectMethod(klass, mid_getName);
		//klassStr.noDeref = true;
		env->DeleteLocalRef( klass );
		


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
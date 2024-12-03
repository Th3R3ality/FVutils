#include "hooks.h"
#include "../minecraft/client/NetHandlerPlayClient/NetHandlerPlayClient.h"
#include "../minecraft/network/S02PacketChat/S02PacketChat.h"
#include "../minecraft/util/IChatComponent/IChatComponent.h"
#include "../global.h"

namespace hooks
{
	void javahk_handleChat( HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel )
	{
		if ( global::glUnhookWant )
			return;

		JNIEnv* env = thread->get_env();

		if ( !TlsSetValue( java::envTlsIndex, env ) )
		{
			printf("TlsSetValue error");
			return;
		}
		//printf("handleChat thread %d: lpvData=%lx\n", GetCurrentThreadId(), env);
		//java::TestTLS();

		//// param 0, instance
		//jobject instance = JavaHook::get_jobject_param_at( frame, 0 );

		//// param 1, S02PacketChat
		//jobject packet = JavaHook::get_jobject_param_at( frame, 1 );


		//jboolean isChat = env->CallBooleanMethod( packet, S02PacketChat::methodIDs[ "isChat" ] );
		////printf( "isChat : %i\n", (int)isChat );
		//jbyte getType = env->CallByteMethod( packet, S02PacketChat::methodIDs[ "getType" ] ); 
		////printf( "getType : %i\n", (int)getType );

		//IChatComponent chatComponent = env->CallObjectMethod( packet, S02PacketChat::methodIDs[ "getChatComponent" ] );
		////printf( "chatComponent : %p\n", chatComponent );

		//{
		//	String Str = env->CallObjectMethod( chatComponent.instance, IChatComponent::methodIDs[ "getUnformattedText" ] );
		//	//Str.noDeref = true;
		//	printf( "Chat: %s\n", Str.ToString().c_str() );
		//}

	}
}
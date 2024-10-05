#include "hooks.h"
#include "../minecraft/client/NetHandlerPlayClient/NetHandlerPlayClient.h"
#include "../minecraft/network/S02PacketChat/S02PacketChat.h"
#include "../minecraft/util/IChatComponent/IChatComponent.h"

namespace hooks
{
	void jhk_handleChat( HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel )
	{
		JNIEnv* env = thread->get_env();

		// param 0, instance
		jobject instance = JavaHook::get_jobject_param_at( frame, 0 );

		// param 1, S02PacketChat
		jobject packet = JavaHook::get_jobject_param_at( frame, 1 );


		jboolean isChat = env->CallBooleanMethod( packet, S02PacketChat::methodIDs[ "isChat" ] );
		//printf( "isChat : %i\n", (int)isChat );
		jbyte getType = env->CallByteMethod( packet, S02PacketChat::methodIDs[ "getType" ] ); 
		//printf( "getType : %i\n", (int)getType );

		IChatComponent chatComponent = env->CallObjectMethod( packet, S02PacketChat::methodIDs[ "getChatComponent" ] );
		//printf( "chatComponent : %p\n", chatComponent );

		{
			String Str = env->CallObjectMethod( chatComponent.instance, IChatComponent::methodIDs[ "getUnformattedText" ] );
			//Str.noDeref = true;
			printf( "Chat: %s\n", Str.ToString().c_str() );
		}

	}
}
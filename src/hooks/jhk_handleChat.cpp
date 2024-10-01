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

		jobject chatComponent = env->CallObjectMethod( packet, S02PacketChat::methodIDs[ "getChatComponent" ] );
		//printf( "chatComponent : %p\n", chatComponent );

		//{
		//	jstring formatted = (jstring)env->CallObjectMethod( chatComponent, IChatComponent::methodIDs[ "getFormattedText" ] );
		//	
		//	int bufferSize = env->GetStringUTFLength(formatted);
		//	char* buffer = new char[bufferSize + 1] { 0 };
		//	env->GetStringUTFRegion( formatted, 0, env->GetStringLength(formatted), buffer );
		//	buffer[ bufferSize ] = '\0';
		//	std::string str = buffer;
		//	delete[] buffer;

		//	printf( "formatted: %s\n", str.c_str() );

		//}
		{
			jstring unformatted = (jstring)env->CallObjectMethod( chatComponent, IChatComponent::methodIDs[ "getUnformattedText" ] );

			int bufferSize = env->GetStringUTFLength(unformatted);
			char* buffer = new char[bufferSize + 1] { 0 };
			env->GetStringUTFRegion( unformatted, 0, env->GetStringLength(unformatted), buffer );
			buffer[ bufferSize ] = '\0';
			std::string str = buffer;
			delete[] buffer;

			printf( "unformatted: %s\n", str.c_str() );
		}

		return;
	}
}
#include "hooks.h"


namespace hooks
{
	void jhk_handleChat( HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel )
	{
		//if ( !java::env ) return;
		JNIEnv* env = thread->get_env();
		printf( "handleChat\n" );

		// param 0, instance
		jobject instance = JavaHook::get_jobject_param_at( frame, 0 );
		printf( "param 0, instance: %p\n", instance );

		// param 1, S02PacketChat
		jobject packet = JavaHook::get_jobject_param_at( frame, 1 );
		printf( "param 1, S02PacketChat: %p\n", packet );


		//int i = -1;
		//jboolean isChat = env->CallBooleanMethod( packet, _isChat );
		//i = isChat;
		//printf( "isChat : %i\n", i );
		//jbyte chattype = env->CallByteMethod( packet, _getType );
		//i = chattype;
		//printf( "getType : %i\n", i );

		//jobject chatComponent = env->CallObjectMethod( packet, _getChatComponent );
		//printf( "chatComponent : %p\n", chatComponent );

		//String formatted = String( env->CallObjectMethod( chatComponent, _getFormattedText ) );
		//std::string str = formatted.toStdString();
		//printf( "formatted: %s\n", str.c_str() );
		//String unformatted = String( env->CallObjectMethod( chatComponent, _getUnformattedText ) );
		//str = unformatted.toStdString();
		//printf( "unformatted: %s\n", str.c_str() );


		return;
	}
}
#pragma once
#include "../../IClass.h"

#define CURRENTCLASSNAME S02PacketChat

SETCLASSPATH( "net/minecraft/network/play/server/S02PacketChat" );

struct CURRENTCLASSNAME : IClass
{
	//static std::map<std::string, jmethodID> methodIDs; 
	//static std::map<std::string, jfieldID> fieldIDs; 
	//static jclass klass; 
	//static bool initialised; 
	//static const char* klassPath;
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		GET_METHOD( "getType", "()B" );
		GET_METHOD( "isChat", "()Z" );
		GET_METHOD( "getChatComponent", "()Lnet/minecraft/util/IChatComponent;" );

	}

	//S02PacketChat(INITIALISER_TYPE) {
	//	java::classInitialisers.push_back(&Initialise);
	//} 
	//S02PacketChat(jobject _instance) {
	//	instance = _instance;
	//} 
	//~S02PacketChat() {
	//	if (instance) java::env->DeleteLocalRef(instance);
	//}
	STRUCTORS();



};





#undef CURRENTCLASSNAME
#pragma once
#include "../../IClass.h"

#define CURRENTCLASSNAME NetHandlerPlayClient

SETCLASSPATH( "net/minecraft/client/network/NetHandlerPlayClient" );

struct CURRENTCLASSNAME : IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		//NetHandlerPlayClient::methodIDs["handleChat"] = java::env->GetMethodID( NetHandlerPlayClient::klass, "handleChat", "(Lnet/minecraft/network/play/server/S02PacketChat;)V" );
		METHOD( "handleChat", "(Lnet/minecraft/network/play/server/S02PacketChat;)V" );
	}

	STRUCTORS();

};


#undef CURRENTCLASSNAME
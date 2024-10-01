#pragma once
#include "../../IClass.h"

#define CURRENTCLASSNAME NetHandlerPlayClient

SETCLASSPATH( "net/minecraft/client/network/NetHandlerPlayClient" );

struct NetHandlerPlayClient : IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		//NetHandlerPlayClient::methodIDs["handleChat"] = java::env->GetMethodID( NetHandlerPlayClient::klass, "handleChat", "(Lnet/minecraft/network/play/server/S02PacketChat;)V" );
		GET_METHOD( "handleChat", "(Lnet/minecraft/network/play/server/S02PacketChat;)V" );
	}

	STRUCTORS();

};

#undef CURRENTCLASSNAME
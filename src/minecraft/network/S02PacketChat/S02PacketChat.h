#pragma once
#include "../../IClass.h"

#define CURRENTCLASSNAME S02PacketChat

SETCLASSPATH( "net/minecraft/network/play/server/S02PacketChat" );

struct S02PacketChat : IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		GET_METHOD( "getType", "()B" );
		GET_METHOD( "isChat", "()Z" );
		GET_METHOD( "getChatComponent", "()Lnet/minecraft/util/IChatComponent;" );

	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME
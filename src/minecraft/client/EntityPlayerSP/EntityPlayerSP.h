#pragma once
#include "../../entity/EntityPlayer/EntityPlayer.h"

struct EntityPlayerSP : public EntityPlayer
{
	const char* klassPath = "net.minecraft.client.entity.EntityPlayerSP";
	
	STRUCTORS( EntityPlayerSP );

	jobject GetInstance();
};
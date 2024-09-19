#pragma once
#include "../Entity/Entity.h"

struct EntityLivingBase : public Entity
{
	const char* klassPath = "net.minecraft.entity.EntityLivingBase";

	jfloat getHealth();
};
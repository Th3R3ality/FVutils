#pragma once
#include "../Entity/Entity.h"

#define CURRENTCLASSNAME EntityLivingBase

SETCLASSPATH( "net/minecraft/entity/EntityLivingBase" );

struct EntityLivingBase : public Entity
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER( );


		GET_METHOD( "getHealth", "()F");
		GET_METHOD( "getMaxHealth", "()F");
		GET_METHOD( "canEntityBeSeen", "(Lnet/minecraft/entity/Entity;)Z");
	}

	float getHealth()
	{
		return java::env->CallFloatMethod(this->instance, EntityLivingBase::methodIDs["getHealth"]);
	}

	float getMaxHealth()
	{
		return java::env->CallFloatMethod(this->instance, EntityLivingBase::methodIDs["getMaxHealth"]);
	}

	bool canEntityBeSeen(jobject entityInstance)
	{
		return java::env->CallBooleanMethod(this->instance, EntityLivingBase::methodIDs["canEntityBeSeen"], entityInstance);
	}

	STRUCTORS( );
};

#undef CURRENTCLASSNAME
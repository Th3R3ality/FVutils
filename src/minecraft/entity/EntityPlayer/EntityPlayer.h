#pragma once
#include "../EntityLivingBase/EntityLivingBase.h"

#define CURRENTCLASSNAME EntityPlayer

SETCLASSPATH( "net/minecraft/entity/player/EntityPlayer" );

struct EntityPlayer : public EntityLivingBase
{
	using EntityLivingBase::EntityLivingBase;

	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER( );
	}

	EntityPlayer( INITIALISER_TYPE )
	{
		java::classInitialisers.push_back( &Initialise );
	}
	EntityPlayer( jobject _instance )
	{
		instance = _instance;
	}
	~EntityPlayer()
	{
		if ( instance ) java::env->DeleteLocalRef( instance );
	};
};

#undef CURRENTCLASSNAME
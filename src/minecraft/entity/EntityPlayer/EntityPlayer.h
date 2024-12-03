#pragma once
#include "../EntityLivingBase/EntityLivingBase.h"
#include <iostream>

#define CURRENTCLASSNAME EntityPlayer

SETCLASSPATH( "net/minecraft/entity/player/EntityPlayer" );

namespace cache
{
	struct PlayerData;
}

struct EntityPlayer : public EntityLivingBase
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER( );
	}

	STRUCTORS();

	cache::PlayerData ToPlayerData();
	

	//EntityPlayer() = default; EntityPlayer( INITIALISER_TYPE )
	//{
	//	java::classInitialisers.push_back( &Initialise );
	//} EntityPlayer( jobject _instance )
	//{
	//	instance = _instance;
	//	//printf( "EntityPlayer( instance ) : %p\n", instance );
	//} ~EntityPlayer()
	//{
	//	//printf( "~EntityPlayer() : %p%s\n", instance, noDeref ? " : noDeref" : "");
	//	if ( instance && !this->noDeref ) TLSENV->DeleteLocalRef( instance );
	//};
};

#undef CURRENTCLASSNAME
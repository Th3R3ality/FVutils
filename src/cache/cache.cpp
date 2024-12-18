#include "cache.h"
#include <iostream>
#include <mutex>
#include <string>

#include "../minecraft/minecraft.h"
#include "../minecraft/client/renderer/ActiveRenderInfo/ActiveRenderInfo.h"

#include "../config/config.h"

namespace cache
{

	void UpdateCache()
	{
		CacheData temp;

		// players
		std::vector<EntityPlayer> playerEntities;
		minecraft::world->playerEntities( playerEntities );

		for ( auto& pe : playerEntities )
		{
			bool found = false;
			for ( auto&& gp : globalPlayers )
			{
				if ( TLSENV->IsSameObject( pe.instance, gp.instance ) )
				{
					gp.checked = true;
					found = true;
				}
			}
			if ( !found )
			{
				globalPlayers.push_back( { .checked = true, .instance = TLSENV->NewGlobalRef( pe.instance ) } );
			}
		}
		//	PlayerData pd = pe.ToPlayerData();
		//	if ( pd.realname == minecraft::localPlayer->getName().ToString() )
		//	{
		//		temp.local = pd;
		//		if ( !config::current.render.players.hideSelf )
		//		{
		//			temp.players.push_back( pd );
		//		}
		//	}
		//	else
		//	{
		//		if ( config::current.render.players.hideBots
		//			&& pd.invalidName )
		//			continue;


		//		temp.players.push_back( pd );

		//	}
		//}

		std::vector<GlobalPlayer> newGPlist;

		for ( auto&& gp : globalPlayers )
		{
			if ( gp.checked )
			{
				newGPlist.push_back( gp );
			}
			else
			{
				TLSENV->DeleteGlobalRef( gp.instance );
			}
		}

		{
			std::lock_guard<std::mutex> guard( gpMutex );
			globalPlayers = newGPlist;
		}

		//for ( jint idx = 0; idx < size; idx++ )
		//{

		//	if ( temp.players.at( idx ).realname == minecraft::localPlayer->getName().ToString() )
		//	{
		//		temp.local = temp.players.at( idx );
		//	}
		//	else
		//	{
		//		temp.players.at( idx ) = PlayerData( playerEntities.at( idx ) );

		//	}
		//}


		temp._modelView = ActiveRenderInfo::RawModelViewMatrix();
		temp._projection = ActiveRenderInfo::RawProjectionMatrix();

		temp.modelView = ActiveRenderInfo::ModelViewMatrix();
		temp.projection = ActiveRenderInfo::ProjectionMatrix();


		temp.viewport = ActiveRenderInfo::Viewport();
		temp.renderOffset = ActiveRenderInfo::RenderPos();
		temp.renderPos = minecraft::renderManager->RenderPos();
		//temp.renderPos.y += 3.4f;

		temp.renderPartialTicks = minecraft::timer->renderPartialTicks();

		// only lock the data when copying so we keep the shared data free for the render thread as much as possible
		std::lock_guard<std::mutex> guard( dataMutex );
		cache::data = temp;
	}
}

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
		minecraft::world->playerEntities(playerEntities);

		int size = playerEntities.size();
		temp.players.clear();
		//temp.players.reserve( size );

		for ( auto&& pe : playerEntities )
		{
			PlayerData pd = pe;
			if ( pd.realname == minecraft::localPlayer->getName().ToString() )
			{
				temp.local = pd;
				if ( !config::current.render.players.hideSelf )
				{
					temp.players.push_back(pd);
				}
			}
			else
			{
				if ( config::current.render.players.hideBots
					&& pd.invalidName )
					continue;


				temp.players.push_back(pd);

			}
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

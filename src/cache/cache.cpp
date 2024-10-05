#include "cache.h"
#include "../minecraft/minecraft.h"
#include "../minecraft/client/renderer/ActiveRenderInfo/ActiveRenderInfo.h"

#include <iostream>
#include <mutex>
#include <string>

namespace cache
{
	CacheData temp;

	void UpdateCache()
	{

		// players
		std::vector<EntityPlayer> playerEntities;
		minecraft::world->playerEntities(playerEntities);

		int size = playerEntities.size();
		temp.players.resize( size );

		for ( jint idx = 0; idx < size; idx++ )
		{
			temp.players.at( idx ) = PlayerData( playerEntities.at( idx ) );

			if ( temp.players.at( idx ).realname == minecraft::localPlayer->getName().ToString() )
			{
				temp.local = temp.players.at( idx );
			}
		}



		temp.modelView = ActiveRenderInfo::ModelViewMatrix();
		temp.projection = ActiveRenderInfo::ProjectionMatrix();
		temp.viewport = ActiveRenderInfo::Viewport();
		temp.renderOffset = ActiveRenderInfo::RenderPos();
		temp.renderPos = minecraft::renderManager->RenderPos();
		temp.renderPos.y += 3.4f;

		temp.renderPartialTicks = minecraft::timer->renderPartialTicks();

		// only lock the data when copying so we keep the shared data free for the render thread as much as possible
		std::lock_guard<std::mutex> guard( dataMutex );
		cache::data = temp;
	}
}

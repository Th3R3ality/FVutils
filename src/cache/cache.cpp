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
		// players
		std::vector<EntityPlayer> playerEntities;
		minecraft::world->playerEntities( playerEntities );

		{
			std::lock_guard<std::mutex> gpguard( gpMutex );
			for ( auto&& gp : globalPlayers )
			{
				if ( gp.instance )
					TLSENV->DeleteGlobalRef( gp.instance );
			}

			globalPlayers.clear();

			for ( auto& pe : playerEntities )
			{
				if ( TLSENV->IsSameObject( pe.instance, minecraft::localPlayer->instance ) )
					continue;

				globalPlayers.push_back( { .instance = TLSENV->NewGlobalRef( pe.instance ) } );
			}
		}

		CacheData temp;

		temp._modelView = ActiveRenderInfo::RawModelViewMatrix();
		temp._projection = ActiveRenderInfo::RawProjectionMatrix();

		temp.modelView = ActiveRenderInfo::ModelViewMatrix();
		temp.projection = ActiveRenderInfo::ProjectionMatrix();


		temp.viewport = ActiveRenderInfo::Viewport();
		temp.renderOffset = ActiveRenderInfo::RenderPos();
		temp.renderPos = minecraft::renderManager->RenderPos();
		//temp.renderPos.y += 3.4f;

		temp.renderPartialTicks = minecraft::timer->renderPartialTicks();

		std::lock_guard<std::mutex> guard( dataMutex );
		cache::data = temp;
	}
}

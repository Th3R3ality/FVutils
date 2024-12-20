#pragma once
#include "../minecraft/world/World/World.h"

#include <mutex>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <array>
#include <vector>

#include "../config/config.h"
#include "../fv/PlayerType.h"
#include "../util/math/vec.h"

namespace cache
{
	inline std::mutex dataMutex;
	inline std::mutex gpMutex;

	struct GlobalPlayer
	{
		jobject instance;
		fvec3 pos;
		fvec3 lastTickPos;
	};
	inline std::vector<GlobalPlayer> globalPlayers;

	inline struct RenderEntitiesData
	{
		/*RenderGlobal*/ jobject instance;
		/*Entity*/ jobject renderViewEntity;
		/*ICamera*/jobject camera;
		float partialTicks;
	} renderEntitiesData;
	//struct PlayerData
	//{
	//	PlayerData() = default;
	//	PlayerData( int i ) {};

	//	std::string realname = "";
	//	std::string name = "";
	//	bool invalidName = false;
	//	fv::PlayerType type = {};
	//	fvec3 pos = { 0.f };
	//	fvec3 lastTickPos = { 0.f };
	//	float health = 0;
	//	float maxHealth = 0;

	//};

	struct CacheData
	{
		//PlayerData local;
		//std::vector<PlayerData> players;
		float renderPartialTicks;
		std::array<double, 16> _modelView;
		std::array<double, 16> _projection;
		matrix modelView;
		matrix projection;
		ivec4 viewport;
		fvec3 renderPos;
		fvec3 renderOffset;

	};
	inline CacheData data = {};

	void UpdateCache();
}
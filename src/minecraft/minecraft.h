#pragma once
#include <memory>

#include "IClass.h"
#include "client/EntityPlayerSP/EntityPlayerSP.h"
#include "client/WorldClient/WorldClient.h"

namespace minecraft
{
	inline std::map<std::string, jmethodID> methodIDs;
	inline std::map<std::string, jfieldID> fieldIDs;

	inline jobject instance = nullptr;
	inline jclass klass = nullptr;
	inline const char* klassPath = "net.minecraft.client.Minecraft";

	inline std::unique_ptr<EntityPlayerSP> localPlayer = nullptr;
	inline std::unique_ptr<WorldClient> world = nullptr;

	void Init();
	void Destroy();

	jobject GetInstance();
	jclass GetClass();

	bool ValidateObjects();
};
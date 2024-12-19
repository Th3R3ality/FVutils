#pragma once
#include <vector>
#include <map>
#include <string>
#include "../imgui/imgui.h"

namespace modules
{
	inline std::vector<void( * )( )> moduleInitialisers = {};

	namespace callbacks
	{
		// places in hooks
		namespace hooks
		{
			// if callback returns true original method will be cancelled
			inline std::vector<bool( * )( )> preRunTick = {};
			inline std::vector<void( * )( )> postRunTick = {};
		}

		// wglSwapBuffers hook
		namespace render
		{
			inline std::map<std::string, std::vector<void( * )( )>> gui = {};

			inline std::vector<void( * )( )> GL3d = {};
			inline std::vector<void( * )( ImDrawList* )> ImGuiOverlay = {};
		}
	}

	void Init();
}
#include "render.h"

#include <format>

#include "helper.h"
#include "../minecraft/minecraft.h"
#include "../cache/cache.h"

namespace render
{
	void DoGui();
	void DoPlayers();
	void DoIndicators();

	ImVec2 clientRect = {};

	void DoFrame()
	{
		RECT _clientRect = {};
		GetClientRect( render::window, &_clientRect );
		clientRect.x = _clientRect.right;
		clientRect.y = _clientRect.bottom;

		if ( render::GuiOpen )
			DoGui();

		if ( !minecraft::objectsAreValid )
			return;

		std::lock_guard<std::mutex> guard(cache::dataMutex);

		DoPlayers();
		DoIndicators();
	}
	void DoGui()
	{
		ImGui::ShowDemoWindow();

		ImGui::Begin("FVutils");
		for ( auto&& p : cache::data.players )
		{
			ImGui::Text( p.name.c_str() );
		}
		ImGui::End();
	}
	void DoPlayers()
	{

	}
	void DoIndicators()
	{
		ImGui::SetNextWindowPos( ImVec2( 0, 0 ) );
		ImGui::SetNextWindowSize( clientRect );
		ImGui::Begin( "Overlay", nullptr,
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground );

		ImDrawList* drawlist = ImGui::GetWindowDrawList();

		ImVec2 textSize = ImGui::CalcTextSize( "FVutils" );

		AddTextShadow( drawlist, ImVec2( clientRect.x - 200, 50 ), ImColor( 255, 0, 255, 255 ), "FVutils" );


		AddTextShadow( drawlist, ImVec2( clientRect.x - 200, textSize.y * 1.5 + 50 ), ImColor( 0, 0, 255, 255 ),
			std::format( "LocalPlayer: {}", (void*)minecraft::localPlayer->instance ).c_str() );

		AddTextShadow( drawlist, ImVec2( clientRect.x - 200, textSize.y * 3 + 50 ), ImColor( 0, 255, 0, 255 ),
			std::format( "World: {}", (void*)minecraft::world->instance ).c_str() );

		//AddTextShadow( drawlist, ImVec2( clientRect.x - 200, textSize.y * 4.5 + 50 ), ImColor( 255, 0, 255, 255 ),
		//	std::format( "Health {}", minecraft::localPlayer->getHealth() ).c_str() );

		ImGui::End();
	}
}
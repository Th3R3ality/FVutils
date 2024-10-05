#include "rendering.h"

#include <format>

#include <gl/GLU.h>

#include "helper.h"
#include "../minecraft/minecraft.h"
#include "../cache/cache.h"
#include "../util/math/mathutils.h"

namespace rendering
{
	void DoGui();
	void DoPlayers();
	void DoIndicators();

	ImVec2 clientRect = {};

	void DoFrame()
	{
		RECT _clientRect = {};
		GetClientRect( rendering::window, &_clientRect );
		clientRect.x = _clientRect.right;
		clientRect.y = _clientRect.bottom;

		if ( rendering::GuiOpen )
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

			ImGui::TextColored( p.type == fv::PlayerType::titan ? ImColor(0xFFFF8888) : ImColor(0xFF88FF88), "%s", p.name.c_str());
		}
		ImGui::End();
	}
	void DoPlayers()
	{
		ImGui::SetNextWindowPos( ImVec2( 0, 0 ) );
		ImGui::SetNextWindowSize( clientRect );
		ImGui::Begin( "Overlay", nullptr,
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground );

		ImDrawList* drawlist = ImGui::GetWindowDrawList();

		for ( auto& p : cache::data.players )
		{
			vec3<double> projected;
			//gluProject( p.pos.x, p.pos.y, p.pos.z, (GLdouble*)&cache::data.modelView, (GLdouble*)&cache::data.projection, (GLint*)&cache::data.viewport, &projected.x, &projected.y, &projected.z );

			std::optional<ivec2> xy = mathutils::WorldToScreen(p.pos, cache::data.modelView, cache::data.projection, clientRect.x, clientRect.y );

			if ( xy.has_value() )
			{
				drawlist->AddText( xy.value(), ImColor( 0xffff00ff ), p.name.c_str() );
			}
		}

		ImGui::End();
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

		AddTextShadow( drawlist, ImVec2( clientRect.x - 200, textSize.y * 4.5 + 50 ), ImColor( 0, 255, 255, 255 ),
			std::format( "Timer: {}", (void*)minecraft::timer->instance ).c_str() );


		ImGui::End();
	}
}
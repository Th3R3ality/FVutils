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

		std::lock_guard<std::mutex> guard( cache::dataMutex );

		DoPlayers();
		DoIndicators();
	}
	void DoGui()
	{
		ImGui::ShowDemoWindow();

		ImGui::Begin( "FVutils" );

		ImGui::Text( "renderPos: %f, %f, %f", cache::data.renderPos.x, cache::data.renderPos.y, cache::data.renderPos.z );
		ImGui::Text( "renderOffset: %f, %f, %f", cache::data.renderOffset.x, cache::data.renderOffset.y, cache::data.renderOffset.z );
		ImGui::Text( "local: %f, %f, %f", cache::data.local.pos.x, cache::data.local.pos.y, cache::data.local.pos.z );

		for ( auto&& p : cache::data.players )
		{
			ImGui::TextColored( p.type == fv::PlayerType::titan ? ImColor( 0xFFFF8888 ) : ImColor( 0xFF88FF88 ), "%s", p.name.c_str() );
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
			//( fvec3() + cache::data.renderOffset )
			fvec3 origin = ( cache::data.renderPos - cache::data.renderOffset ) - p.lastTickPos + ( p.lastTickPos - p.pos ) * cache::data.renderPartialTicks; // At the feet

			std::optional<ivec2> xy = mathutils::WorldToScreen( origin , cache::data.modelView, cache::data.projection, clientRect.x, clientRect.y );

			if ( xy.has_value() )
			{
				drawlist->AddText( xy.value(), ImColor( 0xffff00ff ), p.realname.c_str() );
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
			std::format( "LocalPlayer: {}", ( void* )minecraft::localPlayer->instance ).c_str() );

		AddTextShadow( drawlist, ImVec2( clientRect.x - 200, textSize.y * 3 + 50 ), ImColor( 0, 255, 0, 255 ),
			std::format( "World: {}", ( void* )minecraft::world->instance ).c_str() );

		AddTextShadow( drawlist, ImVec2( clientRect.x - 200, textSize.y * 4.5 + 50 ), ImColor( 0, 255, 255, 255 ),
			std::format( "Timer: {}", ( void* )minecraft::timer->instance ).c_str() );

		AddTextShadow( drawlist, ImVec2( clientRect.x - 200, textSize.y * 6 + 50 ), ImColor( 255, 255, 0, 255 ),
			std::format( "RenderManager: {}", ( void* )minecraft::renderManager->instance ).c_str() );

		ImGui::End();
	}
}
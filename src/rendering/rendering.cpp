#include "rendering.h"

#include <format>

#include <gl/GLU.h>

#define GL_VEC_HELPERS
#define GL_COLOR_HELPERS
#include "../util/GLhelpers.h"

#include "helper.h"
#include "../minecraft/minecraft.h"
#include "../cache/cache.h"
#include "../util/math/mathutils.h"

#include <string>
#include <format>
#include <vector>

#include "../config/config.h"
#include "../util/Color.h"
#include "../cheat/common/Input.h"
#include "../minecraft/client/renderer/RenderGlobal/RenderGlobal.h"
#include "../hooks/hooks.h"
#include "../minecraft/client/renderer/GlStateManager/GlStateManager.h"
#include "../cheat/modules/Modules.h"

namespace rendering
{
	void DoGui();
	void DoPlayers();
	void DoIndicators();

	void DoEsp3D();

	ImVec2 clientRect = {};

	namespace debug
	{
		fvec3 firstForward = {};
		fvec3 firstUp = {};
		fvec3 firstRight = {};
	}

	void DoFrame()
	{
		RECT _clientRect = {};
		GetClientRect( rendering::window, &_clientRect );
		clientRect.x = _clientRect.right;
		clientRect.y = _clientRect.bottom;

		if ( rendering::GuiOpen )
			DoGui();

		DoIndicators();

		if ( !minecraft::objectsAreValid )
			return;

		std::lock_guard<std::mutex> guard( cache::dataMutex );

		// 3d
		DoEsp3D();

		// imgui
		DoPlayers();

		//for (auto&& gp : cache::globalPlayers )
		//{
		//	auto ep = EntityPlayer( gp.instance );
		//	ep.noDeref = true;
		//	
		//	
		//	printf( "%s : %f\n", ep.getName().ToString().c_str(), ep.getHealth());
		//}
	}

	void DoEsp3D()
	{
		glViewport( 0, 0, cache::data.viewport[ 2 ], cache::data.viewport[ 3 ] );

		glPushMatrix();
		glMatrixMode( GL_PROJECTION );
		glLoadMatrixd( cache::data._projection.data() );
		glMatrixMode( GL_MODELVIEW );
		glLoadMatrixd( cache::data._modelView.data() );

		glPushMatrix();
		glEnable( GL_LINE_SMOOTH );
		glEnable( GL_POLYGON_SMOOTH );
		glDisable( GL_DEPTH_TEST );
		glDisable( GL_TEXTURE_2D );
		glDepthMask( false );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glEnable( GL_BLEND );
		glLineWidth( 1.f );

		for ( auto&& callback : modules::callbacks::render::GL3d )
		{
			callback();
		}

		glDisable( GL_BLEND );
		glDepthMask( true );
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_DEPTH_TEST );
		glDisable( GL_POLYGON_SMOOTH );
		glDisable( GL_LINE_SMOOTH );

		glPopMatrix();
		glPopMatrix();
	}

	void DoGui()
	{
		ImGui::ShowDemoWindow();

		ImGui::Begin( "FVutils" );
		{
			ImGui::BeginChild( "debug" );
			ImGui::Checkbox( "Debug Indicators", &config::current.debug.showIndicators );

			ImGui::Text( "firstForward: %f, %f, %f", debug::firstForward.x, debug::firstForward.y, debug::firstForward.z );
			ImGui::Text( "firstUp: %f, %f, %f", debug::firstUp.x, debug::firstUp.y, debug::firstUp.z );
			ImGui::Text( "firstRight: %f, %f, %f", debug::firstRight.x, debug::firstRight.y, debug::firstRight.z );

			ImGui::EndChild();
		}
		ImGui::End();

		for ( auto&& category : modules::callbacks::render::gui )
		{
			ImGui::Begin( category.first.c_str() );
			for ( auto&& mod : category.second )
			{
				mod();
			}
			ImGui::End();
		}

		ImGui::Begin( "Key States" );
		for ( auto&& keyState : Input::keyStates )
		{
			ImGui::Text( "%p | %c | %d", keyState.keyCode, ( char )keyState.keyCode, ( int )keyState.state );
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

		for ( auto&& callback : modules::callbacks::render::ImGuiOverlay )
		{
			callback( drawlist );
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

		if ( config::current.debug.showIndicators )
		{
			AddTextShadow( drawlist, ImVec2( clientRect.x - 200, textSize.y * 1.5 + 50 ), ImColor( 200, 200, 200, 255 ),
				std::format( "Objects Are {}", minecraft::objectsAreValid ? "Valid [+]" : "Invalid [-]" ).c_str() );

			if ( minecraft::localPlayer != nullptr )
				AddTextShadow( drawlist, ImVec2( clientRect.x - 200, textSize.y * 3 + 50 ), ImColor( 0, 0, 255, 255 ),
					std::format( "LocalPlayer: {}", ( void* )minecraft::localPlayer->instance ).c_str() );

			if ( minecraft::world != nullptr )
				AddTextShadow( drawlist, ImVec2( clientRect.x - 200, textSize.y * 4.5 + 50 ), ImColor( 0, 255, 0, 255 ),
					std::format( "World: {}", ( void* )minecraft::world->instance ).c_str() );

			if ( minecraft::timer != nullptr )
				AddTextShadow( drawlist, ImVec2( clientRect.x - 200, textSize.y * 6 + 50 ), ImColor( 0, 255, 255, 255 ),
					std::format( "Timer: {}", ( void* )minecraft::timer->instance ).c_str() );

			if ( minecraft::renderManager != nullptr )
				AddTextShadow( drawlist, ImVec2( clientRect.x - 200, textSize.y * 7.5 + 50 ), ImColor( 255, 255, 0, 255 ),
					std::format( "RenderManager: {}", ( void* )minecraft::renderManager->instance ).c_str() );
		}

		ImGui::End();
	}
}
#include "rendering.h"

#include <format>

#include <gl/GLU.h>

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

namespace rendering
{
	struct _HealthText
	{
		ivec2 pos;
		ImColor color;
		std::string text;
	};
	std::vector<_HealthText> healthTextPositions = {};

	void DoGui();
	void DoPlayers();
	void DoIndicators();

	void DoEsp3D();

	ImVec2 clientRect = {};

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


	}

	void DoEsp3D()
	{
		//GLint viewport[ 4 ]{};

		//glGetIntegerv( GL_VIEWPORT, viewport );
		glViewport( 0, 0, cache::data.viewport[ 2 ], cache::data.viewport[ 3 ] );

		glPushMatrix();
		glMatrixMode( GL_PROJECTION );
		glLoadMatrixd( cache::data._projection.data() );
		glMatrixMode( GL_MODELVIEW );
		glLoadMatrixd( cache::data._modelView.data() );

		glPushMatrix();
		glEnable( GL_LINE_SMOOTH );
		glDisable( GL_DEPTH_TEST );
		glDisable( GL_TEXTURE_2D );
		glDepthMask( false );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glEnable( GL_BLEND );
		glLineWidth( 1.f );

		healthTextPositions.clear();

		for ( auto& p : cache::data.players )
		{
			//fvec3 pos = p.pos - cache::data.renderPos;

			fvec3 pos = ( fvec3() - cache::data.renderPos ) + p.lastTickPos - ( p.lastTickPos - p.pos ) * cache::data.renderPartialTicks; // At the feet

			// box
			Color col = p.type.GetTypeColor();
			glColor4f( col.r, col.g, col.b, col.a );
			glBegin( GL_LINE_STRIP );
			glVertex3f( pos.x - 0.5f, pos.y, pos.z );
			glVertex3f( pos.x - 0.5f, pos.y + 2, pos.z );
			glVertex3f( pos.x + 0.5f, pos.y + 2, pos.z );
			glVertex3f( pos.x + 0.5f, pos.y, pos.z );
			glVertex3f( pos.x - 0.5f, pos.y, pos.z );
			glEnd();



			// health bar
			//background
			glColor4f( 0.0f, 0.0f, 0.f, 1.f );
			glBegin( GL_TRIANGLE_STRIP );
			glVertex3f( pos.x - 0.52f, pos.y, pos.z );
			glVertex3f( pos.x - 0.6f, pos.y, pos.z );
			glVertex3f( pos.x - 0.52f, pos.y + 2, pos.z );
			glVertex3f( pos.x - 0.6f, pos.y + 2, pos.z );
			glEnd();

			// colored part
			float top = 1.98 * ( p.health / p.maxHealth );

			glColor4f( 1.0f - ( p.health / p.maxHealth ), ( p.health / p.maxHealth ), 0.f, 1.f );
			glBegin( GL_TRIANGLE_STRIP );
			glVertex3f( pos.x - 0.54f, pos.y + 0.02, pos.z );
			glVertex3f( pos.x - 0.58f, pos.y + 0.02, pos.z );
			glVertex3f( pos.x - 0.54f, pos.y + top, pos.z );
			glVertex3f( pos.x - 0.58f, pos.y + top, pos.z );
			glEnd();


			std::optional<ivec2> healthw2s = mathutils::Project( fvec3( pos.x - 0.62f, pos.y + top, pos.z ) );
			if ( healthw2s.has_value() )
			{
				ivec2& val = healthw2s.value();
				std::string healthText = std::format( "{}", p.health );
				ImVec2 textSize = ImGui::CalcTextSize( healthText.c_str() );


				ivec2 healthTextFinal = ivec2( /*-textSize.x / 2*/ 0, ( int )( textSize.y / 2 ) ) + val;
				healthTextFinal.y = ( int )clientRect.y - healthTextFinal.y;
				healthTextPositions.emplace_back( _HealthText{ healthTextFinal, ImColor( 1.0f - ( p.health / p.maxHealth ), ( p.health / p.maxHealth ), 0.f, 1.f ), healthText } );

			}
		}


		glDisable( GL_BLEND );
		glDepthMask( true );
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_DEPTH_TEST );
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

			ImGui::Checkbox( "Name", &config::current.render.players.name );

			ImGui::Checkbox( "2D", &config::current.render.players.d2.master );
			if ( config::current.render.players.d2.master )
			{

			}

			ImGui::Checkbox( "3D", &config::current.render.players.d3.master );
			if ( config::current.render.players.d3.master )
			{
				ImGui::Checkbox( "Health Bar", &config::current.render.players.d2.healthbar );
				if ( config::current.render.players.d2.healthbar )
				{
					ImGui::Checkbox( "Health Bar Number", &config::current.render.players.d2.healthbarnumber );
				}
			}

			ImGui::EndChild();
		}
		ImGui::End();
		//ImGui::Text( "renderPos: %f, %f, %f", cache::data.renderPos.x, cache::data.renderPos.y, cache::data.renderPos.z );
		//ImGui::Text( "renderOffset: %f, %f, %f", cache::data.renderOffset.x, cache::data.renderOffset.y, cache::data.renderOffset.z );
		//ImGui::Text( "local: %f, %f, %f", cache::data.local.pos.x, cache::data.local.pos.y, cache::data.local.pos.z );

		ImGui::Begin( "Combat" );
		{
			ImGui::Checkbox( "Clicker", &config::current.combat.clicker.enabled );
			if ( config::current.combat.clicker.enabled )
			{
				ImGui::Indent( 16.f );

				ImGui::Checkbox( "Left", &config::current.combat.clicker.left.enabled );
				ImGui::DragIntRange2( "CPS##leftclicker",
					&config::current.combat.clicker.left.minCps,
					&config::current.combat.clicker.left.maxCps,
					1.0f, 1, 40 );
				ImGui::Checkbox( "Right", &config::current.combat.clicker.right.enabled );
				ImGui::DragIntRange2( "CPS##rightclicker",
					&config::current.combat.clicker.right.minCps,
					&config::current.combat.clicker.right.maxCps,
					1.0f, 1, 40 );

				ImGui::Unindent( 16.f );

			}
		}
		ImGui::End();


		ImGui::Begin( "Players In Render" );
		{
			for ( auto&& p : cache::data.players )
			{
				ImGui::TextColored( p.type.GetRankColor(), "%s ", p.type.GetRankString().c_str(), p.name.c_str() );
				ImGui::SameLine();
				ImGui::TextColored( p.type.GetTypeColor(), "%s %s", p.type.GetTypeString().c_str(), p.name.c_str() );
			}
		}
		ImGui::End();

		ImGui::Begin("Key States");
		for ( auto&& keyState : Input::keyStates )
		{
			ImGui::Text( "%p | %c | %d", keyState.keyCode, (char)keyState.keyCode, (int)keyState.state );
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
			//fvec3 origin = ( cache::data.renderPos - cache::data.renderOffset ) - p.lastTickPos + ( p.lastTickPos - p.pos ) * cache::data.renderPartialTicks; // At the feet
			fvec3 origin = ( fvec3() - cache::data.renderPos ) + p.lastTickPos - ( p.lastTickPos - p.pos ) * cache::data.renderPartialTicks;



			//vec3<double> projected;
			//if ( GL_TRUE == gluProject( origin.x, origin.y + 2.f, origin.z, cache::data._modelView.data(), cache::data._projection.data(), cache::data.viewport, &projected.x, &projected.y, &projected.z )
			//	&& projected.z < 1.0)
			fvec3 namePos = origin; namePos.y += 2.f;
			std::optional<ivec2> namew2s = mathutils::Project( namePos );
			if ( namew2s.has_value() )
			{
				ivec2& val = namew2s.value();
				ImVec2 nameSize = ImGui::CalcTextSize( p.realname.c_str() );
				AddTextShadow( drawlist, ImVec2( val.x - nameSize.x / 2, clientRect.y - val.y - nameSize.y ), p.type.GetTypeColor(), p.realname.c_str() );
			}

			//std::optional<ivec2> xy = mathutils::WorldToScreen( origin , cache::data.modelView, cache::data.projection, clientRect.x, clientRect.y );
			//if ( xy.has_value() )
			//{
			//	drawlist->AddText( xy.value(), ImColor( 0xffff00ff ), p.realname.c_str() );
			//}
		}

		for ( auto& health : healthTextPositions )
		{
			AddTextShadow( drawlist, health.pos, health.color, health.text.c_str() );
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
				std::format( "Objects Are {}", minecraft::objectsAreValid ? "Valid [+]" : "Invalid [-]").c_str());

			if (minecraft::localPlayer != nullptr )
				AddTextShadow( drawlist, ImVec2( clientRect.x - 200, textSize.y * 3 + 50 ), ImColor( 0, 0, 255, 255 ),
					std::format( "LocalPlayer: {}", ( void* )minecraft::localPlayer->instance ).c_str() );

			if (minecraft::world != nullptr )
				AddTextShadow( drawlist, ImVec2( clientRect.x - 200, textSize.y * 4.5 + 50 ), ImColor( 0, 255, 0, 255 ),
					std::format( "World: {}", ( void* )minecraft::world->instance ).c_str() );

			if (minecraft::timer != nullptr )
				AddTextShadow( drawlist, ImVec2( clientRect.x - 200, textSize.y * 6 + 50 ), ImColor( 0, 255, 255, 255 ),
					std::format( "Timer: {}", ( void* )minecraft::timer->instance ).c_str() );
			
			if (minecraft::renderManager != nullptr )
				AddTextShadow( drawlist, ImVec2( clientRect.x - 200, textSize.y * 7.5 + 50 ), ImColor( 255, 255, 0, 255 ),
					std::format( "RenderManager: {}", ( void* )minecraft::renderManager->instance ).c_str() );
		}

		ImGui::End();
	}
}
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

		if ( !minecraft::objectsAreValid )
			return;

		std::lock_guard<std::mutex> guard( cache::dataMutex );

		// 3d
		DoEsp3D();

		// imgui
		DoPlayers();
		DoIndicators();

	}

	void DoEsp3D()
	{
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		glViewport(0, 0, viewport[2], viewport[3]);

		glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixd(cache::data._projection.data());
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(cache::data._modelView.data());

		glPushMatrix();
		glEnable(GL_LINE_SMOOTH);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);
		glDepthMask(false);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glLineWidth(1.f);


		healthTextPositions.clear();

		for ( auto& p : cache::data.players )
		{
			//fvec3 pos = p.pos - cache::data.renderPos;

			fvec3 pos = ( fvec3() - cache::data.renderPos ) + p.lastTickPos - ( p.lastTickPos - p.pos ) * cache::data.renderPartialTicks; // At the feet
			//			( fvec3() - cache::data.renderPos ) + p.lastTickPos - ( p.lastTickPos - p.pos ) * cache::data.renderPartialTicks;
			
			// box
			glColor4f(1.0f, 1.f, 1.f, 1.f);
			glBegin(GL_LINE_STRIP);
			glVertex3f(pos.x - 0.5f, pos.y, pos.z);
			glVertex3f(pos.x - 0.5f, pos.y + 2, pos.z);
			glVertex3f(pos.x + 0.5f, pos.y + 2, pos.z);
			glVertex3f(pos.x + 0.5f, pos.y, pos.z);
			glVertex3f(pos.x - 0.5f, pos.y, pos.z);
			glEnd();



			// health bar
			//background
			glColor4f(0.0f, 0.0f, 0.f, 1.f);
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(pos.x - 0.52f, pos.y, pos.z);
			glVertex3f(pos.x - 0.6f, pos.y, pos.z);
			glVertex3f(pos.x - 0.52f, pos.y + 2, pos.z);
			glVertex3f(pos.x - 0.6f, pos.y + 2, pos.z);
			glEnd();

			// colored part
			float top = 1.98 * ( p.health / p.maxHealth );

			glColor4f(1.0f - (p.health / p.maxHealth), (p.health / p.maxHealth), 0.f, 1.f);
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(pos.x - 0.54f, pos.y + 0.02, pos.z);
			glVertex3f(pos.x - 0.58f, pos.y + 0.02, pos.z);
			glVertex3f(pos.x - 0.54f, pos.y + top, pos.z);
			glVertex3f(pos.x - 0.58f, pos.y + top, pos.z);
			glEnd();


			std::optional<ivec2> healthw2s = mathutils::Project( fvec3(pos.x - 0.56f, pos.y + top, pos.z) );
			if ( healthw2s.has_value() )
			{
				ivec2& val = healthw2s.value();
				std::string healthText = std::format( "{}", p.health );
				ImVec2 textSize = ImGui::CalcTextSize( healthText.c_str() );


				ivec2 healthTextFinal = ivec2(-textSize.x/2, textSize.y) + val;
				healthTextFinal.y = clientRect.y - healthTextFinal.y;
				healthTextPositions.emplace_back( _HealthText{healthTextFinal, ImColor(1.0f - (p.health / p.maxHealth), (p.health / p.maxHealth), 0.f, 1.f), healthText});

			}
		}


		glDisable(GL_BLEND);
		glDepthMask(true);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_LINE_SMOOTH);

		glPopMatrix();
		glPopMatrix();
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
				AddTextShadow(drawlist, ImVec2( val.x - nameSize.x / 2, clientRect.y - val.y - nameSize.y ), ImColor( 0xffffffff ), p.realname.c_str());
			}

			//std::optional<ivec2> xy = mathutils::WorldToScreen( origin , cache::data.modelView, cache::data.projection, clientRect.x, clientRect.y );
			//if ( xy.has_value() )
			//{
			//	drawlist->AddText( xy.value(), ImColor( 0xffff00ff ), p.realname.c_str() );
			//}
		}

		for ( auto& health : healthTextPositions )
		{
			AddTextShadow(drawlist, health.pos, health.color, health.text.c_str());
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
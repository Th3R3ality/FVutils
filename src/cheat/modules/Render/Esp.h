#pragma once
#include "../ModuleBase.h"
#include "../../../imgui/imgui.h"
#include "../../../config/config.h"
#include "../../../cache/cache.h"
#include <gl/GL.h>

#include "../util/GLhelpers.h"

void GL25d();
void GLbox();
class Esp : public ModuleBase
{
public:
	MODULE_STRUCTOR( Esp );

	static void Initialise()
	{
		modules::callbacks::render::gui[ "Render" ].push_back( &gui );
		modules::callbacks::render::GL3d.push_back( &GL3d );
	}

	static void gui()
	{

		ImGui::Checkbox( "Names", &config::current.render.esp.names.enabled );
		if ( config::current.render.esp.names.enabled )
		{
			ImGui::Indent( 16.f );
			ImGui::Checkbox( "Health", &config::current.render.esp.names.health );
			ImGui::Checkbox( "Absorption", &config::current.render.esp.names.absorption );
			ImGui::Unindent( 16.f );
		}

		ImGui::Checkbox( "2D", &config::current.render.esp.d2.enabled );
		if ( config::current.render.esp.d2.enabled )
		{
			ImGui::Indent( 16.f );
			ImGui::Unindent( 16.f );
		}

		ImGui::Checkbox( "3D", &config::current.render.esp.d3.enabled );
		if ( config::current.render.esp.d3.enabled )
		{
			ImGui::Indent( 16.f );
			ImGui::Combo("mode", (int*)&config::current.render.esp.d3.mode, "2.5D\0Box\0\0");
			ImGui::Indent( 16.f );
			switch ( config::current.render.esp.d3.mode )
			{
			case config::Config::__render::__esp::__d3::ESP25d:
			{
				ImGui::Checkbox( "Box", &config::current.render.esp.d3.d25.box );
				ImGui::Checkbox( "Health Bar", &config::current.render.esp.d3.d25.healthbar );
				break;
			}
			case config::Config::__render::__esp::__d3::ESPbox:
			{

				break;
			}
			}
			ImGui::Unindent( 16.f );
			ImGui::Unindent( 16.f );
		}
	}

	
	static void GL3d()
	{
		if ( !config::current.render.esp.d3.enabled )
			return;

		if ( config::current.render.esp.d3.mode == config::Config::__render::__esp::__d3::ESP25d )
			GL25d();
		if ( config::current.render.esp.d3.mode == config::Config::__render::__esp::__d3::ESPbox )
			GLbox();
	}
};

void GL25d()
{
	fvec3 lpPos = minecraft::localPlayer->GetPos();

	for ( auto&& gp : cache::globalPlayers )
	{
		if ( gp.instance == nullptr )
			continue;

		EntityPlayer p = gp.instance;
		p.noDeref = true;

		fvec3 pos = ( fvec3{} - cache::data.renderPos ) + p.GetLastTickPos() - ( p.GetLastTickPos() - p.GetPos() ) * cache::data.renderPartialTicks;

		// ( pos - lpPos );
		fvec3 temp = pos; temp.y = 0.f;
		temp.normalize();
		const fvec3 forward = temp;
		const fvec3 up = fvec3{ 0,1,0 };
		const fvec3 right = forward.cross( up ); //right.normalize();
		const fvec3 halfright = right * 0.5f;

		if ( config::current.render.esp.d3.d25.box )
		{
			// box
			// Color col = p.type.GetTypeColor();
			glColor4f( Color( 1.f ) );
			glBegin( GL_LINE_STRIP );
			glVertex3f( pos - halfright );
			glVertex3f( pos + halfright );
			glVertex3f( pos + halfright + up * 2.f );
			glVertex3f( pos - halfright + up * 2.f );
			glVertex3f( pos - halfright );
			glEnd();
		}


		if ( config::current.render.esp.d3.d25.healthbar )
		{
			// health bar
			// background
			glColor4f( 0.0f, 0.0f, 0.f, 1.f );
			glBegin( GL_TRIANGLE_STRIP );
			glVertex3f( pos + halfright + halfright * 0.1f );
			glVertex3f( pos + halfright + halfright * 0.2f );
			glVertex3f( pos + halfright + halfright * 0.1f + up * 2.f );
			glVertex3f( pos + halfright + halfright * 0.2f + up * 2.f );
			glEnd();

			//	// colored part
			//	float top = 1.98 * ( p.health / p.maxHealth );

			//	glColor4f( 1.0f - ( p.health / p.maxHealth ), ( p.health / p.maxHealth ), 0.f, 1.f );
			//	glBegin( GL_TRIANGLE_STRIP );
			//	glVertex3f( pos.x - 0.54f, pos.y + 0.02, pos.z );
			//	glVertex3f( pos.x - 0.58f, pos.y + 0.02, pos.z );
			//	glVertex3f( pos.x - 0.54f, pos.y + top, pos.z );
			//	glVertex3f( pos.x - 0.58f, pos.y + top, pos.z );
			//	glEnd();

			const float health = p.getHealth();
			const float maxHealth = p.getMaxHealth();
			const fvec3 healthUp = up * 2.f * ( health / maxHealth );

			glColor4f( 1.0f - ( health / maxHealth ), ( health / maxHealth ), 0.f, 1.f );
			glBegin( GL_TRIANGLE_STRIP );
			glVertex3f( pos + halfright + halfright * 0.1f );
			glVertex3f( pos + halfright + halfright * 0.2f );
			glVertex3f( pos + halfright + halfright * 0.1f + healthUp );
			glVertex3f( pos + halfright + halfright * 0.2f + healthUp );
			glEnd();
		}
	}
}
void GLbox()
{

}

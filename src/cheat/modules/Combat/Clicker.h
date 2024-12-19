#pragma once
#include "../ModuleBase.h"
#include "../../../config/config.h"
#include "../../common/Input.h"
#include "../../common/ClickScheduler.h"
#include "../../../minecraft/minecraft.h"
#include "../../../rendering/rendering.h"
#include "../../../imgui/imgui.h"

class Clicker : public ModuleBase
{
public:
	MODULE_STRUCTOR( Clicker );

	static void Initialise()
	{
		modules::callbacks::hooks::postRunTick.push_back( &run );
		modules::callbacks::render::gui[ "Combat" ].push_back( &gui );
	}

	static void gui()
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

	static void run()
	{
		do
		{
			if ( !config::current.combat.clicker.enabled ) break;
			if ( rendering::GuiOpen ) break;
			if ( Minecraft::IsInGuiState() ) break;
			//if ( ignoreBlocks && SDK::Minecraft->GetMouseOver().IsTypeOfBlock() ) return;

			static std::array<int, 20> leftclickSchedule = { 0 };
			static int leftnextClickIdx = 0;
			if ( leftnextClickIdx == 0 )
			{
				leftclickSchedule = ClickScheduler::Generate(
					ClickScheduler::ClickMethod::STABILISED,
					config::current.combat.clicker.left.minCps,
					config::current.combat.clicker.left.maxCps );
			}
			if ( config::current.combat.clicker.left.enabled && Input::GetMouseState( MK_LBUTTON ) )
			{
				for ( int i = 0; i < leftclickSchedule[ leftnextClickIdx ]; i++ )
				{
					POINT pos_cursor;
					GetCursorPos( &pos_cursor );
					SendMessageW( rendering::window, WM_LBUTTONDOWN, 0x1337, MAKELPARAM( pos_cursor.x, pos_cursor.y ) );
					SendMessageW( rendering::window, WM_LBUTTONUP, 0x1337, MAKELPARAM( pos_cursor.x, pos_cursor.y ) );
				}
			}
			leftnextClickIdx++; leftnextClickIdx %= 20;

			static std::array<int, 20> rightclickSchedule = { 0 };
			static int rightnextClickIdx = 0;
			if ( rightnextClickIdx == 0 )
			{
				rightclickSchedule = ClickScheduler::Generate(
					ClickScheduler::ClickMethod::STABILISED,
					config::current.combat.clicker.right.minCps,
					config::current.combat.clicker.right.maxCps );
			}
			if ( config::current.combat.clicker.right.enabled && Input::GetMouseState( MK_RBUTTON ) )
			{
				for ( int i = 0; i < rightclickSchedule[ rightnextClickIdx ]; i++ )
				{
					POINT pos_cursor;
					GetCursorPos( &pos_cursor );
					SendMessageW( rendering::window, WM_RBUTTONDOWN, 0x1337, MAKELPARAM( pos_cursor.x, pos_cursor.y ) );
					SendMessageW( rendering::window, WM_RBUTTONUP, 0x1337, MAKELPARAM( pos_cursor.x, pos_cursor.y ) );
				}
			}
			rightnextClickIdx++; rightnextClickIdx %= 20;

		} while ( false );
	}
};


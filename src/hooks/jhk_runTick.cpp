#include "hooks.h"
#include "../config/config.h"
#include "../rendering/rendering.h"
#include "../minecraft/minecraft.h"

#include "../cheat/common/ClickScheduler.h"
#include "../cache/cache.h"

namespace hooks
{
	void jhk_runTick( HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel )
	{
		JNIEnv* env = thread->get_env();

		if ( !TlsSetValue( java::envTlsIndex, env ) )
		{
			printf( "TlsSetValue error" );
			return;
		}

		printf( "runTick\n" );

		if ( ( minecraft::objectsAreValid = minecraft::ValidateObjects() ) )
		{
			cache::UpdateCache();
		}

		//printf("runTick thread %d: lpvData=%lx\n", GetCurrentThreadId(), env);
		//java::TestTLS();
		do
		{
			if ( !config::current.combat.clicker.enabled ) break;
			//if ( rendering::GuiOpen ) break;
			if ( Minecraft::IsInGuiState() ) break;
			//if ( ignoreBlocks && SDK::Minecraft->GetMouseOver().IsTypeOfBlock() ) return;

			static std::array<int, 20> clickSchedule = { 0 };
			static int nextClickIdx = 0;

			if ( nextClickIdx == 0 )
			{
				clickSchedule = ClickScheduler::Generate(
					ClickScheduler::ClickMethod::STABILISED,
					config::current.combat.clicker.left.minCps,
					config::current.combat.clicker.left.maxCps );
			}


			if (config::current.combat.clicker.left.enabled && GetAsyncKeyState(VK_LBUTTON))
			{
				for ( int i = 0; i < clickSchedule[ nextClickIdx ]; i++ )
				{
					POINT pos_cursor;
					GetCursorPos(&pos_cursor);
					SendMessageW( rendering::window, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM( pos_cursor.x, pos_cursor.y ) );
					SendMessageW( rendering::window, WM_LBUTTONUP, 0, MAKELPARAM( pos_cursor.x, pos_cursor.y ) );
				}
			}
			else if ( config::current.combat.clicker.right.enabled && GetAsyncKeyState( VK_RBUTTON ) )
			{
				for ( int i = 0; i < clickSchedule[ nextClickIdx ]; i++ )
				{
					POINT pos_cursor;
					GetCursorPos(&pos_cursor);
					SendMessageW( rendering::window, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM( pos_cursor.x, pos_cursor.y ) );
					SendMessageW( rendering::window, WM_RBUTTONUP, 0, MAKELPARAM( pos_cursor.x, pos_cursor.y ) );
				}
			}

			nextClickIdx++; nextClickIdx %= 20;
		} while ( false );


	}
}
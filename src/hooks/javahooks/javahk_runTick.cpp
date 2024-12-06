#include "../hooks.h"
#include "../../config/config.h"
#include "../../rendering/rendering.h"
#include "../../minecraft/minecraft.h"
#include "../../cheat/common/ClickScheduler.h"
#include "../../cache/cache.h"
#include "../../global.h"
#include "../../cheat/common/Input.h"

namespace hooks
{
	void javahk_runTick( HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel )
	{
		if ( global::glUnhookWant )
			return;

		JNIEnv* env = thread->get_env();

		if ( !TlsSetValue( java::envTlsIndex, env ) )
		{
			printf( "TlsSetValue error" );
			return;
		}

		//printf( "runTick\n" );



		//printf("runTick thread %d: lpvData=%lx\n", GetCurrentThreadId(), env);
		//java::TestTLS();
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
			if (config::current.combat.clicker.left.enabled && Input::GetMouseState(MK_LBUTTON))
			{
				for ( int i = 0; i < leftclickSchedule[ leftnextClickIdx ]; i++ )
				{
					POINT pos_cursor;
					GetCursorPos(&pos_cursor);
					SendMessageW( rendering::window, WM_LBUTTONDOWN,  0x1337, MAKELPARAM( pos_cursor.x, pos_cursor.y ) );
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
			if ( config::current.combat.clicker.right.enabled && Input::GetMouseState(MK_RBUTTON) )
			{
				for ( int i = 0; i < rightclickSchedule[ rightnextClickIdx ]; i++ )
				{
					POINT pos_cursor;
					GetCursorPos(&pos_cursor);
					SendMessageW( rendering::window, WM_RBUTTONDOWN, 0x1337, MAKELPARAM( pos_cursor.x, pos_cursor.y ) );
					SendMessageW( rendering::window, WM_RBUTTONUP, 0x1337, MAKELPARAM( pos_cursor.x, pos_cursor.y ) );
				}
			}
			rightnextClickIdx++; rightnextClickIdx %= 20;

		} while ( false );


	}
}
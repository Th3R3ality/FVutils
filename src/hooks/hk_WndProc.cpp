#include "hooks.h"
#include <Windows.h>
#include "../rendering/rendering.h"
#include "../cheat/common/Input.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace hooks
{
	LRESULT CALLBACK hkWndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		if (msg == WM_KEYDOWN)
		{
			if (wParam == VK_INSERT)
				rendering::GuiOpen = !rendering::GuiOpen;
			if (wParam == VK_ESCAPE && rendering::GuiOpen)
				rendering::GuiOpen = false;

			Input::DeltaKey( wParam, 1 );
		}
		if ( msg == WM_KEYUP )
		{
			Input::DeltaKey( wParam, -1 );
		}

		if ( rendering::GuiOpen && hooks::initialised )
		{
			ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
			return true;
		}

		return ( ( decltype( &hkWndProc ) )wndProcOrig )( hwnd, msg, wParam, lParam );
	}
}
#include "hooks.h"
#include <Windows.h>
#include "../render/render.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace hooks
{
	LRESULT CALLBACK hkWndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		if (msg == WM_KEYDOWN)
		{
			if (wParam == VK_INSERT)
				render::GuiOpen = !render::GuiOpen;
			if (wParam == VK_ESCAPE && render::GuiOpen)
				render::GuiOpen = false;
		}

		if ( render::GuiOpen && hooks::initialised )
		{
			ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
			return true;
		}

		return ( ( decltype( &hkWndProc ) )wndProcOrig )( hwnd, msg, wParam, lParam );
	}
}
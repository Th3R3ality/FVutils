#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <wingdi.h>

#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_opengl2.h"
#include "../imgui/imgui.h"

namespace rendering
{
	inline HGLRC glContext = nullptr;
	inline HDC hdc = nullptr;
	inline HWND window;
	inline HGLRC glContextOrig;
	inline ImGuiContext* imGuiContext;

	inline bool GuiOpen = false;

	void DoFrame();
}
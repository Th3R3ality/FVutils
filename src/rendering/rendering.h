#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <wingdi.h>

#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_opengl2.h"
#include "../imgui/imgui.h"

namespace rendering
{
	inline HDC hdc = nullptr;
	inline HWND window = NULL;
	inline HGLRC glContext = nullptr;
	inline HGLRC glContextOrig = nullptr;
	inline ImGuiContext* imGuiContext;

	inline bool GuiOpen = false;

	void DoFrame();
}
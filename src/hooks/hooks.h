#pragma once
#include <Windows.h>
#include <jni.h>
#include "../java/java.h"
#include "../JavaHook/JavaHook.h"

#include "../minhook/include/MinHook.h"

inline void VMTEntryHook(uintptr_t VMT, size_t Index, uintptr_t Detour, uintptr_t* ppOrig = nullptr)
{
	uintptr_t* Address = (uintptr_t*)(VMT + Index * sizeof(uintptr_t));

	DWORD OldProtection{ 0 };
	VirtualProtect(Address, sizeof(uintptr_t), PAGE_READWRITE, &OldProtection);
	if (ppOrig != nullptr)
		*ppOrig = *Address;
	*Address = Detour;
	VirtualProtect(Address, sizeof(uintptr_t), OldProtection, &OldProtection);
}

#define DECL_JHOOK(name) \
void name ( HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel )

namespace hooks
{
	inline bool initialised = false;
	void Init();
	void Destroy();

	inline uintptr_t vtable = 0;
	inline void* wglSwapBuffersOrig = nullptr;
	inline LONG_PTR wndProcOrig = 0;

	//void jhk_handleChat( HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel );
	//void jhk_renderName( HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel );

	DECL_JHOOK( jhk_handleChat );
	DECL_JHOOK( jhk_renderName );
	DECL_JHOOK( jhk_runTick );
	DECL_JHOOK( jhk_runGameLoop );
	DECL_JHOOK( jhk_clickMouse );

	LRESULT CALLBACK hkWndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
	BOOL __stdcall hkwglSwapBuffers( IN HDC hdc );
}
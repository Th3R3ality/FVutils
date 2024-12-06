#pragma once
#include <Windows.h>
#include <jni.h>
#include "../java/java.h"
#include "../minhook/include/MinHook.h"

#include "../JavaHook/JavaHook.h"

#include "../jnihook/jnihook.h"
#include "../jnihook/jnihook.hpp"

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

#define DECL_JAVA_HOOK(name) \
void name ( HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel )

#define DECL_JNI_HOOK(ret, name, args) \
inline jmethodID __orig_mid_ ## name = nullptr; \
JNIEXPORT ret JNICALL name args


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

	DECL_JAVA_HOOK( javahk_handleChat );
	DECL_JAVA_HOOK( javahk_renderName );
	DECL_JAVA_HOOK( javahk_runTick );
	DECL_JAVA_HOOK( javahk_runGameLoop );
	DECL_JAVA_HOOK( javahk_clickMouse );
	DECL_JAVA_HOOK( javahk_endStartSection );

	DECL_JNI_HOOK( void, jnihk_runGameLoop, ( JNIEnv* env, jobject instance ) );
	DECL_JNI_HOOK( void, jnihk_runTick, ( JNIEnv* env, jobject instance ) );
	
	//inline jmethodID __orig_mid_runGameLoop = nullptr;
	//JNIEXPORT void JNICALL jnihk_runGameLoop(JNIEnv *jni, jobject obj);

	LRESULT CALLBACK hkWndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
	BOOL __stdcall hkwglSwapBuffers( IN HDC hdc );
}
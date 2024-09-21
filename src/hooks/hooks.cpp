#include "hooks.h"
#include <iostream>
#include "../global.h"
#include "../render/render.h"

#define INDEX_ENDSCENE 42
#define INDEX_PRESENT 17
#define INDEX_RESET 16

uintptr_t GetDeviceVtable()
{
	IDirect3D9* pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	if ( !pD3D )
		return NULL;

	IDirect3DDevice9* pDummyDevice = NULL;

	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.Windowed = false;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GetForegroundWindow();

	HRESULT dummyDeviceCreated = pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice );

	if ( dummyDeviceCreated != S_OK )
	{
		d3dpp.Windowed = !d3dpp.Windowed;
		dummyDeviceCreated = pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice );

		if ( dummyDeviceCreated != S_OK )
		{
			pD3D->Release();
			return NULL;
		}
	}

	uintptr_t _vtable = *( uintptr_t* )pDummyDevice;

	pDummyDevice->Release();
	pD3D->Release();

	return _vtable;
}

void hooks::Init()
{
	MH_Initialize();

	auto hMod = GetModuleHandleA( "OPENGL32.dll" );
	if ( !hMod ) return;

	MH_CreateHook( GetProcAddress( hMod, "wglSwapBuffers" ), hkwglSwapBuffers, &wglSwapBuffersOrig );


	MH_EnableHook( MH_ALL_HOOKS );



}

void hooks::Destroy()
{


	while ( !global::glUnhookWaiting )
	{
		global::glUnhookWant = true;
		Sleep( 1 );
	}
	//if ( EndSceneOrig )
	//{
	//	VMTEntryHook( vtable, INDEX_ENDSCENE, EndSceneOrig );
	//}

	MH_DisableHook( MH_ALL_HOOKS );
	MH_Uninitialize();
}

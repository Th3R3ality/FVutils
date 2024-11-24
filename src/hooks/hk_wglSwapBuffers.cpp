#include "hooks.h"
#include <iostream>

#include <jni.h>
#include <jvmti.h>

#include "../rendering/rendering.h"
#include "../global.h"

namespace hooks
{
	BOOL __stdcall hkwglSwapBuffers( IN  HDC hdc )
	{
		if ( global::glUnhookWant )
		{
			if ( !global::glUnhookWaiting )
			{
				SetWindowLongPtrW( rendering::window, GWLP_WNDPROC, wndProcOrig );
			}
			global::glUnhookWaiting = true;
			return ( ( decltype( &hkwglSwapBuffers ) )wglSwapBuffersOrig )( hdc );
		}

		if ( rendering::window != WindowFromDC( hdc ) && initialised )
		{
			printf( "FVutils: reset window\n" );
			rendering::window = WindowFromDC( hdc );

			rendering::glContextOrig = wglGetCurrentContext();
			wglMakeCurrent( hdc, wglCreateContext( hdc ) );

			ImGui_ImplOpenGL2_Shutdown();
			ImGui_ImplWin32_Shutdown();

			ImGui_ImplWin32_Init( rendering::window );
			ImGui_ImplOpenGL2_Init();

			wndProcOrig = SetWindowLongPtrW( rendering::window, GWLP_WNDPROC, ( LONG_PTR )hkWndProc );

			wglMakeCurrent( hdc, rendering::glContextOrig );

			return ( ( decltype( &hkwglSwapBuffers ) )wglSwapBuffersOrig )( hdc );
		}

		rendering::hdc = hdc;
		rendering::window = WindowFromDC( hdc );
		rendering::glContextOrig = wglGetCurrentContext();

		if ( !initialised )
		{
			wndProcOrig = SetWindowLongPtrW( rendering::window, GWLP_WNDPROC, ( LONG_PTR )hkWndProc );

			rendering::glContextMenu = wglCreateContext(rendering::hdc);
			wglMakeCurrent(rendering::hdc, rendering::glContextMenu);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			GLint m_viewport[4];
			glGetIntegerv(GL_VIEWPORT, m_viewport);

			glOrtho(0, m_viewport[2], m_viewport[3], 0, 1, -1);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glClearColor(0, 0, 0, 0);

			rendering::imGuiContext = ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.Fonts->AddFontDefault();

			ImGui_ImplWin32_Init( rendering::window );
			ImGui_ImplOpenGL2_Init();

			//io.Fonts->AddFontFromMemoryTTF( 0, sizeof( 0 ), 0 );

			initialised = true;
		}

		wglMakeCurrent(rendering::hdc, rendering::glContextMenu);

		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		rendering::DoFrame();

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

		wglMakeCurrent(rendering::hdc, rendering::glContextOrig);
		return ( ( decltype( &hkwglSwapBuffers ) )wglSwapBuffersOrig )( hdc );
	}
}
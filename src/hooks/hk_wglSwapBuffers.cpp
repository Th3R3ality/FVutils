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
		rendering::hdc = hdc;
		rendering::window = WindowFromDC( hdc );
		rendering::glContextOrig = wglGetCurrentContext();

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

		if ( !initialised )
		{
			rendering::glContext = wglCreateContext( rendering::hdc );;
			wglMakeCurrent( rendering::hdc, rendering::glContext );

			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();

			GLint m_viewport[ 4 ];
			glGetIntegerv( GL_VIEWPORT, m_viewport );

			glOrtho( 0, m_viewport[ 2 ], m_viewport[ 3 ], 0, 1, -1 );
			glMatrixMode( GL_MODELVIEW );
			glLoadIdentity();
			glClearColor( 0, 0, 0, 0 );

			rendering::imGuiContext = ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();

			ImGui_ImplWin32_Init( rendering::window );
			ImGui_ImplOpenGL2_Init();

			wndProcOrig = SetWindowLongPtrW( rendering::window, GWLP_WNDPROC, ( LONG_PTR )hkWndProc );

			initialised = true;
		}

		wglMakeCurrent(rendering::hdc, rendering::glContext);

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
#include "hooks.h"
#include <iostream>

#include <jni.h>
#include <jvmti.h>

#include "../render/render.h"
#include "../global.h"

namespace hooks
{
	BOOL __stdcall hkwglSwapBuffers( IN  HDC hdc )
	{
		render::hdc = hdc;
		render::window = WindowFromDC( hdc );
		render::glContextOrig = wglGetCurrentContext();

		if ( global::glUnhookWant )
		{
			if ( !global::glUnhookWaiting )
			{
				SetWindowLongPtrW( render::window, GWLP_WNDPROC, wndProcOrig );
			}
			global::glUnhookWaiting = true;
			return ( ( decltype( &hkwglSwapBuffers ) )wglSwapBuffersOrig )( hdc );
		}

		if ( render::window != WindowFromDC( hdc ) && initialised )
		{
			render::window = WindowFromDC( hdc );

			render::glContextOrig = wglGetCurrentContext();
			wglMakeCurrent( hdc, wglCreateContext( hdc ) );

			ImGui_ImplOpenGL2_Shutdown();
			ImGui_ImplWin32_Shutdown();

			ImGui_ImplWin32_Init( render::window );
			ImGui_ImplOpenGL2_Init();

			wndProcOrig = SetWindowLongPtrW( render::window, GWLP_WNDPROC, ( LONG_PTR )hkWndProc );

			wglMakeCurrent( hdc, render::glContextOrig );

			return ( ( decltype( &hkwglSwapBuffers ) )wglSwapBuffersOrig )( hdc );
		}

		if ( !initialised )
		{
			render::glContext = wglCreateContext( render::hdc );;
			wglMakeCurrent( render::hdc, render::glContext );

			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();

			GLint m_viewport[ 4 ];
			glGetIntegerv( GL_VIEWPORT, m_viewport );

			glOrtho( 0, m_viewport[ 2 ], m_viewport[ 3 ], 0, 1, -1 );
			glMatrixMode( GL_MODELVIEW );
			glLoadIdentity();
			glClearColor( 0, 0, 0, 0 );

			render::imGuiContext = ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();

			ImGui_ImplWin32_Init( render::window );
			ImGui_ImplOpenGL2_Init();

			wndProcOrig = SetWindowLongPtrW( render::window, GWLP_WNDPROC, ( LONG_PTR )hkWndProc );

			initialised = true;
		}

		wglMakeCurrent(render::hdc, render::glContext);

		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		render::DoFrame();

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

		wglMakeCurrent(render::hdc, render::glContextOrig);
		return ( ( decltype( &hkwglSwapBuffers ) )wglSwapBuffersOrig )( hdc );
	}
}
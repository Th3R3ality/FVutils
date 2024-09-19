#include "render.h"

namespace render
{
	void DoGui();
	void DoPlayers();
	void DoIndicators();

	ImVec2 clientRect = {};

	void DoFrame()
	{
		RECT _clientRect = {};
		GetClientRect( render::window, &_clientRect);
		clientRect.x = _clientRect.right;
		clientRect.y = _clientRect.bottom;

		if ( render::GuiOpen )
			DoGui();

		DoPlayers();
		DoIndicators();
	}
	void DoGui()
	{
		ImGui::ShowDemoWindow();
	}
	void DoPlayers()
	{

	}
	void DoIndicators()
	{
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(clientRect);
		ImGui::Begin("Overlay", nullptr,
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);

		ImDrawList* drawlist = ImGui::GetWindowDrawList();
		drawlist->AddText( ImVec2( clientRect.x - 199, 51 ), ImColor( 0, 0, 0, 255 ), "FVutils" );
		drawlist->AddText( ImVec2( clientRect.x - 200, 50 ), ImColor( 255, 0, 255, 255 ), "FVutils" );

		ImGui::End();
	}
}
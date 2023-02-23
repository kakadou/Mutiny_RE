#include "C:/ClientFramework/Framework/Include/Frame-Include.h"
#include "C:/ClientFramework/Framework/Menu/Fonts.h"
const char* Keys[] =
{
	"",
	"Mouse 1",
	"Mouse 2",
	"Cancel",
	"Middle Mouse",
	"Mouse 4",
	"Mouse 5",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12"

};
#ifdef FRAME_DX9
MutinyFrame::UserInterface::UserInterface()
{
}

MutinyFrame::UserInterface::UserInterface(HWND Window, IDirect3DDevice9* IDevice)
{
	ImGui_ImplDX9_Init(Window, IDevice);
	ImGuiStyle * style = &ImGui::GetStyle();
	style->WindowTitleAlign = ImVec2(0.5, 0.5);
	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 5.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 4.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;

	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
	style->Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
	style->Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
	ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(RudaCompressed, RudaSize, 12);
	ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(RudaCompressed, RudaSize, 10);
	ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(RudaCompressed, RudaSize, 14);
	ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(RudaCompressed, RudaSize, 18);
	this->Tabs = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(RudaCompressed, RudaSize, 20);
	this->Initialized = true;
}

void MutinyFrame::UserInterface::Draw()
{
	if (!this->Initialized)
		return;

	ImGui::GetIO().MouseDrawCursor = MenuOpen;

	ImGui_ImplDX9_NewFrame();

	static int CurrentTab = 0;
	if (MenuOpen)
	{
		if (ImGui::Begin(("Mutiny.pw"), &MenuOpen, ImVec2(800, 400), 1.f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoClose))
		{
			const char* Tabs[] = {
				"Triggerbot",
				"Aimbot",
				"Visuals",
				"Misc",
				"Colors",
			};
			static const char* Configs[] = {
				"Default",
				"MM",
				"CEVO",
				"Secret",
			};
			ImGui::Columns(2, "Tabs", false);
			{
				ImGui::SetColumnOffset(1, 130);
				for (auto i = 0; i < ARRAYSIZE(Tabs); i++)
				{
					ImGui::PushFont(this->Tabs);
					if (ImGui::Button(Tabs[i], ImVec2(120, 40)))
					{
						CurrentTab = i;
					}

					ImGui::PopFont();
				}

			}

			ImGui::NextColumn();
			ImGui::SetColumnOffset(2, ImGui::GetWindowWidth());
			if (CurrentTab == 0)
			{
				//	ImGui::SameLine();
				if (ImGui::BeginChild("Trigger", ImVec2(600, 300), true))
				{
					this->Checkbox("Enable", "trigger");
					ImGui::SameLine();
					this->Combo("Trigger Key", "trigger_key", Keys, ARRAYSIZE(Keys));
					this->SlideInt("OverBurst Amount", "trigger_overburst", 5);
					this->SlideInt("Max Shots", "trigger_maxshots", 5);
					this->SlideInt("Delay (MS)", "trigger_delay", 500);
					this->Checkbox("Smoke Check", "trigger_smoke");
					ImGui::SameLine();
					this->Checkbox("Flash Check", "trigger_flash");
					ImGui::SameLine();
					this->Checkbox("Air Check", "trigger_air");
					ImGui::SameLine();
					this->Checkbox("Team Check", "trigger_enemy");
					ImGui::EndChild();
				}
			}
			if (CurrentTab == 1)
			{
				//ImGui::SameLine();
				if (ImGui::BeginChild("ESP", ImVec2(600, 300), true))
				{
					this->Checkbox("Enable ESP", "esp");
	
					ImGui::EndChild();
				}
			}
			if (CurrentTab == 3)
			{
				//	ImGui::SameLine();
				if (ImGui::BeginChild("Configs", ImVec2(600, 300), true))
				{
					this->Combo("Configs", "cheat_config", Configs, ARRAYSIZE(Configs));
					if (ImGui::Button("Save Config"))
						Config.SaveConfig(Configs[Config.GetConfigValue("cheat_config")]);

					ImGui::SameLine();

					if (ImGui::Button("Load Config"))
						Config.LoadConfig(Configs[Config.GetConfigValue("cheat_config")]);


					ImGui::EndChild();
				}
			}
			if (CurrentTab == 4)
			{
				//ImGui::SameLine();
				if (ImGui::BeginChild("Colors", ImVec2(600, 300), true))
				{
					static int Item = 0;
					ImGui::Combo("Feature", &Item, "Team\0Enemy\0Team Vis\0Enemy Vis\0");
					switch (Item)
					{
					case 1:
						this->ColorPicker("Enemy", "esp_r", "esp_g", "esp_b");
						break;
					case 2:
						this->ColorPicker("Team Vis", "esp_team_r_vis", "esp_team_g_vis", "esp_team_b_vis");
						break;
					case 3:
						this->ColorPicker("Enemy Vis", "esp_r_vis", "esp_g_vis", "esp_b_vis");
						break;
					default:
						this->ColorPicker("Team", "esp_team_r", "esp_team_g", "esp_team_b");
						break;
					}
					ImGui::EndChild();
				}
			}
			ImGui::Columns(1);
			ImGui::End();
		}
		ImGui::Render();
	}
}

bool MutinyFrame::UserInterface::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (!this)
		return false;
	auto& io = ImGui::GetIO();
	switch (uMsg)
	{

	case WM_LBUTTONDOWN:
		PressedKey[VK_LBUTTON] = true;
		break;
	case WM_LBUTTONUP:
		PressedKey[VK_LBUTTON] = false;
		break;
	case WM_RBUTTONDOWN:
		PressedKey[VK_RBUTTON] = true;
		break;
	case WM_RBUTTONUP:
		PressedKey[VK_RBUTTON] = false;
		break;
	case WM_KEYDOWN:
		PressedKey[wParam] = true;
		break;
	case WM_KEYUP:
		PressedKey[wParam] = false;
		break;
	case WM_MOUSEMOVE:
		io.MousePos.x = static_cast<signed short>(lParam);
		io.MousePos.y = static_cast<signed short>(lParam >> 16);
		break;
	default: break;
	}
	{
		static bool ShouldShow, isPressed = false;
		if (PressedKey[VK_INSERT])
		{
			isPressed = true;
			ShouldShow = false;
		}
		else if (!PressedKey[VK_INSERT] && isPressed)
		{
			ShouldShow = true;
			isPressed = false;
		}
		else
		{
			ShouldShow = false;
			isPressed = false;		
		}

		if (ShouldShow)
		{
			MenuOpen = !MenuOpen;
              /*Make it possible to move mouse( Source Engine is cl_mouseenable)*/
			static auto cl_mouseenable = Interfaces.g_ICVars->FindVar(("cl_mouseenable"));
			cl_mouseenable->SetValue(!MenuOpen);
		}

	}
	if (this->Initialized && MenuOpen && ImGui_ImplDX9_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;
	return false;
}
void MutinyFrame::UserInterface::Checkbox(std::string Option, std::string strOption)
{
	bool TempVal = static_cast<bool>(Config.GetConfigValue(strOption));

	if (ImGui::Checkbox(Option.c_str(), &TempVal))
		Config.RegisterConfigValue(strOption, static_cast<int>(TempVal));
}

void MutinyFrame::UserInterface::InputInt(std::string Option, std::string strOption)
{
	int TempInt = static_cast<int>(Config.GetConfigValue(strOption));

	if (ImGui::InputInt(Option.c_str(), &TempInt))
		Config.RegisterConfigValue(strOption, static_cast<int>(TempInt));
}

void MutinyFrame::UserInterface::SlideInt(std::string Option, std::string strOption, int Max)
{
	int TempInt = static_cast<int>(Config.GetConfigValue(strOption));

	if (ImGui::SliderInt(Option.c_str(), &TempInt, 0, Max))
		Config.RegisterConfigValue(strOption, static_cast<int>(TempInt));
}
void MutinyFrame::UserInterface::SlideInt(std::string Option, std::string strOption, int Min, int Max)
{
	int TempInt = static_cast<int>(Config.GetConfigValue(strOption));

	if (ImGui::SliderInt(Option.c_str(), &TempInt, Min, Max))
		Config.RegisterConfigValue(strOption, static_cast<int>(TempInt));
}
void MutinyFrame::UserInterface::InputFloat(std::string Option, std::string strOption)
{
	auto Tempfloat = static_cast<float>(Config.GetPreciseConfigValue(strOption));

	if (ImGui::InputFloat(Option.c_str(), &Tempfloat))
		Config.RegisterConfigValue(strOption, static_cast<float>(Tempfloat));
}
void MutinyFrame::UserInterface::SlideFloat(std::string Option, std::string strOption, float Max)
{
	auto Tempfloat = static_cast<float>(Config.GetPreciseConfigValue(strOption));

	if (ImGui::SliderFloat(Option.c_str(), &Tempfloat, 0, Max))
		Config.RegisterConfigValue(strOption, static_cast<float>(Tempfloat));
}
void MutinyFrame::UserInterface::SlideFloat(std::string Option, std::string strOption, float Min, float Max)
{
	auto Tempfloat = static_cast<float>(Config.GetPreciseConfigValue(strOption));

	if (ImGui::SliderFloat(Option.c_str(), &Tempfloat, Min, Max))
		Config.RegisterConfigValue(strOption, static_cast<float>(Tempfloat));
}
void MutinyFrame::UserInterface::Combo(std::string Option, std::string strOption, const char* Options)
{
	int TempInt = static_cast<int>(Config.GetConfigValue(strOption));

	if (ImGui::Combo(Option.c_str(), &TempInt, Options))
		Config.RegisterConfigValue(strOption, static_cast<int>(TempInt));
}
void MutinyFrame::UserInterface::Combo(std::string Option, std::string strOption, const char* const* items, int items_count)
{
	int TempInt = static_cast<int>(Config.GetConfigValue(strOption));

	if (ImGui::Combo(Option.c_str(), &TempInt, items, items_count))
		Config.RegisterConfigValue(strOption, static_cast<int>(TempInt));
}

void MutinyFrame::UserInterface::ColorPicker(std::string strOption, std::string r, std::string g, std::string b)
{
	float Color[3] = {
		Config.GetPreciseConfigValue(r),
		Config.GetPreciseConfigValue(g),
		Config.GetPreciseConfigValue(b)
	};

	if (ImGui::ColorPicker(strOption.c_str(), Color))
	{
		Config.RegisterConfigValue(r, Color[0]);
		Config.RegisterConfigValue(g, Color[1]);
		Config.RegisterConfigValue(b, Color[2]);
	}
}
#endif
#ifdef FRAME_DX11
MutinyFrame::UserInterface::UserInterface()
{
}

MutinyFrame::UserInterface::UserInterface(HWND Window, ID3D11Device* IDevice)
{
	IDevice->GetImmediateContext(&this->DX11DeviceContext);
	InitImGUI(Window, IDevice, DX11DeviceContext);
	ImGuiStyle * style = &ImGui::GetStyle();
	style->WindowTitleAlign = ImVec2(0.5, 0.5);
	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 5.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 4.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;

	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
	style->Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
	style->Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
	ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(RudaCompressed, RudaSize, 12);
	ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(RudaCompressed, RudaSize, 10);
	ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(RudaCompressed, RudaSize, 14);
	ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(RudaCompressed, RudaSize, 18);
	this->Tabs = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(RudaCompressed, RudaSize, 20);
	this->Initialized = true;
}

void MutinyFrame::UserInterface::Draw()
{
	if (!this->Initialized)
		return;

	ImGui::GetIO().MouseDrawCursor = MenuOpen;

	ImGui_ImplDX11_NewFrame();

	static int CurrentTab = 0;
	if (MenuOpen)
	{
		if (ImGui::Begin(("Mutiny.pw"), &MenuOpen, ImVec2(800, 400), 1.f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoClose))
		{
			const char* Tabs[] = {
				"Aim",
				"Visual",
				"Misc",
				"Colors",
			};

			ImGui::Columns(2, "Tabs", false);
			{
				ImGui::SetColumnOffset(1, 130);
				for (auto i = 0; i < ARRAYSIZE(Tabs); i++)
				{
					ImGui::PushFont(this->Tabs);
					if (ImGui::Button(Tabs[i], ImVec2(120, 40)))
					{
						CurrentTab = i;
					}

					ImGui::PopFont();
				}

			}

			ImGui::NextColumn();
			ImGui::SetColumnOffset(2, ImGui::GetWindowWidth());
			if (CurrentTab == 0)
			{
				//	ImGui::SameLine();
				if (ImGui::BeginChild("Aim", ImVec2(600, 300), true))
				{
					this->Checkbox("Enable", "aimbot");
					this->Combo("Aimbot Key", "aimbot_key", Keys, ARRAYSIZE(Keys));
					this->Checkbox("Aim Prediction", "aimbot_prediction");
					this->Checkbox("Disable Sway", "aimbot_sway");
					this->Checkbox("Instant Hit", "aimbot_instant");
					this->SlideInt("FOV", "aimbot_fov", 360);
					this->SlideInt("Smooth", "aimbot_smooth", 100);
					this->SlideInt("Max Distance", "aimbot_distance", 2000);

					ImGui::EndChild();
				}
			}
			if (CurrentTab == 1)
			{
				//ImGui::SameLine();
				if (ImGui::BeginChild("ESP", ImVec2(600, 300), true))
				{
					this->Checkbox("Enable ESP", "esp");
					this->Checkbox("Team ESP", "esp_team");
					this->Checkbox("ESP Glow", "esp_glow");
					this->Checkbox("Draw Health", "esp_health");
					this->Checkbox("Draw Box", "esp_box");
					this->Checkbox("Draw Distance", "esp_distance");
					this->Checkbox("Draw Weapon", "esp_weapon");
					this->Checkbox("Visualize FOV", "esp_fov");
					this->SlideInt("Distance", "esp_distancemod", 2000);
					ImGui::EndChild();
				}
			}

			if (CurrentTab == 3)
			{
				//ImGui::SameLine();
				if (ImGui::BeginChild("Colors", ImVec2(600, 300), true))
				{
					static int Item = 0;
					ImGui::Combo("Feature", &Item, "Team\0Enemy\0Team Vis\0Enemy Vis\0");
					switch (Item)
					{
					case 1:
						this->ColorPicker("Enemy", "esp_r", "esp_g", "esp_b");
						break;
					case 2:
						this->ColorPicker("Team Vis", "esp_team_r_vis", "esp_team_g_vis", "esp_team_b_vis");
						break;
					case 3:
						this->ColorPicker("Enemy Vis", "esp_r_vis", "esp_g_vis", "esp_b_vis");
						break;
					default:
						this->ColorPicker("Team", "esp_team_r", "esp_team_g", "esp_team_b");
						break;
					}
					ImGui::EndChild();
				}
			}
			ImGui::Columns(1);
			ImGui::End();
		}
	}
}

bool MutinyFrame::UserInterface::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (!this)
		return false;
	auto& io = ImGui::GetIO();
	switch (uMsg)
	{

	case WM_LBUTTONDOWN:
		PressedKey[VK_LBUTTON] = true;
		break;
	case WM_LBUTTONUP:
		PressedKey[VK_LBUTTON] = false;
		break;
	case WM_RBUTTONDOWN:
		PressedKey[VK_RBUTTON] = true;
		break;
	case WM_RBUTTONUP:
		PressedKey[VK_RBUTTON] = false;
		break;
	case WM_KEYDOWN:
		PressedKey[wParam] = true;
		break;
	case WM_KEYUP:
		PressedKey[wParam] = false;
		break;
	case WM_MOUSEMOVE:
		io.MousePos.x = static_cast<signed short>(lParam);
		io.MousePos.y = static_cast<signed short>(lParam >> 16);
		break;
	default: break;
	}
	{
		static bool ShouldShow, isPressed = false;
		if (PressedKey[VK_INSERT])
		{
			isPressed = true;
			ShouldShow = false;
		}
		else if (!PressedKey[VK_INSERT] && isPressed)
		{
			ShouldShow = true;
			isPressed = false;
		}
		else
		{
			ShouldShow = false;
			isPressed = false;
		}

		if (ShouldShow)
		{
			MenuOpen = !MenuOpen;
			/*Make it possible to move mouse( Source Engine is cl_mouseenable)*/

		}

	}
	if (this->Initialized && MenuOpen && ImGui_ImplDX11_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;
	return false;
}

void MutinyFrame::UserInterface::Checkbox(std::string Option, std::string strOption)
{
	bool TempVal = static_cast<bool>(Config.GetConfigValue(strOption));

	if (ImGui::Checkbox(Option.c_str(), &TempVal))
		Config.RegisterConfigValue(strOption, static_cast<int>(TempVal));
}

void MutinyFrame::UserInterface::InputInt(std::string Option, std::string strOption)
{
	int TempInt = static_cast<int>(Config.GetConfigValue(strOption));

	if (ImGui::InputInt(Option.c_str(), &TempInt))
		Config.RegisterConfigValue(strOption, static_cast<int>(TempInt));
}

void MutinyFrame::UserInterface::SlideInt(std::string Option, std::string strOption, int Max)
{
	int TempInt = static_cast<int>(Config.GetConfigValue(strOption));

	if (ImGui::SliderInt(Option.c_str(), &TempInt, 0, Max))
		Config.RegisterConfigValue(strOption, static_cast<int>(TempInt));
}
void MutinyFrame::UserInterface::SlideInt(std::string Option, std::string strOption, int Min, int Max)
{
	int TempInt = static_cast<int>(Config.GetConfigValue(strOption));

	if (ImGui::SliderInt(Option.c_str(), &TempInt, Min, Max))
		Config.RegisterConfigValue(strOption, static_cast<int>(TempInt));
}
void MutinyFrame::UserInterface::InputFloat(std::string Option, std::string strOption)
{
	auto Tempfloat = static_cast<float>(Config.GetPreciseConfigValue(strOption));

	if (ImGui::InputFloat(Option.c_str(), &Tempfloat))
		Config.RegisterConfigValue(strOption, static_cast<float>(Tempfloat));
}
void MutinyFrame::UserInterface::SlideFloat(std::string Option, std::string strOption, float Max)
{
	auto Tempfloat = static_cast<float>(Config.GetPreciseConfigValue(strOption));

	if (ImGui::SliderFloat(Option.c_str(), &Tempfloat, 0, Max))
		Config.RegisterConfigValue(strOption, static_cast<float>(Tempfloat));
}
void MutinyFrame::UserInterface::SlideFloat(std::string Option, std::string strOption, float Min, float Max)
{
	auto Tempfloat = static_cast<float>(Config.GetPreciseConfigValue(strOption));

	if (ImGui::SliderFloat(Option.c_str(), &Tempfloat, Min, Max))
		Config.RegisterConfigValue(strOption, static_cast<float>(Tempfloat));
}
void MutinyFrame::UserInterface::Combo(std::string Option, std::string strOption, const char* Options)
{
	int TempInt = static_cast<int>(Config.GetConfigValue(strOption));

	if (ImGui::Combo(Option.c_str(), &TempInt, Options))
		Config.RegisterConfigValue(strOption, static_cast<int>(TempInt));
}
void MutinyFrame::UserInterface::Combo(std::string Option, std::string strOption, const char* const* items, int items_count)
{
	int TempInt = static_cast<int>(Config.GetConfigValue(strOption));

	if (ImGui::Combo(Option.c_str(), &TempInt, items, items_count))
		Config.RegisterConfigValue(strOption, static_cast<int>(TempInt));
}

void MutinyFrame::UserInterface::ColorPicker(std::string strOption, std::string r, std::string g, std::string b)
{
	float Color[3] = {
		Config.GetPreciseConfigValue(r),
		Config.GetPreciseConfigValue(g),
		Config.GetPreciseConfigValue(b)
	};

	if (ImGui::ColorPicker(strOption.c_str(), Color))
	{
		Config.RegisterConfigValue(r, Color[0]);
		Config.RegisterConfigValue(g, Color[1]);
		Config.RegisterConfigValue(b, Color[2]);
	}
}
#endif
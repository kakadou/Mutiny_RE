#ifdef FRAME_IMGUI

// dear imgui, v1.50 WIP
// (demo code)

// Don't remove this file from your project! It is useful reference code that you can execute.
// You can call ImGui::ShowTestWindow() in your code to learn about various features of ImGui.
// Everything in this file will be stripped out by the linker if you don't call ImGui::ShowTestWindow().

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "imgui.h"
#include <ctype.h>          // toupper, isprint
#include <math.h>           // sqrtf, powf, cosf, sinf, floorf, ceilf
#include <stdio.h>          // vsnprintf, sscanf, printf
#include <stdlib.h>         // NULL, malloc, free, qsort, atoi
#if defined(_MSC_VER) && _MSC_VER <= 1500 // MSVC 2008 or earlier
#include <stddef.h>         // intptr_t
#else
#include <stdint.h>         // intptr_t
#endif

#ifdef _MSC_VER
#pragma warning (disable: 4996) // 'This function or variable may be unsafe': strcpy, strdup, sprintf, vsnprintf, sscanf, fopen
#define snprintf _snprintf
#endif
#ifdef __clang__
#pragma clang diagnostic ignored "-Wold-style-cast"             // warning : use of old-style cast                              // yes, they are more terse.
#pragma clang diagnostic ignored "-Wdeprecated-declarations"    // warning : 'xx' is deprecated: The POSIX name for this item.. // for strdup used in demo code (so user can copy & paste the code)
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"   // warning : cast to 'void *' from smaller integer type 'int'
#pragma clang diagnostic ignored "-Wformat-security"            // warning : warning: format string is not a string literal
#pragma clang diagnostic ignored "-Wexit-time-destructors"      // warning : declaration requires an exit-time destructor       // exit-time destruction order is undefined. if MemFree() leads to users code that has been disabled before exit it might cause problems. ImGui coding style welcomes static/globals.
#if __has_warning("-Wreserved-id-macro")
#pragma clang diagnostic ignored "-Wreserved-id-macro"          // warning : macro name is a reserved identifier                //
#endif
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"          // warning: cast to pointer from integer of different size
#pragma GCC diagnostic ignored "-Wformat-security"              // warning : format string is not a string literal (potentially insecure)
#pragma GCC diagnostic ignored "-Wdouble-promotion"             // warning: implicit conversion from 'float' to 'double' when passing argument to function
#pragma GCC diagnostic ignored "-Wconversion"                   // warning: conversion to 'xxxx' from 'xxxx' may alter its value
#if (__GNUC__ >= 6)
#pragma GCC diagnostic ignored "-Wmisleading-indentation"       // warning: this 'if' clause does not guard this statement      // GCC 6.0+ only. See #883 on github.
#endif
#endif

// Play it nice with Windows users. Notepad in 2015 still doesn't display text data with Unix-style \n.
#ifdef _WIN32
#define IM_NEWLINE "\r\n"
#else
#define IM_NEWLINE "\n"
#endif

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))
#define IM_MAX(_A,_B)       (((_A) >= (_B)) ? (_A) : (_B))

//-----------------------------------------------------------------------------
// DEMO CODE
//-----------------------------------------------------------------------------

#ifndef IMGUI_DISABLE_TEST_WINDOWS

static void ShowExampleAppConsole(bool* p_open);
static void ShowExampleAppLog(bool* p_open);
static void ShowExampleAppLayout(bool* p_open);
static void ShowExampleAppPropertyEditor(bool* p_open);
static void ShowExampleAppLongText(bool* p_open);
static void ShowExampleAppAutoResize(bool* p_open);
static void ShowExampleAppConstrainedResize(bool* p_open);
static void ShowExampleAppFixedOverlay(bool* p_open);
static void ShowExampleAppManipulatingWindowTitle(bool* p_open);
static void ShowExampleAppCustomRendering(bool* p_open);
static void ShowExampleAppMainMenuBar();
static void ShowExampleMenuFile();

static void ShowHelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(450.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void ImGui::ShowUserGuide()
{
	BulletText("Double-click on title bar to collapse window.");
	BulletText("Click and drag on lower right corner to resize window.");
	BulletText("Click and drag on any empty space to move window.");
	BulletText("Mouse Wheel to scroll.");
	if (GetIO().FontAllowUserScaling)
		BulletText("CTRL+Mouse Wheel to zoom window contents.");
	BulletText("TAB/SHIFT+TAB to cycle through keyboard editable fields.");
	BulletText("CTRL+Click on a slider or drag box to input text.");
	BulletText(
		"While editing text:\n"
		"- Hold SHIFT or use mouse to select text\n"
		"- CTRL+Left/Right to word jump\n"
		"- CTRL+A or double-click to select all\n"
		"- CTRL+X,CTRL+C,CTRL+V clipboard\n"
		"- CTRL+Z,CTRL+Y undo/redo\n"
		"- ESCAPE to revert\n"
		"- You can apply arithmetic operators +,*,/ on numerical values.\n"
		"  Use +- to subtract.\n");
}

// Demonstrate most ImGui features (big function!)
void ImGui::ShowTestWindow(bool* p_open)
{
	// Examples apps
	static bool show_app_main_menu_bar = false;
	static bool show_app_console = false;
	static bool show_app_log = false;
	static bool show_app_layout = false;
	static bool show_app_property_editor = false;
	static bool show_app_long_text = false;
	static bool show_app_auto_resize = false;
	static bool show_app_constrained_resize = false;
	static bool show_app_fixed_overlay = false;
	static bool show_app_manipulating_window_title = false;
	static bool show_app_custom_rendering = false;
	static bool show_app_style_editor = false;

	static bool show_app_metrics = false;
	static bool show_app_about = false;

	if (show_app_main_menu_bar) ShowExampleAppMainMenuBar();
	if (show_app_console) ShowExampleAppConsole(&show_app_console);
	if (show_app_log) ShowExampleAppLog(&show_app_log);
	if (show_app_layout) ShowExampleAppLayout(&show_app_layout);
	if (show_app_property_editor) ShowExampleAppPropertyEditor(&show_app_property_editor);
	if (show_app_long_text) ShowExampleAppLongText(&show_app_long_text);
	if (show_app_auto_resize) ShowExampleAppAutoResize(&show_app_auto_resize);
	if (show_app_constrained_resize) ShowExampleAppConstrainedResize(&show_app_constrained_resize);
	if (show_app_fixed_overlay) ShowExampleAppFixedOverlay(&show_app_fixed_overlay);
	if (show_app_manipulating_window_title) ShowExampleAppManipulatingWindowTitle(&show_app_manipulating_window_title);
	if (show_app_custom_rendering) ShowExampleAppCustomRendering(&show_app_custom_rendering);

	if (show_app_metrics) ShowMetricsWindow(&show_app_metrics);
	if (show_app_style_editor)
	{
		Begin("Style Editor", &show_app_style_editor);
		ShowStyleEditor();
		End();
	}
	if (show_app_about)
	{
		Begin("About ImGui", &show_app_about, ImGuiWindowFlags_AlwaysAutoResize);
		Text("dear imgui, %s", GetVersion());
		Separator();
		Text("By Omar Cornut and all github contributors.");
		Text("ImGui is licensed under the MIT License, see LICENSE for more information.");
		End();
	}

	static bool no_titlebar = false;
	static bool no_border = true;
	static bool no_resize = false;
	static bool no_move = false;
	static bool no_scrollbar = false;
	static bool no_collapse = false;
	static bool no_menu = false;

	// Demonstrate the various window flags. Typically you would just use the default.
	ImGuiWindowFlags window_flags = 0;
	if (no_titlebar) window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (!no_border) window_flags |= ImGuiWindowFlags_ShowBorders;
	if (no_resize) window_flags |= ImGuiWindowFlags_NoResize;
	if (no_move) window_flags |= ImGuiWindowFlags_NoMove;
	if (no_scrollbar) window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (no_collapse) window_flags |= ImGuiWindowFlags_NoCollapse;
	if (!no_menu) window_flags |= ImGuiWindowFlags_MenuBar;
	SetNextWindowSize(ImVec2(550, 680), ImGuiSetCond_FirstUseEver);
	if (!Begin("ImGui Demo", p_open, window_flags))
	{
		// Early out if the window is collapsed, as an optimization.
		End();
		return;
	}

	//ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.65f);    // 2/3 of the space for widget and 1/3 for labels
	PushItemWidth(-140); // Right align, keep 140 pixels for labels

	Text("Dear ImGui says hello.");

	// Menu
	if (BeginMenuBar())
	{
		if (BeginMenu("Menu"))
		{
			ShowExampleMenuFile();
			EndMenu();
		}
		if (BeginMenu("Examples"))
		{
			MenuItem("Main menu bar", nullptr, &show_app_main_menu_bar);
			MenuItem("Console", nullptr, &show_app_console);
			MenuItem("Log", nullptr, &show_app_log);
			MenuItem("Simple layout", nullptr, &show_app_layout);
			MenuItem("Property editor", nullptr, &show_app_property_editor);
			MenuItem("Long text display", nullptr, &show_app_long_text);
			MenuItem("Auto-resizing window", nullptr, &show_app_auto_resize);
			MenuItem("Constrained-resizing window", nullptr, &show_app_constrained_resize);
			MenuItem("Simple overlay", nullptr, &show_app_fixed_overlay);
			MenuItem("Manipulating window title", nullptr, &show_app_manipulating_window_title);
			MenuItem("Custom rendering", nullptr, &show_app_custom_rendering);
			EndMenu();
		}
		if (BeginMenu("Help"))
		{
			MenuItem("Metrics", nullptr, &show_app_metrics);
			MenuItem("Style Editor", nullptr, &show_app_style_editor);
			MenuItem("About ImGui", nullptr, &show_app_about);
			EndMenu();
		}
		EndMenuBar();
	}

	Spacing();
	if (CollapsingHeader("Help"))
	{
		TextWrapped("This window is being created by the ShowTestWindow() function. Please refer to the code for programming reference.\n\nUser Guide:");
		ShowUserGuide();
	}

	if (CollapsingHeader("Window options"))
	{
		Checkbox("No titlebar", &no_titlebar);
		SameLine(150);
		Checkbox("No border", &no_border);
		SameLine(300);
		Checkbox("No resize", &no_resize);
		Checkbox("No move", &no_move);
		SameLine(150);
		Checkbox("No scrollbar", &no_scrollbar);
		SameLine(300);
		Checkbox("No collapse", &no_collapse);
		Checkbox("No menu", &no_menu);

		if (TreeNode("Style"))
		{
			ShowStyleEditor();
			TreePop();
		}

		if (TreeNode("Logging"))
		{
			TextWrapped("The logging API redirects all text output so you can easily capture the content of a window or a block. Tree nodes can be automatically expanded. You can also call ImGui::LogText() to output directly to the log without a visual output.");
			LogButtons();
			TreePop();
		}
	}

	if (CollapsingHeader("Widgets"))
	{
		if (TreeNode("Trees"))
		{
			if (TreeNode("Basic trees"))
			{
				for (int i = 0; i < 5; i++)
					if (TreeNode((void*)(intptr_t)i, "Child %d", i))
					{
						Text("blah blah");
						SameLine();
						if (SmallButton("print")) printf("Child %d pressed", i);
						TreePop();
					}
				TreePop();
			}

			if (TreeNode("Advanced, with Selectable nodes"))
			{
				ShowHelpMarker("This is a more standard looking tree with selectable nodes.\nClick to select, CTRL+Click to toggle, click on arrows or double-click to open.");
				static bool align_label_with_current_x_position = false;
				Checkbox("Align label with current X position)", &align_label_with_current_x_position);
				Text("Hello!");
				if (align_label_with_current_x_position)
					Unindent(GetTreeNodeToLabelSpacing());

				static int selection_mask = (1 << 2); // Dumb representation of what may be user-side selection state. You may carry selection state inside or outside your objects in whatever format you see fit.
				int node_clicked = -1; // Temporary storage of what node we have clicked to process selection at the end of the loop. May be a pointer to your own node type, etc.
				PushStyleVar(ImGuiStyleVar_IndentSpacing, GetFontSize() * 3); // Increase spacing to differentiate leaves from expanded contents.
				for (int i = 0; i < 6; i++)
				{
					// Disable the default open on single-click behavior and pass in Selected flag according to our selection state.
					ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ((selection_mask & (1 << i)) ? ImGuiTreeNodeFlags_Selected : 0);
					if (i < 3)
					{
						// Node
						bool node_open = TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Node %d", i);
						if (IsItemClicked())
							node_clicked = i;
						if (node_open)
						{
							Text("Blah blah\nBlah Blah");
							TreePop();
						}
					}
					else
					{
						// Leaf: The only reason we have a TreeNode at all is to allow selection of the leaf. Otherwise we can use BulletText() or TreeAdvanceToLabelPos()+Text().
						TreeNodeEx((void*)(intptr_t)i, node_flags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen, "Selectable Leaf %d", i);
						if (IsItemClicked())
							node_clicked = i;
					}
				}
				if (node_clicked != -1)
				{
					// Update selection state. Process outside of tree loop to avoid visual inconsistencies during the clicking-frame.
					if (GetIO().KeyCtrl)
						selection_mask ^= (1 << node_clicked); // CTRL+click to toggle
					else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, this commented bit preserve selection when clicking on item that is part of the selection
						selection_mask = (1 << node_clicked); // Click to single-select
				}
				PopStyleVar();
				if (align_label_with_current_x_position)
					Indent(GetTreeNodeToLabelSpacing());
				TreePop();
			}
			TreePop();
		}

		if (TreeNode("Collapsing Headers"))
		{
			static bool closable_group = true;
			if (CollapsingHeader("Header"))
			{
				Checkbox("Enable extra group", &closable_group);
				for (int i = 0; i < 5; i++)
					Text("Some content %d", i);
			}
			if (CollapsingHeader("Header with a close button", &closable_group))
			{
				for (int i = 0; i < 5; i++)
					Text("More content %d", i);
			}
			TreePop();
		}

		if (TreeNode("Bullets"))
		{
			BulletText("Bullet point 1");
			BulletText("Bullet point 2\nOn multiple lines");
			Bullet();
			Text("Bullet point 3 (two calls)");
			Bullet();
			SmallButton("Button");
			TreePop();
		}

		if (TreeNode("Colored Text"))
		{
			// Using shortcut. You can use PushStyleColor()/PopStyleColor() for more flexibility.
			TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Pink");
			TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Yellow");
			TextDisabled("Disabled");
			TreePop();
		}

		if (TreeNode("Word Wrapping"))
		{
			// Using shortcut. You can use PushTextWrapPos()/PopTextWrapPos() for more flexibility.
			TextWrapped("This text should automatically wrap on the edge of the window. The current implementation for text wrapping follows simple rules suitable for English and possibly other languages.");
			Spacing();

			static float wrap_width = 200.0f;
			SliderFloat("Wrap width", &wrap_width, -20, 600, "%.0f");

			Text("Test paragraph 1:");
			ImVec2 pos = GetCursorScreenPos();
			GetWindowDrawList()->AddRectFilled(ImVec2(pos.x + wrap_width, pos.y), ImVec2(pos.x + wrap_width + 10, pos.y + GetTextLineHeight()), IM_COL32(255,0,255,255));
			PushTextWrapPos(GetCursorPos().x + wrap_width);
			Text("The lazy dog is a good dog. This paragraph is made to fit within %.0f pixels. Testing a 1 character word. The quick brown fox jumps over the lazy dog.", wrap_width);
			GetWindowDrawList()->AddRect(GetItemRectMin(), GetItemRectMax(), IM_COL32(255,255,0,255));
			PopTextWrapPos();

			Text("Test paragraph 2:");
			pos = GetCursorScreenPos();
			GetWindowDrawList()->AddRectFilled(ImVec2(pos.x + wrap_width, pos.y), ImVec2(pos.x + wrap_width + 10, pos.y + GetTextLineHeight()), IM_COL32(255,0,255,255));
			PushTextWrapPos(GetCursorPos().x + wrap_width);
			Text("aaaaaaaa bbbbbbbb, c cccccccc,dddddddd. d eeeeeeee   ffffffff. gggggggg!hhhhhhhh");
			GetWindowDrawList()->AddRect(GetItemRectMin(), GetItemRectMax(), IM_COL32(255,255,0,255));
			PopTextWrapPos();

			TreePop();
		}

		if (TreeNode("UTF-8 Text"))
		{
			// UTF-8 test with Japanese characters
			// (needs a suitable font, try Arial Unicode or M+ fonts http://mplus-fonts.sourceforge.jp/mplus-outline-fonts/index-en.html)
			// Most compiler appears to support UTF-8 in source code (with Visual Studio you need to save your file as 'UTF-8 without signature')
			// However for the sake for maximum portability here we are *not* including raw UTF-8 character in this source file, instead we encode the string with hexadecimal constants.
			// In your own application be reasonable and use UTF-8 in source or retrieve the data from file system!
			// Note that characters values are preserved even if the font cannot be displayed, so you can safely copy & paste garbled characters into another application.
			TextWrapped("CJK text will only appears if the font was loaded with the appropriate CJK character ranges. Call io.Font->LoadFromFileTTF() manually to load extra character ranges.");
			Text("Hiragana: \xe3\x81\x8b\xe3\x81\x8d\xe3\x81\x8f\xe3\x81\x91\xe3\x81\x93 (kakikukeko)");
			Text("Kanjis: \xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e (nihongo)");
			static char buf[32] = "\xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e";
			InputText("UTF-8 input", buf, IM_ARRAYSIZE(buf));
			TreePop();
		}

		if (TreeNode("Images"))
		{
			TextWrapped("Below we are displaying the font texture (which is the only texture we have access to in this demo). Use the 'ImTextureID' type as storage to pass pointers or identifier to your own texture data. Hover the texture for a zoomed view!");
			ImVec2 tex_screen_pos = GetCursorScreenPos();
			float tex_w = (float)GetIO().Fonts->TexWidth;
			float tex_h = (float)GetIO().Fonts->TexHeight;
			ImTextureID tex_id = GetIO().Fonts->TexID;
			Text("%.0fx%.0f", tex_w, tex_h);
			Image(tex_id, ImVec2(tex_w, tex_h), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
			if (IsItemHovered())
			{
				BeginTooltip();
				float focus_sz = 32.0f;
				float focus_x = GetMousePos().x - tex_screen_pos.x - focus_sz * 0.5f;
				if (focus_x < 0.0f) focus_x = 0.0f;
				else if (focus_x > tex_w - focus_sz) focus_x = tex_w - focus_sz;
				float focus_y = GetMousePos().y - tex_screen_pos.y - focus_sz * 0.5f;
				if (focus_y < 0.0f) focus_y = 0.0f;
				else if (focus_y > tex_h - focus_sz) focus_y = tex_h - focus_sz;
				Text("Min: (%.2f, %.2f)", focus_x, focus_y);
				Text("Max: (%.2f, %.2f)", focus_x + focus_sz, focus_y + focus_sz);
				ImVec2 uv0 = ImVec2((focus_x) / tex_w, (focus_y) / tex_h);
				ImVec2 uv1 = ImVec2((focus_x + focus_sz) / tex_w, (focus_y + focus_sz) / tex_h);
				Image(tex_id, ImVec2(128, 128), uv0, uv1, ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
				EndTooltip();
			}
			TextWrapped("And now some textured buttons..");
			static int pressed_count = 0;
			for (int i = 0; i < 8; i++)
			{
				PushID(i);
				int frame_padding = -1 + i; // -1 = uses default padding
				if (ImageButton(tex_id, ImVec2(32, 32), ImVec2(0, 0), ImVec2(32.0f / tex_w, 32 / tex_h), frame_padding, ImColor(0, 0, 0, 255)))
					pressed_count += 1;
				PopID();
				SameLine();
			}
			NewLine();
			Text("Pressed %d times.", pressed_count);
			TreePop();
		}

		if (TreeNode("Selectables"))
		{
			if (TreeNode("Basic"))
			{
				static bool selected[4] = {false, true, false, false};
				Selectable("1. I am selectable", &selected[0]);
				Selectable("2. I am selectable", &selected[1]);
				Text("3. I am not selectable");
				Selectable("4. I am selectable", &selected[2]);
				if (Selectable("5. I am double clickable", selected[3], ImGuiSelectableFlags_AllowDoubleClick))
					if (IsMouseDoubleClicked(0))
						selected[3] = !selected[3];
				TreePop();
			}
			if (TreeNode("Rendering more text into the same block"))
			{
				static bool selected[3] = {false, false, false};
				Selectable("main.c", &selected[0]);
				SameLine(300);
				Text(" 2,345 bytes");
				Selectable("Hello.cpp", &selected[1]);
				SameLine(300);
				Text("12,345 bytes");
				Selectable("Hello.h", &selected[2]);
				SameLine(300);
				Text(" 2,345 bytes");
				TreePop();
			}
			if (TreeNode("In columns"))
			{
				Columns(3, nullptr, false);
				static bool selected[16] = {false};
				for (int i = 0; i < 16; i++)
				{
					char label[32];
					sprintf(label, "Item %d", i);
					if (Selectable(label, &selected[i]))
					{
					}
					NextColumn();
				}
				Columns(1);
				TreePop();
			}
			if (TreeNode("Grid"))
			{
				static bool selected[16] = {true, false, false, false, false, true, false, false, false, false, true, false, false, false, false, true};
				for (int i = 0; i < 16; i++)
				{
					PushID(i);
					if (Selectable("Sailor", &selected[i], 0, ImVec2(50, 50)))
					{
						int x = i % 4, y = i / 4;
						if (x > 0) selected[i - 1] ^= 1;
						if (x < 3) selected[i + 1] ^= 1;
						if (y > 0) selected[i - 4] ^= 1;
						if (y < 3) selected[i + 4] ^= 1;
					}
					if ((i % 4) < 3) SameLine();
					PopID();
				}
				TreePop();
			}
			TreePop();
		}

		if (TreeNode("Filtered Text Input"))
		{
			static char buf1[64] = "";
			InputText("default", buf1, 64);
			static char buf2[64] = "";
			InputText("decimal", buf2, 64, ImGuiInputTextFlags_CharsDecimal);
			static char buf3[64] = "";
			InputText("hexadecimal", buf3, 64, ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase);
			static char buf4[64] = "";
			InputText("uppercase", buf4, 64, ImGuiInputTextFlags_CharsUppercase);
			static char buf5[64] = "";
			InputText("no blank", buf5, 64, ImGuiInputTextFlags_CharsNoBlank);
			struct TextFilters
			{
				static int FilterImGuiLetters(ImGuiTextEditCallbackData* data)
				{
					if (data->EventChar < 256 && strchr("imgui", (char)data->EventChar)) return 0;
					return 1;
				}
			};
			static char buf6[64] = "";
			InputText("\"imgui\" letters", buf6, 64, ImGuiInputTextFlags_CallbackCharFilter, TextFilters::FilterImGuiLetters);

			Text("Password input");
			static char bufpass[64] = "password123";
			InputText("password", bufpass, 64, ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank);
			SameLine();
			ShowHelpMarker("Display all characters as '*'.\nDisable clipboard cut and copy.\nDisable logging.\n");
			InputText("password (clear)", bufpass, 64, ImGuiInputTextFlags_CharsNoBlank);

			TreePop();
		}

		if (TreeNode("Multi-line Text Input"))
		{
			static bool read_only = false;
			static char text[1024 * 16] =
				"/*\n"
				" The Pentium F00F bug, shorthand for F0 0F C7 C8,\n"
				" the hexadecimal encoding of one offending instruction,\n"
				" more formally, the invalid operand with locked CMPXCHG8B\n"
				" instruction bug, is a design flaw in the majority of\n"
				" Intel Pentium, Pentium MMX, and Pentium OverDrive\n"
				" processors (all in the P5 microarchitecture).\n"
				"*/\n\n"
				"label:\n"
				"\tlock cmpxchg8b eax\n";

			PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
			Checkbox("Read-only", &read_only);
			PopStyleVar();
			InputTextMultiline("##source", text, IM_ARRAYSIZE(text), ImVec2(-1.0f, GetTextLineHeight() * 16), ImGuiInputTextFlags_AllowTabInput | (read_only ? ImGuiInputTextFlags_ReadOnly : 0));
			TreePop();
		}

		static bool a = false;
		if (Button("Button"))
		{
			printf("Clicked\n");
			a ^= 1;
		}
		if (a)
		{
			SameLine();
			Text("Thanks for clicking me!");
		}

		static bool check = true;
		Checkbox("checkbox", &check);

		static int e = 0;
		RadioButton("radio a", &e, 0);
		SameLine();
		RadioButton("radio b", &e, 1);
		SameLine();
		RadioButton("radio c", &e, 2);

		// Color buttons, demonstrate using PushID() to add unique identifier in the ID stack, and changing style.
		for (int i = 0; i < 7; i++)
		{
			if (i > 0) SameLine();
			PushID(i);
			PushStyleColor(ImGuiCol_Button, ImColor::HSV(i / 7.0f, 0.6f, 0.6f));
			PushStyleColor(ImGuiCol_ButtonHovered, ImColor::HSV(i / 7.0f, 0.7f, 0.7f));
			PushStyleColor(ImGuiCol_ButtonActive, ImColor::HSV(i / 7.0f, 0.8f, 0.8f));
			Button("Click");
			PopStyleColor(3);
			PopID();
		}

		Text("Hover over me");
		if (IsItemHovered())
			SetTooltip("I am a tooltip");

		SameLine();
		Text("- or me");
		if (IsItemHovered())
		{
			BeginTooltip();
			Text("I am a fancy tooltip");
			static float arr[] = {0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f};
			PlotLines("Curve", arr, IM_ARRAYSIZE(arr));
			EndTooltip();
		}

		// Testing IMGUI_ONCE_UPON_A_FRAME macro
		//for (int i = 0; i < 5; i++)
		//{
		//  IMGUI_ONCE_UPON_A_FRAME
		//  {
		//      ImGui::Text("This will be displayed only once.");
		//  }
		//}

		Separator();

		LabelText("label", "Value");

		static int item = 1;
		Combo("combo", &item, "aaaa\0bbbb\0cccc\0dddd\0eeee\0\0"); // Combo using values packed in a single constant string (for really quick combo)

		const char* items[] = {"AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK"};
		static int item2 = -1;
		Combo("combo scroll", &item2, items, IM_ARRAYSIZE(items)); // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.

		{
			static char str0[128] = "Hello, world!";
			static int i0 = 123;
			static float f0 = 0.001f;
			InputText("input text", str0, IM_ARRAYSIZE(str0));
			SameLine();
			ShowHelpMarker("Hold SHIFT or use mouse to select text.\n" "CTRL+Left/Right to word jump.\n" "CTRL+A or double-click to select all.\n" "CTRL+X,CTRL+C,CTRL+V clipboard.\n" "CTRL+Z,CTRL+Y undo/redo.\n" "ESCAPE to revert.\n");

			InputInt("input int", &i0);
			SameLine();
			ShowHelpMarker("You can apply arithmetic operators +,*,/ on numerical values.\n  e.g. [ 100 ], input \'*2\', result becomes [ 200 ]\nUse +- to subtract.\n");

			InputFloat("input float", &f0, 0.01f, 1.0f);

			static float vec4a[4] = {0.10f, 0.20f, 0.30f, 0.44f};
			InputFloat3("input float3", vec4a);
		}

		{
			static int i1 = 50, i2 = 42;
			DragInt("drag int", &i1, 1);
			SameLine();
			ShowHelpMarker("Click and drag to edit value.\nHold SHIFT/ALT for faster/slower edit.\nDouble-click or CTRL+click to input value.");

			DragInt("drag int 0..100", &i2, 1, 0, 100, "%.0f%%");

			static float f1 = 1.00f, f2 = 0.0067f;
			DragFloat("drag float", &f1, 0.005f);
			DragFloat("drag small float", &f2, 0.0001f, 0.0f, 0.0f, "%.06f ns");
		}

		{
			static int i1 = 0;
			SliderInt("slider int", &i1, -1, 3);
			SameLine();
			ShowHelpMarker("CTRL+click to input value.");

			static float f1 = 0.123f, f2 = 0.0f;
			SliderFloat("slider float", &f1, 0.0f, 1.0f, "ratio = %.3f");
			SliderFloat("slider log float", &f2, -10.0f, 10.0f, "%.4f", 3.0f);
			static float angle = 0.0f;
			SliderAngle("slider angle", &angle);
		}

		static float col1[3] = {1.0f,0.0f,0.2f};
		static float col2[4] = {0.4f,0.7f,0.0f,0.5f};
		ColorEdit3("color 1", col1);
		SameLine();
		ShowHelpMarker("Click on the colored square to change edit mode.\nCTRL+click on individual component to input value.\n");

		ColorEdit4("color 2", col2);

		const char* listbox_items[] = {"Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pineapple", "Strawberry", "Watermelon"};
		static int listbox_item_current = 1;
		ListBox("listbox\n(single select)", &listbox_item_current, listbox_items, IM_ARRAYSIZE(listbox_items), 4);

		//static int listbox_item_current2 = 2;
		//ImGui::PushItemWidth(-1);
		//ImGui::ListBox("##listbox2", &listbox_item_current2, listbox_items, IM_ARRAYSIZE(listbox_items), 4);
		//ImGui::PopItemWidth();

		if (TreeNode("Range Widgets"))
		{
			Unindent();

			static float begin = 10, end = 90;
			static int begin_i = 100, end_i = 1000;
			DragFloatRange2("range", &begin, &end, 0.25f, 0.0f, 100.0f, "Min: %.1f %%", "Max: %.1f %%");
			DragIntRange2("range int (no bounds)", &begin_i, &end_i, 5, 0, 0, "Min: %.0f units", "Max: %.0f units");

			Indent();
			TreePop();
		}

		if (TreeNode("Multi-component Widgets"))
		{
			Unindent();

			static float vec4f[4] = {0.10f, 0.20f, 0.30f, 0.44f};
			static int vec4i[4] = {1, 5, 100, 255};

			InputFloat2("input float2", vec4f);
			DragFloat2("drag float2", vec4f, 0.01f, 0.0f, 1.0f);
			SliderFloat2("slider float2", vec4f, 0.0f, 1.0f);
			DragInt2("drag int2", vec4i, 1, 0, 255);
			InputInt2("input int2", vec4i);
			SliderInt2("slider int2", vec4i, 0, 255);
			Spacing();

			InputFloat3("input float3", vec4f);
			DragFloat3("drag float3", vec4f, 0.01f, 0.0f, 1.0f);
			SliderFloat3("slider float3", vec4f, 0.0f, 1.0f);
			DragInt3("drag int3", vec4i, 1, 0, 255);
			InputInt3("input int3", vec4i);
			SliderInt3("slider int3", vec4i, 0, 255);
			Spacing();

			InputFloat4("input float4", vec4f);
			DragFloat4("drag float4", vec4f, 0.01f, 0.0f, 1.0f);
			SliderFloat4("slider float4", vec4f, 0.0f, 1.0f);
			InputInt4("input int4", vec4i);
			DragInt4("drag int4", vec4i, 1, 0, 255);
			SliderInt4("slider int4", vec4i, 0, 255);

			Indent();
			TreePop();
		}

		if (TreeNode("Vertical Sliders"))
		{
			Unindent();
			const float spacing = 4;
			PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spacing, spacing));

			static int int_value = 0;
			VSliderInt("##int", ImVec2(18, 160), &int_value, 0, 5);
			SameLine();

			static float values[7] = {0.0f, 0.60f, 0.35f, 0.9f, 0.70f, 0.20f, 0.0f};
			PushID("set1");
			for (int i = 0; i < 7; i++)
			{
				if (i > 0) SameLine();
				PushID(i);
				PushStyleColor(ImGuiCol_FrameBg, ImColor::HSV(i / 7.0f, 0.5f, 0.5f));
				PushStyleColor(ImGuiCol_FrameBgHovered, ImColor::HSV(i / 7.0f, 0.6f, 0.5f));
				PushStyleColor(ImGuiCol_FrameBgActive, ImColor::HSV(i / 7.0f, 0.7f, 0.5f));
				PushStyleColor(ImGuiCol_SliderGrab, ImColor::HSV(i / 7.0f, 0.9f, 0.9f));
				VSliderFloat("##v", ImVec2(18, 160), &values[i], 0.0f, 1.0f, "");
				if (IsItemActive() || IsItemHovered())
					SetTooltip("%.3f", values[i]);
				PopStyleColor(4);
				PopID();
			}
			PopID();

			SameLine();
			PushID("set2");
			static float values2[4] = {0.20f, 0.80f, 0.40f, 0.25f};
			const int rows = 3;
			const ImVec2 small_slider_size(18, (160.0f - (rows - 1) * spacing) / rows);
			for (int nx = 0; nx < 4; nx++)
			{
				if (nx > 0) SameLine();
				BeginGroup();
				for (int ny = 0; ny < rows; ny++)
				{
					PushID(nx * rows + ny);
					VSliderFloat("##v", small_slider_size, &values2[nx], 0.0f, 1.0f, "");
					if (IsItemActive() || IsItemHovered())
						SetTooltip("%.3f", values2[nx]);
					PopID();
				}
				EndGroup();
			}
			PopID();

			SameLine();
			PushID("set3");
			for (int i = 0; i < 4; i++)
			{
				if (i > 0) SameLine();
				PushID(i);
				PushStyleVar(ImGuiStyleVar_GrabMinSize, 40);
				VSliderFloat("##v", ImVec2(40, 160), &values[i], 0.0f, 1.0f, "%.2f\nsec");
				PopStyleVar();
				PopID();
			}
			PopID();
			PopStyleVar();

			Indent();
			TreePop();
		}
	}

	if (CollapsingHeader("Graphs widgets"))
	{
		static bool animate = true;
		Checkbox("Animate", &animate);

		static float arr[] = {0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f};
		PlotLines("Frame Times", arr, IM_ARRAYSIZE(arr));

		// Create a dummy array of contiguous float values to plot
		// Tip: If your float aren't contiguous but part of a structure, you can pass a pointer to your first float and the sizeof() of your structure in the Stride parameter.
		static float values[90] = {0};
		static int values_offset = 0;
		if (animate)
		{
			static float refresh_time = GetTime(); // Create dummy data at fixed 60 hz rate for the demo
			for (; GetTime() > refresh_time + 1.0f / 60.0f; refresh_time += 1.0f / 60.0f)
			{
				static float phase = 0.0f;
				values[values_offset] = cosf(phase);
				values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
				phase += 0.10f * values_offset;
			}
		}
		PlotLines("Lines", values, IM_ARRAYSIZE(values), values_offset, "avg 0.0", -1.0f, 1.0f, ImVec2(0, 80));
		PlotHistogram("Histogram", arr, IM_ARRAYSIZE(arr), 0, nullptr, 0.0f, 1.0f, ImVec2(0, 80));

		// Use functions to generate output
		// FIXME: This is rather awkward because current plot API only pass in indices. We probably want an API passing floats and user provide sample rate/count.
		struct Funcs
		{
			static float Sin(void*, int i) { return sinf(i * 0.1f); }
			static float Saw(void*, int i) { return (i & 1) ? 1.0f : 0.0f; }
		};
		static int func_type = 0, display_count = 70;
		Separator();
		PushItemWidth(100);
		Combo("func", &func_type, "Sin\0Saw\0");
		PopItemWidth();
		SameLine();
		SliderInt("Sample count", &display_count, 1, 400);
		float (*func)(void*, int) = (func_type == 0) ? Funcs::Sin : Funcs::Saw;
		PlotLines("Lines", func, nullptr, display_count, 0, nullptr, -1.0f, 1.0f, ImVec2(0, 80));
		PlotHistogram("Histogram", func, nullptr, display_count, 0, nullptr, -1.0f, 1.0f, ImVec2(0, 80));
		Separator();

		// Animate a simple progress bar
		static float progress = 0.0f, progress_dir = 1.0f;
		if (animate)
		{
			progress += progress_dir * 0.4f * GetIO().DeltaTime;
			if (progress >= +1.1f)
			{
				progress = +1.1f;
				progress_dir *= -1.0f;
			}
			if (progress <= -0.1f)
			{
				progress = -0.1f;
				progress_dir *= -1.0f;
			}
		}

		// Typically we would use ImVec2(-1.0f,0.0f) to use all available width, or ImVec2(width,0.0f) for a specified width. ImVec2(0.0f,0.0f) uses ItemWidth.
		ProgressBar(progress, ImVec2(0.0f, 0.0f));
		SameLine(0.0f, GetStyle().ItemInnerSpacing.x);
		Text("Progress Bar");

		float progress_saturated = (progress < 0.0f) ? 0.0f : (progress > 1.0f) ? 1.0f : progress;
		char buf[32];
		sprintf(buf, "%d/%d", (int)(progress_saturated * 1753), 1753);
		ProgressBar(progress, ImVec2(0.f, 0.f), buf);
	}

	if (CollapsingHeader("Layout"))
	{
		if (TreeNode("Child regions"))
		{
			Text("Without border");
			static int line = 50;
			bool goto_line = Button("Goto");
			SameLine();
			PushItemWidth(100);
			goto_line |= InputInt("##Line", &line, 0, 0, ImGuiInputTextFlags_EnterReturnsTrue);
			PopItemWidth();
			BeginChild("Sub1", ImVec2(GetWindowContentRegionWidth() * 0.5f, 300), false, ImGuiWindowFlags_HorizontalScrollbar);
			for (int i = 0; i < 100; i++)
			{
				Text("%04d: scrollable region", i);
				if (goto_line && line == i)
					SetScrollHere();
			}
			if (goto_line && line >= 100)
				SetScrollHere();
			EndChild();

			SameLine();

			PushStyleVar(ImGuiStyleVar_ChildWindowRounding, 5.0f);
			BeginChild("Sub2", ImVec2(0, 300), true);
			Text("With border");
			Columns(2);
			for (int i = 0; i < 100; i++)
			{
				if (i == 50)
					NextColumn();
				char buf[32];
				sprintf(buf, "%08x", i * 5731);
				Button(buf, ImVec2(-1.0f, 0.0f));
			}
			EndChild();
			PopStyleVar();

			TreePop();
		}

		if (TreeNode("Widgets Width"))
		{
			static float f = 0.0f;
			Text("PushItemWidth(100)");
			SameLine();
			ShowHelpMarker("Fixed width.");
			PushItemWidth(100);
			DragFloat("float##1", &f);
			PopItemWidth();

			Text("PushItemWidth(GetWindowWidth() * 0.5f)");
			SameLine();
			ShowHelpMarker("Half of window width.");
			PushItemWidth(GetWindowWidth() * 0.5f);
			DragFloat("float##2", &f);
			PopItemWidth();

			Text("PushItemWidth(GetContentRegionAvailWidth() * 0.5f)");
			SameLine();
			ShowHelpMarker("Half of available width.\n(~ right-cursor_pos)\n(works within a column set)");
			PushItemWidth(GetContentRegionAvailWidth() * 0.5f);
			DragFloat("float##3", &f);
			PopItemWidth();

			Text("PushItemWidth(-100)");
			SameLine();
			ShowHelpMarker("Align to right edge minus 100");
			PushItemWidth(-100);
			DragFloat("float##4", &f);
			PopItemWidth();

			Text("PushItemWidth(-1)");
			SameLine();
			ShowHelpMarker("Align to right edge");
			PushItemWidth(-1);
			DragFloat("float##5", &f);
			PopItemWidth();

			TreePop();
		}

		if (TreeNode("Basic Horizontal Layout"))
		{
			TextWrapped("(Use ImGui::SameLine() to keep adding items to the right of the preceding item)");

			// Text
			Text("Two items: Hello");
			SameLine();
			TextColored(ImVec4(1, 1, 0, 1), "Sailor");

			// Adjust spacing
			Text("More spacing: Hello");
			SameLine(0, 20);
			TextColored(ImVec4(1, 1, 0, 1), "Sailor");

			// Button
			AlignFirstTextHeightToWidgets();
			Text("Normal buttons");
			SameLine();
			Button("Banana");
			SameLine();
			Button("Apple");
			SameLine();
			Button("Corniflower");

			// Button
			Text("Small buttons");
			SameLine();
			SmallButton("Like this one");
			SameLine();
			Text("can fit within a text block.");

			// Aligned to arbitrary position. Easy/cheap column.
			Text("Aligned");
			SameLine(150);
			Text("x=150");
			SameLine(300);
			Text("x=300");
			Text("Aligned");
			SameLine(150);
			SmallButton("x=150");
			SameLine(300);
			SmallButton("x=300");

			// Checkbox
			static bool c1 = false, c2 = false, c3 = false, c4 = false;
			Checkbox("My", &c1);
			SameLine();
			Checkbox("Tailor", &c2);
			SameLine();
			Checkbox("Is", &c3);
			SameLine();
			Checkbox("Rich", &c4);

			// Various
			static float f0 = 1.0f, f1 = 2.0f, f2 = 3.0f;
			PushItemWidth(80);
			const char* items[] = {"AAAA", "BBBB", "CCCC", "DDDD"};
			static int item = -1;
			Combo("Combo", &item, items, IM_ARRAYSIZE(items));
			SameLine();
			SliderFloat("X", &f0, 0.0f, 5.0f);
			SameLine();
			SliderFloat("Y", &f1, 0.0f, 5.0f);
			SameLine();
			SliderFloat("Z", &f2, 0.0f, 5.0f);
			PopItemWidth();

			PushItemWidth(80);
			Text("Lists:");
			static int selection[4] = {0, 1, 2, 3};
			for (int i = 0; i < 4; i++)
			{
				if (i > 0) SameLine();
				PushID(i);
				ListBox("", &selection[i], items, IM_ARRAYSIZE(items));
				PopID();
				//if (ImGui::IsItemHovered()) ImGui::SetTooltip("ListBox %d hovered", i);
			}
			PopItemWidth();

			// Dummy
			ImVec2 sz(30, 30);
			Button("A", sz);
			SameLine();
			Dummy(sz);
			SameLine();
			Button("B", sz);

			TreePop();
		}

		if (TreeNode("Groups"))
		{
			TextWrapped("(Using ImGui::BeginGroup()/EndGroup() to layout items. BeginGroup() basically locks the horizontal position. EndGroup() bundles the whole group so that you can use functions such as IsItemHovered() on it.)");
			BeginGroup();
			{
				BeginGroup();
				Button("AAA");
				SameLine();
				Button("BBB");
				SameLine();
				BeginGroup();
				Button("CCC");
				Button("DDD");
				EndGroup();
				if (IsItemHovered())
					SetTooltip("Group hovered");
				SameLine();
				Button("EEE");
				EndGroup();
			}
			// Capture the group size and create widgets using the same size
			ImVec2 size = GetItemRectSize();
			const float values[5] = {0.5f, 0.20f, 0.80f, 0.60f, 0.25f};
			PlotHistogram("##values", values, IM_ARRAYSIZE(values), 0, nullptr, 0.0f, 1.0f, size);

			Button("ACTION", ImVec2((size.x - GetStyle().ItemSpacing.x) * 0.5f, size.y));
			SameLine();
			Button("REACTION", ImVec2((size.x - GetStyle().ItemSpacing.x) * 0.5f, size.y));
			EndGroup();
			SameLine();

			Button("LEVERAGE\nBUZZWORD", size);
			SameLine();

			ListBoxHeader("List", size);
			Selectable("Selected", true);
			Selectable("Not Selected", false);
			ListBoxFooter();

			TreePop();
		}

		if (TreeNode("Text Baseline Alignment"))
		{
			TextWrapped("(This is testing the vertical alignment that occurs on text to keep it at the same baseline as widgets. Lines only composed of text or \"small\" widgets fit in less vertical spaces than lines with normal widgets)");

			Text("One\nTwo\nThree");
			SameLine();
			Text("Hello\nWorld");
			SameLine();
			Text("Banana");

			Text("Banana");
			SameLine();
			Text("Hello\nWorld");
			SameLine();
			Text("One\nTwo\nThree");

			Button("HOP##1");
			SameLine();
			Text("Banana");
			SameLine();
			Text("Hello\nWorld");
			SameLine();
			Text("Banana");

			Button("HOP##2");
			SameLine();
			Text("Hello\nWorld");
			SameLine();
			Text("Banana");

			Button("TEST##1");
			SameLine();
			Text("TEST");
			SameLine();
			SmallButton("TEST##2");

			AlignFirstTextHeightToWidgets(); // If your line starts with text, call this to align it to upcoming widgets.
			Text("Text aligned to Widget");
			SameLine();
			Button("Widget##1");
			SameLine();
			Text("Widget");
			SameLine();
			SmallButton("Widget##2");

			// Tree
			const float spacing = GetStyle().ItemInnerSpacing.x;
			Button("Button##1");
			SameLine(0.0f, spacing);
			if (TreeNode("Node##1"))
			{
				for (int i = 0; i < 6; i++) BulletText("Item %d..", i);
				TreePop();
			} // Dummy tree data

			AlignFirstTextHeightToWidgets(); // Vertically align text node a bit lower so it'll be vertically centered with upcoming widget. Otherwise you can use SmallButton (smaller fit).
			bool node_open = TreeNode("Node##2"); // Common mistake to avoid: if we want to SameLine after TreeNode we need to do it before we add child content.
			SameLine(0.0f, spacing);
			Button("Button##2");
			if (node_open)
			{
				for (int i = 0; i < 6; i++) BulletText("Item %d..", i);
				TreePop();
			} // Dummy tree data

			// Bullet
			Button("Button##3");
			SameLine(0.0f, spacing);
			BulletText("Bullet text");

			AlignFirstTextHeightToWidgets();
			BulletText("Node");
			SameLine(0.0f, spacing);
			Button("Button##4");

			TreePop();
		}

		if (TreeNode("Scrolling"))
		{
			TextWrapped("(Use SetScrollHere() or SetScrollFromPosY() to scroll to a given position.)");
			static bool track = true;
			static int track_line = 50, scroll_to_px = 200;
			Checkbox("Track", &track);
			PushItemWidth(100);
			SameLine(130);
			track |= DragInt("##line", &track_line, 0.25f, 0, 99, "Line %.0f");
			bool scroll_to = Button("Scroll To");
			SameLine(130);
			scroll_to |= DragInt("##pos_y", &scroll_to_px, 1.00f, 0, 9999, "y = %.0f px");
			PopItemWidth();
			if (scroll_to) track = false;

			for (int i = 0; i < 5; i++)
			{
				if (i > 0) SameLine();
				BeginGroup();
				Text("%s", i == 0 ? "Top" : i == 1 ? "25%" : i == 2 ? "Center" : i == 3 ? "75%" : "Bottom");
				BeginChild(GetID((void*)(intptr_t)i), ImVec2(GetWindowWidth() * 0.17f, 200.0f), true);
				if (scroll_to)
					SetScrollFromPosY(GetCursorStartPos().y + scroll_to_px, i * 0.25f);
				for (int line = 0; line < 100; line++)
				{
					if (track && line == track_line)
					{
						TextColored(ImColor(255, 255, 0), "Line %d", line);
						SetScrollHere(i * 0.25f); // 0.0f:top, 0.5f:center, 1.0f:bottom
					}
					else
					{
						Text("Line %d", line);
					}
				}
				EndChild();
				EndGroup();
			}
			TreePop();
		}

		if (TreeNode("Horizontal Scrolling"))
		{
			Bullet();
			TextWrapped("Horizontal scrolling for a window has to be enabled explicitly via the ImGuiWindowFlags_HorizontalScrollbar flag.");
			Bullet();
			TextWrapped("You may want to explicitly specify content width by calling SetNextWindowContentWidth() before Begin().");
			static int lines = 7;
			SliderInt("Lines", &lines, 1, 15);
			PushStyleVar(ImGuiStyleVar_FrameRounding, 3.0f);
			PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2.0f, 1.0f));
			BeginChild("scrolling", ImVec2(0, GetItemsLineHeightWithSpacing() * 7 + 30), true, ImGuiWindowFlags_HorizontalScrollbar);
			for (int line = 0; line < lines; line++)
			{
				// Display random stuff (for the sake of this trivial demo we are using basic Button+SameLine. If you want to create your own time line for a real application you may be better off 
				// manipulating the cursor position yourself, aka using SetCursorPos/SetCursorScreenPos to position the widgets yourself. You may also want to use the lower-level ImDrawList API)
				int num_buttons = 10 + ((line & 1) ? line * 9 : line * 3);
				for (int n = 0; n < num_buttons; n++)
				{
					if (n > 0) SameLine();
					PushID(n + line * 1000);
					char num_buf[16];
					const char* label = (!(n % 15)) ? "FizzBuzz" : (!(n % 3)) ? "Fizz" : (!(n % 5)) ? "Buzz" : (sprintf(num_buf, "%d", n) , num_buf);
					float hue = n * 0.05f;
					PushStyleColor(ImGuiCol_Button, ImColor::HSV(hue, 0.6f, 0.6f));
					PushStyleColor(ImGuiCol_ButtonHovered, ImColor::HSV(hue, 0.7f, 0.7f));
					PushStyleColor(ImGuiCol_ButtonActive, ImColor::HSV(hue, 0.8f, 0.8f));
					Button(label, ImVec2(40.0f + sinf((float)(line + n)) * 20.0f, 0.0f));
					PopStyleColor(3);
					PopID();
				}
			}
			EndChild();
			PopStyleVar(2);
			float scroll_x_delta = 0.0f;
			SmallButton("<<");
			if (IsItemActive()) scroll_x_delta = -GetIO().DeltaTime * 1000.0f;
			SameLine();
			Text("Scroll from code");
			SameLine();
			SmallButton(">>");
			if (IsItemActive()) scroll_x_delta = +GetIO().DeltaTime * 1000.0f;
			if (scroll_x_delta != 0.0f)
			{
				BeginChild("scrolling"); // Demonstrate a trick: you can use Begin to set yourself in the context of another window (here we are already out of your child window)
				SetScrollX(GetScrollX() + scroll_x_delta);
				End();
			}
			TreePop();
		}

		if (TreeNode("Clipping"))
		{
			static ImVec2 size(100, 100), offset(50, 20);
			TextWrapped("On a per-widget basis we are occasionally clipping text CPU-side if it won't fit in its frame. Otherwise we are doing coarser clipping + passing a scissor rectangle to the renderer. The system is designed to try minimizing both execution and CPU/GPU rendering cost.");
			DragFloat2("size", (float*)&size, 0.5f, 0.0f, 200.0f, "%.0f");
			TextWrapped("(Click and drag)");
			ImVec2 pos = GetCursorScreenPos();
			ImVec4 clip_rect(pos.x, pos.y, pos.x + size.x, pos.y + size.y);
			InvisibleButton("##dummy", size);
			if (IsItemActive() && IsMouseDragging())
			{
				offset.x += GetIO().MouseDelta.x;
				offset.y += GetIO().MouseDelta.y;
			}
			GetWindowDrawList()->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), ImColor(90, 90, 120, 255));
			GetWindowDrawList()->AddText(GetFont(), GetFontSize() * 2.0f, ImVec2(pos.x + offset.x, pos.y + offset.y), ImColor(255, 255, 255, 255), "Line 1 hello\nLine 2 clip me!", nullptr, 0.0f, &clip_rect);
			TreePop();
		}
	}

	if (CollapsingHeader("Popups & Modal windows"))
	{
		if (TreeNode("Popups"))
		{
			TextWrapped("When a popup is active, it inhibits interacting with windows that are behind the popup. Clicking outside the popup closes it.");

			static int selected_fish = -1;
			const char* names[] = {"Bream", "Haddock", "Mackerel", "Pollock", "Tilefish"};
			static bool toggles[] = {true, false, false, false, false};

			// Simple selection popup
			// (If you want to show the current selection inside the Button itself, you may want to build a string using the "###" operator to preserve a constant ID with a variable label)
			if (Button("Select.."))
				OpenPopup("select");
			SameLine();
			Text(selected_fish == -1 ? "<None>" : names[selected_fish]);
			if (BeginPopup("select"))
			{
				Text("Aquarium");
				Separator();
				for (int i = 0; i < IM_ARRAYSIZE(names); i++)
					if (Selectable(names[i]))
						selected_fish = i;
				EndPopup();
			}

			// Showing a menu with toggles
			if (Button("Toggle.."))
				OpenPopup("toggle");
			if (BeginPopup("toggle"))
			{
				for (int i = 0; i < IM_ARRAYSIZE(names); i++)
					MenuItem(names[i], "", &toggles[i]);
				if (BeginMenu("Sub-menu"))
				{
					MenuItem("Click me");
					EndMenu();
				}

				Separator();
				Text("Tooltip here");
				if (IsItemHovered())
					SetTooltip("I am a tooltip over a popup");

				if (Button("Stacked Popup"))
					OpenPopup("another popup");
				if (BeginPopup("another popup"))
				{
					for (int i = 0; i < IM_ARRAYSIZE(names); i++)
						MenuItem(names[i], "", &toggles[i]);
					if (BeginMenu("Sub-menu"))
					{
						MenuItem("Click me");
						EndMenu();
					}
					EndPopup();
				}
				EndPopup();
			}

			if (Button("Popup Menu.."))
				OpenPopup("FilePopup");
			if (BeginPopup("FilePopup"))
			{
				ShowExampleMenuFile();
				EndPopup();
			}

			Spacing();
			TextWrapped("Below we are testing adding menu items to a regular window. It's rather unusual but should work!");
			Separator();
			// NB: As a quirk in this very specific example, we want to differentiate the parent of this menu from the parent of the various popup menus above.
			// To do so we are encloding the items in a PushID()/PopID() block to make them two different menusets. If we don't, opening any popup above and hovering our menu here
			// would open it. This is because once a menu is active, we allow to switch to a sibling menu by just hovering on it, which is the desired behavior for regular menus.
			PushID("foo");
			MenuItem("Menu item", "CTRL+M");
			if (BeginMenu("Menu inside a regular window"))
			{
				ShowExampleMenuFile();
				EndMenu();
			}
			PopID();
			Separator();

			TreePop();
		}

		if (TreeNode("Context menus"))
		{
			static float value = 0.5f;
			Text("Value = %.3f (<-- right-click here)", value);
			if (BeginPopupContextItem("item context menu"))
			{
				if (Selectable("Set to zero")) value = 0.0f;
				if (Selectable("Set to PI")) value = 3.1415f;
				EndPopup();
			}

			static ImVec4 color = ImColor(0.8f, 0.5f, 1.0f, 1.0f);
			ColorButton(color);
			if (BeginPopupContextItem("color context menu"))
			{
				Text("Edit color");
				ColorEdit3("##edit", (float*)&color);
				if (Button("Close"))
					CloseCurrentPopup();
				EndPopup();
			}
			SameLine();
			Text("(<-- right-click here)");

			TreePop();
		}

		if (TreeNode("Modals"))
		{
			TextWrapped("Modal windows are like popups but the user cannot close them by clicking outside the window.");

			if (Button("Delete.."))
				OpenPopup("Delete?");
			if (BeginPopupModal("Delete?", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				Text("All those beautiful files will be deleted.\nThis operation cannot be undone!\n\n");
				Separator();

				//static int dummy_i = 0;
				//ImGui::Combo("Combo", &dummy_i, "Delete\0Delete harder\0");

				static bool dont_ask_me_next_time = false;
				PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
				Checkbox("Don't ask me next time", &dont_ask_me_next_time);
				PopStyleVar();

				if (Button("OK", ImVec2(120, 0))) { CloseCurrentPopup(); }
				SameLine();
				if (Button("Cancel", ImVec2(120, 0))) { CloseCurrentPopup(); }
				EndPopup();
			}

			if (Button("Stacked modals.."))
				OpenPopup("Stacked 1");
			if (BeginPopupModal("Stacked 1"))
			{
				Text("Hello from Stacked The First");

				if (Button("Another one.."))
					OpenPopup("Stacked 2");
				if (BeginPopupModal("Stacked 2"))
				{
					Text("Hello from Stacked The Second");
					if (Button("Close"))
						CloseCurrentPopup();
					EndPopup();
				}

				if (Button("Close"))
					CloseCurrentPopup();
				EndPopup();
			}

			TreePop();
		}
	}

	if (CollapsingHeader("Columns"))
	{
		// Basic columns
		if (TreeNode("Basic"))
		{
			Text("Without border:");
			Columns(3, "mycolumns3", false); // 3-ways, no border
			Separator();
			for (int n = 0; n < 14; n++)
			{
				char label[32];
				sprintf(label, "Item %d", n);
				if (Selectable(label))
				{
				}
				//if (ImGui::Button(label, ImVec2(-1,0))) {}
				NextColumn();
			}
			Columns(1);
			Separator();

			Text("With border:");
			Columns(4, "mycolumns"); // 4-ways, with border
			Separator();
			Text("ID");
			NextColumn();
			Text("Name");
			NextColumn();
			Text("Path");
			NextColumn();
			Text("Flags");
			NextColumn();
			Separator();
			const char* names[3] = {"One", "Two", "Three"};
			const char* paths[3] = {"/path/one", "/path/two", "/path/three"};
			static int selected = -1;
			for (int i = 0; i < 3; i++)
			{
				char label[32];
				sprintf(label, "%04d", i);
				if (Selectable(label, selected == i, ImGuiSelectableFlags_SpanAllColumns))
					selected = i;
				NextColumn();
				Text(names[i]);
				NextColumn();
				Text(paths[i]);
				NextColumn();
				Text("....");
				NextColumn();
			}
			Columns(1);
			Separator();
			TreePop();
		}

		// Scrolling columns
		/*
		if (ImGui::TreeNode("Scrolling"))
		{
		    ImGui::BeginChild("##header", ImVec2(0, ImGui::GetTextLineHeightWithSpacing()+ImGui::GetStyle().ItemSpacing.y));
		    ImGui::Columns(3);
		    ImGui::Text("ID"); ImGui::NextColumn();
		    ImGui::Text("Name"); ImGui::NextColumn();
		    ImGui::Text("Path"); ImGui::NextColumn();
		    ImGui::Columns(1);
		    ImGui::Separator();
		    ImGui::EndChild();
		    ImGui::BeginChild("##scrollingregion", ImVec2(0, 60));
		    ImGui::Columns(3);
		    for (int i = 0; i < 10; i++)
		    {
		        ImGui::Text("%04d", i); ImGui::NextColumn();
		        ImGui::Text("Foobar"); ImGui::NextColumn();
		        ImGui::Text("/path/foobar/%04d/", i); ImGui::NextColumn();
		    }
		    ImGui::Columns(1);
		    ImGui::EndChild();
		    ImGui::TreePop();
		}
		*/

		// Create multiple items in a same cell before switching to next column
		if (TreeNode("Mixed items"))
		{
			Columns(3, "mixed");
			Separator();

			Text("Hello");
			Button("Banana");
			NextColumn();

			Text("ImGui");
			Button("Apple");
			static float foo = 1.0f;
			InputFloat("red", &foo, 0.05f, 0, 3);
			Text("An extra line here.");
			NextColumn();

			Text("Sailor");
			Button("Corniflower");
			static float bar = 1.0f;
			InputFloat("blue", &bar, 0.05f, 0, 3);
			NextColumn();

			if (CollapsingHeader("Category A")) Text("Blah blah blah");
			NextColumn();
			if (CollapsingHeader("Category B")) Text("Blah blah blah");
			NextColumn();
			if (CollapsingHeader("Category C")) Text("Blah blah blah");
			NextColumn();
			Columns(1);
			Separator();
			TreePop();
		}

		// Word wrapping
		if (TreeNode("Word-wrapping"))
		{
			Columns(2, "word-wrapping");
			Separator();
			TextWrapped("The quick brown fox jumps over the lazy dog.");
			TextWrapped("Hello Left");
			NextColumn();
			TextWrapped("The quick brown fox jumps over the lazy dog.");
			TextWrapped("Hello Right");
			Columns(1);
			Separator();
			TreePop();
		}

		if (TreeNode("Borders"))
		{
			static bool h_borders = true;
			static bool v_borders = true;
			Checkbox("horizontal", &h_borders);
			SameLine();
			Checkbox("vertical", &v_borders);
			Columns(4, nullptr, v_borders);
			if (h_borders) Separator();
			for (int i = 0; i < 8; i++)
			{
				Text("%c%c%c", 'a' + i, 'a' + i, 'a' + i);
				NextColumn();
			}
			Columns(1);
			if (h_borders) Separator();
			TreePop();
		}

		bool node_open = TreeNode("Tree within single cell");
		SameLine();
		ShowHelpMarker("NB: Tree node must be poped before ending the cell.\nThere's no storage of state per-cell.");
		if (node_open)
		{
			Columns(2, "tree items");
			Separator();
			if (TreeNode("Hello"))
			{
				BulletText("Sailor");
				TreePop();
			}
			NextColumn();
			if (TreeNode("Bonjour"))
			{
				BulletText("Marin");
				TreePop();
			}
			NextColumn();
			Columns(1);
			Separator();
			TreePop();
		}
	}

	if (CollapsingHeader("Filtering"))
	{
		static ImGuiTextFilter filter;
		Text("Filter usage:\n"
			"  \"\"         display all lines\n"
			"  \"xxx\"      display lines containing \"xxx\"\n"
			"  \"xxx,yyy\"  display lines containing \"xxx\" or \"yyy\"\n"
			"  \"-xxx\"     hide lines containing \"xxx\"");
		filter.Draw();
		const char* lines[] = {"aaa1.c", "bbb1.c", "ccc1.c", "aaa2.cpp", "bbb2.cpp", "ccc2.cpp", "abc.h", "hello, world"};
		for (int i = 0; i < IM_ARRAYSIZE(lines); i++)
			if (filter.PassFilter(lines[i]))
				BulletText("%s", lines[i]);
	}

	if (CollapsingHeader("Keyboard, Mouse & Focus"))
	{
		if (TreeNode("Tabbing"))
		{
			Text("Use TAB/SHIFT+TAB to cycle through keyboard editable fields.");
			static char buf[32] = "dummy";
			InputText("1", buf, IM_ARRAYSIZE(buf));
			InputText("2", buf, IM_ARRAYSIZE(buf));
			InputText("3", buf, IM_ARRAYSIZE(buf));
			PushAllowKeyboardFocus(false);
			InputText("4 (tab skip)", buf, IM_ARRAYSIZE(buf));
			//ImGui::SameLine(); ShowHelperMarker("Use ImGui::PushAllowKeyboardFocus(bool)\nto disable tabbing through certain widgets.");
			PopAllowKeyboardFocus();
			InputText("5", buf, IM_ARRAYSIZE(buf));
			TreePop();
		}

		if (TreeNode("Focus from code"))
		{
			bool focus_1 = Button("Focus on 1");
			SameLine();
			bool focus_2 = Button("Focus on 2");
			SameLine();
			bool focus_3 = Button("Focus on 3");
			int has_focus = 0;
			static char buf[128] = "click on a button to set focus";

			if (focus_1) SetKeyboardFocusHere();
			InputText("1", buf, IM_ARRAYSIZE(buf));
			if (IsItemActive()) has_focus = 1;

			if (focus_2) SetKeyboardFocusHere();
			InputText("2", buf, IM_ARRAYSIZE(buf));
			if (IsItemActive()) has_focus = 2;

			PushAllowKeyboardFocus(false);
			if (focus_3) SetKeyboardFocusHere();
			InputText("3 (tab skip)", buf, IM_ARRAYSIZE(buf));
			if (IsItemActive()) has_focus = 3;
			PopAllowKeyboardFocus();
			if (has_focus)
				Text("Item with focus: %d", has_focus);
			else
				Text("Item with focus: <none>");
			TextWrapped("Cursor & selection are preserved when refocusing last used item in code.");
			TreePop();
		}

		if (TreeNode("Dragging"))
		{
			TextWrapped("You can use ImGui::GetMouseDragDelta(0) to query for the dragged amount on any widget.");
			Button("Drag Me");
			if (IsItemActive())
			{
				// Draw a line between the button and the mouse cursor
				ImDrawList* draw_list = GetWindowDrawList();
				draw_list->PushClipRectFullScreen();
				draw_list->AddLine(CalcItemRectClosestPoint(GetIO().MousePos, true, -2.0f), GetIO().MousePos, ImColor(GetStyle().Colors[ImGuiCol_Button]), 4.0f);
				draw_list->PopClipRect();
				ImVec2 value_raw = GetMouseDragDelta(0, 0.0f);
				ImVec2 value_with_lock_threshold = GetMouseDragDelta(0);
				ImVec2 mouse_delta = GetIO().MouseDelta;
				SameLine();
				Text("Raw (%.1f, %.1f), WithLockThresold (%.1f, %.1f), MouseDelta (%.1f, %.1f)", value_raw.x, value_raw.y, value_with_lock_threshold.x, value_with_lock_threshold.y, mouse_delta.x, mouse_delta.y);
			}
			TreePop();
		}

		if (TreeNode("Keyboard & Mouse State"))
		{
			ImGuiIO& io = GetIO();

			Text("MousePos: (%g, %g)", io.MousePos.x, io.MousePos.y);
			Text("Mouse down:");
			for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++)
				if (io.MouseDownDuration[i] >= 0.0f)
				{
					SameLine();
					Text("b%d (%.02f secs)", i, io.MouseDownDuration[i]);
				}
			Text("Mouse clicked:");
			for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++)
				if (IsMouseClicked(i))
				{
					SameLine();
					Text("b%d", i);
				}
			Text("Mouse dbl-clicked:");
			for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++)
				if (IsMouseDoubleClicked(i))
				{
					SameLine();
					Text("b%d", i);
				}
			Text("Mouse released:");
			for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++)
				if (IsMouseReleased(i))
				{
					SameLine();
					Text("b%d", i);
				}
			Text("MouseWheel: %.1f", io.MouseWheel);

			Text("Keys down:");
			for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++)
				if (io.KeysDownDuration[i] >= 0.0f)
				{
					SameLine();
					Text("%d (%.02f secs)", i, io.KeysDownDuration[i]);
				}
			Text("Keys pressed:");
			for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++)
				if (IsKeyPressed(i))
				{
					SameLine();
					Text("%d", i);
				}
			Text("Keys release:");
			for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++)
				if (IsKeyReleased(i))
				{
					SameLine();
					Text("%d", i);
				}
			Text("KeyMods: %s%s%s%s", io.KeyCtrl ? "CTRL " : "", io.KeyShift ? "SHIFT " : "", io.KeyAlt ? "ALT " : "", io.KeySuper ? "SUPER " : "");

			Text("WantCaptureMouse: %s", io.WantCaptureMouse ? "true" : "false");
			Text("WantCaptureKeyboard: %s", io.WantCaptureKeyboard ? "true" : "false");
			Text("WantTextInput: %s", io.WantTextInput ? "true" : "false");

			Button("Hovering me sets the\nkeyboard capture flag");
			if (IsItemHovered())
				CaptureKeyboardFromApp(true);
			SameLine();
			Button("Holding me clears the\nthe keyboard capture flag");
			if (IsItemActive())
				CaptureKeyboardFromApp(false);

			TreePop();
		}

		if (TreeNode("Mouse cursors"))
		{
			TextWrapped("Your application can render a different mouse cursor based on what ImGui::GetMouseCursor() returns. You can also set io.MouseDrawCursor to ask ImGui to render the cursor for you in software.");
			Checkbox("io.MouseDrawCursor", &GetIO().MouseDrawCursor);
			Text("Hover to see mouse cursors:");
			for (int i = 0; i < ImGuiMouseCursor_Count_; i++)
			{
				char label[32];
				sprintf(label, "Mouse cursor %d", i);
				Bullet();
				Selectable(label, false);
				if (IsItemHovered())
					SetMouseCursor(i);
			}
			TreePop();
		}
	}

	End();
}

void ImGui::ShowStyleEditor(ImGuiStyle* ref)
{
	ImGuiStyle& style = GetStyle();

	// You can pass in a reference ImGuiStyle structure to compare to, revert to and save to (else it compares to the default style)
	const ImGuiStyle default_style; // Default style
	if (Button("Revert Style"))
		style = ref ? *ref : default_style;

	if (ref)
	{
		SameLine();
		if (Button("Save Style"))
			*ref = style;
	}

	PushItemWidth(GetWindowWidth() * 0.55f);

	if (TreeNode("Rendering"))
	{
		Checkbox("Anti-aliased lines", &style.AntiAliasedLines);
		Checkbox("Anti-aliased shapes", &style.AntiAliasedShapes);
		PushItemWidth(100);
		DragFloat("Curve Tessellation Tolerance", &style.CurveTessellationTol, 0.02f, 0.10f, FLT_MAX, nullptr, 2.0f);
		if (style.CurveTessellationTol < 0.0f) style.CurveTessellationTol = 0.10f;
		DragFloat("Global Alpha", &style.Alpha, 0.005f, 0.20f, 1.0f, "%.2f"); // Not exposing zero here so user doesn't "lose" the UI (zero alpha clips all widgets). But application code could have a toggle to switch between zero and non-zero.
		PopItemWidth();
		TreePop();
	}

	if (TreeNode("Settings"))
	{
		SliderFloat2("WindowPadding", (float*)&style.WindowPadding, 0.0f, 20.0f, "%.0f");
		SliderFloat("WindowRounding", &style.WindowRounding, 0.0f, 16.0f, "%.0f");
		SliderFloat("ChildWindowRounding", &style.ChildWindowRounding, 0.0f, 16.0f, "%.0f");
		SliderFloat2("FramePadding", (float*)&style.FramePadding, 0.0f, 20.0f, "%.0f");
		SliderFloat("FrameRounding", &style.FrameRounding, 0.0f, 16.0f, "%.0f");
		SliderFloat2("ItemSpacing", (float*)&style.ItemSpacing, 0.0f, 20.0f, "%.0f");
		SliderFloat2("ItemInnerSpacing", (float*)&style.ItemInnerSpacing, 0.0f, 20.0f, "%.0f");
		SliderFloat2("TouchExtraPadding", (float*)&style.TouchExtraPadding, 0.0f, 10.0f, "%.0f");
		SliderFloat("IndentSpacing", &style.IndentSpacing, 0.0f, 30.0f, "%.0f");
		SliderFloat("ScrollbarSize", &style.ScrollbarSize, 1.0f, 20.0f, "%.0f");
		SliderFloat("ScrollbarRounding", &style.ScrollbarRounding, 0.0f, 16.0f, "%.0f");
		SliderFloat("GrabMinSize", &style.GrabMinSize, 1.0f, 20.0f, "%.0f");
		SliderFloat("GrabRounding", &style.GrabRounding, 0.0f, 16.0f, "%.0f");
		Text("Alignment");
		SliderFloat2("WindowTitleAlign", (float*)&style.WindowTitleAlign, 0.0f, 1.0f, "%.2f");
		SliderFloat2("ButtonTextAlign", (float*)&style.ButtonTextAlign, 0.0f, 1.0f, "%.2f");
		SameLine();
		ShowHelpMarker("Alignment applies when a button is larger than its text content.");
		TreePop();
	}

	if (TreeNode("Colors"))
	{
		static int output_dest = 0;
		static bool output_only_modified = false;
		if (Button("Copy Colors"))
		{
			if (output_dest == 0)
				LogToClipboard();
			else
				LogToTTY();
			LogText("ImGuiStyle& style = ImGui::GetStyle();" IM_NEWLINE);
			for (int i = 0; i < ImGuiCol_COUNT; i++)
			{
				const ImVec4& col = style.Colors[i];
				const char* name = GetStyleColName(i);
				if (!output_only_modified || memcmp(&col, (ref ? &ref->Colors[i] : &default_style.Colors[i]), sizeof(ImVec4)) != 0)
					LogText("style.Colors[ImGuiCol_%s]%*s= ImVec4(%.2ff, %.2ff, %.2ff, %.2ff);" IM_NEWLINE, name, 22 - (int)strlen(name), "", col.x, col.y, col.z, col.w);
			}
			LogFinish();
		}
		SameLine();
		PushItemWidth(120);
		Combo("##output_type", &output_dest, "To Clipboard\0To TTY\0");
		PopItemWidth();
		SameLine();
		Checkbox("Only Modified Fields", &output_only_modified);

		static ImGuiColorEditMode edit_mode = ImGuiColorEditMode_RGB;
		RadioButton("RGB", &edit_mode, ImGuiColorEditMode_RGB);
		SameLine();
		RadioButton("HSV", &edit_mode, ImGuiColorEditMode_HSV);
		SameLine();
		RadioButton("HEX", &edit_mode, ImGuiColorEditMode_HEX);
		//ImGui::Text("Tip: Click on colored square to change edit mode.");

		static ImGuiTextFilter filter;
		filter.Draw("Filter colors", 200);

		BeginChild("#colors", ImVec2(0, 300), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);
		PushItemWidth(-160);
		ColorEditMode(edit_mode);
		for (int i = 0; i < ImGuiCol_COUNT; i++)
		{
			const char* name = GetStyleColName(i);
			if (!filter.PassFilter(name))
				continue;
			PushID(i);
			ColorEdit4(name, (float*)&style.Colors[i], true);
			if (memcmp(&style.Colors[i], (ref ? &ref->Colors[i] : &default_style.Colors[i]), sizeof(ImVec4)) != 0)
			{
				SameLine();
				if (Button("Revert")) style.Colors[i] = ref ? ref->Colors[i] : default_style.Colors[i];
				if (ref)
				{
					SameLine();
					if (Button("Save")) ref->Colors[i] = style.Colors[i];
				}
			}
			PopID();
		}
		PopItemWidth();
		EndChild();

		TreePop();
	}

	if (TreeNode("Fonts", "Fonts (%d)", GetIO().Fonts->Fonts.Size))
	{
		SameLine();
		ShowHelpMarker("Tip: Load fonts with io.Fonts->AddFontFromFileTTF()\nbefore calling io.Fonts->GetTex* functions.");
		ImFontAtlas* atlas = GetIO().Fonts;
		if (TreeNode("Atlas texture", "Atlas texture (%dx%d pixels)", atlas->TexWidth, atlas->TexHeight))
		{
			Image(atlas->TexID, ImVec2((float)atlas->TexWidth, (float)atlas->TexHeight), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
			TreePop();
		}
		PushItemWidth(100);
		for (int i = 0; i < atlas->Fonts.Size; i++)
		{
			ImFont* font = atlas->Fonts[i];
			BulletText("Font %d: \'%s\', %.2f px, %d glyphs", i, font->ConfigData ? font->ConfigData[0].Name : "", font->FontSize, font->Glyphs.Size);
			TreePush((void*)(intptr_t)i);
			SameLine();
			if (SmallButton("Set as default")) GetIO().FontDefault = font;
			PushFont(font);
			Text("The quick brown fox jumps over the lazy dog");
			PopFont();
			if (TreeNode("Details"))
			{
				DragFloat("Font scale", &font->Scale, 0.005f, 0.3f, 2.0f, "%.1f"); // Scale only this font
				SameLine();
				ShowHelpMarker("Note than the default embedded font is NOT meant to be scaled.\n\nFont are currently rendered into bitmaps at a given size at the time of building the atlas. You may oversample them to get some flexibility with scaling. You can also render at multiple sizes and select which one to use at runtime.\n\n(Glimmer of hope: the atlas system should hopefully be rewritten in the future to make scaling more natural and automatic.)");
				Text("Ascent: %f, Descent: %f, Height: %f", font->Ascent, font->Descent, font->Ascent - font->Descent);
				Text("Fallback character: '%c' (%d)", font->FallbackChar, font->FallbackChar);
				Text("Texture surface: %d pixels (approx)", font->MetricsTotalSurface);
				for (int config_i = 0; config_i < font->ConfigDataCount; config_i++)
				{
					ImFontConfig* cfg = &font->ConfigData[config_i];
					BulletText("Input %d: \'%s\', Oversample: (%d,%d), PixelSnapH: %d", config_i, cfg->Name, cfg->OversampleH, cfg->OversampleV, cfg->PixelSnapH);
				}
				if (TreeNode("Glyphs", "Glyphs (%d)", font->Glyphs.Size))
				{
					// Display all glyphs of the fonts in separate pages of 256 characters
					const ImFont::Glyph* glyph_fallback = font->FallbackGlyph; // Forcefully/dodgily make FindGlyph() return NULL on fallback, which isn't the default behavior.
					font->FallbackGlyph = nullptr;
					for (int base = 0; base < 0x10000; base += 256)
					{
						int count = 0;
						for (int n = 0; n < 256; n++)
							count += font->FindGlyph((ImWchar)(base + n)) ? 1 : 0;
						if (count > 0 && TreeNode((void*)(intptr_t)base, "U+%04X..U+%04X (%d %s)", base, base + 255, count, count > 1 ? "glyphs" : "glyph"))
						{
							float cell_spacing = style.ItemSpacing.y;
							ImVec2 cell_size(font->FontSize * 1, font->FontSize * 1);
							ImVec2 base_pos = GetCursorScreenPos();
							ImDrawList* draw_list = GetWindowDrawList();
							for (int n = 0; n < 256; n++)
							{
								ImVec2 cell_p1(base_pos.x + (n % 16) * (cell_size.x + cell_spacing), base_pos.y + (n / 16) * (cell_size.y + cell_spacing));
								ImVec2 cell_p2(cell_p1.x + cell_size.x, cell_p1.y + cell_size.y);
								const ImFont::Glyph* glyph = font->FindGlyph((ImWchar)(base + n));
								draw_list->AddRect(cell_p1, cell_p2, glyph ? IM_COL32(255,255,255,100) : IM_COL32(255,255,255,50));
								font->RenderChar(draw_list, cell_size.x, cell_p1, GetColorU32(ImGuiCol_Text), (ImWchar)(base + n)); // We use ImFont::RenderChar as a shortcut because we don't have UTF-8 conversion functions available to generate a string.
								if (glyph && IsMouseHoveringRect(cell_p1, cell_p2))
								{
									BeginTooltip();
									Text("Codepoint: U+%04X", base + n);
									Separator();
									Text("XAdvance+1: %.1f", glyph->XAdvance);
									Text("Pos: (%.2f,%.2f)->(%.2f,%.2f)", glyph->X0, glyph->Y0, glyph->X1, glyph->Y1);
									Text("UV: (%.3f,%.3f)->(%.3f,%.3f)", glyph->U0, glyph->V0, glyph->U1, glyph->V1);
									EndTooltip();
								}
							}
							Dummy(ImVec2((cell_size.x + cell_spacing) * 16, (cell_size.y + cell_spacing) * 16));
							TreePop();
						}
					}
					font->FallbackGlyph = glyph_fallback;
					TreePop();
				}
				TreePop();
			}
			TreePop();
		}
		static float window_scale = 1.0f;
		DragFloat("this window scale", &window_scale, 0.005f, 0.3f, 2.0f, "%.1f"); // scale only this window
		DragFloat("global scale", &GetIO().FontGlobalScale, 0.005f, 0.3f, 2.0f, "%.1f"); // scale everything
		PopItemWidth();
		SetWindowFontScale(window_scale);
		TreePop();
	}

	PopItemWidth();
}

// Demonstrate creating a fullscreen menu bar and populating it.
static void ShowExampleAppMainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ShowExampleMenuFile();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z"))
			{
			}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false))
			{
			} // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X"))
			{
			}
			if (ImGui::MenuItem("Copy", "CTRL+C"))
			{
			}
			if (ImGui::MenuItem("Paste", "CTRL+V"))
			{
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

static void ShowExampleMenuFile()
{
	ImGui::MenuItem("(dummy menu)", nullptr, false, false);
	if (ImGui::MenuItem("New"))
	{
	}
	if (ImGui::MenuItem("Open", "Ctrl+O"))
	{
	}
	if (ImGui::BeginMenu("Open Recent"))
	{
		ImGui::MenuItem("fish_hat.c");
		ImGui::MenuItem("fish_hat.inl");
		ImGui::MenuItem("fish_hat.h");
		if (ImGui::BeginMenu("More.."))
		{
			ImGui::MenuItem("Hello");
			ImGui::MenuItem("Sailor");
			if (ImGui::BeginMenu("Recurse.."))
			{
				ShowExampleMenuFile();
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
	if (ImGui::MenuItem("Save", "Ctrl+S"))
	{
	}
	if (ImGui::MenuItem("Save As.."))
	{
	}
	ImGui::Separator();
	if (ImGui::BeginMenu("Options"))
	{
		static bool enabled = true;
		ImGui::MenuItem("Enabled", "", &enabled);
		ImGui::BeginChild("child", ImVec2(0, 60), true);
		for (int i = 0; i < 10; i++)
			ImGui::Text("Scrolling Text %d", i);
		ImGui::EndChild();
		static float f = 0.5f;
		static int n = 0;
		ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
		ImGui::InputFloat("Input", &f, 0.1f);
		ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Colors"))
	{
		for (int i = 0; i < ImGuiCol_COUNT; i++)
			ImGui::MenuItem(ImGui::GetStyleColName((ImGuiCol)i));
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Disabled", false)) // Disabled
	{
		IM_ASSERT(0);
	}
	if (ImGui::MenuItem("Checked", nullptr, true))
	{
	}
	if (ImGui::MenuItem("Quit", "Alt+F4"))
	{
	}
}

// Demonstrate creating a window which gets auto-resized according to its content.
static void ShowExampleAppAutoResize(bool* p_open)
{
	if (!ImGui::Begin("Example: Auto-resizing window", p_open, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
		return;
	}

	static int lines = 10;
	ImGui::Text("Window will resize every-frame to the size of its content.\nNote that you probably don't want to query the window size to\noutput your content because that would create a feedback loop.");
	ImGui::SliderInt("Number of lines", &lines, 1, 20);
	for (int i = 0; i < lines; i++)
		ImGui::Text("%*sThis is line %d", i * 4, "", i); // Pad with space to extend size horizontally
	ImGui::End();
}

// Demonstrate creating a window with custom resize constraints.
static void ShowExampleAppConstrainedResize(bool* p_open)
{
	struct CustomConstraints // Helper functions to demonstrate programmatic constraints
	{
		static void Square(ImGuiSizeConstraintCallbackData* data) { data->DesiredSize = ImVec2(IM_MAX(data->DesiredSize.x, data->DesiredSize.y), IM_MAX(data->DesiredSize.x, data->DesiredSize.y)); }

		static void Step(ImGuiSizeConstraintCallbackData* data)
		{
			float step = (float)(int)(intptr_t)data->UserData;
			data->DesiredSize = ImVec2((int)(data->DesiredSize.x / step + 0.5f) * step, (int)(data->DesiredSize.y / step + 0.5f) * step);
		}
	};

	static int type = 0;
	if (type == 0) ImGui::SetNextWindowSizeConstraints(ImVec2(-1, 0), ImVec2(-1, FLT_MAX)); // Vertical only
	if (type == 1) ImGui::SetNextWindowSizeConstraints(ImVec2(0, -1), ImVec2(FLT_MAX, -1)); // Horizontal only
	if (type == 2) ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(FLT_MAX, FLT_MAX)); // Width > 100, Height > 100
	if (type == 3) ImGui::SetNextWindowSizeConstraints(ImVec2(300, 0), ImVec2(400, FLT_MAX)); // Width 300-400
	if (type == 4) ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), CustomConstraints::Square); // Always Square
	if (type == 5) ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), CustomConstraints::Step, (void*)100);// Fixed Step

	if (ImGui::Begin("Example: Constrained Resize", p_open))
	{
		const char* desc[] =
		{
			"Resize vertical only",
			"Resize horizontal only",
			"Width > 100, Height > 100",
			"Width 300-400",
			"Custom: Always Square",
			"Custom: Fixed Steps (100)",
		};
		ImGui::Combo("Constraint", &type, desc, IM_ARRAYSIZE(desc));
		if (ImGui::Button("200x200")) ImGui::SetWindowSize(ImVec2(200, 200));
		ImGui::SameLine();
		if (ImGui::Button("500x500")) ImGui::SetWindowSize(ImVec2(500, 500));
		ImGui::SameLine();
		if (ImGui::Button("800x200")) ImGui::SetWindowSize(ImVec2(800, 200));
		for (int i = 0; i < 10; i++)
			ImGui::Text("Hello, sailor! Making this line long enough for the example.");
	}
	ImGui::End();
}

// Demonstrate creating a simple static window with no decoration.
static void ShowExampleAppFixedOverlay(bool* p_open)
{
	ImGui::SetNextWindowPos(ImVec2(10, 10));
	if (!ImGui::Begin("Example: Fixed Overlay", p_open, ImVec2(0, 0), 0.3f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings))
	{
		ImGui::End();
		return;
	}
	ImGui::Text("Simple overlay\non the top-left side of the screen.");
	ImGui::Separator();
	ImGui::Text("Mouse Position: (%.1f,%.1f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
	ImGui::End();
}

// Demonstrate using "##" and "###" in identifiers to manipulate ID generation.
// Read section "How can I have multiple widgets with the same label? Can I have widget without a label? (Yes). A primer on the purpose of labels/IDs." about ID.
static void ShowExampleAppManipulatingWindowTitle(bool*)
{
	// By default, Windows are uniquely identified by their title.
	// You can use the "##" and "###" markers to manipulate the display/ID.

	// Using "##" to display same title but have unique identifier.
	ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Same title as another window##1");
	ImGui::Text("This is window 1.\nMy title is the same as window 2, but my identifier is unique.");
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(100, 200), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Same title as another window##2");
	ImGui::Text("This is window 2.\nMy title is the same as window 1, but my identifier is unique.");
	ImGui::End();

	// Using "###" to display a changing title but keep a static identifier "AnimatedTitle"
	char buf[128];
	sprintf(buf, "Animated title %c %d###AnimatedTitle", "|/-\\"[(int)(ImGui::GetTime() / 0.25f) & 3], rand());
	ImGui::SetNextWindowPos(ImVec2(100, 300), ImGuiSetCond_FirstUseEver);
	ImGui::Begin(buf);
	ImGui::Text("This window has a changing title.");
	ImGui::End();
}

// Demonstrate using the low-level ImDrawList to draw custom shapes. 
static void ShowExampleAppCustomRendering(bool* p_open)
{
	ImGui::SetNextWindowSize(ImVec2(350, 560), ImGuiSetCond_FirstUseEver);
	if (!ImGui::Begin("Example: Custom rendering", p_open))
	{
		ImGui::End();
		return;
	}

	// Tip: If you do a lot of custom rendering, you probably want to use your own geometrical types and benefit of overloaded operators, etc.
	// Define IM_VEC2_CLASS_EXTRA in imConfig.h to create implicit conversions between your types and ImVec2/ImVec4.
	// ImGui defines overloaded operators but they are internal to imgui.cpp and not exposed outside (to avoid messing with your types)
	// In this example we are not using the maths operators!
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	// Primitives
	ImGui::Text("Primitives");
	static float sz = 36.0f;
	static ImVec4 col = ImVec4(1.0f, 1.0f, 0.4f, 1.0f);
	ImGui::DragFloat("Size", &sz, 0.2f, 2.0f, 72.0f, "%.0f");
	ImGui::ColorEdit3("Color", &col.x);
	{
		const ImVec2 p = ImGui::GetCursorScreenPos();
		const ImU32 col32 = ImColor(col);
		float x = p.x + 4.0f, y = p.y + 4.0f, spacing = 8.0f;
		for (int n = 0; n < 2; n++)
		{
			float thickness = (n == 0) ? 1.0f : 4.0f;
			draw_list->AddCircle(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, col32, 20, thickness);
			x += sz + spacing;
			draw_list->AddRect(ImVec2(x, y), ImVec2(x + sz, y + sz), col32, 0.0f, ~0, thickness);
			x += sz + spacing;
			draw_list->AddRect(ImVec2(x, y), ImVec2(x + sz, y + sz), col32, 10.0f, ~0, thickness);
			x += sz + spacing;
			draw_list->AddTriangle(ImVec2(x + sz * 0.5f, y), ImVec2(x + sz, y + sz - 0.5f), ImVec2(x, y + sz - 0.5f), col32, thickness);
			x += sz + spacing;
			draw_list->AddLine(ImVec2(x, y), ImVec2(x + sz, y), col32, thickness);
			x += sz + spacing;
			draw_list->AddLine(ImVec2(x, y), ImVec2(x + sz, y + sz), col32, thickness);
			x += sz + spacing;
			draw_list->AddLine(ImVec2(x, y), ImVec2(x, y + sz), col32, thickness);
			x += spacing;
			draw_list->AddBezierCurve(ImVec2(x, y), ImVec2(x + sz * 1.3f, y + sz * 0.3f), ImVec2(x + sz - sz * 1.3f, y + sz - sz * 0.3f), ImVec2(x + sz, y + sz), col32, thickness);
			x = p.x + 4;
			y += sz + spacing;
		}
		draw_list->AddCircleFilled(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, col32, 32);
		x += sz + spacing;
		draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + sz, y + sz), col32);
		x += sz + spacing;
		draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + sz, y + sz), col32, 10.0f);
		x += sz + spacing;
		draw_list->AddTriangleFilled(ImVec2(x + sz * 0.5f, y), ImVec2(x + sz, y + sz - 0.5f), ImVec2(x, y + sz - 0.5f), col32);
		x += sz + spacing;
		draw_list->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + sz, y + sz), ImColor(0, 0, 0), ImColor(255, 0, 0), ImColor(255, 255, 0), ImColor(0, 255, 0));
		ImGui::Dummy(ImVec2((sz + spacing) * 8, (sz + spacing) * 3));
	}
	ImGui::Separator();
	{
		static ImVector<ImVec2> points;
		static bool adding_line = false;
		ImGui::Text("Canvas example");
		if (ImGui::Button("Clear")) points.clear();
		if (points.Size >= 2)
		{
			ImGui::SameLine();
			if (ImGui::Button("Undo"))
			{
				points.pop_back();
				points.pop_back();
			}
		}
		ImGui::Text("Left-click and drag to add lines,\nRight-click to undo");

		// Here we are using InvisibleButton() as a convenience to 1) advance the cursor and 2) allows us to use IsItemHovered()
		// However you can draw directly and poll mouse/keyboard by yourself. You can manipulate the cursor using GetCursorPos() and SetCursorPos().
		// If you only use the ImDrawList API, you can notify the owner window of its extends by using SetCursorPos(max).
		ImVec2 canvas_pos = ImGui::GetCursorScreenPos(); // ImDrawList API uses screen coordinates!
		ImVec2 canvas_size = ImGui::GetContentRegionAvail(); // Resize canvas to what's available
		if (canvas_size.x < 50.0f) canvas_size.x = 50.0f;
		if (canvas_size.y < 50.0f) canvas_size.y = 50.0f;
		draw_list->AddRectFilledMultiColor(canvas_pos, ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y), ImColor(50, 50, 50), ImColor(50, 50, 60), ImColor(60, 60, 70), ImColor(50, 50, 60));
		draw_list->AddRect(canvas_pos, ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y), ImColor(255, 255, 255));

		bool adding_preview = false;
		ImGui::InvisibleButton("canvas", canvas_size);
		ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - canvas_pos.x, ImGui::GetIO().MousePos.y - canvas_pos.y);
		if (adding_line)
		{
			adding_preview = true;
			points.push_back(mouse_pos_in_canvas);
			if (!ImGui::GetIO().MouseDown[0])
				adding_line = adding_preview = false;
		}
		if (ImGui::IsItemHovered())
		{
			if (!adding_line && ImGui::IsMouseClicked(0))
			{
				points.push_back(mouse_pos_in_canvas);
				adding_line = true;
			}
			if (ImGui::IsMouseClicked(1) && !points.empty())
			{
				adding_line = adding_preview = false;
				points.pop_back();
				points.pop_back();
			}
		}
		draw_list->PushClipRect(canvas_pos, ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y)); // clip lines within the canvas (if we resize it, etc.)
		for (int i = 0; i < points.Size - 1; i += 2)
			draw_list->AddLine(ImVec2(canvas_pos.x + points[i].x, canvas_pos.y + points[i].y), ImVec2(canvas_pos.x + points[i + 1].x, canvas_pos.y + points[i + 1].y), IM_COL32(255,255,0,255), 2.0f);
		draw_list->PopClipRect();
		if (adding_preview)
			points.pop_back();
	}
	ImGui::End();
}

// Demonstrating creating a simple console window, with scrolling, filtering, completion and history.
// For the console example, here we are using a more C++ like approach of declaring a class to hold the data and the functions.
struct ExampleAppConsole
{
	char InputBuf[256];
	ImVector<char*> Items;
	bool ScrollToBottom;
	ImVector<char*> History;
	int HistoryPos; // -1: new line, 0..History.Size-1 browsing history.
	ImVector<const char*> Commands;

	ExampleAppConsole()
	{
		ClearLog();
		memset(InputBuf, 0, sizeof(InputBuf));
		HistoryPos = -1;
		Commands.push_back("HELP");
		Commands.push_back("HISTORY");
		Commands.push_back("CLEAR");
		Commands.push_back("CLASSIFY"); // "classify" is here to provide an example of "C"+[tab] completing to "CL" and displaying matches.
		AddLog("Welcome to ImGui!");
	}

	~ExampleAppConsole()
	{
		ClearLog();
		for (int i = 0; i < History.Size; i++)
			free(History[i]);
	}

	// Portable helpers
	static int Stricmp(const char* str1, const char* str2)
	{
		int d;
		while ((d = toupper(*str2) - toupper(*str1)) == 0 && *str1)
		{
			str1++;
			str2++;
		}
		return d;
	}

	static int Strnicmp(const char* str1, const char* str2, int n)
	{
		int d = 0;
		while (n > 0 && (d = toupper(*str2) - toupper(*str1)) == 0 && *str1)
		{
			str1++;
			str2++;
			n--;
		}
		return d;
	}

	static char* Strdup(const char* str)
	{
		size_t len = strlen(str) + 1;
		void* buff = malloc(len);
		return (char*)memcpy(buff, (const void*)str, len);
	}

	void ClearLog()
	{
		for (int i = 0; i < Items.Size; i++)
			free(Items[i]);
		Items.clear();
		ScrollToBottom = true;
	}

	void AddLog(const char* fmt, ...) IM_PRINTFARGS(2)
	{
		char buf[1024];
		va_list args;
		va_start(args, fmt);
		vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
		buf[IM_ARRAYSIZE(buf) - 1] = 0;
		va_end(args);
		Items.push_back(Strdup(buf));
		ScrollToBottom = true;
	}

	void Draw(const char* title, bool* p_open)
	{
		ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiSetCond_FirstUseEver);
		if (!ImGui::Begin(title, p_open))
		{
			ImGui::End();
			return;
		}

		ImGui::TextWrapped("This example implements a console with basic coloring, completion and history. A more elaborate implementation may want to store entries along with extra data such as timestamp, emitter, etc.");
		ImGui::TextWrapped("Enter 'HELP' for help, press TAB to use text completion.");

		// TODO: display items starting from the bottom

		if (ImGui::SmallButton("Add Dummy Text"))
		{
			AddLog("%d some text", Items.Size);
			AddLog("some more text");
			AddLog("display very important message here!");
		}
		ImGui::SameLine();
		if (ImGui::SmallButton("Add Dummy Error")) AddLog("[error] something went wrong");
		ImGui::SameLine();
		if (ImGui::SmallButton("Clear")) ClearLog();
		ImGui::SameLine();
		if (ImGui::SmallButton("Scroll to bottom")) ScrollToBottom = true;
		//static float t = 0.0f; if (ImGui::GetTime() - t > 0.02f) { t = ImGui::GetTime(); AddLog("Spam %f", t); }

		ImGui::Separator();

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
		static ImGuiTextFilter filter;
		filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
		ImGui::PopStyleVar();
		ImGui::Separator();

		ImGui::BeginChild("ScrollingRegion", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::Selectable("Clear")) ClearLog();
			ImGui::EndPopup();
		}

		// Display every line as a separate entry so we can change their color or add custom widgets. If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
		// NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping to only process visible items.
		// You can seek and display only the lines that are visible using the ImGuiListClipper helper, if your elements are evenly spaced and you have cheap random access to the elements.
		// To use the clipper we could replace the 'for (int i = 0; i < Items.Size; i++)' loop with:
		//     ImGuiListClipper clipper(Items.Size);
		//     while (clipper.Step())
		//         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
		// However take note that you can not use this code as is if a filter is active because it breaks the 'cheap random-access' property. We would need random-access on the post-filtered list.
		// A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices that passed the filtering test, recomputing this array when user changes the filter,
		// and appending newly elements as they are inserted. This is left as a task to the user until we can manage to improve this example code!
		// If your items are of variable size you may want to implement code similar to what ImGuiListClipper does. Or split your data into fixed height items to allow random-seeking into your list.
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
		for (int i = 0; i < Items.Size; i++)
		{
			const char* item = Items[i];
			if (!filter.PassFilter(item))
				continue;
			ImVec4 col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // A better implementation may store a type per-item. For the sample let's just parse the text.
			if (strstr(item, "[error]")) col = ImColor(1.0f, 0.4f, 0.4f, 1.0f);
			else if (strncmp(item, "# ", 2) == 0) col = ImColor(1.0f, 0.78f, 0.58f, 1.0f);
			ImGui::PushStyleColor(ImGuiCol_Text, col);
			ImGui::TextUnformatted(item);
			ImGui::PopStyleColor();
		}
		if (ScrollToBottom)
			ImGui::SetScrollHere();
		ScrollToBottom = false;
		ImGui::PopStyleVar();
		ImGui::EndChild();
		ImGui::Separator();

		// Command-line
		if (ImGui::InputText("Input", InputBuf, IM_ARRAYSIZE(InputBuf), ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory, &TextEditCallbackStub, (void*)this))
		{
			char* input_end = InputBuf + strlen(InputBuf);
			while (input_end > InputBuf && input_end[-1] == ' ') input_end--;
			*input_end = 0;
			if (InputBuf[0])
				ExecCommand(InputBuf);
			strcpy(InputBuf, "");
		}

		// Demonstrate keeping auto focus on the input box
		if (ImGui::IsItemHovered() || (ImGui::IsRootWindowOrAnyChildFocused() && !ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0)))
			ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

		ImGui::End();
	}

	void ExecCommand(const char* command_line)
	{
		AddLog("# %s\n", command_line);

		// Insert into history. First find match and delete it so it can be pushed to the back. This isn't trying to be smart or optimal.
		HistoryPos = -1;
		for (int i = History.Size - 1; i >= 0; i--)
			if (Stricmp(History[i], command_line) == 0)
			{
				free(History[i]);
				History.erase(History.begin() + i);
				break;
			}
		History.push_back(Strdup(command_line));

		// Process command
		if (Stricmp(command_line, "CLEAR") == 0)
		{
			ClearLog();
		}
		else if (Stricmp(command_line, "HELP") == 0)
		{
			AddLog("Commands:");
			for (int i = 0; i < Commands.Size; i++)
				AddLog("- %s", Commands[i]);
		}
		else if (Stricmp(command_line, "HISTORY") == 0)
		{
			for (int i = History.Size >= 10 ? History.Size - 10 : 0; i < History.Size; i++)
				AddLog("%3d: %s\n", i, History[i]);
		}
		else
		{
			AddLog("Unknown command: '%s'\n", command_line);
		}
	}

	static int TextEditCallbackStub(ImGuiTextEditCallbackData* data) // In C++11 you are better off using lambdas for this sort of forwarding callbacks
	{
		ExampleAppConsole* console = (ExampleAppConsole*)data->UserData;
		return console->TextEditCallback(data);
	}

	int TextEditCallback(ImGuiTextEditCallbackData* data)
	{
		//AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
		switch (data->EventFlag)
		{
		case ImGuiInputTextFlags_CallbackCompletion:
			{
				// Example of TEXT COMPLETION

				// Locate beginning of current word
				const char* word_end = data->Buf + data->CursorPos;
				const char* word_start = word_end;
				while (word_start > data->Buf)
				{
					const char c = word_start[-1];
					if (c == ' ' || c == '\t' || c == ',' || c == ';')
						break;
					word_start--;
				}

				// Build a list of candidates
				ImVector<const char*> candidates;
				for (int i = 0; i < Commands.Size; i++)
					if (Strnicmp(Commands[i], word_start, (int)(word_end - word_start)) == 0)
						candidates.push_back(Commands[i]);

				if (candidates.Size == 0)
				{
					// No match
					AddLog("No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
				}
				else if (candidates.Size == 1)
				{
					// Single match. Delete the beginning of the word and replace it entirely so we've got nice casing
					data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
					data->InsertChars(data->CursorPos, candidates[0]);
					data->InsertChars(data->CursorPos, " ");
				}
				else
				{
					// Multiple matches. Complete as much as we can, so inputing "C" will complete to "CL" and display "CLEAR" and "CLASSIFY"
					int match_len = (int)(word_end - word_start);
					for (;;)
					{
						int c = 0;
						bool all_candidates_matches = true;
						for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
							if (i == 0)
								c = toupper(candidates[i][match_len]);
							else if (c == 0 || c != toupper(candidates[i][match_len]))
								all_candidates_matches = false;
						if (!all_candidates_matches)
							break;
						match_len++;
					}

					if (match_len > 0)
					{
						data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
						data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
					}

					// List matches
					AddLog("Possible matches:\n");
					for (int i = 0; i < candidates.Size; i++)
						AddLog("- %s\n", candidates[i]);
				}

				break;
			}
		case ImGuiInputTextFlags_CallbackHistory:
			{
				// Example of HISTORY
				const int prev_history_pos = HistoryPos;
				if (data->EventKey == ImGuiKey_UpArrow)
				{
					if (HistoryPos == -1)
						HistoryPos = History.Size - 1;
					else if (HistoryPos > 0)
						HistoryPos--;
				}
				else if (data->EventKey == ImGuiKey_DownArrow)
				{
					if (HistoryPos != -1)
						if (++HistoryPos >= History.Size)
							HistoryPos = -1;
				}

				// A better implementation would preserve the data on the current input line along with cursor position.
				if (prev_history_pos != HistoryPos)
				{
					data->CursorPos = data->SelectionStart = data->SelectionEnd = data->BufTextLen = (int)snprintf(data->Buf, (size_t)data->BufSize, "%s", (HistoryPos >= 0) ? History[HistoryPos] : "");
					data->BufDirty = true;
				}
			}
		}
		return 0;
	}
};

static void ShowExampleAppConsole(bool* p_open)
{
	static ExampleAppConsole console;
	console.Draw("Example: Console", p_open);
}

// Usage:
//  static ExampleAppLog my_log;
//  my_log.AddLog("Hello %d world\n", 123);
//  my_log.Draw("title");
struct ExampleAppLog
{
	ImGuiTextBuffer Buf;
	ImGuiTextFilter Filter;
	ImVector<int> LineOffsets; // Index to lines offset
	bool ScrollToBottom;

	void Clear()
	{
		Buf.clear();
		LineOffsets.clear();
	}

	void AddLog(const char* fmt, ...) IM_PRINTFARGS(2)
	{
		int old_size = Buf.size();
		va_list args;
		va_start(args, fmt);
		Buf.appendv(fmt, args);
		va_end(args);
		for (int new_size = Buf.size(); old_size < new_size; old_size++)
			if (Buf[old_size] == '\n')
				LineOffsets.push_back(old_size);
		ScrollToBottom = true;
	}

	void Draw(const char* title, bool* p_open = nullptr)
	{
		ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiSetCond_FirstUseEver);
		ImGui::Begin(title, p_open);
		if (ImGui::Button("Clear")) Clear();
		ImGui::SameLine();
		bool copy = ImGui::Button("Copy");
		ImGui::SameLine();
		Filter.Draw("Filter", -100.0f);
		ImGui::Separator();
		ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
		if (copy) ImGui::LogToClipboard();

		if (Filter.IsActive())
		{
			const char* buf_begin = Buf.begin();
			const char* line = buf_begin;
			for (int line_no = 0; line != nullptr; line_no++)
			{
				const char* line_end = (line_no < LineOffsets.Size) ? buf_begin + LineOffsets[line_no] : NULL;
				if (Filter.PassFilter(line, line_end))
					ImGui::TextUnformatted(line, line_end);
				line = line_end && line_end[1] ? line_end + 1 : NULL;
			}
		}
		else
		{
			ImGui::TextUnformatted(Buf.begin());
		}

		if (ScrollToBottom)
			ImGui::SetScrollHere(1.0f);
		ScrollToBottom = false;
		ImGui::EndChild();
		ImGui::End();
	}
};

// Demonstrate creating a simple log window with basic filtering.
static void ShowExampleAppLog(bool* p_open)
{
	static ExampleAppLog log;

	// Demo fill
	static float last_time = -1.0f;
	float time = ImGui::GetTime();
	if (time - last_time >= 0.3f)
	{
		const char* random_words[] = {"system", "info", "warning", "error", "fatal", "notice", "log"};
		log.AddLog("[%s] Hello, time is %.1f, rand() %d\n", random_words[rand() % IM_ARRAYSIZE(random_words)], time, (int)rand());
		last_time = time;
	}

	log.Draw("Example: Log", p_open);
}

// Demonstrate create a window with multiple child windows.
static void ShowExampleAppLayout(bool* p_open)
{
	ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("Example: Layout", p_open, ImGuiWindowFlags_MenuBar))
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Close")) *p_open = false;
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		// left
		static int selected = 0;
		ImGui::BeginChild("left pane", ImVec2(150, 0), true);
		for (int i = 0; i < 100; i++)
		{
			char label[128];
			sprintf(label, "MyObject %d", i);
			if (ImGui::Selectable(label, selected == i))
				selected = i;
		}
		ImGui::EndChild();
		ImGui::SameLine();

		// right
		ImGui::BeginGroup();
		ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing())); // Leave room for 1 line below us
		ImGui::Text("MyObject: %d", selected);
		ImGui::Separator();
		ImGui::TextWrapped("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ");
		ImGui::EndChild();
		ImGui::BeginChild("buttons");
		if (ImGui::Button("Revert"))
		{
		}
		ImGui::SameLine();
		if (ImGui::Button("Save"))
		{
		}
		ImGui::EndChild();
		ImGui::EndGroup();
	}
	ImGui::End();
}

// Demonstrate create a simple property editor.
static void ShowExampleAppPropertyEditor(bool* p_open)
{
	ImGui::SetNextWindowSize(ImVec2(430, 450), ImGuiSetCond_FirstUseEver);
	if (!ImGui::Begin("Example: Property editor", p_open))
	{
		ImGui::End();
		return;
	}

	ShowHelpMarker("This example shows how you may implement a property editor using two columns.\nAll objects/fields data are dummies here.\nRemember that in many simple cases, you can use ImGui::SameLine(xxx) to position\nyour cursor horizontally instead of using the Columns() API.");

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
	ImGui::Columns(2);
	ImGui::Separator();

	struct funcs
	{
		static void ShowDummyObject(const char* prefix, int uid)
		{
			ImGui::PushID(uid); // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
			ImGui::AlignFirstTextHeightToWidgets(); // Text and Tree nodes are less high than regular widgets, here we add vertical spacing to make the tree lines equal high.
			bool node_open = ImGui::TreeNode("Object", "%s_%u", prefix, uid);
			ImGui::NextColumn();
			ImGui::AlignFirstTextHeightToWidgets();
			ImGui::Text("my sailor is rich");
			ImGui::NextColumn();
			if (node_open)
			{
				static float dummy_members[8] = {0.0f,0.0f,1.0f,3.1416f,100.0f,999.0f};
				for (int i = 0; i < 8; i++)
				{
					ImGui::PushID(i); // Use field index as identifier.
					if (i < 2)
					{
						ShowDummyObject("Child", 424242);
					}
					else
					{
						ImGui::AlignFirstTextHeightToWidgets();
						// Here we use a Selectable (instead of Text) to highlight on hover
						//ImGui::Text("Field_%d", i);
						char label[32];
						sprintf(label, "Field_%d", i);
						ImGui::Bullet();
						ImGui::Selectable(label);
						ImGui::NextColumn();
						ImGui::PushItemWidth(-1);
						if (i >= 5)
							ImGui::InputFloat("##value", &dummy_members[i], 1.0f);
						else
							ImGui::DragFloat("##value", &dummy_members[i], 0.01f);
						ImGui::PopItemWidth();
						ImGui::NextColumn();
					}
					ImGui::PopID();
				}
				ImGui::TreePop();
			}
			ImGui::PopID();
		}
	};

	// Iterate dummy objects with dummy members (all the same data)
	for (int obj_i = 0; obj_i < 3; obj_i++)
		funcs::ShowDummyObject("Object", obj_i);

	ImGui::Columns(1);
	ImGui::Separator();
	ImGui::PopStyleVar();
	ImGui::End();
}

// Demonstrate/test rendering huge amount of text, and the incidence of clipping.
static void ShowExampleAppLongText(bool* p_open)
{
	ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiSetCond_FirstUseEver);
	if (!ImGui::Begin("Example: Long text display", p_open))
	{
		ImGui::End();
		return;
	}

	static int test_type = 0;
	static ImGuiTextBuffer log;
	static int lines = 0;
	ImGui::Text("Printing unusually long amount of text.");
	ImGui::Combo("Test type", &test_type, "Single call to TextUnformatted()\0Multiple calls to Text(), clipped manually\0Multiple calls to Text(), not clipped\0");
	ImGui::Text("Buffer contents: %d lines, %d bytes", lines, log.size());
	if (ImGui::Button("Clear"))
	{
		log.clear();
		lines = 0;
	}
	ImGui::SameLine();
	if (ImGui::Button("Add 1000 lines"))
	{
		for (int i = 0; i < 1000; i++)
			log.append("%i The quick brown fox jumps over the lazy dog\n", lines + i);
		lines += 1000;
	}
	ImGui::BeginChild("Log");
	switch (test_type)
	{
	case 0:
		// Single call to TextUnformatted() with a big buffer
		ImGui::TextUnformatted(log.begin(), log.end());
		break;
	case 1:
		{
			// Multiple calls to Text(), manually coarsely clipped - demonstrate how to use the ImGuiListClipper helper.
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
			ImGuiListClipper clipper(lines);
			while (clipper.Step())
				for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
					ImGui::Text("%i The quick brown fox jumps over the lazy dog", i);
			ImGui::PopStyleVar();
			break;
		}
	case 2:
		// Multiple calls to Text(), not clipped (slow)
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		for (int i = 0; i < lines; i++)
			ImGui::Text("%i The quick brown fox jumps over the lazy dog", i);
		ImGui::PopStyleVar();
		break;
	}
	ImGui::EndChild();
	ImGui::End();
}

// End of Demo code
#else

void ImGui::ShowTestWindow(bool*) {}
void ImGui::ShowUserGuide() {}
void ImGui::ShowStyleEditor(ImGuiStyle*) {}

#endif

#endif
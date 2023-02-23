#pragma once

#ifndef DRAW_MANAGER_HPP_
#define DRAW_MANAGER_HPP_

#include "stdafx.h"

#include "C:/ClientFramework/Framework/Menu/Fonts.h"

class DrawManager
{
public:
	DrawManager( );
	///Call Before Drawing
	void begin_scene( bool should_draw = true );
	///Call after Drawing
	void end_scene( );
	///Color, x1, y1, x2, y2, thickness
	void draw_line( ImColor, int, int, int, int, int = 1 );
	///Color, x1, y1, x2, y2, rounding, thickness, esp box
	void draw_box( ImColor, int, int, int, int, int = 0, int = 1, bool = false );
	///Color, x1, y1, x2, y2, rounding
	void draw_box_filled( ImColor, int, int, int, int, int = 0 );
	///Color, font, font_size, x, y, outline, format, args
	void draw_text( ImColor, ImFont*, float, int, int, bool, const char*, ... );
	///Color, x, y, radius, num_points( verticies ), thickness
	void draw_circle( ImColor, int, int, float, int = 64, float = 1 );
	///Color, x, y, radius, num_points( verticies )
	void draw_filled_circle( ImColor, int, int, float, int = 64 );
	///Gets Standard Font
	ImFont *get_font( ) const;

private:
	void draw_1px_box( ImColor, int, int, int, int );

	ImGuiWindow *get_window( );
	ImDrawList *get_draw_list( );

	ImFont *font;
};

extern DrawManager draw_manager;

#endif
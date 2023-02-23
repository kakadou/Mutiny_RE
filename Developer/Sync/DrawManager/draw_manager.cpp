#include "draw_manager.hpp"

DrawManager draw_manager;

DrawManager::DrawManager( )
	: font( nullptr )
{
}

void DrawManager::begin_scene( bool should_draw )
{
	ImGui::PushStyleColor( ImGuiCol_WindowBg, ImVec4( 0.0f, 0.0f, 0.0f, 0.0f ) );

	ImGui::Begin( "##backdraw", &should_draw, ImVec2( 0.0f, 0.0f ), 0.0f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs );

	ImGui::SetWindowPos( ImVec2( 0.0f, 0.0f ), ImGuiSetCond_Always );
	ImGui::SetWindowSize( ImVec2( ImGui::GetIO( ).DisplaySize.x, ImGui::GetIO( ).DisplaySize.y ), ImGuiSetCond_Always );
}

void DrawManager::end_scene( )
{
	get_draw_list( )->PushClipRectFullScreen( );

	ImGui::End( );
	ImGui::PopStyleColor( );
}

void DrawManager::draw_line( ImColor color, int x1, int y1, int x2, int y2, int thickness )
{
	get_draw_list( )->AddLine( ImVec2( x1, y1 ), ImVec2( x2, y2 ), color, thickness );
}

void DrawManager::draw_box( ImColor color, int x1, int y1, int x2, int y2, int rounding, int thickness, bool esp_box )
{
	if ( esp_box )
	{
		get_draw_list( )->AddRect( ImVec2( x1 + 1, y1 + 1 ), ImVec2( x2 + 1, y2 + 1 ), ImColor( 0, 0, 0, 255 ), rounding );
		get_draw_list( )->AddRect( ImVec2( x1 - 1, y1 - 1 ), ImVec2( x2 - 1, y2 - 1 ), ImColor( 0, 0, 0, 255 ), rounding );
	}

	get_draw_list( )->AddRect( ImVec2( x1, y1 ), ImVec2( x2, y2 ), color, rounding );
}

void DrawManager::draw_box_filled( ImColor color, int x1, int y1, int x2, int y2, int rounding )
{
	get_draw_list( )->AddRectFilled( ImVec2( x1, y1 ), ImVec2( x2, y2 ), color, rounding );
}

void DrawManager::draw_text( ImColor color, ImFont *font, float font_size, int x, int y, bool outline, const char* fmt, ... )
{
	char buffer [ 1024 ] = { };

	va_list va;
	va_start( va, fmt );
	vsnprintf_s( buffer, 1024, fmt, va );
	va_end( va );

	std::string text = buffer;

	if ( outline )
	{
		get_draw_list( )->AddText( font, font_size, ImVec2( x + 1, y + 1 ), ImColor( 0, 0, 0, 255 ), text.c_str( ) );
		get_draw_list( )->AddText( font, font_size, ImVec2( x - 1, y + 1 ), ImColor( 0, 0, 0, 255 ), text.c_str( ) );
		get_draw_list( )->AddText( font, font_size, ImVec2( x - 1, y - 1 ), ImColor( 0, 0, 0, 255 ), text.c_str( ) );
		get_draw_list( )->AddText( font, font_size, ImVec2( x + 1, y - 1 ), ImColor( 0, 0, 0, 255 ), text.c_str( ) );
	}

	get_draw_list( )->AddText( font, font_size, ImVec2( x, y ), color, text.c_str( ) );
}

void DrawManager::draw_circle( ImColor color, int x, int y, float radius, int num_segments, float thickness )
{
	get_draw_list( )->AddCircle( ImVec2( x, y ), radius, color, num_segments, thickness );
}

void DrawManager::draw_filled_circle( ImColor color, int x, int y, float radius, int num_segments )
{
	get_draw_list( )->AddCircleFilled( ImVec2( x, y ), radius, color, num_segments );
}

ImFont *DrawManager::get_font( ) const
{
	if ( !font ) {
		ImGui::GetIO( ).Fonts->AddFontFromMemoryCompressedTTF( RudaCompressed, RudaSize, 24.0f );
	}

	return font;
}

void DrawManager::draw_1px_box( ImColor color, int x1, int y1, int x2, int y2 )
{
	draw_line( color, x1, y1, x1, y2 );
	draw_line( color, x2, y1, x2, y2 );
	draw_line( color, x1, y2, x2, y2 );
	draw_line( color, x1, y2, x1, y1 );
}

ImGuiWindow *DrawManager::get_window( )
{
	return ImGui::GetCurrentWindow( );
}

ImDrawList *DrawManager::get_draw_list( )
{
	return get_window( )->DrawList;
}
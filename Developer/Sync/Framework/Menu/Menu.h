#pragma once

#ifdef FRAME_IMGUI

#ifndef FRAME_DISABLE

namespace MutinyFrame
{
#ifdef FRAME_DX9
	class UserInterface
	{
	public:
		UserInterface( );
		UserInterface( HWND, IDirect3DDevice9* );
		CWebConfig Config;
		void Draw( );
		bool WndProc( HWND, UINT, WPARAM, LPARAM );
		void SetupConfig( std::string, std::string );
		ImFont* ESP;
		bool Initialized = false;

	private:
		void Checkbox( std::string, std::string );
		void InputInt( std::string, std::string );
		void SlideInt( std::string, std::string, int );
		void SlideInt( std::string, std::string, int, int );
		void InputFloat( std::string, std::string );
		void SlideFloat( std::string, std::string, float );
		void SlideFloat( std::string, std::string, float, float );
		void SlideFloatTop( std::string, std::string, float, float );
		void Combo( std::string, std::string, const char* );
		void Combo( std::string, std::string, const char*const*, int );
		void ColorPicker( std::string, std::string, std::string, std::string );
		void ColorPicker( std::string strOption, std::string r, std::string g, std::string b, std::string a, std::string rainbow = " ", std::string health = " " );
		bool MenuOpen = false;
		bool PressedKey [ 256 ] = { false };
		ImFont* Tabs;
	};
#endif

#ifdef FRAME_DX11
	class UserInterface
	{
	public:
		UserInterface( );
		UserInterface( HWND, ID3D11Device* );
		CWebConfig Config;
		void Draw( );
		bool WndProc( HWND, UINT, WPARAM, LPARAM );
		void SetupConfig( std::string, std::string );
		ImFont* ESP;

	private:
		bool Initialized = false;
		void Checkbox( std::string, std::string );
		void InputInt( std::string, std::string );
		void SlideInt( std::string, std::string, int );
		void SlideInt( std::string, std::string, int, int );
		void InputFloat( std::string, std::string );
		void SlideFloat( std::string, std::string, float );
		void SlideFloat( std::string, std::string, float, float );
		void Combo( std::string, std::string, const char* );
		void Combo( std::string, std::string, const char*const*, int );
		void ColorPicker( std::string, std::string, std::string, std::string );
		bool MenuOpen = false;
		bool PressedKey [ 256 ] = { false };
		ID3D11DeviceContext* DX11DeviceContext = nullptr;
		ImFont* Tabs;
	};
#endif
}

#endif

#endif
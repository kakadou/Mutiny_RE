#pragma once

#include "Adriel\stdafx.hpp"

#include <unordered_map>
#include <cstdint>
#include <vector>
#include <string>

#define safe_release(p) { if(p) { (p)->Release(); (p) = NULL; } }

#define d3d_font_itatlic (1 << 0)
#define d3d_font_zenable (1 << 1)
#define d3dfvf_font2dvertex (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

class c_font
{
	struct font2dvertex
	{
		D3DXVECTOR4 p;
		uint32_t color;
		float tu, tv;
	};

	static constexpr auto max_vertices = 50 * 6;
	static constexpr auto dpi = 96;

	std::string font;
	uint32_t height;
	uint32_t flags;
	uint32_t quality;
	uint32_t weight;
	uint32_t heighest_char;

	IDirect3DDevice9* dev;
	IDirect3DTexture9* texture;
	IDirect3DVertexBuffer9* vertex_buffer;
	uint32_t text_width;
	uint32_t text_height;
	float text_scale;
	std::vector<std::vector<float>> text_coords;
	uint32_t spacing;

	IDirect3DStateBlock9* saved;
	IDirect3DStateBlock9* draw;

public:
	enum font_flags
	{
		centered_x = 1 << 0,
		centered_y = 1 << 1,
		twosided = 1 << 2,
		filtered = 1 << 3,
		drop_shadow = 1 << 4,
		left_aligned = 1 << 5,
		right_aligned = 1 << 6
	};

	HRESULT draw_string(float x, float y, uint32_t color, const char* text, uint8_t flags = 0L);
	HRESULT get_text_extent(const char* text, SIZE* size);

	HRESULT init_device_objects(IDirect3DDevice9* dev);
	HRESULT restore_device_objects();
	HRESULT invalidate_device_objects();
	HRESULT delete_device_objects();

	c_font();
	c_font(std::string font, uint32_t height, uint32_t weight, uint32_t highest_char = 0x80, uint32_t flags = 0, uint32_t quality = DEFAULT_QUALITY);
	~c_font();

	float line_height;
};

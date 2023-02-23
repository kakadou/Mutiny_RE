#ifdef FRAME_IMGUI

#ifdef FRAME_DX9
struct IDirect3DDevice9;

IMGUI_API bool ImGui_ImplDX9_Init(void* hwnd, IDirect3DDevice9* device);
IMGUI_API void ImGui_ImplDX9_Shutdown();
IMGUI_API void ImGui_ImplDX9_NewFrame();

// Use if you want to reset your rendering device without losing ImGui state.
IMGUI_API void ImGui_ImplDX9_InvalidateDeviceObjects();
IMGUI_API bool ImGui_ImplDX9_CreateDeviceObjects();
#endif
#ifdef FRAME_DX11
struct ID3D11Device;
struct ID3D11DeviceContext;

IMGUI_API bool        InitImGUI(void* hwnd, ID3D11Device* device, ID3D11DeviceContext* device_context);
IMGUI_API void        ImGui_ImplDX11_Shutdown();
IMGUI_API void        ImGui_ImplDX11_NewFrame();

IMGUI_API void        ImGui_ImplDX11_InvalidateDeviceObjects();
IMGUI_API bool        ImGui_ImplDX11_CreateDeviceObjects();
#endif


#endif
#pragma once

// clean up this spaghetti

#ifndef FRAME_DISABLE

#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <windows.h>
#include <IOSTREAM>
#include <string>
#include <Psapi.h>
#include <lmcons.h>
#include <algorithm>
#include <vector>
#include <shlobj.h>
#include <time.h>
#include <random>
#include <sstream>
#include <fstream>
#include <shlwapi.h>
#include <iomanip>
#include <ctime>
#include <array>
#include <intrin.h>
#include <iphlpapi.h>
#include <process.h>
#include <Memory>
#include <chrono>
#include <thread>
#include <WMIUtils.h>
#include <wmistr.h>
#include <comdef.h>
#include <Wbemidl.h>
#include <gdiplus.h>
#include <comutil.h>
#include <locale>
#include <io.h>
#include <Fcntl.h>
#include <tlhelp32.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <psapi.h>
#include <time.h>
#include <process.h>
#include <vector>
#include <map>
#include <ostream>
#include <Shlobj.h>
#include <math.h>
#include <stdint.h>
#include <string>
#include <string.h>
#include <cmath>
#include <float.h>
#include <codecvt>
#include <cctype>
#include <Setupapi.h>

#ifdef FRAME_DX9
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#endif

#ifdef FRAME_DX11

#include <d3d11.h>
#include <d3dx11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

#endif

#include <Winternl.h>
#include <D3Dcompiler.h>

#pragma comment(lib,"Winmm.lib")
#pragma comment (lib,"Gdiplus.lib")
#pragma comment(lib, "ComCtl32.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment (lib, "ws2_32.lib" )
#pragma comment(lib,"Comctl32.lib")
#pragma comment(lib, "wininet")
#pragma comment( lib, "Msimg32" )
#pragma comment(lib, "IPHLPAPI.lib")
#pragma comment(lib, "Dbghelp.lib")
#pragma comment (lib, "urlmon.lib")
#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "Wldap32.lib")
#pragma comment (lib, "crypt32")
#pragma comment(lib,"psapi.lib")
#pragma comment (lib, "d3dcompiler.lib")

//Crypto pp
#include "../../Libs/Headers/cryptlib.h"
#include "../../Libs/Headers/aes.h"
#include "../../Libs/Headers/pwdbased.h"
#include "../../Libs/Headers/sha.h"
#include "../../Libs/Headers/modes.h"
#include "../../Libs/Headers/filters.h"
#include "../../Libs/Headers/base64.h"
#include "../../Libs/Headers/hex.h"
#include "../../Libs/Headers/osrng.h"
#pragma comment (lib,"cryptlib.lib")
#define CURL_STATICLIB
#include "../../LibcURL/curl/curl.h"
#include "../../LibcURL/curl/easy.h"
#include "../../LibcURL/curl/curlbuild.h"

#ifndef NDEBUG
#pragma comment (lib, "libcurld.lib")
#pragma comment (lib, "libeay32MTd.lib")
#pragma comment (lib, "ssleay32MTd.lib")
#else
#pragma comment (lib, "libcurl.lib")
#pragma comment (lib, "libeay32MT.lib")
#pragma comment (lib, "ssleay32MT.lib")
#endif
//Thread Shit
typedef unsigned( __stdcall *PTHREAD_START )( void* );
#define _BEGINTHREAD( x ) _beginthreadex(nullptr, 0, (PTHREAD_START)x, nullptr, 0, nullptr);//use this instead to create threads/ doesnt have a memory leak

//IMGUI
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl.h"
#include "../ImGui/imgui_internal.h"

#ifdef FRAME_IMGUI

#ifdef FRAME_DX9
extern IMGUI_API LRESULT ImGui_ImplDX9_WndProcHandler( HWND, UINT msg, WPARAM wParam, LPARAM lParam );
#endif

#ifdef FRAME_DX11
extern IMGUI_API LRESULT ImGui_ImplDX11_WndProcHandler( HWND, UINT msg, WPARAM wParam, LPARAM lParam );
#endif

#endif

//Framework Includes
#include "../StringEncryption/StringEncryption.h"
#include "../ModuleSecurity/ModuleSec.h"
#include "../Encryption/Crypto.h"
#include "../JSON/JSON.h"
#include "../Winsock/Winsock.h"
#include "../Logging/Logging.h"
#include "../RSA/RSA.h"
#include "../WebConfig/WebConfig.h"
#include "../Heartbeat/Heartbeat.h"
#include "../Menu/Menu.h"
#include "../../VMProtect/VMProtectSDK.h"



namespace MutinyFrame
{
	class Backend
	{
	public:
		/*Call Constructor with window Handle and Device Pointer in EndScene Hook(dx9) or your Present Hook(DX11) where you draw it
		 *Call WndProc in Window Proc hook
		 *Call Draw Where you draw
		 *Call SetupConfig With webaddress and php location Before Drawing(only once) ///Not Yet Implemented
		 */
#ifdef FRAME_IMGUI
#ifndef FRAME_NOMENU
#ifdef FRAME_64
		UserInterface* Menu = nullptr;
#endif
#ifdef FRAME_32
		UserInterface* Menu = nullptr;
#endif
#endif
#endif
		/*Dont Worry about this right now*/
#ifdef FRAME_NETWORK 
		CHeartBeat* Heartbeat = nullptr;
#endif
		/*Call Function Security->Protect(*ModuleHandle*); in Entrypoint*/
#ifdef FRAME_MODSEC
		Security* Security = nullptr;
#endif
	};
}

/*
 * If your Application is 32bit Call put FRAME_32 as a preprocessor if 64 FRAME_64
 * If you Hook DirectX9 use FRAME_DX9 as a preprocessor if DirectX11 FRAME_DX11
 */

#endif

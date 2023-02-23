#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include "CSGO_HX.h"
#include "Adriel/console.hpp"
#include "VMProtectDefs.h"

HANDLE CreateThreadSafe(const LPTHREAD_START_ROUTINE func, const LPVOID lParam)
{
	const HANDLE hThread = CreateThread(nullptr, 0, nullptr, lParam, CREATE_SUSPENDED, nullptr);
	if (!hThread)
	{
		__fastfail(1);
		return 0;
	}

	CONTEXT threadCtx;
	threadCtx.ContextFlags = CONTEXT_INTEGER;
	GetThreadContext(hThread, &threadCtx);
#ifdef _WIN64
	threadCtx.Rax = reinterpret_cast<decltype(threadCtx.Rax)>(func);
#else
	threadCtx.Eax = reinterpret_cast<decltype(threadCtx.Eax)>(func);
	threadCtx.ContextFlags = CONTEXT_INTEGER;
#endif
	SetThreadContext(hThread, &threadCtx);

	if (ResumeThread(hThread) != 1 || ResumeThread(hThread) != NULL)
	{
		__fastfail(1);
		return 0;
	}

	return hThread;
}

extern HINSTANCE hInstance; //Inside Overlay.h

BOOL APIENTRY DllMain(CONST HMODULE hModule, CONST DWORD dwReason, CONST LPVOID lpReserved)
{


	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
	{

		hInstance = (HINSTANCE)hModule;

		console::get().initialize();

		logger::add(LSUCCESS, "reached DllMain");

		CreateThread(0, 0, &CheatInit, hModule, 0, 0);


		logger::add(LSUCCESS, "after cheat init");
		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		//glorious hack to stop the game from getting stuck in valve's delete function when closing the game
		g_bIsExiting = true;
		g_pMemAlloc = nullptr;
		break;
	}
	return TRUE;

}
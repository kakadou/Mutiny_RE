#include "precompiled.h"
#include "Includes.h"
#include "VTHook.h"
#include "LocalPlayer.h"
#include "CWeatherController.h"

vcollide_t* __fastcall Hooks::GetVCollide(void* ecx, DWORD edx, int index)
{
	return oGetVCollide(ecx, index);
}
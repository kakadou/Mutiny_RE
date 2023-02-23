#include "../Include/Frame-Include.h"

#ifdef FRAME_MODSEC

#ifdef FRAME_32

MutinyFrame::Security::Security( )
{
}

MutinyFrame::Security::Security( HMODULE Module )
{
}

void MutinyFrame::Security::Protect( HMODULE Module, bool Hide, bool HidePEB, bool HideX, bool RemoveHeaders )
{
	if ( Hide )
		HideMod( Module );

	if ( HidePEB )
		HideModPEB( Module );

	if ( HideX )
		HideXTA( Module );

	if ( RemoveHeaders )
	{
		RemoveHeader( reinterpret_cast < DWORD > ( Module ) );
		DestroyHeader( Module );
	}
}

PPEB MutinyFrame::Security::GetPEB( )
{
	PTEB tebPtr = reinterpret_cast< PTEB >( __readfsdword( reinterpret_cast< DWORD_PTR >( &static_cast< NT_TIB* >( nullptr )->Self ) ) );
	return tebPtr->ProcessEnvironmentBlock;
}

void MutinyFrame::Security::HideMod( HANDLE Module )
{
	auto DosHeader = reinterpret_cast< PIMAGE_DOS_HEADER >( Module );

	if ( ( DosHeader->e_magic != IMAGE_DOS_SIGNATURE ) )
		return;

	auto NtHeader = reinterpret_cast< PIMAGE_NT_HEADERS >( reinterpret_cast< DWORD64 >( DosHeader ) + static_cast< DWORD64 >( DosHeader->e_lfanew ) );

	if ( NtHeader->Signature == IMAGE_NT_SIGNATURE )
	{
		DWORD oProtect;
		auto Size = NtHeader->OptionalHeader.SizeOfHeaders;
		VirtualProtect( static_cast< LPVOID >( DosHeader ), Size, PAGE_READWRITE, &oProtect );
		RtlZeroMemory( static_cast< void* >( DosHeader ), Size );
		VirtualProtect( static_cast< LPVOID >( DosHeader ), Size, oProtect, &oProtect );
	}

	PTEB TEB = nullptr;

#if defined(_M_X64) // x64
	TEB = reinterpret_cast< PTEB >( __readgsqword( reinterpret_cast< DWORD_PTR >( &static_cast< NT_TIB* >( nullptr )->Self ) ) );
#else // x86
	TEB = reinterpret_cast< PTEB >( __readfsdword( reinterpret_cast< DWORD_PTR >( &static_cast< NT_TIB* >( nullptr )->Self ) ) );
#endif

	auto List = &TEB->ProcessEnvironmentBlock->Ldr->InMemoryOrderModuleList;

	for ( auto Entry = List->Flink; Entry != List; Entry = Entry->Flink )
	{
		auto ModuleLDR = reinterpret_cast< PLDR_MODULE >( Entry );

		if ( ModuleLDR->BaseAddress != Module )
			continue;

		Entry = &ModuleLDR->InLoadOrderModuleList;
		Entry->Blink->Flink = Entry->Flink;
		Entry->Flink->Blink = Entry->Blink;
		RtlZeroMemory( Entry, sizeof( LIST_ENTRY ) );

		Entry = &ModuleLDR->InMemoryOrderModuleList;
		Entry->Blink->Flink = Entry->Flink;
		Entry->Flink->Blink = Entry->Blink;
		RtlZeroMemory( Entry, sizeof( LIST_ENTRY ) );

		Entry = &ModuleLDR->InInitializationOrderModuleList;
		Entry->Blink->Flink = Entry->Flink;
		Entry->Flink->Blink = Entry->Blink;
		RtlZeroMemory( Entry, sizeof( LIST_ENTRY ) );

		Entry = &ModuleLDR->HashTableEntry;
		Entry->Blink->Flink = Entry->Flink;
		Entry->Flink->Blink = Entry->Blink;
		RtlZeroMemory( Entry, sizeof( LIST_ENTRY ) );
		RtlZeroMemory( ModuleLDR->FullDllName.Buffer, ModuleLDR->FullDllName.Length );
		RtlZeroMemory( ModuleLDR, sizeof( LDR_MODULE ) );

		break;
	}
}

void MutinyFrame::Security::HideModPEB( HMODULE Module )
{
	auto PEB = GetPEB( );
	auto PEBData = ( _PPEB_LDR_DATA ) PEB->Ldr;
	auto FirstEntryInLoadOrder = static_cast< PLIST_ENTRY >( &PEBData->InMemoryOrderModuleList );
	auto FirstEntryInMemoryOrder = static_cast< PLIST_ENTRY >( &PEBData->InMemoryOrderModuleList );
	auto FirstEntryInInitOrder = static_cast< PLIST_ENTRY >( &PEBData->InInitializationOrderModuleList );

	for ( auto TempEntry = FirstEntryInLoadOrder->Flink; TempEntry != FirstEntryInLoadOrder; TempEntry = TempEntry->Flink )
	{
		auto TempModule = reinterpret_cast< PLDR_MODULE >( reinterpret_cast< DWORD64 >( TempEntry ) - 0 * sizeof( LIST_ENTRY ) );

		if ( TempModule->BaseAddress == Module )
		{
			TempEntry->Blink->Flink = TempEntry->Flink;
			TempEntry->Flink->Blink = TempEntry->Blink;

			break;
		}
	}

	for ( auto TempEntry = FirstEntryInMemoryOrder->Flink; TempEntry != FirstEntryInMemoryOrder; TempEntry = TempEntry->Flink )
	{
		auto TempModule = reinterpret_cast< PLDR_MODULE >( reinterpret_cast< DWORD64 >( TempEntry ) - 1 * sizeof( LIST_ENTRY ) );

		if ( TempModule->BaseAddress == Module )
		{
			TempEntry->Blink->Flink = TempEntry->Flink;
			TempEntry->Flink->Blink = TempEntry->Blink;

			break;
		}
	}

	for ( auto TempEntry = FirstEntryInInitOrder->Flink; TempEntry != FirstEntryInInitOrder; TempEntry = TempEntry->Flink )
	{
		auto TempModule = reinterpret_cast< PLDR_MODULE >( reinterpret_cast< DWORD64 >( TempEntry ) - 2 * sizeof( LIST_ENTRY ) );

		if ( TempModule->BaseAddress == Module )
		{
			TempEntry->Blink->Flink = TempEntry->Flink;
			TempEntry->Flink->Blink = TempEntry->Blink;

			break;
		}
	}
}

void MutinyFrame::Security::RemoveHeader( DWORD Module )
{
	auto DosHeader = reinterpret_cast< PIMAGE_DOS_HEADER >( Module );

	if ( !( DosHeader->e_magic == IMAGE_DOS_SIGNATURE ) )
		return;

	auto NtHeader = reinterpret_cast< PIMAGE_NT_HEADERS >( reinterpret_cast< DWORD >( DosHeader ) + static_cast< DWORD >( DosHeader->e_lfanew ) );

	if ( !( NtHeader->Signature == IMAGE_NT_SIGNATURE ) )
		return;

	if ( NtHeader->FileHeader.SizeOfOptionalHeader == 0 )
		return;

	DWORD oProtect;

	auto Size = NtHeader->FileHeader.SizeOfOptionalHeader;

	VirtualProtect( reinterpret_cast< LPVOID >( Module ), Size, PAGE_READWRITE, &oProtect );
	RtlZeroMemory( reinterpret_cast< LPVOID >( Module ), Size );
	VirtualProtect( reinterpret_cast< LPVOID >( Module ), Size, oProtect, &oProtect );
}

void MutinyFrame::Security::DestroyHeader( HMODULE Module )
{
	auto DosHeader = reinterpret_cast< PIMAGE_DOS_HEADER >( Module );

	if ( !( DosHeader->e_magic == IMAGE_DOS_SIGNATURE ) )
		return;

	auto NtHeader = reinterpret_cast< PIMAGE_NT_HEADERS >( reinterpret_cast< DWORD >( DosHeader ) + static_cast< DWORD >( DosHeader->e_lfanew ) );

	if ( !( NtHeader->Signature == IMAGE_NT_SIGNATURE ) )
		return;

	if ( NtHeader->FileHeader.SizeOfOptionalHeader == 0 )
		return;

	DWORD oProtect;

	auto Size = NtHeader->OptionalHeader.SizeOfHeaders;

	VirtualProtect( static_cast< LPVOID >( Module ), Size, PAGE_EXECUTE_READWRITE, &oProtect );
	RtlZeroMemory( static_cast< LPVOID >( Module ), Size );
	VirtualProtect( static_cast< LPVOID >( Module ), Size, oProtect, &oProtect );
}

void MutinyFrame::Security::HideXTA( HMODULE Module )
{
	DWORD PEB_LDR_DATA = 0;

	__asm
	{
		pushad;
		pushfd;
		mov eax, fs:[30h]
			mov eax, [ eax + 0Ch ]
			mov PEB_LDR_DATA, eax
			mov esi, [ eax + 0Ch ]
			mov edx, [ eax + 10h ]

			LoopInLoadOrderModuleList :
			lodsd
			mov esi, eax
			mov ecx, [ eax + 18h ]
			cmp ecx, Module
			jne SkipA
			mov ebx, [ eax ]
			mov ecx, [ eax + 4 ]
			mov [ ecx ], ebx
			mov [ ebx + 4 ], ecx
			jmp InMemoryOrderModuleList
			SkipA :
		cmp edx, esi
			jne LoopInLoadOrderModuleList

			InMemoryOrderModuleList :
		mov eax, PEB_LDR_DATA
			mov esi, [ eax + 14h ]
			mov edx, [ eax + 18h ]

			LoopInMemoryOrderModuleList :
			lodsd
			mov esi, eax
			mov ecx, [ eax + 10h ]
			cmp ecx, Module
			jne SkipB
			mov ebx, [ eax ]
			mov ecx, [ eax + 4 ]
			mov [ ecx ], ebx
			mov [ ebx + 4 ], ecx
			jmp InInitializationOrderModuleList
			SkipB :
		cmp edx, esi
			jne LoopInMemoryOrderModuleList

			InInitializationOrderModuleList :
		mov eax, PEB_LDR_DATA
			mov esi, [ eax + 1Ch ]
			mov edx, [ eax + 20h ]

			LoopInInitializationOrderModuleList :
			lodsd
			mov esi, eax
			mov ecx, [ eax + 08h ]
			cmp ecx, Module
			jne SkipC
			mov ebx, [ eax ]
			mov ecx, [ eax + 4 ]
			mov [ ecx ], ebx
			mov [ ebx + 4 ], ecx
			jmp Finisheds
			SkipC :
		cmp edx, esi
			jne LoopInInitializationOrderModuleList

			Finisheds :
		popfd;
		popad;
	}
}

#endif

#ifdef FRAME_64

MutinyFrame::Security::Security( )
{
}

MutinyFrame::Security::Security( HMODULE Module )
{
}

void MutinyFrame::Security::Protect( HMODULE Module, bool Hide, bool HidePEB, bool HideX, bool RemoveHeaders )
{
	if ( Hide )
		HideMod( Module );

	if ( HidePEB )
		HideModPEB( Module );

	if ( HideX )
		HideXTA( Module );

	if ( RemoveHeaders )
	{
		RemoveHeader( reinterpret_cast< DWORD >( Module ) );
		DestroyHeader( Module );
	}
}

PPEB MutinyFrame::Security::GetPEB( )
{
#if defined(_M_X64) // x64
	PTEB tebPtr = reinterpret_cast< PTEB >( __readgsqword( reinterpret_cast< DWORD_PTR >( &static_cast< NT_TIB* >( nullptr )->Self ) ) );
#else // x86
	PTEB tebPtr = reinterpret_cast< PTEB >( __readfsdword( reinterpret_cast< DWORD_PTR >( &static_cast< NT_TIB* >( nullptr )->Self ) ) );
#endif

	// Process Environment Block (PEB)
	return tebPtr->ProcessEnvironmentBlock;
}

void MutinyFrame::Security::HideMod( HANDLE Module )
{
	auto DosHeader = reinterpret_cast< PIMAGE_DOS_HEADER >( Module );

	if ( ( DosHeader->e_magic != IMAGE_DOS_SIGNATURE ) )
		return;

	auto NtHeader = reinterpret_cast< PIMAGE_NT_HEADERS >( reinterpret_cast< DWORD64 >( DosHeader ) + static_cast< DWORD64 >( DosHeader->e_lfanew ) );

	if ( NtHeader->Signature == IMAGE_NT_SIGNATURE )
	{
		DWORD oProtect;
		auto Size = NtHeader->OptionalHeader.SizeOfHeaders;
		VirtualProtect( static_cast< LPVOID >( DosHeader ), Size, PAGE_READWRITE, &oProtect );
		RtlZeroMemory( static_cast< void* >( DosHeader ), Size );
		VirtualProtect( static_cast< LPVOID >( DosHeader ), Size, oProtect, &oProtect );
	}

	PTEB TEB = nullptr;

#if defined(_M_X64) // x64
	TEB = reinterpret_cast< PTEB >( __readgsqword( reinterpret_cast< DWORD_PTR >( &static_cast< NT_TIB* >( nullptr )->Self ) ) );
#else // x86
	TEB = reinterpret_cast< PTEB >( __readfsdword( reinterpret_cast< DWORD_PTR >( &static_cast< NT_TIB* >( nullptr )->Self ) ) );
#endif

	auto List = &TEB->ProcessEnvironmentBlock->Ldr->InMemoryOrderModuleList;

	for ( auto Entry = List->Flink; Entry != List; Entry = Entry->Flink )
	{
		auto ModuleLDR = reinterpret_cast< PLDR_MODULE >( Entry );

		if ( ModuleLDR->BaseAddress != Module )
			continue;

		Entry = &ModuleLDR->InLoadOrderModuleList;
		Entry->Blink->Flink = Entry->Flink;
		Entry->Flink->Blink = Entry->Blink;
		RtlZeroMemory( Entry, sizeof( LIST_ENTRY ) );

		Entry = &ModuleLDR->InMemoryOrderModuleList;
		Entry->Blink->Flink = Entry->Flink;
		Entry->Flink->Blink = Entry->Blink;
		RtlZeroMemory( Entry, sizeof( LIST_ENTRY ) );

		Entry = &ModuleLDR->InInitializationOrderModuleList;
		Entry->Blink->Flink = Entry->Flink;
		Entry->Flink->Blink = Entry->Blink;
		RtlZeroMemory( Entry, sizeof( LIST_ENTRY ) );

		Entry = &ModuleLDR->HashTableEntry;
		Entry->Blink->Flink = Entry->Flink;
		Entry->Flink->Blink = Entry->Blink;
		RtlZeroMemory( Entry, sizeof( LIST_ENTRY ) );
		RtlZeroMemory( ModuleLDR->FullDllName.Buffer, ModuleLDR->FullDllName.Length );
		RtlZeroMemory( ModuleLDR, sizeof( LDR_MODULE ) );

		break;
	}
}

void MutinyFrame::Security::HideModPEB( HMODULE Module )
{
	auto PEB = GetPEB( );
	auto PEBData = ( _PPEB_LDR_DATA ) PEB->Ldr;
	auto FirstEntryInLoadOrder = static_cast< PLIST_ENTRY >( &PEBData->InMemoryOrderModuleList );
	auto FirstEntryInMemoryOrder = static_cast< PLIST_ENTRY >( &PEBData->InMemoryOrderModuleList );
	auto FirstEntryInInitOrder = static_cast< PLIST_ENTRY >( &PEBData->InInitializationOrderModuleList );

	for ( auto TempEntry = FirstEntryInLoadOrder->Flink; TempEntry != FirstEntryInLoadOrder; TempEntry = TempEntry->Flink )
	{
		auto TempModule = reinterpret_cast< PLDR_MODULE >( reinterpret_cast< DWORD64 >( TempEntry ) - 0 * sizeof( LIST_ENTRY ) );

		if ( TempModule->BaseAddress == Module )
		{
			TempEntry->Blink->Flink = TempEntry->Flink;
			TempEntry->Flink->Blink = TempEntry->Blink;

			break;
		}
	}

	for ( auto TempEntry = FirstEntryInMemoryOrder->Flink; TempEntry != FirstEntryInMemoryOrder; TempEntry = TempEntry->Flink )
	{
		auto TempModule = reinterpret_cast< PLDR_MODULE >( reinterpret_cast< DWORD64 >( TempEntry ) - 1 * sizeof( LIST_ENTRY ) );

		if ( TempModule->BaseAddress == Module )
		{
			TempEntry->Blink->Flink = TempEntry->Flink;
			TempEntry->Flink->Blink = TempEntry->Blink;

			break;
		}
	}

	for ( auto TempEntry = FirstEntryInInitOrder->Flink; TempEntry != FirstEntryInInitOrder; TempEntry = TempEntry->Flink )
	{
		auto TempModule = reinterpret_cast< PLDR_MODULE >( reinterpret_cast< DWORD64 >( TempEntry ) - 2 * sizeof( LIST_ENTRY ) );

		if ( TempModule->BaseAddress == Module )
		{
			TempEntry->Blink->Flink = TempEntry->Flink;
			TempEntry->Flink->Blink = TempEntry->Blink;

			break;
		}
	}
}

void MutinyFrame::Security::RemoveHeader( DWORD64 Module )
{
	auto DosHeader = reinterpret_cast< PIMAGE_DOS_HEADER >( Module );

	if ( !( DosHeader->e_magic == IMAGE_DOS_SIGNATURE ) )
		return;

	auto NtHeader = reinterpret_cast< PIMAGE_NT_HEADERS >( reinterpret_cast< DWORD64 >( DosHeader ) + static_cast< DWORD64 >( DosHeader->e_lfanew ) );

	if ( !( NtHeader->Signature == IMAGE_NT_SIGNATURE ) )
		return;

	if ( NtHeader->FileHeader.SizeOfOptionalHeader == 0 )
		return;

	DWORD oProtect;

	auto Size = NtHeader->FileHeader.SizeOfOptionalHeader;

	VirtualProtect( reinterpret_cast< LPVOID >( Module ), Size, PAGE_READWRITE, &oProtect );
	RtlZeroMemory( reinterpret_cast< LPVOID >( Module ), Size );
	VirtualProtect( reinterpret_cast< LPVOID >( Module ), Size, oProtect, &oProtect );
}

void MutinyFrame::Security::DestroyHeader( HMODULE Module )
{
	auto DosHeader = reinterpret_cast< PIMAGE_DOS_HEADER >( Module );

	if ( !( DosHeader->e_magic == IMAGE_DOS_SIGNATURE ) )
		return;

	auto NtHeader = reinterpret_cast< PIMAGE_NT_HEADERS >( reinterpret_cast< DWORD64 >( DosHeader ) + static_cast< DWORD64 >( DosHeader->e_lfanew ) );

	if ( !( NtHeader->Signature == IMAGE_NT_SIGNATURE ) )
		return;

	if ( NtHeader->FileHeader.SizeOfOptionalHeader == 0 )
		return;

	DWORD oProtect;

	auto Size = NtHeader->OptionalHeader.SizeOfHeaders;

	VirtualProtect( static_cast< LPVOID >( Module ), Size, PAGE_EXECUTE_READWRITE, &oProtect );
	RtlZeroMemory( static_cast< LPVOID >( Module ), Size );
	VirtualProtect( static_cast< LPVOID >( Module ), Size, oProtect, &oProtect );
}

#endif

#endif
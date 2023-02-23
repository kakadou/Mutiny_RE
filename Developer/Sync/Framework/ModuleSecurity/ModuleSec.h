#pragma once

#ifdef FRAME_MODSEC

typedef struct _PEB_LDR_DATA_DUMMY_
{
	ULONG Length;
	UCHAR Initialized;
	PVOID SsHandle;
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID EntryInProgress;
} __PEB_LDR_DATA, *_PPEB_LDR_DATA;

typedef struct _LDR_MODULE_DUMMY_
{
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID BaseAddress;

	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	SHORT LoadCount;
	SHORT TlsIndex;
	LIST_ENTRY HashTableEntry;
	ULONG TimeDateStamp;
} LDR_MODULE, *PLDR_MODULE;

#ifdef FRAME_64

namespace MutinyFrame
{
	class Security
	{
	public:
		Security( );
		Security( HMODULE );
		/*HMODULE Module, bool Hide,bool HidePEB,bool HideX,bool RemoveHeaders*/
		void Protect( HMODULE, bool, bool, bool, bool );

	private:
		PPEB GetPEB( );
		void HideMod( HANDLE );
		void HideModPEB( HMODULE );
		void RemoveHeader( DWORD64 );
		void DestroyHeader( HMODULE );
		void HideXTA( HMODULE );
	};
}

#endif

#ifdef FRAME_32

namespace MutinyFrame
{
	class Security
	{
	public:
		Security( );
		Security( HMODULE );
		/*HMODULE Module, bool Hide,bool HidePEB,bool HideX,bool RemoveHeaders*/
		void Protect( HMODULE, bool, bool, bool, bool );

	private:
		PPEB GetPEB( );
		void HideMod( HANDLE );
		void HideModPEB( HMODULE );
		void RemoveHeader( DWORD );
		void DestroyHeader( HMODULE );
		void HideXTA( HMODULE );
	};
}

#endif

#endif

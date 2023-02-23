/*inside your main class for your software, 
make a reference to MutinyFrame::Backend Frame* and make it public
class CheatBackend {
public:
	MutinyFrame::Backend* Frame;
}; this is just an example
*/

/*
void HeartbeatThread()
{
	CheatBackend->Frame->Heartbeat->Heartbeat_wrapper(nullptr);
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		DisableThreadLibraryCalls(hModule);
		CheatBackend->Frame->Security = new MutinyFrame::Security();
		CheatBackend->Frame->Security->Protect(hModule);

		CheatBackend->Frame->Heartbeat = new MutinyFrame::CHeartBeat("firststringinuser", "secondstringinuser", "gameid ");
		_BEGINTHREAD(HeartbeatThread);

		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
	default:
		break;
	}
	return TRUE;
}
*/
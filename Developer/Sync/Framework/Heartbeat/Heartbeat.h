#pragma once

#ifdef FRAME_NETWORK 

namespace MutinyFrame
{
	class CHeartBeat
	{
	public:
		CHeartBeat( std::string, std::string, std::string );
		CHeartBeat( bool );
		void Heartbeat_wrapper( void* );
		static JSON GetUIDJSON( );
		bool Securityloop( );
		bool CryptArrayForRuntume( std::map<std::string, std::string>& );
		bool DecryptElementForUse( std::map<std::string, std::string>::value_type&, std::pair<std::string, std::string>& );
		bool DecryptArrayForUse( std::map<std::string, std::string>& );
		std::string hIV, hKey, hUserAgent;
		std::chrono::time_point<std::chrono::steady_clock> Start, Current;
		void Sleep( int, int );

	private:
		void HandleJSON( std::map<std::string, std::string>& );
		std::string RetToLower( std::string src );
		static void ToLower( std::string& src );
		static std::string createKey( std::string src, int iterations );
		bool CheckExist( std::string, std::unordered_map<std::string, std::string> );
		void GetDrivers( );
		void HeartbeatThread( );
		static std::string getTimeStamp( );
		std::string EncodeArray( std::string Array );
		void SendForbiddenDrivers( );
		void HandleHeartbeat( );
		void KillProx( );
		static std::string GetCpuID( );
		static std::string GetGPUID( );
		static std::string GetWinKey( );
		static std::string ReadFromReg( std::string );
		std::string _User = "", _Password = "";
		json11::Json ResultJson;
		DWORD oProtect;
		std::map<std::string, std::string> SystemDrivers, WebDrivers;
		JSON NewDrivers, Result, Forbidden;
		bool bKillAfterHeartbeat = false;
		bool ThreadState [ 3 ] = { false };
		WebLoggingApi Logs;
	};
}

#endif

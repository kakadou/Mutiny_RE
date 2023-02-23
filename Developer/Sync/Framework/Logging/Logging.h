#pragma once
#ifdef FRAME_NETWORK 
namespace MutinyFrame
{
	class WebLoggingApi
	{
	public:
		WebLoggingApi( ) {}
		WebLoggingApi( std::string, std::string, std::string );
		void LogError( const char*, ... );

	private:
		void SendRequest( JSON );
		void SendLog( std::string );
		std::string hKey, hIV, hUserAgent;
	};
}
#endif
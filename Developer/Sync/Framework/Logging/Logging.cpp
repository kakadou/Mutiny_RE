#include "C:/ClientFramework/Framework/Include/Frame-Include.h"
#ifdef FRAME_NETWORK 
MutinyFrame::WebLoggingApi::WebLoggingApi( std::string key, std::string iv, std::string useragent ) : hKey( key ), hIV( iv ), hUserAgent( useragent )
{
}

void MutinyFrame::WebLoggingApi::LogError( const char* fmt, ... )
{
	char buffer [ 1024 ] = {};
	va_list va;
	va_start( va, fmt );
	vsnprintf_s( buffer, 1024, fmt, va );
	va_end( va );
#ifdef FRAME_APILOGGING
	SendLog( fmt );
#endif
}

void MutinyFrame::WebLoggingApi::SendRequest( JSON Request )
{
	cCryptInstance AES_256 = cCryptInstance( CRYPT_TYPE_ENCRYPT, Request.ExportTable( ).c_str( ), hKey, hIV );

	Request.umTable.EncryptedArray.clear( );

	auto _get( VMProtectDecryptStringA( "/auth.php?session=" ) + AES_256.Execute( ) );
	auto Worker = Network::Winsock( VMProtectDecryptStringA( "api.mutiny.pw" ), _get.c_str( ), hUserAgent.c_str( ) );
}

void MutinyFrame::WebLoggingApi::SendLog( std::string Error )
{
	JSON Request;
	Request += CHeartBeat::GetUIDJSON( );
	Request += JTable( VMProtectDecryptStringA( "action" ), VMProtectDecryptStringA( "errors" ) );
	Request += JTable( VMProtectDecryptStringA( "apiresponse" ), Error.c_str( ) );

	SendRequest( Request );
}
#endif
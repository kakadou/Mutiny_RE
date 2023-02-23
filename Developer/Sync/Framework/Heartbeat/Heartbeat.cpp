#include "../Include/Frame-Include.h"

#ifdef FRAME_NETWORK 
MutinyFrame::CHeartBeat::CHeartBeat( std::string key, std::string iv, std::string useragent )
{
	//VirtualProtect(reinterpret_cast<void*>(this), sizeof this, PAGE_READWRITE, &oProtect);
	hUserAgent = useragent + key + " " + iv + VMProtectDecryptStringA( " Windows NT WOW64" );

	auto KeyDelta = this->createKey( key + iv, 2000 );
	hKey = KeyDelta.substr( 0, 32 );
	hIV = KeyDelta.substr( 32, 48 );
	Logs = WebLoggingApi( hKey, hIV, hUserAgent );
}

bool MutinyFrame::CHeartBeat::CryptArrayForRuntume( std::map<std::string, std::string>& DriverList )
{
	std::map<std::string, std::string> newList;

	for ( auto i : DriverList )
	{
		cCryptInstance EncryptFirst = cCryptInstance( CRYPT_TYPE_ENCRYPT, i.first, hKey, hIV );
		cCryptInstance EncryptSecond = cCryptInstance( CRYPT_TYPE_ENCRYPT, i.second, hKey, hIV );
		newList.emplace( EncryptFirst.Execute( ), EncryptSecond.Execute( ) );
		EncryptFirst.~cCryptInstance( );
		EncryptSecond.~cCryptInstance( );
	}

	DriverList.clear( );
	DriverList = newList;

	newList.clear( );

	return true;
}

bool MutinyFrame::CHeartBeat::DecryptElementForUse( std::map<std::string, std::string>::value_type& Element, std::pair<std::string, std::string>& ReturnElement )
{
	std::pair<std::string, std::string> NewElement;
	cCryptInstance DecryptElement = cCryptInstance( CRYPT_TYPE_DECRYPT, Element.first, hKey, hIV );
	NewElement.first = DecryptElement.Execute( );
	DecryptElement = cCryptInstance( CRYPT_TYPE_DECRYPT, Element.second, hKey, hIV );
	NewElement.second = DecryptElement.Execute( );
	ReturnElement = NewElement;

	return true;
}

bool MutinyFrame::CHeartBeat::DecryptArrayForUse( std::map<std::string, std::string>& DriverList )
{
	std::map<std::string, std::string> newList;

	for ( auto i : DriverList )
	{
		cCryptInstance EncryptFirst = cCryptInstance( CRYPT_TYPE_DECRYPT, i.first, hKey, hIV );
		cCryptInstance EncryptSecond = cCryptInstance( CRYPT_TYPE_DECRYPT, i.second, hKey, hIV );
		newList.emplace( EncryptFirst.Execute( ), EncryptSecond.Execute( ) );
		EncryptFirst.~cCryptInstance( );
		EncryptSecond.~cCryptInstance( );
	}

	DriverList.clear( );
	DriverList = newList;

	newList.clear( );

	return true;
}

MutinyFrame::CHeartBeat::CHeartBeat( bool Kill )
{
	if ( Kill )
	{
		Logs.LogError( VMProtectDecryptStringA( "Manual Kill Called" ) );
		this->KillProx( );
	}
}

void MutinyFrame::CHeartBeat::Heartbeat_wrapper( void* )
{
	if ( _User.empty( ) )
		_User = ReadFromReg( VMProtectDecryptStringA( "username" ) );

	if ( _Password.empty( ) )
		_Password = ReadFromReg( VMProtectDecryptStringA( "password" ) );

	Start = std::chrono::high_resolution_clock::now( );

	HeartbeatThread( );
}

MutinyFrame::JSON MutinyFrame::CHeartBeat::GetUIDJSON( )
{
	JSON UID;
	UID += JTable( VMProtectDecryptStringA( "username" ), ReadFromReg( VMProtectDecryptStringA( "username" ) ) );
	UID += JTable( VMProtectDecryptStringA( "password" ), ReadFromReg( VMProtectDecryptStringA( "password" ) ) );
	UID += JTable( VMProtectDecryptStringA( "cpuid" ), GetCpuID( ) );
	UID += JTable( VMProtectDecryptStringA( "gpuid" ), GetGPUID( ) );
	UID += JTable( VMProtectDecryptStringA( "timestamp" ), getTimeStamp( ) );
	UID += JTable( VMProtectDecryptStringA( "winkey" ), GetWinKey( ) );

	return UID;
}

void MutinyFrame::CHeartBeat::HandleJSON( std::map<std::string, std::string>& WebConfigs )
{
	auto json = ResultJson [ VMProtectDecryptStringA( "drivers" ) ];

	WebConfigs.clear( );

	for ( auto i = 0; i < ResultJson [ VMProtectDecryptStringA( "driverssize" ) ].int_value( ); i++ )
	{
		auto subarray = json [ i ];
		WebConfigs.emplace( subarray [ std::string( VMProtectDecryptStringA( "name" ) ) ].string_value( ), subarray [ std::string( VMProtectDecryptStringA( "forbidden" ) ) ].string_value( ) );
	}

	CryptArrayForRuntume( WebConfigs );

	ThreadState [ 2 ] = true;
}

void MutinyFrame::CHeartBeat::ToLower( std::string& src )
{
	transform( src.begin( ), src.end( ), src.begin( ), tolower );
}

std::string MutinyFrame::CHeartBeat::RetToLower( std::string src )
{
	std::string ret = std::string( src );
	transform( ret.begin( ), ret.end( ), ret.begin( ), tolower );

	return ret;
}

std::string MutinyFrame::CHeartBeat::createKey( std::string src, int iterations )
{
	auto output( src );
	ToLower( output );

	for ( auto i = 0; i <= iterations; i++ )
	{
		cCryptInstance NewCrypt = cCryptInstance( output );
		output = NewCrypt.Execute( );
	}

	return output;
}

bool MutinyFrame::CHeartBeat::CheckExist( std::string strTable, std::unordered_map<std::string, std::string> List )
{
	auto lowerString = std::string( strTable );
	ToLower( lowerString );

	auto Search = List.find( lowerString );

	if ( Search != List.end( ) )
		return true;

	return false;
}

bool MutinyFrame::CHeartBeat::Securityloop( )
{
	if ( !ThreadState [ 2 ] )
	{
		Logs.LogError( VMProtectDecryptStringA( "Failed Setup Drivers" ) );
		//exit( 0 );
	}

	bool bReturn = true;

	ThreadState [ 1 ] = false;
#ifdef FRAME_SCANSEC
	GetDrivers( );

	if (SystemDrivers.empty())
		GetDrivers( );

	if (SystemDrivers.empty())
		Logs.LogError(VMProtectDecryptStringA("GetDrivers( ) : Failed"));

	DecryptArrayForUse( WebDrivers );//

	for ( auto i : SystemDrivers )
	{
		if ( WebDrivers [ i.first ].size( ) != 0 )
		{
			if ( !WebDrivers [ i.first ].compare( "1" ) )
			{
				Forbidden += { i.first, i.first };
				ThreadState [ 1 ] = true;
				bReturn = false;
			}
		}
		else
		{
			NewDrivers += { i.first, i.first };

			if ( !ResultJson [ VMProtectDecryptStringA( "strictmode" ) ].string_value( ).compare("1") )
			{
				bReturn = false;
				ThreadState [ 1 ] = true;
			}
		}
	}

	Current = std::chrono::high_resolution_clock::now( );

	SystemDrivers.clear( );

	CryptArrayForRuntume( WebDrivers );//
#endif
	return bReturn;
}

void MutinyFrame::CHeartBeat::GetDrivers( )
{
	LPVOID drivers [ 1024 ];
	DWORD cbNeeded;

	if ( EnumDeviceDrivers( drivers, sizeof drivers, &cbNeeded ) && cbNeeded < sizeof drivers )
	{
		TCHAR szDriver [ 1024 ];
		int cDrivers = cbNeeded / sizeof drivers [ 0 ];

		for ( auto i = 0; i < cDrivers; i++ )
		{
			if ( GetDeviceDriverBaseName( drivers [ i ], szDriver, sizeof szDriver / sizeof szDriver [ 0 ] ) ) 
			{
				if (szDriver != "")
				{
					SystemDrivers.emplace(RetToLower(std::string(szDriver)), RetToLower(std::string(szDriver)));
				}
			}
		}
	}
}

void MutinyFrame::CHeartBeat::HeartbeatThread( )
{
#ifdef FRAME_HEARTBEAT
	this->HandleHeartbeat( );

	static auto Started = std::chrono::high_resolution_clock::now( );

	while ( true )
	{
		auto NewTime = std::chrono::high_resolution_clock::now( );
		auto DiffTime = std::chrono::duration_cast< std::chrono::seconds >( NewTime - Started );

		if ( DiffTime.count( ) >= 60 )
		{
			Started = std::chrono::high_resolution_clock::now( );
			this->HandleHeartbeat( );
		}

		if ( !this->Securityloop( ) )
		{
			if ( NewDrivers.umTable.EncryptedArray.size( ) > 0 || Forbidden.umTable.EncryptedArray.size( ) > 0 ) {
				SendForbiddenDrivers( );
			}
		}

		if ( !ThreadState [ 0 ] )
		{
			Logs.LogError( VMProtectDecryptStringA( "Heartbeat Didn't Finish" ) );
			exit( 0 );
		}

		if ( ThreadState [ 1 ] )
		{
			Logs.LogError( VMProtectDecryptStringA( "Failed Driver Scan" ) );
			exit( 0 );
		}

		if ( !ThreadState [ 2 ] )
		{
			Logs.LogError( VMProtectDecryptStringA( "Failed Setup Drivers" ) );
			//exit( 0 );
		}

		Sleep( 20, 0 );
	}
#endif
}

std::string MutinyFrame::CHeartBeat::getTimeStamp( )
{
	auto t = time( nullptr );
	auto now = localtime( &t );
	char cBuf [ 255 ] = "";

	sprintf( cBuf, VMProtectDecryptStringA( "%i-%i-%i-%i-%i-%i" ),
		now->tm_mon + 1, now->tm_mday, now->tm_year + 1900,
		now->tm_hour, now->tm_min, now->tm_sec );

	return cBuf;
}
std::string MutinyFrame::CHeartBeat::EncodeArray( std::string Array )
{
	std::string EncodedArray;

	auto Sink = new CryptoPP::StringSink( EncodedArray );
	auto Encoder = new CryptoPP::Base64Encoder( Sink, false );
	CryptoPP::StringSource ss( Array, true, Encoder );

	return EncodedArray;
}
void MutinyFrame::CHeartBeat::SendForbiddenDrivers( )
{
    JSON Request;

	if ( NewDrivers.umTable.EncryptedArray.size( ) > 0 )
	{
		std::string EncodedJSON = this->EncodeArray( NewDrivers.ExportTable( ) );
		Request += {VMProtectDecryptStringA( "newdrivers" ), EncodedJSON};
	}

	if ( Forbidden.umTable.EncryptedArray.size( ) > 0 )
	{
		std::string EncodedJSON2 = EncodeArray( Forbidden.ExportTable( ) );
		Request += {VMProtectDecryptStringA( "forbiddendrivers" ), EncodedJSON2};
	}

	Request += this->GetUIDJSON( );
	Request += JTable( VMProtectDecryptStringA( "action" ), VMProtectDecryptStringA( "heartbeat" ) );

	cCryptInstance AES_256 = cCryptInstance( CRYPT_TYPE_ENCRYPT, Request.ExportTable( ).c_str( ), hKey, hIV );

	auto _Post( VMProtectDecryptStringA( "/auth.php?session=" ) + AES_256.Execute( ) );
	auto Worker = Network::Winsock( VMProtectDecryptStringA( "api.mutiny.pw" ), _Post.c_str( ), hUserAgent.c_str( ) );

	NewDrivers.umTable.EncryptedArray.clear( );
	Forbidden.umTable.EncryptedArray.clear( );
}

void MutinyFrame::CHeartBeat::HandleHeartbeat( )
{
	
#ifdef FRAME_HEARTBEAT
	JSON Request;

	ThreadState [ 0 ] = { false };//needs to be true by end
	ThreadState [ 1 ] = { true }; // needs to be false by end,
	ThreadState [ 2 ] = { false };//needs to be true by end

	Request += this->GetUIDJSON( );
	Request += JTable( VMProtectDecryptStringA( "action" ), VMProtectDecryptStringA( "heartbeat" ) );

	cCryptInstance AES_256 = cCryptInstance( CRYPT_TYPE_ENCRYPT, Request.ExportTable( ).c_str( ), hKey, hIV );

	Request.umTable.EncryptedArray.clear( );

	auto _get( VMProtectDecryptStringA( "/auth.php?session=" ) + AES_256.Execute( ) );
	auto Worker = Network::Winsock( VMProtectDecryptStringA( "api.mutiny.pw" ), _get.c_str( ), hUserAgent.c_str( ) );

	auto FailedToConnect = true;

	for ( auto i = 0; i < 2; i++ )
	{
		if ( Worker.GetReturn( ).compare( VMProtectDecryptStringA( "No Feedback" ) ) )
		{
			FailedToConnect = false;
			break;
		}

		Sleep( 7, 500 );

		Worker.CleanAndRequest( );
	}

	if ( FailedToConnect )
	{
		Logs.LogError( VMProtectDecryptStringA( "Failed To Connect" ) );
		this->KillProx( );
	}

	AES_256 = cCryptInstance( CRYPT_TYPE_DECRYPT, Worker.GetReturn( ), hKey, hIV );

	std::string errorcode;
	ResultJson = json11::Json::parse( AES_256.Execute( ), errorcode );
	Result = JSON( AES_256.Execute( ) );

	if ( Result.GetVal( VMProtectDecryptStringA( "code" ) ).compare( VMProtectDecryptStringA( "200" ) ) )
		this->KillProx( );

	this->HandleJSON( WebDrivers );

	bKillAfterHeartbeat = !Securityloop( );

	if ( NewDrivers.umTable.EncryptedArray.size( ) > 0 || Forbidden.umTable.EncryptedArray.size( ) > 0 )
		SendForbiddenDrivers( );

	if ( ThreadState [ 1 ] )
	{
		Logs.LogError( VMProtectDecryptStringA( "Failed Setup Drivers" ) );
		exit( 0 );
	}

	if ( bKillAfterHeartbeat )
	{
		Logs.LogError( VMProtectDecryptStringA( "KillAfterHeartbeat" ) );
		this->KillProx( );
		exit( 0 );
	}

	ThreadState [ 0 ] = true;

	Result.umTable.EncryptedArray.clear( );
	ResultJson = json11::Json::NUL;
#endif
}

std::string MutinyFrame::CHeartBeat::GetCpuID( )
{
	int Cpuid [ 4 ] = { 0 };
	__cpuid( Cpuid, 0 );
	char cBuf [ 255 ] = "";
	sprintf( cBuf, VMProtectDecryptStringA( "%i-%i-%i-%i" ), Cpuid [ 0 ], Cpuid [ 1 ], Cpuid [ 2 ], Cpuid [ 3 ] );
	return { cBuf };
}

std::string MutinyFrame::CHeartBeat::GetGPUID( )
{

	std::string GpuId;

	DISPLAY_DEVICE Device;
	Device.cb = sizeof( DISPLAY_DEVICE );

	DWORD i = 0;

	while ( EnumDisplayDevices( nullptr, i, &Device, 0 ) )
	{
		if ( Device.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE )
		{
			GpuId = Device.DeviceID;
			break;
		}

		i++;
	}

	cCryptInstance AES_256 = cCryptInstance( GpuId );

	return AES_256.Execute( );
}

std::string MutinyFrame::CHeartBeat::GetWinKey( )
{
	char WinKey [ 35 ] = "";

	HKEY hKey;
	DWORD buffer = NULL;

	if ( RegOpenKeyExA( HKEY_LOCAL_MACHINE,
		VMProtectDecryptStringA( "Software\\Microsoft\\Windows NT\\CurrentVersion" ),
		0, KEY_QUERY_VALUE | KEY_WOW64_64KEY,
		&hKey ) != ERROR_SUCCESS )
	{
		return { "" };
	}

	buffer = sizeof WinKey;

	if ( RegQueryValueExA( hKey,
		VMProtectDecryptStringA( "ProductId" ),
		nullptr,
		nullptr,
		( LPBYTE ) WinKey,
		&buffer ) != ERROR_SUCCESS )
	{
		RegCloseKey( hKey );
		return { "" };
	}

	RegCloseKey( hKey );

	return { WinKey };

}

std::string MutinyFrame::CHeartBeat::ReadFromReg( std::string key )
{
	char Info [ 255 ] = "";

	HKEY hKey;
	DWORD buffer = NULL;

	std::string tkey, iv;
	std::string keybuf = createKey( VMProtectDecryptStringA( "P0iDlH0vXbRiQ50gJs5G4RwbsgmHTODyOL3Zj3l843fKXeRwxL" ), 2500 );
	tkey = keybuf.substr( 0, 32 );
	iv = keybuf.substr( 32, 48 );

	if ( RegOpenKeyExA( HKEY_CURRENT_USER,
		VMProtectDecryptStringA( "SOFTWARE\\Aricepto\\Settings" ),
		0, KEY_QUERY_VALUE | KEY_WOW64_64KEY,
		&hKey ) != ERROR_SUCCESS )
	{
		return { "" };
	}

	buffer = sizeof Info;

	if ( RegQueryValueExA( hKey,
		key.c_str( ),
		nullptr,
		nullptr,
		reinterpret_cast< LPBYTE >( Info ),
		&buffer ) != ERROR_SUCCESS )
	{
		RegCloseKey( hKey );
		return { "" };
	}

	RegCloseKey( hKey );

	cCryptInstance NewDecrypt = cCryptInstance( CRYPT_TYPE_DECRYPT, std::string( Info ), tkey, iv );

	return { NewDecrypt.Execute( ) };
}

void MutinyFrame::CHeartBeat::KillProx( )
{
	//ExitProcess(0);
	exit( EXIT_SUCCESS );
	int* p = nullptr;
	*p = 1;
}

void MutinyFrame::CHeartBeat::Sleep( int Seconds, int Miliseconds )
{
	std::this_thread::sleep_for( std::chrono::milliseconds( Seconds * 1000 + Miliseconds ) );
}

#endif
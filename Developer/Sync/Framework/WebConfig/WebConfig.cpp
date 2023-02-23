#include "../Include/Frame-Include.h"

#ifndef FRAME_DISABLE
#ifdef FRAME_STRINGCONF
#ifndef FRAME_LOCALCONF
#ifdef FRAME_NETWORK 
MutinyFrame::CWebConfig::CWebConfig( )
{
}

MutinyFrame::CWebConfig::CWebConfig( std::string URL, std::string Location, std::string UserAgent, std::string Key, std::string IV ) : _UserAgent( UserAgent ), _URL( URL ), _Location( Location ), _Config( VMProtectDecryptStringA( "Default" ) ), _Key( Key ), _IV( IV )
{
	this->LoadConfig( _Config );
}
#endif
#else
MutinyFrame::CWebConfig::CWebConfig()
{
	this->LoadConfig(_Config);
}
#endif
int MutinyFrame::CWebConfig::GetConfigValue( std::string strOption )
{
	if ( _Table.CheckExist( strOption ) )
		return _Table.GetiVal( strOption );

	return 0;
}

double MutinyFrame::CWebConfig::GetPreciseConfigValue( std::string strOption )
{
	if ( _Table.CheckExist( strOption ) )
		return _Table.GetDVal( strOption );

	return 0.f;
}
#ifndef FRAME_LOCALCONF
#ifdef FRAME_NETWORK 
bool MutinyFrame::CWebConfig::LoadConfig( std::string Config )
{
	_Config = Config;
	this->Fetch( );

	return true;
}

bool MutinyFrame::CWebConfig::SaveConfig( std::string Config )
{
	_Config = Config;
	this->Update( );

	return true;
}
#endif
#else
bool MutinyFrame::CWebConfig::LoadConfig( std::string Config )
{
	_Config = Config;
	this->Fetch( );

	return true;
}

bool MutinyFrame::CWebConfig::SaveConfig( std::string Config )
{
	_Config = Config;
	this->Update( );

	return true;
}
#endif
bool MutinyFrame::CWebConfig::RegisterConfigValue( std::string strOption, int iVal )
{
	if ( !_Table.SetiVal( strOption, iVal ) )
	{
		_Table += JTable( strOption, iVal );
		return true;
	}

	return false;
}

bool MutinyFrame::CWebConfig::RegisterConfigValue( std::string strOption, std::string sVal )
{
	if ( !_Table.SetSVal( strOption, sVal ) )
	{
		_Table += JTable( strOption, sVal );
		return true;
	}

	return false;
}

bool MutinyFrame::CWebConfig::RegisterConfigValue( std::string strOption, double dVal )
{
	if ( !_Table.SetDVal( strOption, dVal ) )
	{
		_Table += JTable( strOption, std::to_string( dVal ) );
		return true;
	}

	return false;
}
#ifndef FRAME_LOCALCONF
#ifdef FRAME_NETWORK 
void MutinyFrame::CWebConfig::Update( )
{
	JSON Request = CHeartBeat::GetUIDJSON( );
	Request += { VMProtectDecryptStringA( "configname" ), _Config };
	Request += { VMProtectDecryptStringA( "action" ), VMProtectDecryptStringA( "configs" ) };
	Request += { VMProtectDecryptStringA( "configaction" ), VMProtectDecryptStringA( "post" ) };

	std::string EncodedJSON;
	auto Sink = new CryptoPP::StringSink( EncodedJSON );
	auto Encoder = new CryptoPP::Base64Encoder( Sink, false );
	CryptoPP::StringSource ss( _Table.ExportTable( ), true, Encoder );
	Request += { VMProtectDecryptStringA( "configdata" ), EncodedJSON };

	cCryptInstance AES_256 = cCryptInstance( CRYPT_TYPE_ENCRYPT, Request.ExportTable( ), _Key, _IV );
	auto _Post( std::string( VMProtectDecryptStringA( "session=" ) ) + AES_256.Execute( ) );
	Network::Winsock Worker( _URL.c_str( ), _Location.c_str( ), _Post.c_str( ), _UserAgent.c_str( ) );
}


void MutinyFrame::CWebConfig::Fetch( )
{
	JSON Request = CHeartBeat::GetUIDJSON( );
	Request += {VMProtectDecryptStringA( "configname" ), _Config};
	Request += {VMProtectDecryptStringA( "action" ), VMProtectDecryptStringA( "configs" )};
	Request += {VMProtectDecryptStringA( "configaction" ), VMProtectDecryptStringA( "get" )};

	cCryptInstance AES_256 = cCryptInstance( CRYPT_TYPE_ENCRYPT, Request.ExportTable( ), _Key, _IV );
	auto _Post( _Location + VMProtectDecryptStringA( "?session=" ) + AES_256.Execute( ).c_str( ) );
	Network::Winsock Worker( _URL.c_str( ), _Post.c_str( ), _UserAgent.c_str( ) );
	AES_256 = cCryptInstance( CRYPT_TYPE_DECRYPT, Worker.GetReturn( ), _Key, _IV );

	if ( Worker.GetReturn( ).compare( VMProtectDecryptStringA( "No Feedback" ) ) )
	{
		auto json = json11::Json::parse( AES_256.Execute( ), std::string( ) );
		_Table = JSON( std::string( json [ VMProtectDecryptStringA( "configdata" ) ].string_value( ) ) );
	}
}
#endif
#else
void MutinyFrame::CWebConfig::Update()
{
	char *file = new char[MAX_PATH];
	strcpy(file, VMProtectDecryptStringA("c:\\mutiny_pw\\"));
	CreateDirectoryA(VMProtectDecryptStringA("c:\\mutiny_pw\\"), nullptr);
	strcat(file, _Config.c_str());
	strcat(file, VMProtectDecryptStringA(".con"));

	std::fstream configFile(file, std::ios::out | std::ios::trunc);

	if (!configFile.is_open())
	{
		//printf("ERROR: could not create %s\n", CONFIG_FILE_NAME);
		delete[] file;
		return;
	}

	configFile << _Table.ExportTable() << std::endl;
	configFile.close();

	delete[] file;
}

void MutinyFrame::CWebConfig::Fetch()
{
	char *file = new char[MAX_PATH];
	strcpy(file, VMProtectDecryptStringA("c:\\mutiny_pw\\"));
	CreateDirectoryA(VMProtectDecryptStringA("c:\\mutiny_pw\\"), nullptr);
	strcat(file, _Config.c_str());

	strcat(file, VMProtectDecryptStringA(".con"));

	std::ifstream inFile;
	inFile.open(file);//open the input file

	std::stringstream strStream;
	strStream << inFile.rdbuf();//read the file
	std::string str = strStream.str();//str holds the content of the file

	_Table = JSON(str);
}
#endif
#else
#ifndef FRAME_LOCALCONF
#ifdef FRAME_NETWORK 
MutinyFrame::CWebConfig::CWebConfig()
{
}

MutinyFrame::CWebConfig::CWebConfig(std::string URL, std::string Location, std::string UserAgent, std::string Key, std::string IV) : _UserAgent(UserAgent), _URL(URL), _Location(Location), _Config(VMProtectDecryptStringA("Default")), _Key(Key), _IV(IV)
{
	this->LoadConfig(_Config);
}
#endif
#else
MutinyFrame::CWebConfig::CWebConfig()
{
	this->LoadConfig(_Config);
}
#endif
double MutinyFrame::CWebConfig::GetConfigValue(int iOption)
{
		return uMap[iOption];
}

bool MutinyFrame::CWebConfig::LoadConfig(std::string Config)
{
	_Config = Config;
	this->Fetch();
	this->ImportJSON();

	return true;
}

bool MutinyFrame::CWebConfig::SaveConfig(std::string Config)
{
	_Config = Config;
	this->ExportUMapToJSON();
	this->Update();

	return true;
}

bool MutinyFrame::CWebConfig::RegisterConfigValue(int iOption, double dVal)
{
	uMap[iOption] = dVal;
	return false;
}

void MutinyFrame::CWebConfig::ExportUMapToJSON()
{
	for (auto i : uMap)
	{
		_Table += { std::to_string(i.first), std::to_string(i.second) };
	}
}

void MutinyFrame::CWebConfig::ImportJSON()
{
	for (auto i : _Table.umTable.EncryptedArray)
	{
		uMap[stoi(_Table.umTable.DecryptString(i.first))] = stod(_Table.umTable.DecryptString(i.second));
	}
	_Table.umTable.EncryptedArray.clear();
}
#ifndef FRAME_LOCALCONF
#ifdef FRAME_NETWORK 

void MutinyFrame::CWebConfig::Update()
{
	JSON Request = CHeartBeat::GetUIDJSON();
	Request += { VMProtectDecryptStringA("configname"), _Config };
	Request += { VMProtectDecryptStringA("action"), VMProtectDecryptStringA("configs") };
	Request += { VMProtectDecryptStringA("configaction"), VMProtectDecryptStringA("post") };

	std::string EncodedJSON;
	auto Sink = new CryptoPP::StringSink(EncodedJSON);
	auto Encoder = new CryptoPP::Base64Encoder(Sink, false);
	CryptoPP::StringSource ss(_Table.ExportTable(), true, Encoder);
	Request += { VMProtectDecryptStringA("configdata"), EncodedJSON };

	cCryptInstance AES_256 = cCryptInstance(CRYPT_TYPE_ENCRYPT, Request.ExportTable(), _Key, _IV);
	auto _Post(std::string(VMProtectDecryptStringA("session=")) + AES_256.Execute());
	Network::Winsock Worker(_URL.c_str(), _Location.c_str(), _Post.c_str(), _UserAgent.c_str());
}


void MutinyFrame::CWebConfig::Fetch()
{
	JSON Request = CHeartBeat::GetUIDJSON();
	Request += {VMProtectDecryptStringA("configname"), _Config};
	Request += {VMProtectDecryptStringA("action"), VMProtectDecryptStringA("configs")};
	Request += {VMProtectDecryptStringA("configaction"), VMProtectDecryptStringA("get")};

	cCryptInstance AES_256 = cCryptInstance(CRYPT_TYPE_ENCRYPT, Request.ExportTable(), _Key, _IV);
	auto _Post(_Location + VMProtectDecryptStringA("?session=") + AES_256.Execute().c_str());
	Network::Winsock Worker(_URL.c_str(), _Post.c_str(), _UserAgent.c_str());
	AES_256 = cCryptInstance(CRYPT_TYPE_DECRYPT, Worker.GetReturn(), _Key, _IV);

	if (Worker.GetReturn().compare(VMProtectDecryptStringA("No Feedback")))
	{
		auto json = json11::Json::parse(AES_256.Execute(), std::string());
		_Table = JSON(std::string(json[VMProtectDecryptStringA("configdata")].string_value()));
	}
}
#endif
#else
void MutinyFrame::CWebConfig::Update()
{
	char *file = new char[MAX_PATH];
	strcpy(file, VMProtectDecryptStringA("c:\\mutiny_pw\\"));
	CreateDirectoryA(VMProtectDecryptStringA("c:\\mutiny_pw\\"), nullptr);
	strcat(file, _Config.c_str());
	strcat(file, VMProtectDecryptStringA(".con"));

	std::fstream configFile(file, std::ios::out | std::ios::trunc);

	if (!configFile.is_open())
	{
		//printf("ERROR: could not create %s\n", CONFIG_FILE_NAME);
		delete[] file;
		return;
	}

	configFile << _Table.ExportTable() << std::endl;
	configFile.close();

	delete[] file;
}

void MutinyFrame::CWebConfig::Fetch()
{
	char *file = new char[MAX_PATH];
	strcpy(file, VMProtectDecryptStringA("c:\\mutiny_pw\\"));
	CreateDirectoryA(VMProtectDecryptStringA("c:\\mutiny_pw\\"), nullptr);
	strcat(file, _Config.c_str());

	strcat(file, VMProtectDecryptStringA(".con"));

	std::ifstream inFile;
	inFile.open(file);//open the input file

	std::stringstream strStream;
	strStream << inFile.rdbuf();//read the file
	std::string str = strStream.str();//str holds the content of the file

	_Table = JSON(str);
}
#endif
#endif
#endif
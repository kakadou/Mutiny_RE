#include "../Include/Frame-Include.h"

#ifndef FRAME_DISABLE

MutinyFrame::cCryptInstance::cCryptInstance( CRYPT_TYPE Type, std::string Src, std::string Key, std::string IV )
	: oProtect( 0 )
{
	//VirtualProtect(reinterpret_cast<void*>(this), sizeof this, PAGE_READWRITE, &oProtect);
	this->_iCryptType = Type;
	this->_Src = Src;
	this->_Key = Key;
	this->_IV = IV;
}

MutinyFrame::cCryptInstance::~cCryptInstance( )
{
	//VirtualProtect(reinterpret_cast<void*>(this), sizeof this, oProtect, &oProtect);
}

MutinyFrame::cCryptInstance::cCryptInstance( std::string Src )
	: oProtect( 0 )
{
	this->_iCryptType = CRYPT_TYPE_HASH;
	this->_Src = Src;
}

std::string MutinyFrame::cCryptInstance::Execute( )
{
	switch ( this->_iCryptType )
	{
	case CRYPT_TYPE_ENCRYPT:
		return this->Encrypt( this->_Src, this->_Key, this->_IV );
	case CRYPT_TYPE_DECRYPT:
		return this->Decrypt( this->_Src, this->_Key, this->_IV );
	case CRYPT_TYPE_HASH:
		return this->SHA256Encode( this->_Src );
	default:
		return VMProtectDecryptStringA( "INVALID TYPE" );
	}
}

std::string MutinyFrame::cCryptInstance::SHA256Encode( std::string Src )
{
	CryptoPP::SHA256 hash;
	byte digest [ CryptoPP::SHA256::DIGESTSIZE ];

	hash.CalculateDigest( digest, ( unsigned char* ) Src.c_str( ), Src.length( ) );

	std::string output;
	auto Sink = new CryptoPP::StringSink( output );

	CryptoPP::HexEncoder encoder( nullptr, false );
	encoder.Attach( Sink );
	encoder.Put( digest, sizeof( digest ) );
	encoder.MessageEnd( );

	return output;
}

std::string MutinyFrame::cCryptInstance::Encrypt( const std::string& Src, const std::string& Key, const std::string& IV )
{
	std::string strOut;
	CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption encryption( ( unsigned char* ) Key.c_str( ), Key.length( ), ( unsigned char* ) IV.c_str( ) );
	auto Sink = new CryptoPP::StringSink( strOut );
	auto Encoder = new CryptoPP::Base64Encoder( Sink, false );
	auto Filter = new CryptoPP::StreamTransformationFilter( encryption, Encoder );
	CryptoPP::StringSource( Src, true, Filter );
	return strOut;
}

std::string MutinyFrame::cCryptInstance::Decrypt( const std::string& Src, const std::string& Key, const std::string& IV )
{
	std::string strOut;
	CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption decryption( ( unsigned char* ) Key.c_str( ), Key.length( ), ( unsigned char* ) IV.c_str( ) );
	auto Sink = new CryptoPP::StringSink( strOut );
	auto Filter = new CryptoPP::StreamTransformationFilter( decryption, Sink );
	auto Decoder = new CryptoPP::Base64Decoder( Filter );
	CryptoPP::StringSource( Src, true, Decoder );

	return strOut;
}

#endif
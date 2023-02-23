#pragma once

#ifndef FRAME_DISABLE

namespace MutinyFrame
{
	enum CRYPT_TYPE
	{
		CRYPT_TYPE_ENCRYPT = 2 << 4,
		CRYPT_TYPE_DECRYPT,
		CRYPT_TYPE_HASH
	};

	class cCryptInstance
	{
	public:
		cCryptInstance( CRYPT_TYPE, std::string, std::string, std::string );
		~cCryptInstance( );
		cCryptInstance( std::string );
		std::string Execute( );

	private:
		std::string Encrypt( const std::string&, const std::string&, const std::string& );
		std::string Decrypt( const std::string&, const std::string&, const std::string& );
		std::string SHA256Encode( std::string src );
		int _iCryptType;
		std::string _Src, _Key, _IV;
		DWORD oProtect;
	};
}

#endif

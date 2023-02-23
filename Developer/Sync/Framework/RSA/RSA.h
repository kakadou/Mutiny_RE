#pragma once

namespace MutinyFrame
{
	class RSA
	{
	public:
		RSA( ) { }
		RSA( std::string ServerPub );
		JSON EncryptArray( JSON );

	private:
		JSON GenRSAKeyPair( );
		JSON GenAESKeyAndEncrypt( JSON );
	};
}
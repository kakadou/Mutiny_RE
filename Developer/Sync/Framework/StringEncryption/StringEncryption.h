#pragma once

#ifndef FRAME_DISABLE

namespace MutinyFrame
{
	class StringEncryption
	{
	public:
		StringEncryption( );
		void RegisterString( std::string, std::string );
		std::string ReturnValue( std::string );
		std::string operator[]( std::string );
		bool operator==( StringEncryption );
		std::string XorMemBlock( std::string, int );
		std::string InflateMemoryBlock( std::string );
		std::string DeflateMemoryBlock( std::string );
		std::map<std::string, std::string> EncryptedArray;
		std::string DecryptString( std::string );

	private:
		std::string EncryptString( std::string );
		void GenKeyInstance( );
		int key;
	};
}

#endif

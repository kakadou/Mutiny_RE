#include "../Include/Frame-Include.h"

#ifndef FRAME_DISABLE

MutinyFrame::StringEncryption::StringEncryption( )
{
	GenKeyInstance( );
}

void MutinyFrame::StringEncryption::RegisterString( std::string src, std::string val )
{
	EncryptedArray [ EncryptString( src ) ] = EncryptString( val );
}

std::string MutinyFrame::StringEncryption::ReturnValue( std::string src )
{
	return DecryptString( EncryptedArray [ EncryptString( src ) ] );
}

std::string MutinyFrame::StringEncryption::operator[]( std::string src )
{
	return ReturnValue( src );
}

bool MutinyFrame::StringEncryption::operator==( StringEncryption That )
{
	if ( this->EncryptedArray == That.EncryptedArray )
		return true;

	return false;
}

std::string MutinyFrame::StringEncryption::XorMemBlock( std::string toEncrypt, int key )
{
	std::string output = toEncrypt;

	for ( int i = 0; i < toEncrypt.size( ); i++ )
		output [ i ] = toEncrypt [ i ] ^ key;

	return output;
}

std::string MutinyFrame::StringEncryption::EncryptString( std::string src )
{
	std::string output = src;
	return XorMemBlock( output, key );
}

std::string MutinyFrame::StringEncryption::DecryptString( std::string encryptedsrc )
{
	std::string output = encryptedsrc;
	return XorMemBlock( output, key );
}

void MutinyFrame::StringEncryption::GenKeyInstance( )
{
	key = rand( ) % 255;
}

#endif
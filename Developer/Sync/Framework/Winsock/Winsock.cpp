#include "../Include/Frame-Include.h"

#ifdef FRAME_NETWORK 
MutinyFrame::Network::Winsock::Winsock( const char* ServerURL, const char* Location, const char* Post, const char* UserAgent )
	:  UserAgent( UserAgent ), Location( Location ), Post( Post )
{
	if (curl_global_init(CURL_GLOBAL_ALL) == CURLE_OK)
	{
		if (!(curl = curl_easy_init()))
			return;
	}

	if (!Connect(ServerURL))
		return;

}

size_t MutinyFrame::Network::OpenSSLWrapper::DataCallbackWrapper(char *cBuf, size_t size, size_t mem_size, void * up)
{
	return static_cast<OpenSSLWrapper*>(up)->DataCallback(cBuf, size, mem_size);
}
size_t MutinyFrame::Network::OpenSSLWrapper::DataCallback(char *cBuf, size_t size, size_t mem_size)
{
	feedback += std::string(cBuf);

	return size * mem_size;
}
MutinyFrame::Network::Winsock::Winsock( )
	:  UserAgent( "" ), ConnectedUrl( nullptr ), Location( "" ), Post( "" )
{
	/*Waits for Arguments to get set*/
}

MutinyFrame::Network::Winsock::Winsock( const char* UserAgent ) :
	 UserAgent( "" ), ConnectedUrl( nullptr ), Location( "" ), Post( "" )
{
	/*Waits for Arguments to get set but Sets UserAgent*/
}

MutinyFrame::Network::Winsock::Winsock( const char* ServerURL, const char* Location, const char* UserAgent )
	: UserAgent( UserAgent ), Location( Location )
{
	if (curl_global_init(CURL_GLOBAL_ALL) == CURLE_OK)
	{
		if (!(curl = curl_easy_init()))
			return;
	}

	if (!Connect(ServerURL))
		return;
	
}

MutinyFrame::Network::Winsock::~Winsock( )
{
	Cleanup( );
}

std::string MutinyFrame::Network::Winsock::GetReturn( ) const
{
	if ( Feedback.size( ) != NULL )
		return Feedback;

	return { "No Feedback" };
}

void MutinyFrame::Network::Winsock::CleanAndRequest( )
{
	this->Cleanup( );
	Feedback.clear( );	
	*this = Winsock(ConnectedUrl.c_str(), Location.c_str(), UserAgent.c_str());
}

void MutinyFrame::Network::Winsock::SetInfo( std::string sServerURL, std::string sLocation, std::string sPost )
{
	this->Cleanup( );
	Feedback.clear( );
	*this = Winsock( sServerURL.c_str( ), sLocation.c_str( ), sPost.c_str( ), UserAgent.c_str() );
}

void MutinyFrame::Network::Winsock::SetInfo( std::string sServerURL, std::string sLocation )
{
	this->Cleanup( );
	Feedback.clear( );
	*this = Winsock(sServerURL.c_str(), sLocation.c_str(), UserAgent.c_str());
}

void MutinyFrame::Network::Winsock::Cleanup( )
{
	curl_easy_cleanup(curl);
	curl_global_cleanup();
}

bool MutinyFrame::Network::Winsock::Connect( const char* URL )
{
	OpenSSLWrapper wrapper;
	ConnectedUrl = std::string(URL + Location);
	curl_easy_setopt(curl, CURLOPT_URL, ConnectedUrl);
	curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
	curl_easy_setopt(curl, CURLOPT_USERAGENT, UserAgent);
	//curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30); 
	curl_easy_setopt(curl, CURLOPT_HEADER, false);
	if (Post.size())
	{
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, Post.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, Post.length());
	}
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &wrapper);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &OpenSSLWrapper::DataCallbackWrapper);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4); 
	
	curl_easy_perform(curl);
	Feedback = wrapper.feedback;

	//this->CleanFeedback();
	return true;
}

void MutinyFrame::Network::Winsock::CleanFeedback()
{
	for (auto i = 0; i < Feedback.size(); i++)
	{
		if (Feedback[i] == '\r' && Feedback[i + 1] == '\n' && Feedback[i + 2] == '\r' && Feedback[i + 3] == '\n')
			Feedback.erase(0, i + 4);
	}
}
#endif
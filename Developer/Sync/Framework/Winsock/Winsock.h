#pragma once

#ifdef FRAME_NETWORK 

namespace MutinyFrame
{
	namespace Network
	{
		class OpenSSLWrapper
		{
		public:
			std::string feedback;
			static size_t DataCallbackWrapper(char*, size_t, size_t, void*);
			size_t DataCallback(char*, size_t, size_t);
		};
		class Winsock
		{
		public:
			Winsock( );
			Winsock( const char* );
			Winsock( const char*, const char*, const char* );
			Winsock( const char*, const char*, const char*, const char* );
			~Winsock( );
			std::string GetReturn( ) const;
			void CleanAndRequest( );
			void SetInfo( std::string, std::string, std::string );
			void SetInfo( std::string, std::string );

		private:
			void Cleanup( );
			bool Connect( const char* );
			void CleanFeedback();
		
			CURL* curl;
			std::string sMsg, UserAgent;
			std::string ConnectedUrl;
			std::string Feedback, Location, Post;
		};
	}
}

#endif

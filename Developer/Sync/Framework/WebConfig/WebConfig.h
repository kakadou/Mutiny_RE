#pragma once

#ifndef FRAME_DISABLE

namespace MutinyFrame
{
#ifdef FRAME_STRINGCONF
	class CWebConfig
	{
	public:
		CWebConfig( );
#ifndef FRAME_LOCALCONF
		CWebConfig( std::string, std::string, std::string, std::string, std::string );
#endif

		int GetConfigValue( std::string );
		double GetPreciseConfigValue( std::string );
#ifndef FRAME_LOCALCONF
		bool LoadConfig( std::string );
		bool SaveConfig( std::string );
#else
		bool LoadConfig( std::string );
		bool SaveConfig( std::string );
#endif
		bool RegisterConfigValue( std::string, int );
		bool RegisterConfigValue( std::string, std::string );
		bool RegisterConfigValue( std::string, double );
		std::string _User, _Password, _UserAgent;
		JSON _Table;

	private:
		void Update( );
		void Fetch( );
		std::string _URL, _Location, _Post, _Config, _Key, _IV;
	};
#else
	class CWebConfig
	{
	public:
		CWebConfig();
#ifndef FRAME_LOCALCONF
#ifdef FRAME_NETWORK 
		CWebConfig(std::string, std::string, std::string, std::string, std::string);
#endif
#endif
		double GetConfigValue(int);

		bool LoadConfig(std::string);
		bool SaveConfig(std::string);

		bool RegisterConfigValue(int, double);
		std::string _User, _Password, _UserAgent;
		void ExportUMapToJSON();
		void ImportJSON();
		JSON _Table;
		std::unordered_map<int, double> uMap;
	private:
		void Update();
		void Fetch();
		std::string _URL, _Location, _Post, _Config, _Key, _IV;


	};
#endif
}

#endif

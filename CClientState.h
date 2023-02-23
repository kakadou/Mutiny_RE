#pragma once
#include "inetmsghandler.h"
#include "utlvector.h"
struct ClientClass;
class INetChannelInfo;

#define STEAM_KEYSIZE 2048 // max size needed to contain a steam authentication key (both server and client)

class CEventInfo
{
public:
	enum
	{
		EVENT_INDEX_BITS = 8,
		EVENT_DATA_LEN_BITS = 11,
		MAX_EVENT_DATA = 192
	};

	short classID;
	float fire_delay;
	const void *pSendTable;
	const ClientClass *pClientClass;
	int bits;
	unsigned char *pData;
	int flags;
	char pad[0x18];
	CEventInfo *pNextEvent;
};

class CNetworkStringTableContainer /* : public INetworkStringTableContainer*/
{
public:
	bool m_bAllowCreation; // creat guard Guard
	int m_nTickCount; // current tick
	bool m_bLocked; // currently locked?
	bool m_bEnableRollback; // enables rollback feature

	CUtlVector< class CNetworkStringTable * > m_Tables; // the string tables
};



class CBaseClientState 
{
public:
	std::byte        pad0[0x9C];                //0x0000
	INetChannel* m_pNetChannel;            //0x009C
	int                m_nChallengeNr;            //0x00A0
	std::byte        pad1[0x64];                //0x00A4
	int                m_nSignonState;            //0x0108
	std::byte        pad2[0x8];                //0x010C
	float            m_flNextCmdTime;            //0x0114
	int                m_nServerCount;            //0x0118
	int                m_nCurrentSequence;        //0x011C
	char _0x0120[4];
	__int32 m_iClockDriftMgr; //0x0124 
	char _0x0128[68];
	__int32 m_nServerTick; //0x016C 
	__int32 m_nClientTick; //0x0170 
	int                m_nDeltaTick;                //0x0174
	bool            bPaused;                //0x0178
	std::byte        pad4[0x7];                //0x0179
	int                iViewEntity;            //0x0180
	int                iPlayerSlot;            //0x0184
	char            szLevelName[260];        //0x0188
	char            szLevelNameShort[80];    //0x028C
	char            szGroupName[80];        //0x02DC
	std::byte        pad5[0x5C];                //0x032C
	int                m_nMaxClients;            //0x0388
	std::byte        pad6[0x4984];            //0x038C
	float            flLastServerTickTime;    //0x4D10
	bool            bInSimulation;            //0x4D14
	std::byte        pad7[0xB];                //0x4D15
	int                iOldTickcount;            //0x4D18
	float            flTickRemainder;        //0x4D1C
	float            flFrameTime;            //0x4D20
	int                lastoutgoingcommand;    //0x4D38
	int                chokedcommands;        //0x4D30
	int                last_command_ack;        //0x4D2C
	int                command_ack;            //0x4D30
	int                m_nSoundSequence;            
	int                command_ack_servertickcount;
	std::byte        pad8[76];                
	Vector            angViewPoint;            
	std::byte        pad9[0xD0];                

};

class CClientState : public CBaseClientState /*, public CClientFrameManager*/
{
public:
	void SetReservationCookie(unsigned long long cookie);
};

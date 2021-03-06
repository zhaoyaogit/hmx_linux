#include "Player.h"
#include "SrvCoreIncludes.h"

Player::Player(zSession* _session)
{
	bChating = false;
	accid = charCount = keytime = 0;
	bzero(charIDList,sizeof(charIDList));
	bzero(keymd5,sizeof(keymd5));
	this->id = _session->id;
	session = _session;
}


Player::~Player()
{
	
}

void Player::Update(const zTaskTimer* timer)
{
	
}


void Player::SendMsg(NetMsgSS* pMsg ,int32 nSize)
{
	// 加密处理 
	static char arrUnBuffer[65536];
	static char arrEnBuffer[65536];
	int nCHeadSize = sizeof(NetMsgC);
	int nSHeadSize = sizeof(NetMsgSS);
	int nCSize = nSize - (nSHeadSize - nCHeadSize);
	memcpy(&arrUnBuffer[0], pMsg, nSize);
	memcpy(&arrEnBuffer[0], &arrUnBuffer[0], nCHeadSize);
	memcpy(&arrEnBuffer[nCHeadSize], &arrUnBuffer[nSHeadSize], nSize - nSHeadSize);
	zEncrypt::xorCode(nCSize, session->encrypt, arrEnBuffer, nCSize);
	session->socket->ParkMsg((NetMsgSS*)&arrEnBuffer[0], nCSize);
	session->socket->SendMsg();
}



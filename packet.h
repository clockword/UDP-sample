#pragma once

#pragma pack(push, 1)

typedef struct _tgPACKETHEADER
{
	unsigned int id;
	unsigned int size;
	_tgPACKETHEADER(unsigned int id, unsigned int size) { this->id = id; this->size = size; }
}PACKETHEADER, *LPPACKETHEADER;

#define PKT_SERVERCHARMOVE	0xa0000100
typedef struct _tgSERVERCHARMOVE : public PACKETHEADER
{
	int curX;
	int curY;
	float count;
	int ballX;
	int ballY;
	int serverScore;
	int clientScore;

	_tgSERVERCHARMOVE() : PACKETHEADER(PKT_SERVERCHARMOVE, sizeof(SERVERCHARMOVE)) {}
}SERVERCHARMOVE, *LPSERVERCHARMOVE;

#define PKT_CLIENTCHARMOVE 0xc0000010
typedef struct _tgCLIENTCHARMOVE : public PACKETHEADER
{
	int curX;
	int curY;

	_tgCLIENTCHARMOVE() : PACKETHEADER(PKT_CLIENTCHARMOVE, sizeof(CLIENTCHARMOVE)) {}
}CLIENTCHARMOVE, * LPCLIENTCHARMOVE;

#define PKT_LOGIN		0xb0000001
typedef struct _tgLOGIN : public PACKETHEADER
{
	bool active;
	_tgLOGIN() : PACKETHEADER(PKT_LOGIN, sizeof(LOGIN)) {}
}LOGIN, *LPLOGIN;

#pragma pack(pop)
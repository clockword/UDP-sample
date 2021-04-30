#pragma once

#pragma pack(push, 1)

typedef struct _tgPACKETHEADER
{
	unsigned int id;
	unsigned int size;
	_tgPACKETHEADER(unsigned int id, unsigned int size) { this->id = id; this->size = size; }
}PACKETHEADER, *LPPACKETHEADER;

#define PKT_CHARMOVE	0xa0000100
typedef struct _tgCHARMOVE : public PACKETHEADER
{
	int curX;
	int curY;
	float count;
	int ballX;
	int ballY;
	_tgCHARMOVE() : PACKETHEADER(PKT_CHARMOVE, sizeof(CHARMOVE)) {}
}CHARMOVE, *LPCHARMOVE;

#define PKT_LOGIN		0xb0000001
typedef struct _tgLOGIN : public PACKETHEADER
{
	bool active;
	_tgLOGIN() : PACKETHEADER(PKT_LOGIN, sizeof(LOGIN)) {}
}LOGIN, *LPLOGIN;

#pragma pack(pop)
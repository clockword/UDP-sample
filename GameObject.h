#pragma once

#include <string>
#include <Windows.h>

#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
using namespace Gdiplus;

enum ANIKIND
{
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3
};

class GameObject
{
private:
	Image* m_image;

	Rect **m_aniRect;
	DWORD m_aniKind;
	DWORD m_aniKindMax;
	DWORD*m_aniIndex;
	DWORD*m_aniIndexMax;
	DWORD*m_aniInterval;
	DWORD*m_aniIntervalMax;

	int m_x;
	int m_y;
	int m_xCenter;
	int m_yCenter;
protected:
	void SetAniKind(ANIKIND kind) { m_aniKind = (DWORD)kind; }
	void SetAniKind(DWORD kind) { m_aniKind = kind; }
	ANIKIND GetAniKind() { return (ANIKIND)m_aniKind; }
	void SetCenter(int x, int y);
	void MoveTo(int x, int y);
	void Translate(int x, int y);

	void UpdateAnim(DWORD tick);
	void Draw(Graphics* g);
public:
	GameObject();
	virtual ~GameObject();

	void SetFile(std::string filename);
	void SetImage(Image* image);
	void SetLocation(int x, int y);

	virtual void Update(Graphics* g, DWORD tick);
};


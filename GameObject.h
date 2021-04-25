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
	float m_sizeX;
	float m_sizeY;
	bool m_active;

	ColorMatrix m_imageColor;

	std::string m_tag;

protected:
	void SetAniKind(ANIKIND kind) { m_aniKind = (DWORD)kind; }
	void SetAniKind(DWORD kind) { m_aniKind = kind; }
	ANIKIND GetAniKind() { return (ANIKIND)m_aniKind; }
	void SetCenter(int x, int y);
	void MoveTo(int x, int y);
	void MoveBy(int x, int y);
	void SetSize(float x, float y);
	void SetActive(bool active) { m_active = active; }
	bool GetActive() { return m_active; }
	Point GetPosition() { return Point(m_x, m_y); }
	Rect GetOriginalImageRect();
	Rect GetImageRect();
	void SetImageColor(ColorMatrix color) { m_imageColor = color; }
	ColorMatrix GetImageColor() { return m_imageColor; }

	void UpdateAnim(DWORD tick);
	virtual void Draw(Graphics* g);
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init() {}

	void SetTag(std::string tag) { m_tag = tag; }
	std::string GetTag() { return m_tag; }

	void SetFile(std::string filename);
	void SetImage(Image* image);
	virtual void SetCollider(std::string filename) {}
	void SetLocation(int x, int y);

	virtual void Update(Graphics* g, DWORD tick);
};


#pragma once

#include <string>
#include <Windows.h>

#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
using namespace Gdiplus;

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

	void* m_vpLevel;

	int m_x;
	int m_y;
	int m_xCenter;
	int m_yCenter;
	float m_sizeX;
	float m_sizeY;
	bool m_active;

	ColorMatrix m_imageColor;

	std::string m_tag;
	std::string m_name;

	SizeF m_imgScale;

protected:
	void SetAniKind(DWORD kind) { m_aniKind = kind; }
	DWORD GetAniKind() { return m_aniKind; }
	void SetCenter(int x, int y);
	void MoveTo(int x, int y);
	void MoveBy(int x, int y);
	Rect GetOriginalImageRect();
	Rect GetImageRect();
	void SetImageColor(ColorMatrix color) { m_imageColor = color; }
	ColorMatrix GetImageColor() { return m_imageColor; }
	Size GetSize() { return Size(m_sizeX, m_sizeY); }

	void UpdateAnim(DWORD tick);
	virtual void Draw(Graphics* g);
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init() {}

	void SetTag(std::string tag) { m_tag = tag; }
	std::string GetTag() { return m_tag; }
	void SetActive(bool active) { m_active = active; }
	bool GetActive() { return m_active; }
	Point GetPosition() { return Point(m_x, m_y); }
	void SetPosition(int x, int y);
	void SetPosition(Point position);
	void SetSize(float x, float y);
	void SetScale(SizeF scale) { m_imgScale = scale; }
	SizeF GetScale() { return m_imgScale; }
	void SetName(std::string name) { m_name = name; }
	std::string GetName() { return m_name; }
	void SetLevel(void* level) { m_vpLevel = level; }
	void* GetLevel() { return m_vpLevel; }

	void SetFile(std::string filename);
	void SetImage(Image* image);
	virtual void SetCollider(std::string filename) {}

	virtual void Update(Graphics* g, DWORD tick);
};


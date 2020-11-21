#include "GameObject.h"

GameObject::GameObject()
{
	m_image = nullptr;

	m_aniRect = nullptr;
	m_aniKind = 0;
	m_aniKindMax = 0;
	m_aniIndex = nullptr;
	m_aniIndexMax = nullptr;
	m_aniInterval = nullptr;
	m_aniIntervalMax = nullptr;

	m_x = 0;
	m_y = 0;
	m_xCenter = 0;
	m_yCenter = 0;
}

GameObject::~GameObject()
{
	m_image = nullptr;

	if (m_aniRect != nullptr)
	{
		for (DWORD i = 0; i < m_aniKindMax; i++)
			delete[] m_aniRect[i];
		delete[] m_aniRect;
	}

	if (m_aniIndex != nullptr)
		delete[] m_aniIndex;
	if (m_aniIndexMax != nullptr)
		delete[] m_aniIndexMax;
	if (m_aniInterval != nullptr)
		delete[] m_aniInterval;
	if (m_aniIntervalMax != nullptr)
		delete[] m_aniIntervalMax;
}

void GameObject::SetFile(std::string filename)
{
	FILE* file = nullptr;

	std::string path = "./Resource/Anim/" + filename + ".txt";

	fopen_s(&file, path.c_str(), "rt");

	fscanf_s(file, "%d", &m_aniKindMax);
	m_aniRect = new Rect * [m_aniKindMax];
	m_aniIndex = new DWORD[m_aniKindMax];
	m_aniIndexMax = new DWORD[m_aniKindMax];
	m_aniInterval = new DWORD[m_aniKindMax];
	m_aniIntervalMax = new DWORD[m_aniKindMax];

	for (DWORD i = 0; i < m_aniKindMax; i++)
	{
		m_aniIndex[i] = 0;
		m_aniInterval[i] = 0;
		DWORD kind;
		fscanf_s(file, "%d %d %d", &kind, &m_aniIndexMax[i], &m_aniIntervalMax[i]);
		m_aniRect[i] = new Rect[m_aniIndexMax[i]];
		for (DWORD j = 0; j < m_aniIndexMax[i]; j++)
		{
			fscanf_s(file, "%d %d %d %d", &m_aniRect[i][j].X, &m_aniRect[i][j].Y,
				&m_aniRect[i][j].Width, &m_aniRect[i][j].Height);
		}
	}

	fclose(file);
}

void GameObject::SetImage(Image* image)
{
	m_image = image;
	SetCenter((int)(image->GetWidth() * 0.5), (int)(image->GetHeight() * 0.5));
}

void GameObject::SetLocation(int x, int y)
{
	m_x = x;
	m_y = y;
}

void GameObject::Update(Graphics* g, DWORD tick)
{
	UpdateAnim(tick);
	Draw(g);
}

void GameObject::UpdateAnim(DWORD tick)
{
	m_aniInterval[m_aniKind] += tick;

	if (m_aniInterval[m_aniKind] >= m_aniIntervalMax[m_aniKind])
	{
		m_aniInterval[m_aniKind] = 0;
		m_aniIndex[m_aniKind]++;
		if (m_aniIndex[m_aniKind] >= m_aniIndexMax[m_aniKind])
		{
			m_aniIndex[m_aniKind] = 0;
		}
	}
}

void GameObject::Draw(Graphics * g)
{
	int x = m_x - m_xCenter;
	int y = m_y - m_yCenter;

	g->DrawImage(m_image, x, y,
		m_aniRect[m_aniKind][m_aniIndex[m_aniKind]].X,
		m_aniRect[m_aniKind][m_aniIndex[m_aniKind]].Y,
		m_aniRect[m_aniKind][m_aniIndex[m_aniKind]].Width,
		m_aniRect[m_aniKind][m_aniIndex[m_aniKind]].Height,
		Gdiplus::UnitPixel);
}

void GameObject::SetCenter(int x, int y)
{
	m_xCenter = x;
	m_yCenter = y;
}

void GameObject::MoveTo(int x, int y)
{
	m_x = x;
	m_y = y;
}

void GameObject::Translate(int x, int y)
{
	m_x += x;
	m_y += y;
}
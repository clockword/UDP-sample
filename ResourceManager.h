#pragma once

#include <Windows.h>
#include <map>
#include <string>

//gdiplus must need to include Windows.h
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
using namespace Gdiplus;

class ResourceManager
{
private:
	static std::map<std::string, Image*> m_img;
public:
	static Image* LoadImage_(std::string name);
	static Image* GetImage(std::string key);
	static void DeleteImages();
};


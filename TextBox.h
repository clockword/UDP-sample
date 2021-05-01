#pragma once

#include "Button.h"
#include <iostream>

class TextBox : public Button
{
private:
	bool m_typeable;
	int m_textLimit;

protected:
	virtual void MouseWork();
	void ImageColorProcess();

public:
	TextBox() : Button(), m_typeable(false) {}
	virtual ~TextBox() {}

	virtual void OnMouseButtonDown(int x, int y);
	virtual void OnMouseButtonUp(int x, int y);
	void OnKeyboardInput(char ch);

	void SetTextLimit(int limit) { m_textLimit = limit; }

	virtual void Update(Graphics* g, DWORD tick);
};


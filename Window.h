#ifndef _WINDOW_H
#define _WINDOW_H

#include "System.h"

//C Runtime Header Files
#ifndef _WINDOWS_
#include<Windows.h>
#endif

//Additional Include Files
#ifndef _CONTEXT_H
#include"context.h"
#endif // !_CONTEXT_H
#ifndef _STRING_H
#include "string.h"
#endif // !_STRING_H



//structs
struct WindowData : public SystemData
{
	WindowData();
	WindowData(int w, int h, const std::tstring& title = _T("LightEngine V1.0"), int b = 32, bool fs = false);

	int width;
	int height;

	int bits;

	std::tstring windowTitle;

	bool fullscreen;
};

struct ResizeData
{
	ResizeData();
	ResizeData(bool resize, int nw, int nh);

	bool mustResize;

	int newWidth;
	int newHeight;

};

class Window :public System
{
	friend class Engine;

public:
	int GetWidth();
	int GetHeight();

	HWND GetWindowHandle() { return m_hWindow; }
	HDC GetDeviceContext() { return m_hDC; }
	HINSTANCE GetInstance() { return m_hInst; }

	ResizeData& GetResizeData() { return m_ResizeData; }

	LRESULT HandleEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	Window(const WindowData& data);
	virtual ~Window();

	virtual bool Initialize();
	virtual bool Update(Context& context);
	virtual bool ShutDown();

private:
	bool CenterWindow();

	

	//members
	HWND m_hWindow;
	HDC m_hDC;
	HINSTANCE m_hInst;

	int m_Width;
	int m_Height;

	byte m_Bits;

	bool m_bFullScreen;

	ResizeData m_ResizeData;

	std::tstring m_Title;


};

#endif // !_WINDOW_H
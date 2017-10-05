#include "Window.h"

//include "Logger.h"

WindowData::WindowData():SystemData(SystemType::Sys_Invalid),
width(-1),
height(-1),
bits(-1),
windowTitle(_T("")),
fullscreen(false)
{}

WindowData::WindowData(int w, int h, const std::tstring& title = _T("LightEngine V1.0"), int b = 32, bool fs = false)
:SystemData(SystemType::Sys_Window),
width(w),
height(h),
bits(b),
windowTitle(title),
fullscreen(fs)
{}

ResizeData::ResizeData()
	:mustResize(false),
	newWidth(-1),
	newHeight(-1)
{

}
ResizeData::ResizeData(bool resize,int nw,int nh)
	:mustResize(resize),
	newWidth(nw),
	newHeight(nh)
{

}


Window::Window(const WindowData& data)
:System(data),
m_hWindow(NULL),
m_hDC(NULL),
m_hInst(NULL),
m_Widht(data.width),
m_Height(data.height),
m_Bits(data.bits),
m_bFullScreen(data.fullscreen),
m_Title(data.windowTitle),
m_ResizeData()
{
}


Window::~Window()
{
}

bool Window::Initialize() {

}
bool Window::Update(Context& context) {

}
bool Window::ShutDown() {

}
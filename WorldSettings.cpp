#include "WorldSettings.h"



WorldSettings::WorldSettings()
	:m_worldSettings()
{
	m_worldSettings.windowWidth = 1280;
	m_worldSettings.windowHeight = 720;
	m_worldSettings.windowTitle = _T("LightEngine v1.5");

}
WorldSettings::~WorldSettings()
{
}

void WorldSettings::setWindowWidth(int width)
{
	m_worldSettings.windowWidth = width;
}
void WorldSettings::setWindowHeight(int height)
{
	m_worldSettings.windowHeight = height;
}

void WorldSettings::setWindowTitle(const std::tstring& title)
{
	m_worldSettings.windowTitle = title;
}
void WorldSettings::setStartSceneName(const std::tstring& name)
{
	m_worldSettings.startSceneName = name;
}
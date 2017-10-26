#ifndef _WORLDSETTINGS_H
#define _WORLDSETTINGS_H

#ifndef _STRING_H
#include"string.h"
#endif // !_STRING_H


struct WorldSettingsData
{
	int windowWidth;
	int windowHeight;

	std::tstring windowTitle;
	std::tstring startSceneName;
};

class WorldSettings
{
public:
	WorldSettings();
	~WorldSettings();

	void setWindowWidth(int width);
	void setWindowHeight(int height);

	void setWindowTitle(const std::tstring& title);
	void setStartSceneName(const std::tstring& name);

	int getWindowWidth()const { return m_worldSettings.windowWidth; }
	int getWindowHeight()const { return m_worldSettings.windowHeight; }

	const std::tstring& getWindowTitle() const { return m_worldSettings.windowTitle; }
	const std::tstring& getStartSceneName() const { return m_worldSettings.startSceneName; }

	const WorldSettingsData& getWorldSettings() const { m_worldSettings; }
private:
	WorldSettingsData m_worldSettings;
};

#endif // !_WORLDSETTINGS_H

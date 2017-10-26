#include "SceneFactory.h"
#include "Scene.h"

#include "Logger.h"

std::map<std::tstring, Scene*>* SceneFactory::map = nullptr;

SceneFactory::SceneFactory()
{
}


SceneFactory::~SceneFactory()
{
	SafeDelete(map);
}

Scene* SceneFactory::CreateObject(const std::tstring& s) 
{
	std::map<std::tstring, Scene*>::iterator it = GetMap()->find(s);
	if (it == GetMap()->end())
	{
	Logger::log(_T("Could not find the given scene with name: ")+s,LOGTYPE_WARNING,false);
		return nullptr;
	}

	return (*it).second;

}
void SceneFactory::ClearScenes() 
{
	for (std::pair<std::tstring, Scene*> pair : *GetMap())
		SafeDelete(pair.second);

	GetMap()->clear();
}

std::map<std::tstring, Scene*>* SceneFactory::GetMap()
{
	if (!map)
		map = new std::map<std::tstring, Scene*>;

	return map;
}
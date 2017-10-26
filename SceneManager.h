#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H

//C runtime header files
#ifndef _MAP_
#include<map>
#endif // !_MAP_

//Additional include files
#include "Singleton.h"

#ifndef _CONTEXT_H
#include "context.h"
#endif // !_CONTEXT_H

#ifndef _STRING_H
#include"string.h"
#endif // !_STRING_H

//Forward Decleration
class Scene;
class LoadingScene;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	bool Initialize();
	bool LoadContent();
	bool Update(Context& context);
	bool Draw(Context& context);
	bool ShutDown();

	bool AddScene(Scene* scene);
	bool RemoveScene(const std::tstring& name);

	Scene* FindScene(const std::tstring& name);
	Scene* GetActiveScene();

	void ClearScene();
	void SetActiveScene(const std::tstring& name);

protected:
	std::map<std::tstring, Scene*> m_mapScenes;
	Scene* m_pActiveScene;
	LoadingScene* m_pLoadingScene;

};
 
#endif // !_SCENEMANAGER_H
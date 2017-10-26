#include "SceneManager.h"

#include "Logger.h"

#include "SceneFactory.h"
#include "Scene.h"
//#include "LoadingScene.h"

//#ifndef _CONSTANTS_H
//#include "constants.h"
//#endif // !_CONSTANTS_H


SceneManager::SceneManager()
	:m_pActiveScene(nullptr)
	, m_pLoadingScene(nullptr)
{
}
SceneManager::~SceneManager()
{
}

bool SceneManager::Initialize()
{
	if (m_pActiveScene)
	{
		if (!m_pActiveScene->IsInitialized())
		{
			if (!m_pActiveScene->Initialize())
				return false;
			m_pActiveScene->SetInitialized();
			if (!m_pActiveScene->PostInitialize())
				return false;
			m_pActiveScene->SetPostInitialized();
		}
	}
	return true;
}
bool SceneManager::LoadContent()
{
	if (m_pActiveScene)
	{
		if (!m_pActiveScene->IsContentLoaded())
		{
			if (!m_pActiveScene->LoadContent())
				return false;
			m_pActiveScene->SetInitialized();
			if (!m_pActiveScene->PostLoadContent())
				return false;
			m_pActiveScene->SetPostContentLoaded();
		}
	}
	return true;
}
bool SceneManager::Update(Context& context)
{
	if (m_pActiveScene)
	{
		if (!m_pActiveScene->IsConstructed())
			return true;
		return m_pActiveScene->Update(context);
	}
	return true;
}
bool SceneManager::Draw(Context& context)
{
	if (m_pActiveScene)
	{
		if (!m_pActiveScene->IsConstructed())
			return true;
		if (!m_pActiveScene->Draw(context))
			return false;
		if (!m_pActiveScene->DrawUI(context))
			return false;
	}
	return true;
}
bool SceneManager::ShutDown()
{
	if (m_pActiveScene)
		return m_pActiveScene->ShutDown();

	return true;
}

bool SceneManager::AddScene(Scene* scene)
{
	std::map<std::tstring, Scene*>::iterator it = m_mapScenes.find(scene->GetName());
	if (it == m_mapScenes.end()) 
	{
		m_mapScenes.insert(std::pair<std::tstring, Scene*>(scene->GetName(), scene));
		return true;
	}
	Logger::log(_T("Scenealready exists with name: ") + scene->GetName(), LOGTYPE_WARNING, false);

	return false;
}
bool SceneManager::RemoveScene(const std::tstring& name)
{
	std::map<std::tstring, Scene*>::iterator it = m_mapScenes.find(name);
	if (it != m_mapScenes.end())
	{
		m_mapScenes.erase(it);

		Logger::log(_T("Clear content of the scene"),LOGTYPE_TODO,false);
		return true;
	}
	Logger::log(_T("Couldnot find scene wtih given name: ")+name, LOGTYPE_TODO, false);
	return false;
}

Scene* SceneManager::FindScene(const std::tstring& name)
{
	std::map<std::tstring, Scene*>::iterator it = m_mapScenes.find(name);
	if (it != m_mapScenes.end())
		return (*it).second;
	Logger::log(_T("Couldnot find scene wtih given name: ") + name, LOGTYPE_TODO, false);
	return nullptr;

}
Scene* SceneManager::GetActiveScene()
{
	Logger::log(_T("Take the loading scene into account"), LOGTYPE_TODO, false);
	return m_pActiveScene;
}

void SceneManager::ClearScene()
{
	SceneFactory::ClearScenes();

	m_mapScenes.clear();
}
void SceneManager::SetActiveScene(const std::tstring& name)
{
	Scene* newScene = this->FindScene(name);
	if (newScene) {
		Scene* ppreviousScene=m_pActiveScene;

		m_pActiveScene = newScene;
		m_pActiveScene->Activate();
		if (ppreviousScene)
			ppreviousScene->DeActivate();
	}

	Logger::log(_T("Take the loading scene into account"), LOGTYPE_TODO, false);
}
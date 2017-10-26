#include "GameLogic.h"

#include"Logger.h"
#include "SceneManager.h"
#include "WorldSettings.h"

#ifndef _DELETEMACROS_H
#include"deletemacros.h"
#endif // !_DELETEMACROS_H

GameLogicData::GameLogicData()
	:SystemData(_T("GameLogic"),SystemType::Sys_Logic)
{
}

GameLogic::GameLogic(const GameLogicData& data)
	:System(data)
{
	TYPE_REGISTER(GameLogic);
}
GameLogic::~GameLogic() 
{}

bool GameLogic::Initialize()
{
	System::Initialize();

	Singleton<SceneManager>::CreateInstance();
	Singleton<SceneManager>::GetInstance()->SetActiveScene(Singleton<WorldSettings>::GetInstance()->getStartSceneName());

	if (!Singleton<SceneManager>::GetInstance()->Initialize())
		return false;
	if (!Singleton<SceneManager>::GetInstance()->LoadContent())
		return false;

	Logger::log(_T("GameLogic Initialized"), LOGTYPE_INFO, false);
	return true;
}
bool GameLogic::Update(Context& context) 
{
	System::Update(context);

	if (!Singleton<SceneManager>::GetInstance()->Update(context))
		return false;

	return true;
}
bool GameLogic::Draw(Context& context)
{
	System::Draw(context);

	if (!Singleton<SceneManager>::GetInstance()->Draw(context))
		return false;

	return true;
}
bool GameLogic::ShutDown() 
{
	System::ShutDown();

	if (!Singleton<SceneManager>::GetInstance()->ShutDown())
	{
		Singleton<SceneManager>::DestroyInstance();
		return false;
	}
	Singleton<SceneManager>::DestroyInstance();
	return true;
}
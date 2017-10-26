#include "Engine.h"

//Additional include files
#include"Logger.h"
#include"Singleton.h"

#include"Renderer.h"

#include"System.h"
#include"Game.h"
#include"Window.h"
#include"Graphics.h"
#include"EngineTimer.h"
#include"GameLogic.h"

#include"GraphicsDeviceManager.h"
#include"WorldSettings.h"

#ifndef _DELETEMACRO_H
#include "deletemacros.h"
#endif
#ifndef _STRING_H
#include"string.h"
#endif


EngineState Engine::m_EngineState = EngineState::Invalid;

Engine::Engine()
{
	m_EngineState = EngineState::Constructing;
}


Engine::~Engine()
{
	m_EngineState = EngineState::Destroying;
}

//Public Methods
int Engine::RunLoop() {

	Context context;
	context.pRenderer = new Renderer();

	if (!this->Initialize())
	{
		Logger::log(_T("Initialization of the engine failed"), LOGTYPE_WARNING, false);
		return 0;
	}

	srand(GetTickCount());

	MSG msg = {};

	m_EngineState = EngineState::Running;

	while (msg.message != WM_QUIT && m_EngineState == EngineState::Running)
	{
		CheckResize();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		this->Update(context);
		this->Draw(context);
	}

	Logger::log(_T("Ending the program"), LOGTYPE_INFO, false);
	Logger::writeLogFile();

	if (!this->ShutDown())
	{
		Logger::log(_T("Shutdown of the engine failed"), LOGTYPE_WARNING, false);
		return 0;
	}

	return msg.wParam;
}

//Private Methods
int Engine::Initialize() {
	m_EngineState = EngineState::Initializing;

	Singleton<WorldSettings>::CreateInstance();
	Game* game = CreateGame();

	if (!game)
		return false;

	//Add some systems
	if (!AddSystem(new Window(WindowData(Singleton<WorldSettings>::GetInstance()->getWindowWidth(), Singleton<WorldSettings>::GetInstance()->getWindowHeight(), Singleton<WorldSettings>::GetInstance()->getWindowTitle()))))
		return false;
	if (!AddSystem(new Graphics(GraphicsData(GetSystem<Window>(SystemType::Sys_Window)))))
		return false;
	if (!AddSystem(new EngineTimer(EngineTimerData())))
		return false;
	if (!AddSystem(new GameLogic(GameLogicData())))
		return false;

	//Initialize the system
	if (!m_mapSystems[SystemType::Sys_Window]->Initialize())
		return false;
	if (!m_mapSystems[SystemType::Sys_Graphics]->Initialize())
		return false;
	if (!m_mapSystems[SystemType::Sys_EngineTimer]->Initialize())
		return false;
	if (!m_mapSystems[SystemType::Sys_Logic]->Initialize())
		return false;

	Singleton<GraphicsDeviceManager>::CreateInstance();
	Singleton<GraphicsDeviceManager>::GetInstance()->SetGraphics(GetSystem<Graphics>(SystemType::Sys_Graphics));

	return true;
}
int Engine::Draw(Context& context) {

	Graphics* graph = GetSystem<Graphics>(SystemType::Sys_Graphics);
	if (graph == nullptr)
		return false;

	GameLogic* logic = GetSystem<GameLogic>(SystemType::Sys_Logic);
	if (logic == nullptr)
		return false;

	graph->BeginDraw();

	logic->Draw(context);

	graph->EndDraw();

	return true;
}
int Engine::Update(Context& context) {
	for (std::pair<SystemType, System*> pSys : m_mapSystems) {
		if (!pSys.second)
			continue;
		pSys.second->Update(context);
	}
	return true;
}
int Engine::ShutDown() {
	m_EngineState = EngineState::ShuttingDown;

	for (std::pair<SystemType, System*> psys : m_mapSystems)
	{
		if (!psys.second->ShutDown()) {
			Logger::log(_T("Failed to shutdown system: " + psys.second->GetName()),LOGTYPE_WARNING,false);
			continue;
		}
		SafeDelete(psys.second);
	}
	Singleton<WorldSettings>::DestroyInstance();

	return true;
}

//Private methods
void Engine::CheckResize() {
	//Find the window system
	//if window has been found,check if it's valid
	//Get the resize data from the window
	Window* wnd = GetSystem<Window>(SystemType::Sys_Window);
	if (wnd&&wnd->GetResizeData().mustResize) {
		//if we need to resize
		//find the graphics system in the system map
		//if graphics has been found check if it is valid
		Graphics* graph = GetSystem<Graphics>(SystemType::Sys_Graphics);
		if (graph) {
			//fire the resize methods from the graphics class
			//set the resize data from the window back to false
			graph->OnResize(wnd->GetResizeData().newWidth, wnd->GetResizeData().newHeight);
			wnd->GetResizeData().mustResize = false;

		}
	}

}

int Engine::AddSystem(System* psys)
{
	auto element = m_mapSystems.insert(std::make_pair(psys->GetType(), psys));
	if (element.second)
		return true;

	return false;
}

Game* Engine::CreateGame() {
	if (!AddSystem(new Game(GameData())))
		return nullptr;
	Game* game = GetSystem<Game>(SystemType::Sys_Game);
	if (!game)
		return nullptr;

	/*if (!game->Initialize())
		return nullptr;*/

	return game;

}
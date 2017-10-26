#include "WinMain.h"

//Additional Include Files
#include"Engine.h"

#ifndef _STRING_H
#include"string.h"
#endif // !_STRING_H
#ifndef _IOSTREAM_H
#include "iostream.h"
#endif // !_IOSTREAM_H

#ifndef _LOGGER_H
#include"Logger.h"
#endif // !_LOGGER_H


#ifndef _GRAPHICSDEVICEMANAGER_H
#include "GraphicsDeviceManager.h"
#endif // !_GRAPHICSDEVICEMANAGER_H

#ifndef _SINGLETON_H
#include"Singleton.h"
#endif // !_SINGLETON_H


#ifndef _TYPECHECKER_H
#include "TypeChecker.h"
#endif // !_TYPECHECKER_H 

#ifndef _DELETEMACRO_H
#include "deletemacros.h"
#endif




#if defined(DEBUG)| defined(_DEBUG)
int _tmain(int argc, char* argv[]) {
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	Logger::log(_T("Start of the application"),LOGTYPE_INFO,false);
	//Logger::Log("Starting the program");

	//Run WinMain function
	WinMain((HINSTANCE)GetModuleHandle(NULL), 0, 0, SW_SHOW);



}
#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

#if defined (DEBUG) | defined (_DEBUG)
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	//Enable Run-Time memory leak check for debug builds.
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(0);
#endif
	//Create the engine
	Engine* pEngine=new Engine();

	//Kick of the game
	int result = pEngine->RunLoop();

	//Delete the engine
	SafeDelete(pEngine);

	//Destroy singleton
	Singleton<GraphicsDeviceManager>::DestroyInstance();
	Singleton<TypeChecker>::DestroyInstance();

	return result;



}

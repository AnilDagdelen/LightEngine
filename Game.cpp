#include "Game.h"


GameData::GameData() 
	:SystemData(_T("Game System"),SystemType::Sys_Game)
{
}
GameData::GameData(const std::tstring& name) 
:SystemData(name,SystemType::Sys_Game)
{
}

Game::Game(const GameData& data)
:System(data)
{
	m_SystemType = SystemType::Sys_Game;
}

Game::~Game()
{
}

#include "Game.h"


GameData::GameData() :SystemData()
{
}
GameData::GameData(const std::tstring& name, SystemType type) 
:SystemData(name,type)
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

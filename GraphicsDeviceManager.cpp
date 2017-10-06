#include "GraphicsDeviceManager.h"

#include"Graphics.h"

GraphicsDeviceManager* GraphicsDeviceManager::m_pInstance = nullptr;

GraphicsDeviceManager::GraphicsDeviceManager()
{
}


GraphicsDeviceManager::~GraphicsDeviceManager()
{
}

GraphicsDeviceManager* GraphicsDeviceManager::GetInstance() {
	if (m_pInstance == nullptr)
		m_pInstance = new GraphicsDeviceManager();
	return m_pInstance;
}
#ifndef _GRAPHICSDEVICEMANAGER_H
#define _GRAPHICSDEVICEMANAGER_H

//Forward Decleration
class Graphics;



class GraphicsDeviceManager
{
	friend class Engine;
public: 
	static GraphicsDeviceManager* m_pInstance;
	GraphicsDeviceManager(); 
	~GraphicsDeviceManager();  

	Graphics* GetGraphics() { return m_pGraphics; }

private: 
	void SetGraphics(Graphics* graphics) { m_pGraphics = graphics; }

	Graphics* m_pGraphics;
};


#endif // !_GRAPHICSDEVICEMANAGER_H
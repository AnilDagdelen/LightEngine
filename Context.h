#ifndef _CONTEXT_H
#define _CONTEXT_H

//Forward Declaration
class Window;
class Renderer;

//Defines
#define WINDOW (context.pWnd)
#define RENDERER (context.pRenderer)

struct Context
{
	float dTime;

	Window* pWnd;
	Renderer* pRenderer;

};
#endif // !_CONTEXT_H

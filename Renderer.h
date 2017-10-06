#ifndef _RENDERER_H
#define _RENDERER_H

//C Runtime Header files
#ifndef _WINDOWS_H
#include "Windows.h"
#endif // !_WINDOWS_H




//Additional include files
#ifndef _VECTOR2D_H
#include "Vector2D.h"
#endif
#ifndef _MATRIX2D_H
#include"Matrix2D.h"
#endif // !_MATRIX2D_H
#ifndef _RECT2D_H
#include"Rect2D.h"
#endif // !_RECT2D_H
#ifndef _COLOR_H
#include"color.h"
#endif

//Forward Decleration
//Class Image;

class Renderer
{
public:
	Renderer();
	~Renderer();


	//Methods
	/*void* operator new (size_t size);
	void operator delete(void* pdelete);*/

	void SetColor(const Color& c);
	void SetColor(float r, float g, float b, float a = 1.0f);

	void DrawRect(double left, double top, double width, double height,float lineWidth=0.5f);
	void DrawRect(const Vector2D& lefttop, const Vector2D& rightbottom, float lineWidth = 0.5f);
	void DrawRect(const Rect2D& rect, float lineWidth = 0.5f);

	void FillRect(double left, double top, double width, double height);
	void FillRect(const Vector2D& lefttop, const Vector2D& rightbottom);
	void FillRect(const Rect2D& rect);


};

#endif // !_RENDERER_H

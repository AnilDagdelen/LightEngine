#include "Renderer.h"

//Additional include files
#include"Graphics.h"
#include"GraphicsDeviceManager.h"

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}


void Renderer::SetColor(const Color& c){
	GRAPHICSDEVICEMANAGER->GetGraphics()->GetColorBrush()->SetColor(D2D1::ColorF(c.red, c.green, c.blue, c.alpha));
}
void Renderer::SetColor(float r, float g, float b, float a ){
	SetColor(Color(r, g, b, a));
}
	 
void Renderer::DrawRect(double left, double top, double width, double height, float lineWidth ){
	DrawRect(Rect2D(left, top, left + width, top + height), lineWidth);
}
void Renderer::DrawRect(const Vector2D& lefttop, const Vector2D& rightbottom, float lineWidth ){
	DrawRect(Rect2D(lefttop,rightbottom),lineWidth);
}
void Renderer::DrawRect(const Rect2D& rect, float lineWidth ){
	D2D1_RECT_F d2dRect = D2D1::RectF((FLOAT)rect.left, (FLOAT)rect.top, (FLOAT)rect.right, (FLOAT)rect.bottom);
	GRAPHICSDEVICEMANAGER->GetGraphics()->GetRenderTarget()->DrawRectangle(d2dRect, GRAPHICSDEVICEMANAGER->GetGraphics()->GetColorBrush(), lineWidth);

}
	 
void Renderer::FillRect(double left, double top, double width, double height){
	FillRect(Rect2D(left, top, left + width, top + height));

}
void Renderer::FillRect(const Vector2D& lefttop, const Vector2D& rightbottom){
	FillRect(Rect2D(lefttop, rightbottom));
}
void Renderer::FillRect(const Rect2D& rect){
	D2D1_RECT_F d2dRect = D2D1::RectF((FLOAT)rect.left, (FLOAT)rect.top,(FLOAT) rect.right, (FLOAT)rect.bottom);
	GRAPHICSDEVICEMANAGER->GetGraphics()->GetRenderTarget()->FillRectangle(d2dRect, GRAPHICSDEVICEMANAGER->GetGraphics()->GetColorBrush());

}

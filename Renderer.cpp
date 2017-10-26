#include "Renderer.h"

//Additional include files
#include"Graphics.h"
#include"GraphicsDeviceManager.h"


#include"Logger.h"

#ifndef _DELETEMACROS_H
#include "deletemacros.h"  
#endif // !_DEFINEMACROS

#ifndef _SINGLETON_H
#include"Singleton.h"
#endif // !_SINGLETON_H


Renderer::Renderer()
	:m_InterpolationMode(D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR)
{
}
Renderer::~Renderer()
{
}


void Renderer::SetColor(const Color& c) {
	Singleton<GraphicsDeviceManager>::GetInstance()->GetGraphics()->GetColorBrush()->SetColor(D2D1::ColorF(c.red, c.green, c.blue, c.alpha));
}
void Renderer::SetColor(float r, float g, float b, float a) {
	SetColor(Color(r, g, b, a));
}

void Renderer::DrawLine(const Vector2D& v1, const Vector2D& v2, float lineWidth) {
	D2D1_POINT_2F p1, p2;
	p1.x = (FLOAT)v1.x;	p1.y = (FLOAT)v1.y;
	p2.x = (FLOAT)v2.x;	p2.y = (FLOAT)v2.y;


	Singleton<GraphicsDeviceManager>::GetInstance()->GetGraphics()->GetRenderTarget()->DrawLine(p1, p2, Singleton<GraphicsDeviceManager>::GetInstance()->GetGraphics()->GetColorBrush(), lineWidth);

}
void Renderer::DrawLine(float x1, float y1, float x2, float y2, float lineWidth) {
	Vector2D v1(x1, y1);
	Vector2D v2(x2, y2);

	DrawLine(v1, v2, lineWidth);
}

void Renderer::DrawRect(double left, double top, double width, double height, float lineWidth) {
	DrawRect(Rect2D(left, top, left + width, top + height), lineWidth);
}
void Renderer::DrawRect(const Vector2D& lefttop, const Vector2D& rightbottom, float lineWidth) {
	DrawRect(Rect2D(lefttop, rightbottom), lineWidth);
}
void Renderer::DrawRect(const Rect2D& rect, float lineWidth) {
	D2D1_RECT_F d2dRect = D2D1::RectF((FLOAT)rect.left, (FLOAT)rect.top, (FLOAT)rect.right, (FLOAT)rect.bottom);
	Singleton<GraphicsDeviceManager>::GetInstance()->GetGraphics()->GetRenderTarget()->DrawRectangle(d2dRect, Singleton<GraphicsDeviceManager>::GetInstance()->GetGraphics()->GetColorBrush(), lineWidth);

}

void Renderer::DrawCircle(double xcenter, double ycenter, double r, float lineWidth) {
	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2((FLOAT)xcenter, (FLOAT)ycenter), (FLOAT)r, (FLOAT)r);
	Singleton<GraphicsDeviceManager>::GetInstance()->GetGraphics()->GetRenderTarget()->DrawEllipse(ellipse, Singleton<GraphicsDeviceManager>::GetInstance()->GetGraphics()->GetColorBrush(), lineWidth);
}
void Renderer::DrawCircle(const Vector2D& center, double r, float linewidth) {
	DrawCircle(center.x, center.y, r, linewidth);
}

void Renderer::DrawPolygon(const std::vector<Vector2D>& vecPoints, bool close , float lineWidth) {
	Vector2D* points = new Vector2D[(int)vecPoints.size()];
	for (int i = 0; i < (int)vecPoints.size(); ++i)
		points[i] = vecPoints[i];
	DrawPolygon(points, vecPoints.size(), close, lineWidth);
}
void Renderer::DrawPolygon(Vector2D* points, int size, bool close , float lineWidth) {
	//Do not draw an empty polygon
	if (size < 3)
		return;

	for (int countloop = 0; countloop < size - 1; ++countloop)
		DrawLine(points[countloop], points[countloop + 1], lineWidth);

	if (close)
		DrawLine(points[0], points[size - 1], lineWidth);

}

void Renderer::FillRect(double left, double top, double width, double height) {
	FillRect(Rect2D(left, top, left + width, top + height));

}
void Renderer::FillRect(const Vector2D& lefttop, const Vector2D& rightbottom) {
	FillRect(Rect2D(lefttop, rightbottom));
}
void Renderer::FillRect(const Rect2D& rect) {
	D2D1_RECT_F d2dRect = D2D1::RectF((FLOAT)rect.left, (FLOAT)rect.top, (FLOAT)rect.right, (FLOAT)rect.bottom);
	Singleton<GraphicsDeviceManager>::GetInstance()->GetGraphics()->GetRenderTarget()->FillRectangle(d2dRect, Singleton<GraphicsDeviceManager>::GetInstance()->GetGraphics()->GetColorBrush());

}

void Renderer::FillCircle(const Vector2D& center, double r) {
	FillCircle(center.x, center.y, r);
}
void Renderer::FillCircle(double xcenter, double ycenter, double r) {
	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2((FLOAT)xcenter, (FLOAT)ycenter), (FLOAT)r, (FLOAT)r);
	Singleton<GraphicsDeviceManager>::GetInstance()->GetGraphics()->GetRenderTarget()->FillEllipse(ellipse, Singleton<GraphicsDeviceManager>::GetInstance()->GetGraphics()->GetColorBrush());

}

void Renderer::FillPolygon(const std::vector<Vector2D>& vecPoints) {
	Vector2D* points = new Vector2D[(int)vecPoints.size()];
	for (int i = 0; i < (int)vecPoints.size(); ++i)
		points[i] = vecPoints[i];

	FillPolygon(points, vecPoints.size());
}
void Renderer::FillPolygon(Vector2D* points, int size) {
	if (size < 3)
		return;
	HRESULT hr;
	ID2D1PathGeometry* pGeometry=nullptr;
	hr = Singleton<GraphicsDeviceManager>::GetInstance()->GetGraphics()->GetD2DFactory()->CreatePathGeometry(&pGeometry);
	if (FAILED(hr)) {
		SafeRelease(pGeometry);
		Logger::log(_T("Failed to create path geometry"),LOGTYPE_WARNING,false);
		return;
	}

	//write to the path geometry using the geometry sink
	ID2D1GeometrySink* pGeometrySink = nullptr;
	hr = pGeometry->Open(&pGeometrySink);
	if (FAILED(hr)) {
		SafeRelease(pGeometrySink);
		SafeRelease(pGeometry);

		Logger::log(_T("Failed to create geometry sink"),LOGTYPE_WARNING,false);
		return;
	}
	if (SUCCEEDED(hr)) {
		pGeometrySink->BeginFigure(D2D1::Point2F((FLOAT)points[0].x, (FLOAT)points[0].y), D2D1_FIGURE_BEGIN_FILLED);
		for (int i = 0; i < size; i++)
			pGeometrySink->AddLine(D2D1::Point2F((FLOAT)points[i].x, (FLOAT)points[i].y));

		pGeometrySink->EndFigure(D2D1_FIGURE_END_CLOSED);

		hr = pGeometrySink->Close();
		SafeRelease(pGeometrySink);
	}

	if (SUCCEEDED(hr)) {
		Singleton<GraphicsDeviceManager>::GetInstance()->GetGraphics()->GetRenderTarget()->FillGeometry(pGeometry, Singleton<GraphicsDeviceManager>::GetInstance()->GetGraphics()->GetColorBrush());
		SafeRelease(pGeometry);
		return;
	}
	SafeRelease(pGeometry);

}

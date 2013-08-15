#pragma once
#include <array>
#include <xutility>
#include <wrl.h>
#include <d2d1.h>

using namespace Microsoft::WRL;
using namespace D2D1;
using namespace std;

class Ball
{
private:
	ColorF m_color;
	float m_radius;
	float m_posx, m_posy;
	float m_incrementx, m_incrementy;
	ComPtr<ID2D1GradientStopCollection> m_gradientstopcollection;
	ComPtr<ID2D1RadialGradientBrush> m_brush;

	void RecreateRadialGradientBrush(ComPtr<ID2D1HwndRenderTarget>& rendertarget);

public:
	Ball(ComPtr<ID2D1HwndRenderTarget>& rendertarget);
	~Ball(void);

	ColorF GetColor() const;
	float GetRadius() const;
	float GetX() const;
	float GetY() const;

	Ball *SetColor(ColorF color);
	Ball *SetRadius(float radius);
	Ball *SetPos(float posx, float posy);
	Ball *SetIncrementX(float increment);
	Ball *SetIncrementY(float increment);

	void Move();
	void Draw(ComPtr<ID2D1HwndRenderTarget>& rendertarget, const D2D1_POINT_2F & lightpos, bool recreatebrush);
};


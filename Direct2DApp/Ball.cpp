#include "Ball.h"


Ball::Ball(ComPtr<ID2D1HwndRenderTarget>& rendertarget)
	: m_color(ColorF::Black),
	m_radius(0.0f),
	m_posx(0.0f),
	m_posy(0.0f),
	m_incrementx(0.0f),
	m_incrementy(0.0f)
{}

Ball::~Ball(void) {}

void Ball::RecreateRadialGradientBrush(ComPtr<ID2D1HwndRenderTarget>& rendertarget)
{
	// Destroys previous 'GradientStopCollection' object and 'RadialBrush' object and
	//	recreates a new one
	array<D2D1_GRADIENT_STOP, 2U> GradientStops = { GradientStop(0.0f, ColorF(ColorF::White)), GradientStop(1.0f, m_color) };
	rendertarget->CreateGradientStopCollection(GradientStops.data(), GradientStops.size(), m_gradientstopcollection.ReleaseAndGetAddressOf());
	rendertarget->CreateRadialGradientBrush(RadialGradientBrushProperties(Point2F(), Point2F(-2.0f, -2.0f), m_radius, m_radius), m_gradientstopcollection.Get(), m_brush.ReleaseAndGetAddressOf());

	m_brush->SetRadiusX(m_radius);
	m_brush->SetRadiusY(m_radius);

	m_brush->SetCenter(Point2F(m_posx, m_posy));
}

ColorF Ball::GetColor() const {	return m_color; }
float Ball::GetRadius() const {	return m_radius; }
float Ball::GetX() const { return m_posx; }
float Ball::GetY() const { return m_posy; }
Ball *Ball::SetColor(ColorF color)
{
	m_color = color;
	
	return this;
}

Ball *Ball::SetRadius(float radius)
{
	m_radius = radius;

	return this;
}

Ball *Ball::SetPos(float posx, float posy)
{
	m_posx = posx;
	m_posy = posy;

	return this;
}

Ball *Ball::SetIncrementX(float increment)
{
	m_incrementx = increment;

	return this;
}

Ball *Ball::SetIncrementY(float increment)
{
	m_incrementy = increment;

	return this;
}

void Ball::Move()
{
	SetPos(m_posx + m_incrementx, m_posy + m_incrementy);
}

D2D1_POINT_2F CalculateLightPosOnBall(const D2D1_POINT_2F& lightpos)
{
	return lightpos;
}

void Ball::Draw(ComPtr<ID2D1HwndRenderTarget>& rendertarget, const D2D1_POINT_2F & lightpos, bool recreatebrush = false)
{
	if (recreatebrush || !m_brush)
		RecreateRadialGradientBrush(rendertarget);
	
	m_brush->SetGradientOriginOffset(CalculateLightPosOnBall(lightpos));

	D2D1_ELLIPSE circle = { Point2F(GetX(), GetY()), GetRadius(), GetRadius() };

	rendertarget->FillEllipse(circle, m_brush.Get());
}
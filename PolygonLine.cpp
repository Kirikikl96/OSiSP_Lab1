#include "stdafx.h"
#include "PolygonLine.h"


PolygonLine::PolygonLine()
{
}

PolygonLine::PolygonLine(COLORREF color, int weight, COLORREF brushColor) :PolygonShape(color, weight, brushColor)
{
}

PolygonLine::~PolygonLine()
{
}

void PolygonLine::Draw(HDC hdc, int weight)
{
	SetPen(hdc, weight);
	SelectObject(hdc, hPen);
	Polyline(hdc, points, pointsCount);
}

void PolygonLine::SetPoint(POINTS point)
{
	PolygonShape::SetPoint(point);
}

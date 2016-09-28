#include "stdafx.h"
#include "PolygonLineFactory.h"


PolygonLineFactory::PolygonLineFactory()
{
}


PolygonLineFactory::~PolygonLineFactory()
{
}

Shape* PolygonLineFactory::CreateShape(COLORREF color, int weight, COLORREF brushColor)
{
	return new PolygonLine(color, weight, brushColor);
}

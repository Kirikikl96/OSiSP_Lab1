#include "stdafx.h"
#include "LineFactory.h"


LineFactory::LineFactory()
{
}


LineFactory::~LineFactory()
{
}

Shape* LineFactory::CreateShape(COLORREF color, int weight, COLORREF brushColor)
{
	return new Line(color, weight, brushColor);
}

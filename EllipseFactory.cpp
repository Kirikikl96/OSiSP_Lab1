#include "stdafx.h"
#include "EllipseFactory.h"


EllipseFactory::EllipseFactory()
{
}


EllipseFactory::~EllipseFactory()
{
}

Shape* EllipseFactory::CreateShape(COLORREF color, int weight, COLORREF brushColor)
{
	return new EllipseShape(color, weight, brushColor);
}

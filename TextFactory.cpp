#include "stdafx.h"
#include "TextFactory.h"


TextFactory::TextFactory()
{
}


TextFactory::~TextFactory()
{
}

Shape* TextFactory::CreateShape(COLORREF color, int weight, COLORREF brushColor)
{
	return new Text(color, weight, brushColor);
}

#pragma once
class RectangleFactory : public ShapeFactory
{
public:
	RectangleFactory();
	~RectangleFactory();
	Shape* CreateShape(COLORREF, int, COLORREF);
};


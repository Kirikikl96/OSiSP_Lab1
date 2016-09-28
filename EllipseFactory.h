#pragma once
class EllipseFactory : public ShapeFactory
{
public:
	EllipseFactory();
	~EllipseFactory();
	Shape* CreateShape(COLORREF, int, COLORREF);
};


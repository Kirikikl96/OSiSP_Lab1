#pragma once
class PolygonShape :public Shape
{
public:
	PolygonShape();
	PolygonShape(COLORREF, int, COLORREF);
	~PolygonShape();
	void Draw(HDC, int);
	void SetPoint(POINTS);
protected:
	COLORREF polygonPenColor;
	int prevPointsCount, weight;
	void SetPen(HDC, int);
private:
	COLORREF polygonBrushColor;
	void SetBrush(HDC);
};


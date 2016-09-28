// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ��������� ����� ������������ ���������� �� ���������� Windows
// ����� ���������� Windows:
#include <windows.h>

// ����� ���������� C RunTime
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <commctrl.h>
#include <string.h>
#include <wchar.h>
#include <tchar.h>
#include <commdlg.h>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#ifndef __shapemodule_h__
#define __shapemodule_h__
#include "Shape.h"
#include "Line.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "Polygon.h"
#include "PolygonLine.h"
#include "Text.h"
#include "Pen.h"
#include "FileName.h"

#include "ShapeFactory.h"
#include "PolygonFactory.h"
#include "PolygonLineFactory.h"
#include "PenFactory.h"
#include "LineFactory.h"
#include "EllipseFactory.h"
#include "RectangleFactory.h"
#include "TextFactory.h"
#endif


// TODO: ���������� ����� ������ �� �������������� ���������, ����������� ��� ���������

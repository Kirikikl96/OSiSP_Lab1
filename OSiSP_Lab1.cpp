// OSiSP_Lab1.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "OSiSP_Lab1.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

int penColor, brushColor, weight = DEFAULT_WEIGHT;
float zoom = 1;
POINT mousePos, prevOrigin, origin;
POINTS startPoint, endPoint;
int currentShapeId;
Shape* currentShape;
bool isCreatePolygon, isFileChanged, isPrintSelected, isMoving;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_OSISP_LAB1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OSISP_LAB1));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OSISP_LAB1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_OSISP_LAB1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//creating and initialization toolbar
HWND CreateToolBar(HWND parent, HINSTANCE hInst)
{
	const int ImageListID = 0;
	const int numButtons = 10;
	const int iconSize = 16;

	DWORD buttonStyles = BTNS_AUTOSIZE;

	// Create the toolbar.
	HWND hWndTB = CreateWindowEx(WS_EX_WINDOWEDGE, TOOLBARCLASSNAME, NULL,
		WS_CHILD | CCS_TOP | TBSTYLE_FLAT | TBSTYLE_WRAPABLE, 0, 0, 0, 0,
		parent, NULL, hInst, NULL);
	if (hWndTB == NULL)
		return NULL;

	// Create the image list.
	HIMAGELIST hImgl = ImageList_Create(iconSize, iconSize,   // Dimensions of individual bitmaps.
		ILC_COLOR32 | ILC_MASK,   // Ensures transparent background.
		numButtons, 0);
	for (int i = 0; i < numButtons; i++)
		ImageList_AddIcon(hImgl, LoadIcon(hInst, MAKEINTRESOURCE(IDI_PENICON + i)));

	// Set the image list.
	SendMessage(hWndTB, TB_SETIMAGELIST, (WPARAM)ImageListID, (LPARAM)hImgl);

	// Load the button images.
	SendMessage(hWndTB, TB_LOADIMAGES, (WPARAM)IDB_STD_SMALL_COLOR, (LPARAM)HINST_COMMCTRL);

	// Initialize button info.
	// IDM_NEW, IDM_OPEN, and IDM_SAVE are application-defined command constants.

	TBBUTTON tbButtons[numButtons];
	std::vector<std::string> buttonsText = { "Карандаш","Линия","Прямоугольник","Эллипс","Многоугольник","Ломаная","Текст","Заливка","Толщина","Изменение цветов" };
	for (int i = 0; i < numButtons; i++)
	{
		tbButtons[i].iBitmap = i;
		tbButtons[i].fsStyle = buttonStyles;
		tbButtons[i].fsState = TBSTATE_ENABLED;
		tbButtons[i].iString = (INT_PTR)buttonsText[i].data();
		tbButtons[i].idCommand = IDM_PEN + i;
	}
	// Add buttons.
	SendMessage(hWndTB, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	SendMessage(hWndTB, TB_ADDBUTTONS, (WPARAM)numButtons, (LPARAM)&tbButtons);

	// Resize the toolbar, and then show it.
	ShowWindow(hWndTB, SW_SHOW);
	return hWndTB;
}

//creating and initialization trackbar
HWND CreateTrackBar(HWND hwndDlg, HINSTANCE hInst)
{
	InitCommonControls();
	HWND hWndTrackBar = CreateWindowEx(0, TRACKBAR_CLASS, "Trackbar Control", WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_ENABLESELRANGE | TBS_TRANSPARENTBKGND, 10, 20, 200, 30, hwndDlg, NULL, hInst, NULL);
	if (hWndTrackBar == NULL)
		return NULL;
	SendMessage(hWndTrackBar, TBM_SETRANGE, 0, (LPARAM)MAKELONG(0, DEFAULT_TRACKBAR_MAXSIZE));
	SendMessage(hWndTrackBar, TBM_SETPAGESIZE, 0, (LPARAM)DEFAULT_TRACKBAR_PAGESIZE);                  // new page size 
	SendMessage(hWndTrackBar, TBM_SETSEL, (WPARAM)FALSE, (LPARAM)MAKELONG(0, DEFAULT_TRACKBAR_MAXSIZE)); // redraw flag
	SendMessage(hWndTrackBar, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)weight);                   // redraw flag
	SetFocus(hWndTrackBar);
	return hWndTrackBar;
}

//change current zoom
void zoomIn(HWND hWnd, float currentZoom)
{
	if (((zoom * currentZoom) <= 8) && ((zoom * currentZoom) >= 0.25))
	{
		zoom *= currentZoom;
		InvalidateRect(hWnd, NULL, true);
	}
}

void MouseWheel(HWND hWnd, WPARAM wParam)
{
	WORD wParamLowWord = LOWORD(wParam);
	if ((wParamLowWord == MK_CONTROL) || (wParamLowWord == (MK_CONTROL | MK_SHIFT)))
	{
		WORD wheelDestiny = HIWORD(wParam);
		if (wheelDestiny > 65000)
			zoomIn(hWnd, 0.5);
		else
			zoomIn(hWnd, 2);
	}
}

void SetOriginTo(POINT newOrigin)
{
	prevOrigin = origin;
	origin = newOrigin;
}

void MouseMove(HWND hWnd, POINT prevMousePos, POINT currentMousePos)
{
	if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
	{
		endPoint.x = currentMousePos.x;
		endPoint.y = currentMousePos.y;
		if (currentShapeId != 0 && !isCreatePolygon && currentShape != NULL && currentShapeId != IDM_TEXT)
			currentShape->SetPoint(endPoint);
		InvalidateRect(hWnd, NULL, FALSE);
	}
	if (isMoving && (GetKeyState(VK_MBUTTON) & 0x100) != 0)
	{
		bool altPushed = (GetKeyState(VK_MENU) & 0x100) != 0;
		bool ctrlPushed = (GetKeyState(VK_CONTROL) & 0x100) != 0;
		bool shiftPushed = (GetKeyState(VK_SHIFT) & 0x100) != 0;
		if ((!shiftPushed && !altPushed && !ctrlPushed) || (shiftPushed && !altPushed && !ctrlPushed))
		{
			POINT prevOrigin = origin;
			POINT newOrigin;
			newOrigin.x = prevOrigin.x + (currentMousePos.x - prevMousePos.x);
			newOrigin.y = prevOrigin.y + (currentMousePos.y - prevMousePos.y);
			SetOriginTo(newOrigin);
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
}



//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
		HWND hWndTB = CreateToolBar(hWnd,hInst);
		SendMessage(hWndTB, TB_AUTOSIZE, NULL, NULL);
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

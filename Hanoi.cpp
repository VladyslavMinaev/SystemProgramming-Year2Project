#include <windows.h> // підключення бібліотеки з функціями API
#include "Header.h"
#include <ctime>
#include <fstream>
#include <string>

// Глобальні змінні:
#define IDM_CREATE 1230
HINSTANCE hInst; 	//Дескриптор програми	
LPCTSTR szWindowClass = L"QWERTY";
LPCTSTR szTitle = L"Game";
static SHORT x = 0;
static SHORT y = 0;
const int ShiftUp = 200; // сдвиг вверх
int *tower1 = new int[8]{ 1,2,3,4,5,6,7,8 };	//массив для башни №1
int *tower2 = new int[8]{ 0 };	//массив для башни №2
int *tower3 = new int[8]{ 0 };	//массив для башни №3
int raisedRing = 0; //поднятое кольцо
int indexArray;
static HPEN hPen, hPen1, hPen2, hPen3, hPen4, hPen5, hPen6, hPen7, hPen8, hPen9;
static HBRUSH hB, hB1, hB2, hB3, hB4, hB5, hB6, hB7, hB8, hB9;
bool tower = false;
int firstTime;
HWND hEdit;
std::string writeToFile;
// Попередній опис функцій

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HMENU hMenu, hMenuPopup;

// Основна програма 
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	hMenu = CreateMenu();
	hMenuPopup = CreateMenu();
	AppendMenu(hMenuPopup, MF_STRING, IDM_CREATE, L"&New game");
	AppendMenu(hMenuPopup, MF_STRING, IDM_CREATE + 1, L"&Result");
	AppendMenu(hMenu, MF_POPUP, (UINT)hMenuPopup, L"&Game");
	AppendMenu(hMenu, MF_POPUP, IDM_CREATE + 2, L"&Rules");

	MSG msg;

	// Реєстрація класу вікна 
	MyRegisterClass(hInstance);

	// Створення вікна програми
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	// Цикл обробки повідомлень
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW; 		//стиль вікна
	wcex.lpfnWndProc = (WNDPROC)WndProc; 		//віконна процедура
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; 			//дескриптор програми
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		//визначення іконки
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); 	//визначення курсору
	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW); //установка фону
	wcex.lpszMenuName = NULL; 				//визначення меню
	wcex.lpszClassName = szWindowClass; 		//ім’я класу
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex); 			//реєстрація класу вікна
}

// FUNCTION: InitInstance (HANDLE, int)
// Створює вікно програми і зберігає дескриптор програми в змінній hInst

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; //зберігає дескриптор додатка в змінній hInst
	hWnd = CreateWindow(szWindowClass, 	// ім’я класу вікна
		szTitle, 				// назва програми
		WS_DLGFRAME | WS_MINIMIZEBOX | WS_SYSMENU | WS_MAXIMIZE,			// стиль вікна
		0, 			// положення по Х	
		0,			// положення по Y	
		1500, 			// розмір по Х
		900, 			// розмір по Y
		NULL, 					// дескриптор батьківського вікна	
		hMenu, 					// дескриптор меню вікна
		hInstance, 				// дескриптор програми
		NULL); 				// параметри створення.

	if (!hWnd) 	//Якщо вікно не творилось, функція повертає FALSE
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow); 		//Показати вікно
	UpdateWindow(hWnd); 				//Оновити вікно
	return TRUE;
}

// FUNCTION: WndProc (HWND, unsigned, WORD, LONG)
// Віконна процедура. Приймає і обробляє всі повідомлення, що приходять в додаток


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;

	switch (message)
	{
	case WM_CREATE: 				//Повідомлення приходить при створенні вік-на
		hEdit = CreateWindow(L"edit", L"Enter your name",
			WS_CHILD | WS_VISIBLE | ES_CENTER,
			10, 50, 1480, 20,
			hWnd, NULL, hInst, NULL);
		break;

	case WM_PAINT: 				//Перемалювати вікно
		hdc = BeginPaint(hWnd, &ps); 	//Почати графічний вивід	
		GetClientRect(hWnd, &rt); 		//Область вікна для малювання


		hPen9 = CreatePen(BS_SOLID, 0, RGB(43, 255, 0));
		hB9 = CreateSolidBrush(RGB(43, 255, 0));


		hPen8 = CreatePen(BS_SOLID, 0, RGB(248, 6, 3));
		hB8 = CreateSolidBrush(RGB(248, 6, 3));


		hPen7 = CreatePen(BS_SOLID, 0, RGB(211, 139, 225));
		hB7 = CreateSolidBrush(RGB(211, 139, 225));


		hPen6 = CreatePen(BS_SOLID, 0, RGB(242, 112, 28));
		hB6 = CreateSolidBrush(RGB(242, 112, 28));


		hPen5 = CreatePen(BS_SOLID, 0, RGB(0, 55, 25));
		hB5 = CreateSolidBrush(RGB(0, 55, 25));


		hPen4 = CreatePen(BS_SOLID, 0, RGB(0, 108, 254));
		hB4 = CreateSolidBrush(RGB(0, 108, 254));


		hPen3 = CreatePen(BS_SOLID, 0, RGB(0, 124, 73));
		hB3 = CreateSolidBrush(RGB(0, 124, 73));


		hPen2 = CreatePen(BS_SOLID, 0, RGB(242, 234, 0));
		hB2 = CreateSolidBrush(RGB(242, 234, 0));


		hPen1 = CreatePen(BS_SOLID, 0, RGB(134, 5, 134));
		hB1 = CreateSolidBrush(RGB(134, 5, 134));


		if (tower)
		{
			SelectObject(hdc, hPen4);
			SelectObject(hdc, hB4);
			Rectangle(hdc, 0, 0, 1500, 450);
			SelectObject(hdc, hPen2);
			SelectObject(hdc, hB2);
			Rectangle(hdc, 0, 450, 1500, 900);
		}

		DeleteObject(hPen2);
		DeleteObject(hB2);

		DeleteObject(hPen4);
		DeleteObject(hB4);

		if (tower)
		{
			hPen4 = CreatePen(BS_SOLID, 0, RGB(10, 118, 264));
			hB4 = CreateSolidBrush(RGB(10, 118, 264));
		}
		else
		{
			hPen4 = CreatePen(BS_SOLID, 0, RGB(0, 108, 254));
			hB4 = CreateSolidBrush(RGB(0, 108, 254));
		}

		if (tower)
		{
			hPen2 = CreatePen(BS_SOLID, 0, RGB(252, 244, 10));
			hB2 = CreateSolidBrush(RGB(252, 244, 10));
		}
		else
		{
			hPen2 = CreatePen(BS_SOLID, 0, RGB(242, 234, 0));
			hB2 = CreateSolidBrush(RGB(242, 234, 0));
		}


		hPen = CreatePen(BS_SOLID, 0, RGB(227, 175, 112));
		hB = CreateSolidBrush(RGB(227, 175, 112));
		SelectObject(hdc, hPen);
		SelectObject(hdc, hB);
		Rectangle(hdc, 235, 390 - ShiftUp, 265, 820 - ShiftUp);	//столб №1
		Rectangle(hdc, 28, 800 - ShiftUp, 473, 830 - ShiftUp);
		SelectObject(hdc, hPen9);
		SelectObject(hdc, hB9);
		Rectangle(hdc, 735, 390 - ShiftUp, 765, 820 - ShiftUp);	//столб №2
		Rectangle(hdc, 528, 800 - ShiftUp, 973, 830 - ShiftUp);
		SelectObject(hdc, hPen);
		SelectObject(hdc, hB);
		Rectangle(hdc, 1235, 390 - ShiftUp, 1265, 820 - ShiftUp);	//столб №3
		Rectangle(hdc, 1028, 800 - ShiftUp, 1473, 830 - ShiftUp);

		switch (raisedRing) // когда кольцо в поднятом положении
		{
		case (1):
			SelectObject(hdc, hPen1);
			SelectObject(hdc, hB1);
			Rectangle(hdc, 713, 300 - ShiftUp, 788, 350 - ShiftUp);
			break;
		case (2):
			SelectObject(hdc, hPen2);
			SelectObject(hdc, hB2);
			Rectangle(hdc, 688, 300 - ShiftUp, 813, 350 - ShiftUp);
			break;
		case (3):
			SelectObject(hdc, hPen3);
			SelectObject(hdc, hB3);
			Rectangle(hdc, 663, 300 - ShiftUp, 838, 350 - ShiftUp);
			break;
		case (4):
			SelectObject(hdc, hPen4);
			SelectObject(hdc, hB4);
			Rectangle(hdc, 638, 300 - ShiftUp, 863, 350 - ShiftUp);

			break;
		case (5):
			SelectObject(hdc, hPen5);
			SelectObject(hdc, hB5);
			Rectangle(hdc, 613, 300 - ShiftUp, 888, 350 - ShiftUp);
			break;
		case (6):
			SelectObject(hdc, hPen6);
			SelectObject(hdc, hB6);
			Rectangle(hdc, 588, 300 - ShiftUp, 913, 350 - ShiftUp);
			break;
		case (7):
			SelectObject(hdc, hPen7);
			SelectObject(hdc, hB7);
			Rectangle(hdc, 563, 300 - ShiftUp, 938, 350 - ShiftUp);
			break;
		case (8):
			SelectObject(hdc, hPen8);
			SelectObject(hdc, hB8);
			Rectangle(hdc, 538, 300 - ShiftUp, 963, 350 - ShiftUp);
			break;
		}

		if (ArraySearch(tower1, 8, indexArray))
		{
			SelectObject(hdc, hPen8);
			SelectObject(hdc, hB8);
			indexArray = (indexArray + 1 - 8) * 50 - ShiftUp;
			Rectangle(hdc, 38, 750 + indexArray, 463, 800 + indexArray);
		}

		if (ArraySearch(tower1, 7, indexArray))
		{
			SelectObject(hdc, hPen7);
			SelectObject(hdc, hB7);
			indexArray = (indexArray + 1 - 7) * 50 - ShiftUp;
			Rectangle(hdc, 63, 700 + indexArray, 438, 750 + indexArray);
		}

		if (ArraySearch(tower1, 6, indexArray))
		{
			SelectObject(hdc, hPen6);
			SelectObject(hdc, hB6);
			indexArray = (indexArray + 1 - 6) * 50 - ShiftUp;
			Rectangle(hdc, 88, 650 + indexArray, 413, 700 + indexArray);
		}

		if (ArraySearch(tower1, 5, indexArray))
		{
			SelectObject(hdc, hPen5);
			SelectObject(hdc, hB5);
			indexArray = (indexArray + 1 - 5) * 50 - ShiftUp;
			Rectangle(hdc, 113, 600 + indexArray, 388, 650 + indexArray);
		}

		if (ArraySearch(tower1, 4, indexArray))
		{
			SelectObject(hdc, hPen4);
			SelectObject(hdc, hB4);
			indexArray = (indexArray + 1 - 4) * 50 - ShiftUp;
			Rectangle(hdc, 138, 550 + indexArray, 363, 600 + indexArray);
		}

		if (ArraySearch(tower1, 3, indexArray))
		{
			SelectObject(hdc, hPen3);
			SelectObject(hdc, hB3);
			indexArray = (indexArray + 1 - 3) * 50 - ShiftUp;
			Rectangle(hdc, 163, 500 + indexArray, 338, 550 + indexArray);
		}

		if (ArraySearch(tower1, 2, indexArray))
		{
			SelectObject(hdc, hPen2);
			SelectObject(hdc, hB2);
			indexArray = (indexArray + 1 - 2) * 50 - ShiftUp;
			Rectangle(hdc, 188, 450 + indexArray, 313, 500 + indexArray);
		}

		if (ArraySearch(tower1, 1, indexArray))
		{
			SelectObject(hdc, hPen1);
			SelectObject(hdc, hB1);
			indexArray = (indexArray + 1 - 1) * 50 - ShiftUp;
			Rectangle(hdc, 213, 400 + indexArray, 288, 450 + indexArray);
		}


		if (ArraySearch(tower2, 8, indexArray))
		{
			SelectObject(hdc, hPen8);
			SelectObject(hdc, hB8);
			indexArray = (indexArray + 1 - 8) * 50 - ShiftUp;
			Rectangle(hdc, 38 + 500, indexArray, 463 + 500, 800 + indexArray);
		}

		if (ArraySearch(tower2, 7, indexArray))
		{
			SelectObject(hdc, hPen7);
			SelectObject(hdc, hB7);
			indexArray = (indexArray + 1 - 7) * 50 - ShiftUp;
			Rectangle(hdc, 63 + 500, 700 + indexArray, 438 + 500, 750 + indexArray);
		}

		if (ArraySearch(tower2, 6, indexArray))
		{
			SelectObject(hdc, hPen6);
			SelectObject(hdc, hB6);
			indexArray = (indexArray + 1 - 6) * 50 - ShiftUp;
			Rectangle(hdc, 88 + 500, 650 + indexArray, 413 + 500, 700 + indexArray);
		}

		if (ArraySearch(tower2, 5, indexArray))
		{
			SelectObject(hdc, hPen5);
			SelectObject(hdc, hB5);
			indexArray = (indexArray + 1 - 5) * 50 - ShiftUp;
			Rectangle(hdc, 113 + 500, 600 + indexArray, 388 + 500, 650 + indexArray);
		}

		if (ArraySearch(tower2, 4, indexArray))
		{
			SelectObject(hdc, hPen4);
			SelectObject(hdc, hB4);
			indexArray = (indexArray + 1 - 4) * 50 - ShiftUp;
			Rectangle(hdc, 138 + 500, 550 + indexArray, 363 + 500, 600 + indexArray);
		}

		if (ArraySearch(tower2, 3, indexArray))
		{
			SelectObject(hdc, hPen3);
			SelectObject(hdc, hB3);
			indexArray = (indexArray + 1 - 3) * 50 - ShiftUp;
			Rectangle(hdc, 163 + 500, 500 + indexArray, 338 + 500, 550 + indexArray);
		}

		if (ArraySearch(tower2, 2, indexArray))
		{
			SelectObject(hdc, hPen2);
			SelectObject(hdc, hB2);
			indexArray = (indexArray + 1 - 2) * 50 - ShiftUp;
			Rectangle(hdc, 188 + 500, 450 + indexArray, 313 + 500, 500 + indexArray);
		}

		if (ArraySearch(tower2, 1, indexArray))
		{
			SelectObject(hdc, hPen1);
			SelectObject(hdc, hB1);
			indexArray = (indexArray + 1 - 1) * 50 - ShiftUp;
			Rectangle(hdc, 213 + 500, 400 + indexArray, 288 + 500, 450 + indexArray);
		}


		if (ArraySearch(tower3, 8, indexArray))
		{
			SelectObject(hdc, hPen8);
			SelectObject(hdc, hB8);
			indexArray = (indexArray + 1 - 8) * 50 - ShiftUp;
			Rectangle(hdc, 38 + 1000, 750 + indexArray, 463 + 1000, 800 + indexArray);
		}

		if (ArraySearch(tower3, 7, indexArray))
		{
			SelectObject(hdc, hPen7);
			SelectObject(hdc, hB7);
			indexArray = (indexArray + 1 - 7) * 50 - ShiftUp;
			Rectangle(hdc, 63 + 1000, 700 + indexArray, 438 + 1000, 750 + indexArray);
		}

		if (ArraySearch(tower3, 6, indexArray))
		{
			SelectObject(hdc, hPen6);
			SelectObject(hdc, hB6);
			indexArray = (indexArray + 1 - 6) * 50 - ShiftUp;
			Rectangle(hdc, 88 + 1000, 650 + indexArray, 413 + 1000, 700 + indexArray);
		}

		if (ArraySearch(tower3, 5, indexArray))
		{
			SelectObject(hdc, hPen5);
			SelectObject(hdc, hB5);
			indexArray = (indexArray + 1 - 5) * 50 - ShiftUp;
			Rectangle(hdc, 113 + 1000, 600 + indexArray, 388 + 1000, 650 + indexArray);
		}

		if (ArraySearch(tower3, 4, indexArray))
		{
			SelectObject(hdc, hPen4);
			SelectObject(hdc, hB4);
			indexArray = (indexArray + 1 - 4) * 50 - ShiftUp;
			Rectangle(hdc, 138 + 1000, 550 + indexArray, 363 + 1000, 600 + indexArray);
		}

		if (ArraySearch(tower3, 3, indexArray))
		{
			SelectObject(hdc, hPen3);
			SelectObject(hdc, hB3);
			indexArray = (indexArray + 1 - 3) * 50 - ShiftUp;
			Rectangle(hdc, 163 + 1000, 500 + indexArray, 338 + 1000, 550 + indexArray);
		}

		if (ArraySearch(tower3, 2, indexArray))
		{
			SelectObject(hdc, hPen2);
			SelectObject(hdc, hB2);
			indexArray = (indexArray + 1 - 2) * 50 - ShiftUp;
			Rectangle(hdc, 188 + 1000, 450 + indexArray, 313 + 1000, 500 + indexArray);
		}

		if (ArraySearch(tower3, 1, indexArray))
		{
			SelectObject(hdc, hPen1);
			SelectObject(hdc, hB1);
			indexArray = (indexArray + 1 - 1) * 50 - ShiftUp;
			Rectangle(hdc, 213 + 1000, 400 + indexArray, 288 + 1000, 450 + indexArray);
		}



		DeleteObject(hPen);
		DeleteObject(hB);

		DeleteObject(hPen1);
		DeleteObject(hB1);

		DeleteObject(hPen2);
		DeleteObject(hB2);

		DeleteObject(hPen3);
		DeleteObject(hB3);

		DeleteObject(hPen4);
		DeleteObject(hB4);

		DeleteObject(hPen5);
		DeleteObject(hB5);

		DeleteObject(hPen6);
		DeleteObject(hB6);

		DeleteObject(hPen7);
		DeleteObject(hB7);

		DeleteObject(hPen8);
		DeleteObject(hB8);

		DeleteObject(hPen9);
		DeleteObject(hB9);

		if (tower2[0] == 1)
		{
			char str[100];
			TextOut(hdc, 705, CW_USEDEFAULT, (LPCWSTR)str, wsprintf((LPWSTR)str, L"You Win!!!"));
			std::fstream fout("E:\\lessons\\SPRO\\kursach\\Leaders.txt", std::ios_base::app);
			char buffArr[200];
			int buffTime;
			GetWindowTextA(hEdit, (LPSTR)buffArr, 200);
			writeToFile = writeToFile + buffArr;
			writeToFile.push_back('-');
			buffTime = clock();
			buffTime = buffTime - firstTime;
			std::string buffStringTime;
			buffStringTime = std::to_string(buffTime);
			writeToFile = writeToFile + buffStringTime;
			writeToFile.push_back('\n');
			fout << writeToFile;
			buffStringTime.clear();
			writeToFile.clear();
			fout.close();
		}

		if (tower1[0] == 1)
		{
			firstTime = clock();
		}


		EndPaint(hWnd, &ps); 		//Закінчити графічний вивід	
		break;

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		if (y > 380 - ShiftUp && x > 0 && x < 500)
		{
			if (raisedRing)
			{
				PutRingDown(1, raisedRing, tower1, tower2, tower3);
			}
			else
			{
				RingLift(1, raisedRing, tower1, tower2, tower3);
			}
			InvalidateRect(hWnd, NULL, true);
		}
		if (y > 380 - ShiftUp && x > 500 && x < 1000)
		{
			if (raisedRing)
			{
				PutRingDown(2, raisedRing, tower1, tower2, tower3);
			}
			else
			{
				RingLift(2, raisedRing, tower1, tower2, tower3);
			}
			InvalidateRect(hWnd, NULL, true);
		}
		if (y > 380 - ShiftUp && x > 1000 && x < 1500)
		{
			if (raisedRing)
			{
				PutRingDown(3, raisedRing, tower1, tower2, tower3);
			}
			else
			{
				RingLift(3, raisedRing, tower1, tower2, tower3);
			}
			InvalidateRect(hWnd, NULL, true);
		}
		if (y < 2 && x < 1500 && x >1400)
		{
			tower = true;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_CREATE:
			raisedRing = 0;
			for (int i = 0; i < 8; i++)
			{
				tower1[i] = i + 1;
				tower2[i] = 0;
				tower3[i] = 0;
				tower = false;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case IDM_CREATE + 1:
			ShellExecute(NULL, L"open", L"Leaders.txt", NULL, NULL, SW_SHOWNORMAL);
			break;

		case IDM_CREATE + 2:
			ShellExecute(NULL, L"open", L"Rules.txt", NULL, NULL, SW_SHOWNORMAL);
			break;
		}
		break;

	case WM_DESTROY: 				//Завершення роботи
		PostQuitMessage(0);
		break;
	default:
		//Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

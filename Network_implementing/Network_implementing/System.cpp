#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include "Sources_Consumers.h"

#include <stdio.h>
#include <time.h>
#include <math.h>

#define WND_CLASS_NAME "My window class"

LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

//INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd)
//{
//	WNDCLASS wc;
//	HWND hWnd;
//	MSG msg;
//
//	wc.style = CS_VREDRAW | CS_HREDRAW;
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.hIcon = LoadIcon(NULL, IDI_ERROR);
//	wc.lpszMenuName = NULL;
//	wc.hInstance = hInstance;
//	wc.lpfnWndProc = MyWindowFunc;
//	wc.lpszClassName = WND_CLASS_NAME;
//
//	if (!RegisterClass(&wc))
//	{
//		MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
//		return 0;
//	}
//	hWnd =
//		CreateWindow(WND_CLASS_NAME,
//			"Text",
//			WS_OVERLAPPEDWINDOW,
//			CW_USEDEFAULT, CW_USEDEFAULT,
//			CW_USEDEFAULT, CW_USEDEFAULT,
//			NULL,
//			NULL,
//			hInstance,
//			NULL);
//
//	ShowWindow(hWnd, SW_SHOWNORMAL);
//	UpdateWindow(hWnd);
//
//	while (GetMessage(&msg, NULL, 0, 0))
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//	return msg.wParam;
//}

VOID  DrawEye(HDC hDc, INT X, INT Y, INT R, INT R1, INT mx, INT my)
{
	INT dx = mx - X, dy = my - Y, sx, sy;
	DOUBLE len = sqrt(dx * dx + dy * dy),
		t = (R - R1) / len;

	SelectObject(hDc, GetStockObject(DC_PEN));
	SelectObject(hDc, GetStockObject(DC_BRUSH));
	SetDCPenColor(hDc, RGB(255, 0, 0));
	SetDCBrushColor(hDc, RGB(255, 255, 255));
	Ellipse(hDc, X - R, Y - R, X + R, Y + R);

	if (len < R - R1)
		sx = mx, sy = my;
	else
	{
		sx = (INT)(X + dx * t), sy = (INT)(Y + dy * t);
		t = (R - R1) / len;
	}
	SelectObject(hDc, GetStockObject(DC_PEN));
	SelectObject(hDc, GetStockObject(DC_BRUSH));
	SetDCPenColor(hDc, RGB(0, 0, 0));
	SetDCBrushColor(hDc, RGB(0, 0, 0));
	Ellipse(hDc, sx - R1, sy - R1, sx + R1, sy + R1);

}


LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	HDC hDc;
	POINT pt;
	RECT rc;
	PAINTSTRUCT ps;
	static INT W, H;
	static HDC hMemDC;
	static HBITMAP hBm;
	INT i, j;
	char dc1[] = ("DataCenter 1");
	char dc2[] = ("DataCenter 2");
	char n[] = ("Name");
	char l[] = ("Location");

	DataCenter first("first", "St.Petesburg", 200, 28238);
	DataCenter second("second", "Moscow", 300, 29382);

	char first_name[10] = {}, second_name[10] = {}, first_location[20] = {}, second_location[20] = {};


	int k = 0;

	for (auto letter : first.get_name())
		first_name[k] = letter, k++;

	k = 0;
	for (auto letter : second.get_name())
		second_name[k] = letter, k++;

	k = 0;
	for (auto letter : first.get_location())
		first_location[k] = letter, k++;

	k = 0;
	for (auto letter : second.get_location())
		second_location[k] = letter, k++;


	std::vector<DataCenter> datacenters = { first, second };

	Owner rich("Vladimir", "Gololobov", "Vladimirovich", "06.08.2001", datacenters);

	switch (Msg)
	{
	case WM_CREATE:
		hDc = GetDC(hWnd);
		hMemDC = CreateCompatibleDC(hDc);
		ReleaseDC(hWnd, hDc);
		SetTimer(hWnd, 47, 30, NULL);
		return 0;
	case WM_SIZE:
		H = HIWORD(lParam);
		W = LOWORD(lParam);

		if (hBm != NULL)
			DeleteObject(hBm);

		hBm = CreateCompatibleBitmap(hMemDC, W, H);
		SelectObject(hMemDC, hBm);
		SendMessage(hWnd, WM_TIMER, 0, 0);
		return 0;
	case WM_TIMER:
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);

		SelectObject(hMemDC, GetStockObject(DC_BRUSH));
		SetDCBrushColor(hMemDC, RGB(0, 128, 0));
		Rectangle(hMemDC, 0, 0, W, H);

		for (i = 0; i <= 5000; i += 200)
			for (j = 0; j <= 1000; j += 200)
				DrawEye(hMemDC, 100 + i, 100 + j, 78, 30, pt.x, pt.y);

		InvalidateRect(hWnd, NULL, FALSE);

		return 0;
	case WM_CLOSE:
		if (MessageBox(hWnd, "Do you want to close the window?", "Exit", MB_YESNO == IDYES))
			SendMessage(hWnd, WM_DESTROY, 0, 0);
	case WM_PAINT:
		hDc = BeginPaint(hWnd, &ps);
		BitBlt(hDc, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
		TextOut(hDc, 20, 20, dc1, strlen(dc1));
		TextOut(hDc, 150, 20, dc1, strlen(dc2));
		TextOut(hDc, 20, 40, n, strlen(n));
		TextOut(hDc, 150, 40, n, strlen(n));
		TextOut(hDc, 70, 40, first_name, strlen(first_name));
		TextOut(hDc, 200, 40, second_name, strlen(second_name));
		TextOut(hDc, 20, 60, l, strlen(l));
		TextOut(hDc, 150, 60, l, strlen(l));

		EndPaint(hWnd, &ps);
		return 0;
	case WM_ERASEBKGND:
		return 1;
	case WM_DESTROY:
		DeleteObject(hBm);
		DeleteDC(hMemDC);
		PostMessage(hWnd, WM_QUIT, 0, 0);
		KillTimer(hWnd, 47);
		return 0;
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	DataCenter first("first", "St. Petesburg", 200, 28238);
	DataCenter second("second", "Moscow", 300, 29382);

	std::vector<DataCenter> datacenters = { first, second };

	Owner rich("Vladimir", "Gololobov", "Vladimirovich", "06.08.2001", datacenters);

	Consumer casual("Petrov", "Ivan", "Ivanovich", "05.12.1992", 100000.0, "first", 203393.0);


	std::cout << "Fisrt Datacenter:\n";
	first.info();
	std::cout << "\n";

	std::cout << "Second Datacenter:\n";
	second.info();
	std::cout << "\n";

	std::cout << "Owner:\n";
	rich.info();
	std::cout << "\n";

	std::cout << "Consumer:\n";
	casual.info();
	std::cout << "\n";

	std::cout << "Покупка памяти: \n";
	std::cout << casual.buy_datacenter_memory("first", 10);
	std::cout << std::endl;


	//char choice = '.';
	//char choice2 = '.';
	//int k = 0;
	//bool exit = 0, exit1 = 0;
	//
	//std::string dc_name;
	//double memory;
	//double price_per_gb;
	//std::string location;
	//
	//do
	//{
	//	switch (choice)
	//	{
	//	case '0':
	//		exit = 1;
	//		break;
	//	case '4':
	//		k = 1;
	//		for (auto datacenter : DataCenter::get_dclist())
	//		{
	//			std::cout << "Дата центр " << k << ": \n";
	//			datacenter.info();
	//			std::cout << "=============================\n";
	//			k++;
	//		}
	//
	//		std::cout << "1. Добавление датацентра: \n";
	//		std::cout << "2. Добавление владельца: \n";
	//		std::cout << "3. Добавление покупателя: \n";
	//		std::cout << "4. Список датацентров: \n";
	//		std::cout << "0. Выйти \n";
	//		std::cin >> choice;
	//
	//		break;
	//
	//	case '1':
	//		std::cout << "Введите название датацентра: \n";
	//		std::cin >> dc_name;
	//		std::cout << "Введите память датацентра: \n";
	//		std::cin >> memory;
	//		std::cout << "Введите цену за гигабайт: \n";
	//		std::cin >> price_per_gb;
	//		std::cout << "Введите местоположение: \n";
	//		std::cin >> location;
	//		DataCenter::add_dclist(DataCenter(dc_name, location, memory, price_per_gb));
	//		do
	//		{
	//			switch (choice2)
	//			{
	//			case '0':
	//				exit1 = 1;
	//				break;
	//			case '1':
	//				k = 1;
	//				for (auto datacenter : DataCenter::get_dclist())
	//				{
	//					std::cout << "Дата центр " << k << ": \n";
	//					datacenter.info();
	//					std::cout << "=============================\n";
	//					k++;
	//				}
	//				std::cout << "1. Продолжить \n";
	//				std::cout << "0. Выйти \n";
	//				std::cin >> choice2;
	//				break;
	//			default:
	//				std::cout << "1. Вывод всех датацентров: \n";
	//				std::cout << "0. Выйти \n";
	//				std::cin >> choice2;
	//			}
	//		} while (!exit1);
	//		std::cout << "1. Продолжить\n";
	//		std::cout << "0. Выход\n";
	//		std::cin >> choice;
	//		break;
	//
	//	default:
	//		std::cout << "1. Добавление датацентра: \n";
	//		std::cout << "2. Добавление владельца: \n";
	//		std::cout << "3. Добавление покупателя: \n";
	//		std::cout << "4. Список датацентров: \n";
	//		std::cout << "0. Выйти \n";
	//		std::cin >> choice;
	//	}
	//} while (!exit);

	getchar();
	getchar();
	return 0;
}
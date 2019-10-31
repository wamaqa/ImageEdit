#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include "MemoryMap.h"
#include <fstream>
#include <windows.h>
using namespace cv;
// we're NOT "using namespace std;" here, to avoid collisions between the beta variable and std::beta in c++17
using std::cin;
using std::cout;
using std::endl;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	MSG msg;
	BOOL bRet;
	std::ofstream outFile;
	outFile.open(".\\log.txt", std::ios::out);
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(109));
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
	
	double alpha = 0.5; double beta; double input;
	Mat src1, src2, dst;
	cout << " Simple Linear Blender " << endl;
	cout << "-----------------------" << endl;
	cout << "* Enter alpha [0.0-1.0]: ";
	cin >> input;
	// We use the alpha provided by the user if it is between 0 and 1
	if (input >= 0 && input <= 1)
	{
		alpha = input;
	}
	src1 = imread("../data/LinuxLogo.jpg");
	src2 = imread("../data/WindowsLogo.jpg");
	if (src1.empty()) { cout << "Error loading src1" << endl; return -1; }
	if (src2.empty()) { cout << "Error loading src2" << endl; return -1; }
	beta = (1.0 - alpha);
	addWeighted(src1, alpha, src2, beta, 0.0, dst);
	imshow("Linear Blend", dst);
	waitKey(0);
	return 0;

	//MemoryMap* memory_map = new MemoryMap(L"testMmf");
	//memory_map->Init(1024);
	//while (true)
	//{
	//	wchar_t* data = memory_map->read();
	//	if (memory_map->change())
	//	{
	//		wprintf(L"read %s\n", data);
	//	}
	//	wchar_t input[1024];

	//	wscanf(L"%s", input);
	//	if (input[0] != 'P')
	//	{
	//		memory_map->Write(input);
	//	}

	//	//wprintf(L"read %s\n", memory_map->read());
	//}

	//MSG msg;
	//BOOL bRet;

	//while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	//{
	//	if (bRet == -1)
	//	{
	//		// handle the error and possibly exit
	//	}
	//	else
	//	{
	//		TranslateMessage(&msg);
	//		DispatchMessage(&msg);
	//	}
	//}
}
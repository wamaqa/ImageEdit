#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include "MemoryMap.h"
#include <fstream>
#include <windows.h>
#include "Command.h"
#include <json/json.h>
#include "StringUtils.h"
#include "ConnectPipe.h"
#include "MainOperate.h"

struct BuffData
{
	int Command;
	int DataType;
	int Source;
	int Size;
	char* Data;
};


using namespace cv;
using std::cin;
using std::cout;
using std::endl;
ConnectPipe *m_connect_pipe;
MainOperate* m_MainOperate;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow)
{
	MSG msg;
	BOOL bRet;
	std::ofstream outFile;
	outFile.open(".\\log.txt", std::ios::out);
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(109));
	m_connect_pipe = new ConnectPipe;
	m_MainOperate = new MainOperate;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			switch (msg.message)
			{
			case WM_USER_Command:
				{
				Json::Value json = m_connect_pipe->read();
				ImageData *data = m_MainOperate->Exc(json);
				m_connect_pipe->write(data);
				}
			default: ;
			}
			DispatchMessage(&msg);
		}
	}
	if (m_connect_pipe != nullptr)
		free(m_connect_pipe);
	return 0;
}

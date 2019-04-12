#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine() : chPixelSign(0x2588)
{
	iScreenHeight = 80;
	iScreenWidth = 40;
	iPixelSize = 10;
	ScreenBuffer = NULL;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

GameEngine::~GameEngine()
{
	delete[] ScreenBuffer;
}

int GameEngine::ScreenHeight()
{
	return iScreenHeight;
}

int GameEngine::ScreenWidth()
{
	return iScreenWidth;
}

int GameEngine::PixelSize()
{
	return iPixelSize;
}

void GameEngine::ConstructConsole(int _iScreenWidth, int _iScreenHeight, int _iPixelSize)
{
	iScreenHeight = _iScreenHeight;
	iScreenWidth = _iScreenWidth;
	RectWindow = { 0,0,1,1 };
	SetConsoleWindowInfo(hConsole, TRUE, &RectWindow);
	COORD Coord = { (short)iScreenWidth,(short)iScreenHeight };
	SetConsoleScreenBufferSize(hConsole, Coord);
	SetConsoleActiveScreenBuffer(hConsole);

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = _iPixelSize;
	cfi.dwFontSize.Y = _iPixelSize;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(hConsole, false, &cfi);
	
	RectWindow = { 0,0,(short)iScreenWidth - 1,(short)iScreenHeight - 1 };
	SetConsoleWindowInfo(hConsole, TRUE, &RectWindow);

	ScreenBuffer = new CHAR_INFO[iScreenHeight*iScreenWidth];
	memset(ScreenBuffer, 0, iScreenHeight*iScreenWidth * sizeof(CHAR_INFO));

	OnUserCreate();

	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

void GameEngine::OnUserCreate()
{
	return;
}

void GameEngine::OnUserUpdate()
{
	return;
}

void GameEngine::Draw(int posY, int posX, Color col)
{
	ScreenBuffer[posY*iScreenWidth + posX].Attributes = col;
	ScreenBuffer[posY*iScreenWidth + posX].Char.UnicodeChar = chPixelSign;
}

void GameEngine::Start()
{
	while (true) {
		auto point1 = std::chrono::steady_clock::now();
		OnUserUpdate();
		WriteConsoleOutput(hConsole, ScreenBuffer, { (short)iScreenWidth,(short)iScreenHeight }, { 0,0 }, &RectWindow);
		auto point2 = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds> (std::chrono::steady_clock::now() - point1);
		int FPS = 1000000 / (float)duration.count();
		std::wstring title = L"Game Of Life! FPS: ";
		title += std::to_wstring(FPS);
		SetConsoleTitle(title.c_str());
	}
}

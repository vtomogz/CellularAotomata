#pragma once
#include <windows.h>
#include <chrono>
#include <string>

enum Color {
	BLACK = 0x0000,
	DARK_BLUE = 0x0001,
	DARK_GREEN = 0x0002,
	DARK_CYAN = 0x0003,
	DARK_RED = 0x0004,
	DARK_MAGENTA = 0x0005,
	DARK_YELLOW = 0x0006,
	GREY = 0x0007,
	DARK_GREY = 0x0008,
	BLUE = 0x0009,
	GREEN = 0x000A,
	CYAN = 0x000B,
	RED = 0x000C,
	MAGENTA = 0x000D,
	YELLOW = 0x000E,
	WHITE = 0x000F
};

class GameEngine
{
private:
	int iScreenHeight;
	int iScreenWidth;
	int iPixelSize;
	const wchar_t chPixelSign;
	CHAR_INFO *ScreenBuffer;
	HANDLE hConsole;
	SMALL_RECT RectWindow;
protected:
	void Draw(int, int, Color);
	virtual void OnUserCreate();
	virtual void OnUserUpdate();
public:
	GameEngine();
	~GameEngine();
	int ScreenHeight();
	int ScreenWidth();
	int PixelSize();
	void ConstructConsole(int, int, int);
	void Start();
};


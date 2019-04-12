#include <windows.h>
#include <ctime>
#include <iostream>
#include <vector>
#include "GameEngine.h"

struct cell {
	bool alive = false;
	int neighbours = 0;
	cell(int x, bool y) {
		alive = y;
		neighbours = x;
	}
};

class CellularAutomata : public GameEngine
{
public:
	void OnUserCreate() override
	{
		auto lambda = []() {return rand() % 3 == 0; };
		for (int i = 0; i < ScreenHeight(); i++) {
			cells.push_back(std::vector<cell>());
			for (int j = 0; j < ScreenWidth(); j++) {
				cells[i].push_back(cell(0,lambda()));
			}
		}
	}
	void OnUserUpdate() override
	{
		for (int i = 0; i < ScreenHeight(); i++) {
			for (int j = 0; j < ScreenWidth(); j++) {
				if (cells[i][j].alive) {
					Draw(i, j, WHITE);
				}
				else {
					Draw(i, j, BLACK);
				}
			}
		}
		for (int i = 0; i < ScreenHeight(); i++) {
			for (int j = 0; j < ScreenWidth(); j++) {
				if(i > 0 && j > 0)
					if (cells[i - 1][j - 1].alive)
						cells[i][j].neighbours++;
				if(i > 0)
					if (cells[i - 1][j].alive)
						cells[i][j].neighbours++;
				if(i > 0 && j < ScreenWidth() - 1)
					if (cells[i - 1][j + 1].alive)
						cells[i][j].neighbours++;
				if(j > 0)
					if (cells[i][j - 1].alive)
						cells[i][j].neighbours++;
				if(j < ScreenWidth() - 1)
					if (cells[i][j + 1].alive)
						cells[i][j].neighbours++;
				if(i < ScreenHeight() - 1 && j > 0)
					if (cells[i + 1][j - 1].alive)
						cells[i][j].neighbours++;
				if (i < ScreenHeight() - 1)
					if (cells[i + 1][j].alive)
						cells[i][j].neighbours++;
				if(i < ScreenHeight() - 1 && j < ScreenWidth() - 1)
					if (cells[i + 1][j + 1].alive)
						cells[i][j].neighbours++;
			}
		}
		std::vector<std::vector<cell>> tmp = cells;
		cells.resize(0);
		for (int i = 0; i < ScreenHeight(); i++) {
			cells.push_back(std::vector<cell>());
			for (int j = 0; j < ScreenWidth(); j++) {
				if (tmp[i][j].alive) {
					if (tmp[i][j].neighbours == 2 || tmp[i][j].neighbours == 3)
						cells[i].push_back(cell(0, true));
					else
						cells[i].push_back(cell(0, false));
				}
				else {
					if(tmp[i][j].neighbours == 3)
						cells[i].push_back(cell(0, true));
					else
						cells[i].push_back(cell(0, false));
				}
			}
		}
	}
private:
	std::vector<std::vector<cell>> cells;
};

int main() {
	srand(time(NULL));
	CellularAutomata GameOfLife;
	GameOfLife.ConstructConsole(160, 120, 5);
	GameOfLife.Start();
	return 0;
}
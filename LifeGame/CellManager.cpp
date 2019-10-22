#include <conio.h>
#include <string.h>
#include "CellManager.h"

CCellManager::CCellManager()
{
	// 初期化
	cursorX = 0;
	cursorY = 0;
}

void CCellManager::Initialize()
{
	memset(cell, 0, sizeof(cell));
}

void CCellManager::SetCursor(CFieldManager* cField)
{
	cField->SetField(cursorY, cursorX, "◎");
}

void CCellManager::MoveCursor()
{
	// キー入力受付
	switch (_getch())
	{
		case'a':
			// 左に移動
			cursorX--;
			break;

		case'd':
			// 右に移動
			cursorX++;
			break;

		case'w':
			// 上に移動
			cursorY--;
			break;

		case's':
			// 下に移動
			cursorY++;
			break;

		case' ':
			// セルの状態を切り替える
			cell[cursorY][cursorX] ^= 1;
			break;

		case'\r':
			// 時を経過させる
			GetAdjacenLivesCount(cursorY, cursorX);
			break;
	}
}

// セルの状態をフィールドに反映
void CCellManager::ReflectCellState(CFieldManager* cField)
{
	for (int i = 0; i < FIELD_HEIGHT; i++)
	{
		for (int j = 0; j < FIELD_HEIGHT; j++)
		{
			// セルが生きている場合
			if (cell[i][j] == 1)
			{
				cField->SetField(i, j, "■");
			}
		}
	}
}

// 隣接する生きた細胞の数を取得
int CCellManager::GetAdjacenLivesCount(int vecY, int vecX)
{
	// 生きたセルの数
	int liveCellCount = 0;

	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			// 原点でない場合
			if (!((x == 0) && (y == 0)))
			{
				// 対象の座標を算出
				int targetVecY = (FIELD_HEIGHT + vecY + y) % FIELD_HEIGHT;
				int targetVecX = (FIELD_WIDTH + vecX + x) % FIELD_WIDTH;

				// セルの値を加算（生きている場合1が格納されている）
				liveCellCount += cell[targetVecY][targetVecX];
/*
				if (cell[y][x] == 0)
				{

				}
				else
				{

				}*/
			}
		}
	}

	return liveCellCount;
}

// 次の世代に移行する
void CCellManager::NextGeneration()
{
	for (int y = 0; y < FIELD_HEIGHT; y++)
	{

		for (int x = 0; x < FIELD_WIDTH; x++)
		{
			int cellState = GetAdjacenLivesCount(y, x);
		}
	}
}
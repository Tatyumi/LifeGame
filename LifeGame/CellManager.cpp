#include <conio.h>
#include <string.h>
#include "CellManager.h"

CCellManager::CCellManager()
{
	// 初期化
	cursorX = 0;
	cursorY = 0;
}

// 初期化
void CCellManager::Initialize()
{
	memset(cell, 0, sizeof(cell));
}

// カーソルをセット
void CCellManager::SetCursor(CFieldManager* cField)
{
	cField->SetField(cursorY, cursorX, "◎");
}

// カーソル操作
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
			NextGeneration();
			break;

			// エスケープキー
		case 0x1b:
			// セル全滅
			memset(cell, 0, sizeof(cell));
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
			// 隣接するセルの数を取得
			int AdjacenLivesCellCount = GetAdjacenLivesCount(y, x);

			// セルの次の状態
			int cellNextState = cell[y][x];

			// フィールドのセルをチェック
			if (cell[y][x])
			{
				// 生きている場合

				// 過密、または過疎か判別
				if (AdjacenLivesCellCount <= DEPOPULATION || AdjacenLivesCellCount >= DENSE)
				{
					// 過密、または過疎の場合

					// 次の世代のセルは死滅する
					cellNextState = 0;
				}

			}
			else
			{
				// 死んでいる場合

				// 隣接するセルの個数が3かチェック
				if (AdjacenLivesCellCount == BORN)
				{
					// 3の場合

					// 次の世代のセル誕生させる
					cellNextState = 1;
				}
			}

			// 次のセルの状態を取得
			nextCell[y][x] = cellNextState;
		}
	}

	// 次のセルの状態をコピーする
	memcpy_s(cell, sizeof(cell), nextCell, sizeof(nextCell));
}
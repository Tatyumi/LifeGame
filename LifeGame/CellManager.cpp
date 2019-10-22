#include <conio.h>
#include <string.h>
#include "CellManager.h"

CCellManager::CCellManager()
{
	// ‰Šú‰»
	cursorX = 0;
	cursorY = 0;
}

void CCellManager::Initialize()
{
	memset(cell, 0, sizeof(cell));
}

void CCellManager::SetCursor(CFieldManager* cField)
{
	cField->SetField(cursorY, cursorX, "");
}

void CCellManager::MoveCursor()
{
	// ƒL[“ü—Íó•t
	switch (_getch())
	{
		case'a':
			// ¶‚ÉˆÚ“®
			cursorX--;
			break;

		case'd':
			// ‰E‚ÉˆÚ“®
			cursorX++;
			break;

		case'w':
			// ã‚ÉˆÚ“®
			cursorY--;
			break;

		case's':
			// ‰º‚ÉˆÚ“®
			cursorY++;
			break;

		case' ':
			// ƒZƒ‹‚Ìó‘Ô‚ğØ‚è‘Ö‚¦‚é
			cell[cursorY][cursorX] ^= 1;
			break;

		case'\r':
			// ‚ğŒo‰ß‚³‚¹‚é
			GetAdjacenLivesCount(cursorY, cursorX);
			break;
	}
}

// ƒZƒ‹‚Ìó‘Ô‚ğƒtƒB[ƒ‹ƒh‚É”½‰f
void CCellManager::ReflectCellState(CFieldManager* cField)
{
	for (int i = 0; i < FIELD_HEIGHT; i++)
	{
		for (int j = 0; j < FIELD_HEIGHT; j++)
		{
			// ƒZƒ‹‚ª¶‚«‚Ä‚¢‚éê‡
			if (cell[i][j] == 1)
			{
				cField->SetField(i, j, "¡");
			}
		}
	}
}

// —×Ú‚·‚é¶‚«‚½×–E‚Ì”‚ğæ“¾
int CCellManager::GetAdjacenLivesCount(int vecY, int vecX)
{
	// ¶‚«‚½ƒZƒ‹‚Ì”
	int liveCellCount = 0;

	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			// Œ´“_‚Å‚È‚¢ê‡
			if (!((x == 0) && (y == 0)))
			{
				// ‘ÎÛ‚ÌÀ•W‚ğZo
				int targetVecY = (FIELD_HEIGHT + vecY + y) % FIELD_HEIGHT;
				int targetVecX = (FIELD_WIDTH + vecX + x) % FIELD_WIDTH;

				// ƒZƒ‹‚Ì’l‚ğ‰ÁZi¶‚«‚Ä‚¢‚éê‡1‚ªŠi”[‚³‚ê‚Ä‚¢‚éj
				liveCellCount += cell[targetVecY][targetVecX];
			}
		}
	}

	return liveCellCount;
}

// Ÿ‚Ì¢‘ã‚ÉˆÚs‚·‚é
void CCellManager::NextGeneration()
{
	for (int y = 0; y < FIELD_HEIGHT; y++)
	{
		for (int x = 0; x < FIELD_WIDTH; x++)
		{
			// ï¿½×Ú‚ï¿½ï¿½ï¿½Zï¿½ï¿½ï¿½Ìï¿½ï¿½ï¿½æ“¾
			int AdjacenLivesCellCount = GetAdjacenLivesCount(y, x);

			// ï¿½Zï¿½ï¿½ï¿½Ìï¿½ï¿½Ìï¿½ï¿½
			int cellNextState = cell[y][x];

			// ï¿½tï¿½Bï¿½[ï¿½ï¿½ï¿½hï¿½ÌƒZï¿½ï¿½ï¿½ï¿½`ï¿½Fï¿½bï¿½N
			if (cell[y][x])
			{
				// ï¿½ï¿½ï¿½ï¿½ï¿½Ä‚ï¿½ï¿½ï¿½ê‡

				// ï¿½ß–ï¿½ï¿½Aï¿½Ü‚ï¿½ï¿½Í‰ß‘aï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
				if (AdjacenLivesCellCount <= DEPOPULATION || AdjacenLivesCellCount >= DENSE)
				{
					// ï¿½ß–ï¿½ï¿½Aï¿½Ü‚ï¿½ï¿½Í‰ß‘aï¿½Ìê‡

					// ï¿½ï¿½ï¿½Ìï¿½ï¿½ï¿½ÌƒZï¿½ï¿½ï¿½Íï¿½ï¿½Å‚ï¿½ï¿½ï¿½
					cellNextState = 0;
				}

			}
			else
			{
				// ï¿½ï¿½ï¿½ï¿½Å‚ï¿½ï¿½ï¿½ê‡

				// ï¿½×Ú‚ï¿½ï¿½ï¿½Zï¿½ï¿½ï¿½ÌŒÂï¿½ï¿½ï¿½3ï¿½ï¿½ï¿½`ï¿½Fï¿½bï¿½N
				if (AdjacenLivesCellCount == BORN)
				{
					// 3ï¿½Ìê‡

					// ï¿½ï¿½ï¿½Ìï¿½ï¿½ï¿½ÌƒZï¿½ï¿½ï¿½aï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
					cellNextState = 1;
				}
			}

			// ï¿½ï¿½ï¿½ÌƒZï¿½ï¿½ï¿½Ìï¿½Ô‚ï¿½æ“¾
			nextCell[y][x] = cellNextState;
		}
	}

	// ï¿½ï¿½ï¿½ÌƒZï¿½ï¿½ï¿½Ìï¿½Ô‚ï¿½Rï¿½sï¿½[ï¿½ï¿½ï¿½ï¿½
	memcpy_s(cell, sizeof(cell), nextCell, sizeof(nextCell));
}
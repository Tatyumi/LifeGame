#include <conio.h>
#include <string.h>
#include "CellManager.h"

CCellManager::CCellManager()
{
	// ������
	cursorX = 0;
	cursorY = 0;
}

// ������
void CCellManager::Initialize()
{
	memset(cell, 0, sizeof(cell));
}

// �J�[�\�����Z�b�g
void CCellManager::SetCursor(CFieldManager* cField)
{
	cField->SetField(cursorY, cursorX, "��");
}

// �J�[�\������
void CCellManager::MoveCursor()
{
	// �L�[���͎�t
	switch (_getch())
	{
		case'a':
			// ���Ɉړ�
			cursorX--;
			break;

		case'd':
			// �E�Ɉړ�
			cursorX++;
			break;

		case'w':
			// ��Ɉړ�
			cursorY--;
			break;

		case's':
			// ���Ɉړ�
			cursorY++;
			break;

		case' ':
			// �Z���̏�Ԃ�؂�ւ���
			cell[cursorY][cursorX] ^= 1;
			break;

		case'\r':
			// �����o�߂�����
			NextGeneration();
			break;

			// �G�X�P�[�v�L�[
		case 0x1b:
			// �Z���S��
			memset(cell, 0, sizeof(cell));
			break;
	}
}

// �Z���̏�Ԃ��t�B�[���h�ɔ��f
void CCellManager::ReflectCellState(CFieldManager* cField)
{
	for (int i = 0; i < FIELD_HEIGHT; i++)
	{
		for (int j = 0; j < FIELD_HEIGHT; j++)
		{
			// �Z���������Ă���ꍇ
			if (cell[i][j] == 1)
			{
				cField->SetField(i, j, "��");
			}
		}
	}
}

// �אڂ��鐶�����זE�̐����擾
int CCellManager::GetAdjacenLivesCount(int vecY, int vecX)
{
	// �������Z���̐�
	int liveCellCount = 0;

	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			// ���_�łȂ��ꍇ
			if (!((x == 0) && (y == 0)))
			{
				// �Ώۂ̍��W���Z�o
				int targetVecY = (FIELD_HEIGHT + vecY + y) % FIELD_HEIGHT;
				int targetVecX = (FIELD_WIDTH + vecX + x) % FIELD_WIDTH;

				// �Z���̒l�����Z�i�����Ă���ꍇ1���i�[����Ă���j
				liveCellCount += cell[targetVecY][targetVecX];
			}
		}
	}

	return liveCellCount;
}

// ���̐���Ɉڍs����
void CCellManager::NextGeneration()
{
	for (int y = 0; y < FIELD_HEIGHT; y++)
	{
		for (int x = 0; x < FIELD_WIDTH; x++)
		{
			// �אڂ���Z���̐����擾
			int AdjacenLivesCellCount = GetAdjacenLivesCount(y, x);

			// �Z���̎��̏��
			int cellNextState = cell[y][x];

			// �t�B�[���h�̃Z�����`�F�b�N
			if (cell[y][x])
			{
				// �����Ă���ꍇ

				// �ߖ��A�܂��͉ߑa������
				if (AdjacenLivesCellCount <= DEPOPULATION || AdjacenLivesCellCount >= DENSE)
				{
					// �ߖ��A�܂��͉ߑa�̏ꍇ

					// ���̐���̃Z���͎��ł���
					cellNextState = 0;
				}

			}
			else
			{
				// ����ł���ꍇ

				// �אڂ���Z���̌���3���`�F�b�N
				if (AdjacenLivesCellCount == BORN)
				{
					// 3�̏ꍇ

					// ���̐���̃Z���a��������
					cellNextState = 1;
				}
			}

			// ���̃Z���̏�Ԃ��擾
			nextCell[y][x] = cellNextState;
		}
	}

	// ���̃Z���̏�Ԃ��R�s�[����
	memcpy_s(cell, sizeof(cell), nextCell, sizeof(nextCell));
}
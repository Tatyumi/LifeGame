#include <stdio.h>
#include "FieldManager.h"

// �R���X�g���N�^
CFieldManager::CFieldManager()
{
}

// �t�B�[���h��\��
void CFieldManager::DispField()
{
	for (int i = 0; i < FIELD_HEIGHT; i++)
	{
		for (int j = 0; j < FIELD_HEIGHT; j++)
		{
			printf(field[i][j]);
		}

		printf("\n");
	}
}

// ������
void CFieldManager::Initialize()
{
	for (int i = 0; i < FIELD_HEIGHT; i++)
	{
		for (int j = 0; j < FIELD_HEIGHT; j++)
		{
			SetField(i, j, "�E");
		}
	}
}
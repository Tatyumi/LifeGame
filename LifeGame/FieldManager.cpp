#include <stdio.h>
#include "FieldManager.h"

// コンストラクタ
CFieldManager::CFieldManager()
{
}

// フィールドを表示
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

// 初期化
void CFieldManager::Initialize()
{
	for (int i = 0; i < FIELD_HEIGHT; i++)
	{
		for (int j = 0; j < FIELD_HEIGHT; j++)
		{
			SetField(i, j, "・");
		}
	}
}
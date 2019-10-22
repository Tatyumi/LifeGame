#include<stdlib.h>
#include "FieldManager.h"
#include "CellManager.h"


int main()
{
	CFieldManager cField;
	CCellManager cCell;
	cCell.Initialize();
	while (1)
	{

		// 画面クリア
		system("cls");

		// フィールド初期化
		cField.Initialize();

		// セルの状態を反映
		cCell.ReflectCellState(&cField);

		// カーソルセット
		cCell.SetCursor(&cField);

		// フィールド表示
		cField.DispField();

		// カーソル移動
		cCell.MoveCursor();
	}

	return 0;
}
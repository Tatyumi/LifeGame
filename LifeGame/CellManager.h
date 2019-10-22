#pragma once
#include "FieldManager.h"

class CCellManager
{

public:
	// コンストラクタ
	CCellManager();
	// 初期化
	void Initialize();
	// カーソル設定処理
	void SetCursor(CFieldManager* cField);
	// カーソル移動処理
	void MoveCursor();
	// フィールドにセルの状態を反映
	void ReflectCellState(CFieldManager* cField);
	// 隣接する生きたセルの数を取得
	int GetAdjacenLivesCount(int vecY, int vecX);
	// 次の世代に移行する
	void NextGeneration();
	// cellのアクセサ
	int GetCell(int vecY, int vecX) { return cell[vecY][vecX]; }
	void SetCell(int vecY, int vecX, int state) { cell[vecY][vecX] = state; };

private:
	// カーソルのx座標
	int cursorX;
	// カーソルのy座標
	int cursorY;
	// セルの配置場所
	int cell[FIELD_HEIGHT][FIELD_WIDTH];
	// 次の世代のセル
	int nextCell[FIELD_HEIGHT][FIELD_WIDTH];
};
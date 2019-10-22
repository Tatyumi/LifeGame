#pragma once

static const int FIELD_WIDTH = 24;
static const int FIELD_HEIGHT = 24;

class CFieldManager
{
private:
	const char* field[FIELD_HEIGHT][FIELD_WIDTH];
	//char field[FIELD_HEIGHT][FIELD_WIDTH];

public:
	// コンストラクタ
	CFieldManager();
	// フィールド描画
	void DispField();
	// 初期化
	void Initialize();
	// fieldアクセサ
	void SetField(int vecY, int vecX,const char* sign) { field[vecY][vecX] = sign; };
	//void SetField(int vecY, int vecX, char sign) { field[vecY][vecX] = sign; };
};
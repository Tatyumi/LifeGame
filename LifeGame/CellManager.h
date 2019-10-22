#pragma once
#include "FieldManager.h"

class CCellManager
{

public:
	// �R���X�g���N�^
	CCellManager();
	// ������
	void Initialize();
	// �J�[�\���ݒ菈��
	void SetCursor(CFieldManager* cField);
	// �J�[�\���ړ�����
	void MoveCursor();
	// �t�B�[���h�ɃZ���̏�Ԃ𔽉f
	void ReflectCellState(CFieldManager* cField);
	// �אڂ��鐶�����Z���̐����擾
	int GetAdjacenLivesCount(int vecY, int vecX);
	// ���̐���Ɉڍs����
	void NextGeneration();
	// cell�̃A�N�Z�T
	int GetCell(int vecY, int vecX) { return cell[vecY][vecX]; }
	void SetCell(int vecY, int vecX, int state) { cell[vecY][vecX] = state; };

private:
	// �J�[�\����x���W
	int cursorX;
	// �J�[�\����y���W
	int cursorY;
	// �Z���̔z�u�ꏊ
	int cell[FIELD_HEIGHT][FIELD_WIDTH];
	// ���̐���̃Z��
	int nextCell[FIELD_HEIGHT][FIELD_WIDTH];
};
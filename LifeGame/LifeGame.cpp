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

		// ��ʃN���A
		system("cls");

		// �t�B�[���h������
		cField.Initialize();

		// �Z���̏�Ԃ𔽉f
		cCell.ReflectCellState(&cField);

		// �J�[�\���Z�b�g
		cCell.SetCursor(&cField);

		// �t�B�[���h�\��
		cField.DispField();

		// �J�[�\���ړ�
		cCell.MoveCursor();
	}

	return 0;
}
#include"Mouse.h"
#include"Cheese.h"
#include"Wrench.h"
#include"ModelManager.h"
#include "ObstructManager.h"

//�e���f���̏�����
ObstructManager::ObstructManager()
{
	//���f���̃��[�h
	mouseModelHandle = MV1DuplicateModel(ModelManager::GetMouseModelHandle());
	cheeseModelHandle = MV1DuplicateModel(ModelManager::GetCheeseModelHandle());
	wrenchModelHandle = MV1DuplicateModel(ModelManager::GetWrenchModelHandle());

	//�l�Y�~�����ǉ�
	InitMouse();

	//�`�[�Y�����ǉ�
	InitCheese();

	//�����`�����ǉ�
	InitWrench();

	//�����`���o�����n�߂鎞�Ԃ̍ŏ��̎��Ԃ��擾
	startTime = GetNowCount();
}

//�e���f���̌㏈��
ObstructManager::~ObstructManager()
{
	MV1DeleteModel(mouseModelHandle);
	MV1DeleteModel(cheeseModelHandle);
	MV1DeleteModel(wrenchModelHandle);
}

//�e���f���̍X�V
void ObstructManager::Update()
{
	UpdateMouse();
	UpdateCheese();
	UpdateWrench();
}

//�e���f���̕`��
void ObstructManager::Draw(Field* field)
{
	DrawMouse(field);
	DrawCheese();
	DrawWrench();
}

//�S�}�E�X�̏�������
void ObstructManager::InitMouse()
{
	for (int i = 0; i < MOUSE_NUM; i++)
	{
		//�}�E�X�̏����ǉ�
		mouse.push_back(new Mouse(mouseModelHandle));
	}
	for (mouse_itr = mouse.begin(); mouse_itr != mouse.end(); mouse_itr++)
	{
		//�}�E�X1�̂̏�����
		(*mouse_itr)->Initialize(mouseModelHandle);
	}
}

//�S�`�[�Y�̏�������
void ObstructManager::InitCheese()
{
	for (int i = 0; i < MOUSE_NUM; i++)
	{
		//�`�[�Y�̏����ǉ�
		cheese.push_back(new Cheese(cheeseModelHandle));
	}
}

//�S�����`�̏�������
void ObstructManager::InitWrench()
{
	for (int i = 0; i < MOUSE_NUM; i++)
	{
		//�����`�̏����ǉ�
		wrench.push_back(new Wrench(wrenchModelHandle));
	}
}

//�S�}�E�X�̍X�V����
void ObstructManager::UpdateMouse()
{
	for (mouse_itr = mouse.begin(); mouse_itr != mouse.end(); mouse_itr++)
	{
		//�e�}�E�X�̍X�V
		(*mouse_itr)->Update();
	}
}

//�S�`�[�Y�̍X�V����
void ObstructManager::UpdateCheese()
{
	mouse_itr = mouse.begin();
	for (cheese_itr = cheese.begin(); cheese_itr != cheese.end(); cheese_itr++)
	{
		//�e�`�[�Y�̍X�V
		(*cheese_itr)->Update((*mouse_itr)->GetNowPosition());
		mouse_itr++;
	}
}

//�S�����`�̍X�V����
void ObstructManager::UpdateWrench()
{
	cheese_itr = cheese.begin();
	for (wrench_itr = wrench.begin(); wrench_itr != wrench.end(); wrench_itr++)
	{
		//�e�����`�̍X�V
		(*wrench_itr)->Update((*cheese_itr)->GetPos());
		cheese_itr++;
	}
}

//�S�}�E�X�`��
void ObstructManager::DrawMouse(Field* field)
{
	cheese_itr = cheese.begin();
	wrench_itr = wrench.begin();
	for (mouse_itr = mouse.begin(); mouse_itr != mouse.end(); mouse_itr++)
	{
		//�e�}�E�X�̕`��
		(*mouse_itr)->Draw();
		(*mouse_itr)->DrawShadow(field);

		//�}�E�X���ڕW�n�_�ɓ��B���Ă����珉��������
		if (!(*mouse_itr)->IsCheckMouseAppearance())
		{
			(*mouse_itr)->Initialize(mouseModelHandle);
			(*cheese_itr)->InitFlag();
			(*wrench_itr)->InitAppearance(startTime);
		}
		cheese_itr++;
		wrench_itr++;
	}
}

//�S�`�[�Y�`��
void ObstructManager::DrawCheese()
{
	for (cheese_itr = cheese.begin(); cheese_itr != cheese.end(); cheese_itr++)
	{
		//�e�`�[�Y�̕`��
		(*cheese_itr)->Draw();
	}
}

//�S�����`�`��
void ObstructManager::DrawWrench()
{
	cheese_itr = cheese.begin();
	for (wrench_itr = wrench.begin(); wrench_itr != wrench.end(); wrench_itr++)
	{
		//�o�����Ă���Ε`�悷��
		if ((*wrench_itr)->GetIsAppearance())
		{
			(*wrench_itr)->Draw();
			startTime = GetNowCount();
		}
		cheese_itr++;
	}
}

//�}�E�X�̃N���X��1�擾
Mouse* ObstructManager::GetMouse(int index)
{
	mouse_itr = mouse.begin();
	for (int i = 0; i < index; i++)
	{
		mouse_itr++;
	}
	return (*mouse_itr);
}

//�`�[�Y�̃N���X��1�擾
Cheese* ObstructManager::GetCheese(int index)
{
	cheese_itr = cheese.begin();
	for (int i = 0; i < index; i++)
	{
		cheese_itr++;
	}
	return (*cheese_itr);
}

//�����`�̃N���X��1�擾
Wrench* ObstructManager::GetWrench(int index)
{
	wrench_itr = wrench.begin();
	for (int i = 0; i < index; i++)
	{
		wrench_itr++;
	}
	return (*wrench_itr);
}
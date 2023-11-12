#pragma once
#include<DxLib.h>
#include<list>

#define MOUSE_NUM				5			//�}�E�X�̍ő�o����

class Mouse;
class Cheese;
class Wrench;
class Field;

using namespace std;

/// <summary>
/// �v���C���[�ȊO�̃��f���𐧌䂷��N���X
/// </summary>
class ObstructManager
{
public:
	/// <summary>
	/// �e���f���̏�����
	/// </summary>
	ObstructManager();

	/// <summary>
	/// �e���f���̌㏈��
	/// </summary>
	~ObstructManager();

	/// <summary>
	/// �e���f���̍X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �e���f���̕`��
	/// </summary>
	/// <param name="field">�t�B�[���h���Ǘ�����N���X</param>
	void Draw(Field* field);

	/// <summary>
	/// �S�}�E�X�̏�������
	/// </summary>
	void InitMouse();

	/// <summary>
	/// �S�`�[�Y�̏�������
	/// </summary>
	void InitCheese();

	/// <summary>
	/// �S�����`�̏�������
	/// </summary>
	void InitWrench();

	/// <summary>
	/// �S�}�E�X�̍X�V����
	/// </summary>
	void UpdateMouse();

	/// <summary>
	/// �S�`�[�Y�̍X�V����
	/// </summary>
	void UpdateCheese();

	/// <summary>
	/// �S�����`�̍X�V����
	/// </summary>
	void UpdateWrench();

	/// <summary>
	/// �S�}�E�X�`��
	/// </summary>
	/// <param name="field">�t�B�[���h���Ǘ�����N���X</param>
	void DrawMouse(Field* field);

	/// <summary>
	/// �S�`�[�Y�`��
	/// </summary>
	void DrawCheese();

	/// <summary>
	/// �S�����`�`��
	/// </summary>
	void DrawWrench();

	/// <summary>
	/// �}�E�X�̃N���X��1�擾
	/// </summary>
	/// <param name="index">�}�E�X�N���X��1�w�肷��ϐ�</param>
	/// <returns>�}�E�X�̃N���X</returns>
	Mouse* GetMouse(int index);

	/// <summary>
	/// �`�[�Y�̃N���X��1�擾
	/// </summary>
	/// <param name="index">�`�[�Y�N���X��1�w�肷��ϐ�</param>
	/// <returns>�`�[�Y�̃N���X</returns>
	Cheese* GetCheese(int index);

	/// <summary>
	/// �����`�̃N���X��1�擾
	/// </summary>
	/// <param name="index">�����`�N���X��1�w�肷��ϐ�</param>
	/// <returns>�����`�̃N���X</returns>
	Wrench* GetWrench(int index);
private:
	list<Mouse*> mouse;					//Mouse�N���X��list
	list<Mouse*>::iterator mouse_itr;	//Mouse�N���Xlist�̃C�e���[�^
	int mouseModelHandle;				//�}�E�X�̃��f���n���h��

	list<Cheese*> cheese;				//Cheese�N���X��list
	list<Cheese*>::iterator cheese_itr;	//Cheese�N���Xlist�̃C�e���[�^
	int cheeseModelHandle;				//�`�[�Y�̃��f���n���h��

	list<Wrench*> wrench;				//Wrench�N���X��list
	list<Wrench*>::iterator wrench_itr;	//Wrench�N���Xlist�C�e���[�^
	int wrenchModelHandle;				//�����`�̃��f���n���h��
	int isAppearance;					//���f�����o�����邩�ǂ������m���ő��삷��
	int startTime;						//�����`�̏o������܂ł̃J�E���g
};


#pragma once
#include<DxLib.h>

class Field;
class Player;
class ObstructManager;
class Mouse;
class Collision;
class GameUI;
class Effect;

/// <summary>
/// ���C���Q�[���V�[���𐧌䂷��N���X
/// </summary>
class GameScene :public BaseScene
{
public:
	/// <summary>
	/// �Q�[���V�[���ɕK�v�ȃN���X�̏������ƃe�N�X�`���̃��[�h�A���W�̏�����
	/// </summary>
	GameScene();

	/// <summary>
	/// �N���X�̌㏈��
	/// </summary>
	~GameScene();

	/// <summary>
	/// �Q�[���V�[���̍X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �Q�[���V�[���̕`��
	/// </summary>
	void Draw();
private:
	Field* field;							//�t�B�[���h�Ǘ��N���X
	Player* player;							//�v���C���[����N���X
	ObstructManager* obstructManager;		//�v���C���[�ȊO�̃��f������N���X
	Collision* collision;					//�����蔻��N���X
	GameUI* gameUI;							//�Q�[����UI����N���X
	Effect* effect;							//�G�t�F�N�g����N���X

	VECTOR blackImgPos;						//���w�i�摜�̍��W
	int blackBackGroundHandle;				//���w�i�摜�n���h��

	bool gameSet;							//�Q�[�����I����Ă��邩�ǂ���
	bool changeScene;						//�V�[���J�ڂ��邩�ǂ���
	int blackOutCount;						//�V�[���J�ڎ��̈Ó]����܂ł̍ŏ��̎���
	int alpha;								//�Ó]�p�摜�̃A���t�@�l
	int alphaAdd;							//�A���t�@�l�̕ω��x
};


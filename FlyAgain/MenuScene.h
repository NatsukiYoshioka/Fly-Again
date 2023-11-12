#pragma once
#include"BaseScene.h"
#include<DxLib.h>

#define BACKGROUND_NUM		5		//�w�i�摜�̐�

class BaseScene;

/// <summary>
/// ���j���[�V�[���𐧌䂷��N���X
/// </summary>
class MenuScene :public BaseScene
{
public:
	/// <summary>
	/// �Q�[�����n�߂邩�I��邩�I������
	/// </summary>
	enum class SELECT
	{
		PLAY,
		EXIT
	};

	/// <summary>
	/// �ϐ��ƍ��W�̏������A�e�N�X�`���ƃ��f���̃��[�h
	/// </summary>
	MenuScene();

	/// <summary>
	/// �e�N�X�`���ƃ��f���̌㏈��
	/// </summary>
	~MenuScene();

	/// <summary>
	/// ���j���[�V�[���S�̂̍X�V
	/// </summary>
	void Update();

	/// <summary>
	/// ���{�b�g�̈ʒu�X�V
	/// </summary>
	void UpdateRobot();

	/// <summary>
	/// ���͏���
	/// </summary>
	void UpdateInput();

	/// <summary>
	/// ���j���[�V�[���`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �w�i�`��
	/// </summary>
	void DrawBackgound();

	/// <summary>
	/// UI�`��
	/// </summary>
	void DrawUI();

	/// <summary>
	/// �t�F�[�h�A�E�g�p�̃A���t�@�l�����Z����
	/// </summary>
	void FadeoutProcesse();

	/// <summary>
	/// ���{�b�g�̔������o����
	/// </summary>
	void CrashRobotProcess();

	/// <summary>
	/// ����G�t�F�N�g�̃p�X�擾
	/// </summary>
	/// <returns>����G�t�F�N�g�̃p�X</returns>
	const char* GetBurnEffectPath();

	/// <summary>
	/// �����G�t�F�N�g�̃p�X�擾
	/// </summary>
	/// <returns>�����G�t�F�N�g�̃p�X</returns>
	const char* GetBombEffectPath();

	/// <summary>
	/// ���j���[��ʂ̑I���m�肵�������擾
	/// </summary>
	/// <returns>�I��SELECT�̕ϐ�</returns>
	static SELECT GetMenuSelect() { return choose; }
private:
	static constexpr float speed = 0.01f;					//sin�g�ɂ��ړ��̃X�s�[�h
	static constexpr double exitFontSize = 2.25;			//�uEXIT�v�̃t�H���g�T�C�Y
	static constexpr double controllFontSize = 4.0;			//��������̃t�H���g�T�C�Y
	static constexpr double titleFontSize = 8.0;			//�^�C�g���̃t�H���g�T�C�Y

	int backgroundImgHandle[BACKGROUND_NUM];				//�w�i�摜�n���h��
	int robotModelHandle;									//���{�b�g�̃��f���n���h��
	
	int burnEffectHandle;									//����G�t�F�N�g�n���h��
	int burnPlayingEffectHandle;							//�Đ����̉���G�t�F�N�g�n���h��
	int burnPlayTime;										//����G�t�F�N�g���Đ����鎞��

	int bombEffectHandle;									//�����G�t�F�N�g�n���h��
	int bombPlayingEffectHandle;							//�Đ����̔����G�t�F�N�g�n���h��
	bool isPlayBombEffect;									//�����G�t�F�N�g���Đ��������ǂ���

	int playUIHandle;										//SELEC::PLAY��UI�n���h��
	int nullUIHandle;										//���ȊO��UI�n���h��
	int buttonUIHandle;										//�Q�[������{�^����UI�n���h��
	int stickLightUIHandle;									//�Q�[������X�e�B�b�N��UI�n���h��
	int blackBackgroundHandle;								//�t�F�[�h�C���A�A�E�g�p�̍��w�i�摜

	int scrollSpeed;										//�w�i�̃X�N���[���X�s�[�h
	int scrollX[BACKGROUND_NUM];							//�w�i��X���W�X�N���[����

	VECTOR robotPos;										//���{�b�g�̍��W
	float radian;											//sin�g�̒l

	float fallPower;										//���{�b�g�����������
	const float fallSpeed;									//���{�b�g����������X�s�[�h

	VECTOR playUIPos;										//PLAY�摜�̍��W
	VECTOR nullUIPos;										//�g�݂̂̉摜�̍��W
	VECTOR buttonUIPos;										//�{�^���摜�̍��W
	VECTOR stickLightUIPos;									//���X�e�B�b�N�摜�̍��W

	SELECT select;											//�I�����Ă���UI
	static SELECT choose;									//�I���m�肵��UI

	bool isChoose;											//�I���������ǂ���
	bool isFadeout;											//�t�F�[�h�A�E�g�������s�����ǂ���
	bool isCrashRobot;										//���{�b�g���N���b�V�������鏈�����s�����ǂ���

	int startFlashing;										//�_�ŗp�̏����J�E���g�ϐ�
	int resetFlag;											//startFlashing�����Z�b�g�����񐔂�ێ�����t���O

	int alpha;												//�A���t�@�l
	int blackAlpha;											//�Ó]�p�̃A���t�@�l
	int alphaAdd;											//�A���t�@�l�̕ω��x

	bool isStartGame;										//�Q�[�����X�^�[�g���邩�ǂ���
	bool isStartMenu;										//���j���[��ʂ��n�܂������ǂ���
};
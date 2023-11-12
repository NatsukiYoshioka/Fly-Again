#pragma once
#include"BaseScene.h"

#define BACKGROUND_NUM		6			//�w�i�̖���

class BaseScene;

/// <summary>
/// ���U���g�V�[������N���X
/// </summary>
class ResultScene :public BaseScene
{
public:
	/// <summary>
	/// ���j���[��ʂ��Q�[����ʂɈړ�����
	/// </summary>
	enum class SELECT
	{
		MENU,
		RETRY
	};

	/// <summary>
	/// �ϐ��ƍ��W�̏������A�e�N�X�`���ƃ��f���̃��[�h
	/// </summary>
	ResultScene();

	/// <summary>
	/// �e�N�X�`���ƃ��f���̌㏈��
	/// </summary>
	~ResultScene();

	/// <summary>
	/// ���U���g�V�[���S�̂̍X�V
	/// </summary>
	void Update();

	/// <summary>
	/// ���{�b�g�̋��������X�V
	/// </summary>
	void UpdateRobot();

	/// <summary>
	/// �}�E�X�̋��������X�V
	/// </summary>
	void UpdateMouse();

	/// <summary>
	/// �A�j���[�V�����Đ�����
	/// </summary>
	void UpdateEffect();

	/// <summary>
	/// ���U���g�V�[���`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �N���A���̃G�t�F�N�g�̃p�X�擾
	/// </summary>
	/// <returns>�N���A���̃G�t�F�N�g�̃p�X</returns>
	const char* GetClearEffectPath();

	/// <summary>
	/// �X�^�[���t�������̃G�t�F�N�g�̃p�X�擾
	/// </summary>
	/// <returns>�X�^�[���t�������̃G�t�F�N�g�̃p�X</returns>
	const char* GetStarEffectPath();
private:
	int backgroundImgHandle[BACKGROUND_NUM];				//�w�i�̃n���h��
	int starImgHandle;										//���̉摜�n���h��
	int starShadowImgHandle;								//���̉e�̉摜�n���h��
	int nullUIImgHandle;									//��������UI�n���h��
	int menuImgHandle;										//���j���[UI�n���h��
	int retryImgHandle;										//���g���CUI�n���h��
	int cheeseMarkerImgHandle;								//�I��p�`�[�Y�}�[�J�[�摜�n���h��
	int blackBackgroundHandle;								//���w�i�摜�n���h��

	SELECT select;											//�Q�[���V�[���ړ��ϐ�
	SELECT choose;											//�I�����m�肵���ϐ�
	bool isChoose;											//�I���������ǂ���

	int robotModelHandle;									//���{�b�g�̃��f���n���h��
	int mouseModelHandle;									//�}�E�X�̃��f���n���h��

	int clearEffectHandle;									//�N���A���̃G�t�F�N�g�n���h��
	int clearPlayingEffectHandle;							//�Đ����̃N���A���̃G�t�F�N�g�n���h��

	int starEffectHandle;									//�X�^�[�l�����̃G�t�F�N�g�n���h��
	int starPlayingEffectHandle[3];							//�Đ����̃X�^�[�l�����̃G�t�F�N�g�n���h��

	int mouseAnimation;										//�}�E�X�̃A�j���[�V�����ԍ�

	VECTOR robotPos;										//���{�b�g�̍��W
	VECTOR mousePos;										//�}�E�X�̍��W
	float robotScale;										//���{�b�g�̑傫��
	float mouseScale;										//�}�E�X�̑傫��
	float movePower;										//�ړ��l

	int animationPlayTime;									
	VECTOR clearEffectPos;									//�N���A���̃G�t�F�N�g���W
	bool isPlayingStarEffect[3];							//�X�^�[�G�t�F�N�g���Đ��������ǂ���
	VECTOR starEffectPos[3];								//�X�^�[�l�����̃G�t�F�N�g���W

	static constexpr float risePower = 3.5f;				//�㏸�l
	static constexpr float moveSpeed = 0.05f;				//�ړ����Z�l
	static constexpr float maxMovePower = 20.0f;			//�ő�ړ��l
	static constexpr float scaleSub = 0.0025f;				//�X�P�[���̌��Z�l

	int scrollSpeed;										//�w�i�̃X�N���[���X�s�[�h
	int scrollX[BACKGROUND_NUM];							//�w�i��X���W�X�N���[����

	bool isFadeIn;											//�t�F�[�h�C���������ǂ���
	bool isFadeOut;											//�t�F�[�h�A�E�g���邩�ǂ���
	int alpha;												//�A���t�@�l
	int alphaAdd;											//�A���t�@���Z�l
	int prevCount;											//�b�J�E���g�p�ϐ�
	int maxStarNum;											//����`�悷��ő吔
	int drawStarFlag;										//����`�悷�鐔�𐧌�����t���O
};
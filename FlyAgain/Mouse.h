#pragma once
#include<DxLib.h>

#define MOUSE_FIX_POS_Y		2.5f			//�}�E�X��Y�������蔻�蒲����
#define MOUSE_FIX_POS_Z		5.0f			//�}�E�X��Z�������蔻�蒲����

#define MOUSE_SHADOW_SIZE		15.0f		//�e�̑傫��
#define MOUSE_SHADOW_HEIGHT		700.0f		//�e�������鍂��


class Field;

/// <summary>
/// �}�E�X1�𐧌䂷��N���X
/// </summary>
class Mouse
{
public:
    /// <summary>
    /// ���f���֘A�̃��[�h�ƍ��W�̏�����
    /// </summary>
    /// <param name="modelHandle">�}�E�X�̃��f���n���h��</param>
    Mouse(int modelHandle);

    /// <summary>
    /// ���f���̌㏈��
    /// </summary>
    ~Mouse();

	/// <summary>
	/// �}�E�X�̏o�����W�ƃ��f���̍Ď擾
	/// </summary>
	/// <param name="modelHandle">�}�E�X�̃��f���n���h��</param>
	void Initialize(int modelHandle);

	/// <summary>
	/// �A�j���[�V�����ƍ��W�̍X�V
	/// </summary>
	void Update();

	/// <summary>
	/// ���f���ƃA�j���[�V�����̕`��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���f���̉A�`��
	/// </summary>
	/// <param name="field">�t�B�[���h���f���Ǘ��N���X</param>
	void DrawShadow(Field* field);

	/// <summary>
	/// �}�E�X�̌������Z�b�g
	/// </summary>
	void SetRunningDirection();

	/// <summary>
	/// �}�E�X����ʓ��ɂ��邩�ǂ����̔���
	/// </summary>
	/// <returns>�}�E�X����ʓ��ɂ��邩�ǂ������肷��ϐ�</returns>
	bool IsCheckMouseAppearance();

	/// <summary>
	/// �}�E�X�̌��݂̍��W���擾
	/// </summary>
	/// <returns>�}�E�X�̌��݂̍��W</returns>
	VECTOR GetNowPosition();

	/// <summary>
	/// �}�E�X�̓����蔻����W���擾
	/// </summary>
	/// <returns>�}�E�X�̓����蔻����W</returns>
	VECTOR GetCollPos() { return CollPos; }

	/// <summary>
	/// �}�E�X�̓����蔻��̋��̔��a���擾
	/// </summary>
	/// <returns>�}�E�X�̓����蔻��̋��̔��a</returns>
	float GetHitRadius() { return hitRadius; }

	/// <summary>
	/// �A�̃e�N�X�`���̃p�X�擾
	/// </summary>
	/// <returns></returns>
	const char* GetShadowImgPath();
private:
	enum class AppearanceSide		//�}�E�X���o���������
	{
		TOP,						//�}�E�X����ʏ�̏�̕ǂ���o������
		UNDER,						//�}�E�X����ʏ�̉��̕ǂ���o������
		LEFT,						//�}�E�X����ʏ�̍��̕ǂ���o������
		RIGHT						//�}�E�X����ʏ�̉E�̕ǂ���o������
	};
	int appearanceSide;				//�}�E�X���o������������i�[����ϐ�
	const int MaxTop;				//�e�����̃}�E�X�̏���n�_
	const int MaxUnder;
	const int MaxLeft;
	const int MaxRight;

	VECTOR pos;						//�}�E�X�̍��W
	VECTOR CollPos;					//�}�E�X�̓����蔻����W
	VECTOR firstPos;				//�}�E�X�̏����n�_
	VECTOR finalPos;				//�}�E�X�̍ŏI�n�_
	float angle;					//�}�E�X�̃A���O��
	float fixAngle;					//�}�E�X�̃A���O����X���ɕ��s�ɏC��

	float runningSpeed;				//�ړ����x

	int modelHandle;				//�t�B�[���h�̃��f���n���h��
	int AttachIndex;				//�A�^�b�`����A�j���[�V�����ԍ�
	const int RunningAnimation;		//�}�E�X�̃����A�j���[�V�����ԍ�

	float animPlayTime;				//�A�j���[�V�����Đ�����
	float animTotalTime;			//�A�j���[�V�������Đ�����

	bool isAppearance;				//��ʓ��ɂ��邩�ǂ���

	float hitRadius;				//�����蔻��̋��̔��a

	int shadowHandle;				//�e�摜�n���h��
};


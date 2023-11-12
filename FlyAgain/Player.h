#pragma once
#include<DxLib.h>

#define PLAYER_Z_MAX				15.0f			//�v���C���[��������Z���̍ő���W
#define PLAYER_Z_MIN				-300.0f			//�v���C���[��������Z���̍ŏ����W
#define PLAYER_X_MAX				300.0f			//�v���C���[��������X���̍ő���W
#define PLAYER_X_MIN				-275.0f			//�v���C���[��������X���̍ŏ����W
#define PLAYER_Y_MAX				190.0f			//�v���C���[��������Y���̍ő���W

#define PLAYER_ANGLE_SPEED			20.0f			// �p�x�ω����x
#define PLAYER_MIN_HEIGHT			0.0f			//�v���C���[��������ꏊ�̍Œ�l
#define PLAYER_COLL_POS_Y			12.5f			//�v���C���[��Y�������蔻�蒲����
#define PLAYER_SHADOW_SIZE			20.0f			//�e�̑傫��
#define PLAYER_SHADOW_HEIGHT		700.0f			//�e�������鍂��

#define PLAYER_CLEAR_POINT			5				//�v���C���[���Q�[���N���A����̂ɕK�v�ȃ|�C���g��

#define PLAYER_CRASH_ROTATION_SPEED	10.0f			//�v���C���[�N���b�V�����̉�]�X�s�[�h

class Field;

using namespace std;

/// <summary>
/// �v���C���[�𐧌䂷��N���X
/// </summary>
class Player
{
public:
	/// <summary>
	/// �ϐ��A���W�̏������ƃ��f���̎擾
	/// </summary>
	Player();

	/// <summary>
	/// ���f���̌㏈��
	/// </summary>
	~Player();

	/// <summary>
	/// ���͏����ƍ��W�̍X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �v���C���[�̓��������̍X�V
	/// </summary>
	/// <param name="shaft">�����̗�</param>
	/// <param name="maxSpeed">�v���C���[�����ɓ����X�s�[�h�̍ő�l</param>
	void UpdateSpeed(float* shaft,const float maxSpeed);

	/// <summary>
	/// �v���C���[�̌������C��
	/// </summary>
	void UpdateAngle();

	/// <summary>
	/// ��R����
	/// </summary>
	void ResistanceProcess();

	/// <summary>
	/// �v���C���[���t�B�[���h�O�ɏo�Ȃ��悤�ɂ��鏈��
	/// </summary>
	void FixPos();

	/// <summary>
	/// ���f���̕`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �v���C���[�̉e�̕`��
	/// </summary>
	/// <param name="field"></param>
	void DrawShadow(Field* field);

	/// <summary>
	/// �n�ʂɓ����������̏���
	/// </summary>
	void OnHitGround();

	/// <summary>
	/// �n�ʈȊO�̃��f���ɓ��������ꍇ�̏���
	/// </summary>
	/// <param name="hitFlag">���f���ɓ����������ǂ���</param>
	void OnHitObstruct(bool hitFlag);

	/// <summary>
	/// �|�C���g�t�^�֐�
	/// </summary>
	/// <param name="randNum">�����`�������ɂ��邩�ǂ���</param>
	/// <returns>�����`�������true��Ԃ�</returns>
	bool GivePoint(int randNum);

	/// <summary>
	/// �����蔻����W�擾
	/// </summary>
	/// <returns>�����蔻����W</returns>
	VECTOR GetCollPos() { return CollPos; }

	/// <summary>
	/// �����蔻��̋��̔��a�̎擾
	/// </summary>
	/// <returns>�����蔻��̋��̔��a</returns>
	float GetHitRadius() { return hitRadius; }

	/// <summary>
	/// �R���⋋
	/// </summary>
	void FuelSupply();

	/// <summary>
	/// �v���C���[�̔R�������擾
	/// </summary>
	/// <returns>�R������</returns>
	double GetfuelPercent() { return nowFuel / maxFuel * 100; }

	/// <summary>
	/// �v���C���[�̎c�@�擾
	/// </summary>
	/// <returns>�v���C���[�̎c�@</returns>
	int GetPlayerHP() { return HP; };

	/// <summary>
	/// �v���C���[�̃|�C���g���擾
	/// </summary>
	/// <returns>�v���C���[�̃|�C���g��</returns>
	int GetPoint() { return point; }

	/// <summary>
	/// �A�̃e�N�X�`���p�X�擾
	/// </summary>
	/// <returns></returns>
	const char* GetShadowImgPath();
private:
	static constexpr float jump = 5.0f;						//�W�����v�͌Œ�l
	 			
	static constexpr float gravity = 0.1f;					//�d�͉��Z�l
	static constexpr float maxGravityPower = 7.0f;			//�d�͍ő�l
	 			
	static constexpr float lift = 0.15f;					//�g�͉��Z�l
	static constexpr float maxLiftPower = 3.5f;				//�g�͍ő�l
	static constexpr float crashBoundPower = 2.5f;			//�n�ʂɓ����������̏㏸�x
	 			
	static constexpr float speed = 0.3f;					//�v���C���[�̉��ɓ����X�s�[�h�̉��Z�l
	static constexpr float maxSpeed = 4.0f;					//�v���C���[�����ɓ����X�s�[�h�̍ő�l
	static constexpr float airResistance = 0.1f;			//�v���C���[���i�ޕ����ɂ������C��R
	 			
	static constexpr double maxFuel = 100.0;				//�v���C���[�̃z�o�����O�p�ő�R��
	static constexpr double fuelDecreaseSpeed = -2.5;		//�R���̌����X�s�[�h

	float jumpPower;							//�t���[�����̃W�����v��
	float gravityPower;							//�t���[�����̏d��
	float liftPower;							//�t���[�����̗g��
	float nowXSpeed;							//���݂̃v���C���[��X���X�s�[�h
	float nowZSpeed;							//���݂̃v���C���[��Z���X�s�[�h

	VECTOR MoveVec;								//�v���C���[����������
	VECTOR TargetMoveDirection;					// ���f���������ׂ������̃x�N�g��
	float Angle;								// ���f���������Ă�������̊p�x

	VECTOR pos;									//�v���C���[���f���̍��W
	VECTOR CollPos;								//�v���C���[�̓����蔻����W
	float hitRadius;							//�����蔻��̋��̔��a

	int modelHandle;							//�t�B�[���h�̃��f���n���h��
	int shadowHandle;							//�v���C���[�̉e�̃n���h��

	int HP;										//�v���C���[�̎c�@
	int point;									//�v���C���[���N���A�ɕK�v�ȃ|�C���g��

	bool crash;									//�v���C���[���n�ʂɓ����������ǂ���
	float crashRotation;						//�v���C���[���_���[�W���󂯂����̉�]��

	double nowFuel;								//���݂̔R��
};


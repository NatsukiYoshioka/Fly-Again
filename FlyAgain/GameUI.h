#pragma once

#define BROKEN_HEART_DRAW_COUNT		1		//����n�[�g�摜��`�悷�鎞��
#define WALL_UP_HOLE_NUM			6		//�㑤�̕ǂ̌��̐�
#define WALL_SIDE_HOLE_NUM			4		//���[�̕ǂ̌��̐�
#define HOLE_SIZE					20.0f	//�����̃T�C�Y

class Player;
class Field;

/// <summary>
/// �Q�[���V�[����UI�Ǘ��N���X
/// </summary>
class GameUI
{
public:
	/// <summary>
	/// �ϐ��̏������ƃe�N�X�`���̃��[�h
	/// </summary>
	/// <param name="playerHP">�v���C���[��HP</param>
	GameUI(int playerHP);

	/// <summary>
	/// �e�N�X�`���̌㏈��
	/// </summary>
	~GameUI();

	/// <summary>
	/// UI�`�揈���̍X�V
	/// </summary>
	/// <param name="player">�v���C���[����N���X</param>
	void Update(Player* player);

	/// <summary>
	/// UI�̕`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �����̕`��
	/// </summary>
	/// <param name="field">�t�B�[���h�Ǘ��N���X</param>
	void DrawHole(Field* field);

	/// <summary>
	/// �Q�[�����J�n���邩�ǂ������擾����
	/// </summary>
	/// <returns>�Q�[���J�n���邩�ǂ����m�F����t���O</returns>
	bool GetIsStartGame() { return isStartGame; }
private:
	int heartImgHandle;						//�n�[�g�摜�n���h��
	int brokenHeartImgHandle;				//����n�[�g�摜�n���h��
	int wrenchImgHandle;					//�����`�摜�n���h��
	int circleImgHandle;					//�~�Q�[�W�摜�n���h��
	int circleCheeseImgHandle;				//�`�[�Y�~�Q�[�W�p�摜�n���h��
	int buttonAImgHandle;					//A�{�^���摜�n���h��
	int holeImgHandle;						//�����摜�n���h��
	int blackBackgroundHandle;				//���w�i�摜�n���h��

	VECTOR heartPos;						//�n�[�g�摜�̃��[���h���W

	VECTOR brokenHeartPos;					//����n�[�g�摜�̃��[���h���W

	VECTOR wrenchPos;						//�����`�摜�̃��[���h���W

	int heartNum;							//�n�[�g�̌��݂̐�
	int heartPrevNum;						//�n�[�g�̉ߋ��̐�
	int wrenchNum;							//�����`�̌��݂̐�

	double fuelPercent;						//�v���C���[�̔R���̊���

	int brokenStartCount;					//����n�[�g�摜��`�悷��ŏ��̎���

	bool isStartGame;						//�Q�[���J�n���邩�ǂ���
	int startGameCount;						//�Q�[�����X�^�[�g����܂ł̃J�E���g
	const int maxCount;						//�J�E���g����ő�b��
	int startFlag;							//�Q�[�����n�߂�t���O

	int blackAlpha;							//�J�n�O�̍��w�i�̃A���t�@�l
	int alphaAdd;							//�A���t�@�l�̉��Z�l
	int descriptionAlpha;					//�t�H���g�̃A���t�@�l
	const int maxAlpha;						//�Q�[�����̃A���t�@�l�̍ő�l

	static constexpr int initialHeartPrevNum = 0;			//�n�[�g�̉ߋ��̐��̏������p�萔
	static constexpr int initialWrenchNum = 0;				//�����`�̌��݂̐��̏������p�萔
	static constexpr int initialBrokenStartCount = 0;		//����n�[�g�摜��`�悷��ŏ��̎��Ԃ̏������p�萔
	static constexpr int initialMaxCount = 7;				//�J�E���g����ő�b���̏������p�萔
	static constexpr int initialStartFlag = 0;				//�Q�[�����n�߂�t���O�̏������p�萔
	static constexpr int initialBlackAlpha = 255;			//�J�n�O�̍��w�i�̃A���t�@�l�̏������p�萔
	static constexpr int initialDescriptionAlpha = 0;		//�t�H���g�̃A���t�@�l�̏������p�萔
	static constexpr int initialAlphaAdd = -1;				//�A���t�@�l�̉��Z�l�̏������p�萔
	static constexpr int initialMaxAlpha = 127;				//�A���t�@�l�̍ő�l�̏������p�萔
	static constexpr float initialFuelPercent = 0.0f;		//�v���C���[�̔R���̊����̏������p�萔
	static const VECTOR initialHeartPos;					//�n�[�g�摜�̃��[���h���W�̏������p�萔
	static const VECTOR initialBrokenHeartPos;				//����n�[�g�摜�̃��[���h���W�̏������p�萔
	static const VECTOR initialWrenchPos;					//�����`�摜�̃��[���h���W�̏������p�萔

	static constexpr int secondCount = 1000;				//1�b�̃J�E���g�p�萔
	static constexpr int descriptionFactor = 2;				//�t�H���g�̃A���t�@�l���Z�W��
	static constexpr int alphaMaxLimit = 255;				//�A���t�@�l�̍ő�l

	static constexpr int circleCenterX = 957;				//�~�摜��X���W
	static constexpr int circleCenterY = 100;				//�~�摜��Y���W
	static constexpr double circlePercent = 100.0;			//�~�摜�̕\������
	static constexpr double circleStartPercent = 0.0;		//�~�摜�̏�������
	static constexpr double circleScale = 0.1 * (3.0 / 4.0);//�~�摜�̃X�P�[��
	static constexpr int circleReverseX = 0;				//�~�摜��X�����]
	static constexpr int circleReverseY = 0;				//�~�摜��Y�����]

	static constexpr int circleCheeseCenterX = 960;			//�~�Q�[�W��X���W
	static constexpr int circleCheeseCenterY = 100;			//�~�Q�[�W��Y���W
	static constexpr double circleCheeseScale = 0.1;		//�~�Q�[�W�̃X�P�[��

	static constexpr int jumpUIX1 = 860;					//"JUMP"UI�̍����X���W
	static constexpr int jumpUIY1 = 150;					//"JUMP"UI�̍����Y���W
	static constexpr int jumpUIX2 = 930;					//"JUMP"UI�̉E����X���W
	static constexpr int jumpUIY2 = 220;					//"JUMP"UI�̉E����Y���W

	static constexpr int middleFontSize = 48;				//�t�H���g�̒��T�C�Y
	static constexpr int jumpStringX = 930;					//"JUMP"������X���W
	static constexpr int jumpStringY = 165;					//"JUMP"������Y���W
	static constexpr const char* jumpString = "JUMP";		//"JUMP"������
	static const unsigned int jumpStringColor;				//"JUMP"�����̃J���[
};


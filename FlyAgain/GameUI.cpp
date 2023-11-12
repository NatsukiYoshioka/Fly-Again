#include"UIManager.h"
#include"Player.h"
#include"Field.h"
#include"common.h"
#include"DxLib.h"
#include "GameUI.h"

const VECTOR GameUI::initialHeartPos = VGet(0.0f, 0.0f, 0.0f);
const VECTOR GameUI::initialBrokenHeartPos = VGet(0.0f, 0.0f, 0.0f);
const VECTOR GameUI::initialWrenchPos = VGet(0.0f, 0.0f, 0.0f);

const unsigned int GameUI::jumpStringColor = GetColor(0, 0, 0);

GameUI::GameUI(int playerHP) :
	heartPrevNum			(initialHeartPrevNum),
	wrenchNum				(initialWrenchNum),
	brokenStartCount		(initialBrokenStartCount),
	fuelPercent				(initialFuelPercent),
	isStartGame				(false),
	maxCount				(initialMaxCount),
	startFlag				(initialStartFlag),
	blackAlpha				(initialBlackAlpha),
	descriptionAlpha		(initialDescriptionAlpha),
	alphaAdd				(initialAlphaAdd),
	maxAlpha				(initialMaxAlpha)
{
	//UI�e�N�X�`���̎擾
	heartImgHandle = UIManager::GetHeartImgHandle();
	brokenHeartImgHandle = UIManager::GetBrokenHeartImgHandle();
	wrenchImgHandle = UIManager::GetWrenchImgHandle();
	circleImgHandle = UIManager::GetCircleImgHandle();
	circleCheeseImgHandle = UIManager::GetCircleCheeseImgHandle();
	buttonAImgHandle = UIManager::GetButtonAImgHandle();
	holeImgHandle = UIManager::GetHoleImgHandle();
	blackBackgroundHandle = UIManager::GetBlackBackGroundHandle();

	//�e�N�X�`�����W�̐ݒ�
	heartPos = initialHeartPos;

	brokenHeartPos = initialBrokenHeartPos;

	wrenchPos = initialWrenchPos;

	heartNum = playerHP;

	//�Q�[�����X�^�[�g����ŏ��̎��Ԃ��擾
	startGameCount = GetNowCount();
}

//�e�N�X�`���̌㏈��
GameUI::~GameUI()
{
	DeleteGraph(heartImgHandle);
	DeleteGraph(brokenHeartImgHandle);
	DeleteGraph(wrenchImgHandle);
	DeleteGraph(circleImgHandle);
	DeleteGraph(circleCheeseImgHandle);
	DeleteGraph(buttonAImgHandle);
	DeleteGraph(holeImgHandle);
	DeleteGraph(blackBackgroundHandle);
}

//UI�`�揈���̍X�V
void GameUI::Update(Player* player)
{
	//�v���C���[�̔R���̊������擾
	fuelPercent = player->GetfuelPercent();

	//�v���C���[�̎c�@���X�V����Ă����ꍇ�̏���
	if (heartNum > player->GetPlayerHP())
	{
		//�X�V�����O�̎c�@��ۑ�
		heartPrevNum = heartNum;
		//�X�V��̎c�@�擾
		heartNum = player->GetPlayerHP();
		//����n�[�g��`�悷��ŏ��̎��Ԃ��擾
		brokenStartCount = GetNowCount();
	}
	//�v���C���[�̃|�C���g�擾
	wrenchNum = player->GetPoint();
	
	//�Q�[���J�n�J�E���g�_�E��
	if (GetNowCount() - startGameCount > secondCount && startFlag <= maxCount)
	{
		startGameCount = GetNowCount();
		startFlag++;
	}

	//�J�n�O��UI�A���t�@�l����
	if (!isStartGame)
	{
		if (startFlag == maxCount)
		{
			isStartGame = true;
		}
		blackAlpha += alphaAdd;
		descriptionAlpha -= alphaAdd * descriptionFactor;
		if (blackAlpha <= maxAlpha)
		{
			blackAlpha = maxAlpha;
		}
		if (descriptionAlpha >= alphaMaxLimit)
		{
			descriptionAlpha = alphaMaxLimit;
		}
	}
}

//UI�`��
void GameUI::Draw()
{
	//�v���C���[�̔R���Q�[�W�`��
	DrawCircleGauge(circleCenterX, circleCenterY, circlePercent, circleImgHandle, circleStartPercent, circleScale, circleReverseX, circleReverseY);
	DrawCircleGauge(circleCheeseCenterX, circleCheeseCenterY, fuelPercent, circleCheeseImgHandle, circleStartPercent, circleCheeseScale, circleReverseX, circleReverseY);
	DrawExtendGraph(jumpUIX1, jumpUIY1, jumpUIX2, jumpUIY2, buttonAImgHandle, TRUE);

	SetFontSize(middleFontSize);
	DrawString(jumpStringX, jumpStringY, jumpString, jumpStringColor);
	//�n�[�g�̕`��
	for (int i = 0; i < heartNum; i++)
	{
		heartPos = VGet(-400.0f + static_cast<float>(i) * 50.0f, 250.0f, 0.0f);
		DrawBillboard3D(heartPos, 0.5f, 0.5f, 50.0f, 0.0f, heartImgHandle, TRUE);
	}
	//����n�[�g�̕`��
	if (heartNum < heartPrevNum && brokenStartCount + (BROKEN_HEART_DRAW_COUNT * 1000) > GetNowCount() && heartNum >= 0)
	{
		brokenHeartPos = VGet(-400.0f + static_cast<float>(heartPrevNum - 1) * 50.0f, 250.0f, 0.0f);
		DrawBillboard3D(brokenHeartPos, 0.5f, 0.5f, 50.0f, 0.0f, brokenHeartImgHandle, TRUE);
	}
	//�擾���������`�̕`��
	if (wrenchNum > 0)
	{
		for (int i = 0; i < wrenchNum; i++)
		{
			wrenchPos = VGet(-400.0f + static_cast<float>(i) * 50.0f, 200.0f, 0.0f);
			DrawBillboard3D(wrenchPos, 0.5f, 0.5f, 50.0f, 45.0f, wrenchImgHandle, TRUE);
		}
	}

	//�J�n�O�̐���
	if (!isStartGame)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, blackAlpha);
		DrawExtendGraph(0, 0, 1920, 1080, blackBackgroundHandle, FALSE);

		ChangeFont("x12y16pxMaruMonica", DX_CHARSET_DEFAULT);
		SetFontSize(64);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, descriptionAlpha);
		DrawStringF(360.0f, 740.0f, "�n�ʂɗ������Ƀl�Y�~�𓥂�Ń����`��5�W�߂悤�I", GetColor(255, 255, 0));

		if (descriptionAlpha == 255)
		{
			SetFontSize(256);
			//�J�E���g�_�E���\��
			if (static_cast<float>(maxCount) - static_cast<float>(startFlag * 1000 + (GetNowCount() - startGameCount)) / 1000.0f < 1.0f)
			{
				DrawString(700.0f, 340.0f, "Start!", GetColor(255, 255, 255));
			}
			else
			{
				DrawFormatStringF(835.0f, 340.0f, GetColor(255, 255, 255), "%.1f", static_cast<float>(maxCount) - static_cast<float>(startFlag * 1000 + (GetNowCount() - startGameCount)) / 1000.0f);
			}
		}
		ChangeFont("ArcadeClassic", DX_CHARSET_DEFAULT);
		SetFontSize(16);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		
	}
}

void GameUI::DrawHole(Field* field)
{
	VERTEX3D Vertex[6];

	// ���C�e�B���O�𖳌��ɂ���
	SetUseLighting(FALSE);

	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �Q�|���S�����̒��_�̍��W�Ɩ@���ȊO�̃f�[�^���Z�b�g
	Vertex[0].dif = GetColorU8(255, 255, 255, 255);
	Vertex[0].spc = GetColorU8(0, 0, 0, 0);
	Vertex[0].u = 0.0f;
	Vertex[0].v = 0.0f;
	Vertex[0].su = 0.0f;
	Vertex[0].sv = 0.0f;

	Vertex[1].dif = GetColorU8(255, 255, 255, 255);
	Vertex[1].spc = GetColorU8(0, 0, 0, 0);
	Vertex[1].u = 1.0f;
	Vertex[1].v = 0.0f;
	Vertex[1].su = 0.0f;
	Vertex[1].sv = 0.0f;

	Vertex[2].dif = GetColorU8(255, 255, 255, 255);
	Vertex[2].spc = GetColorU8(0, 0, 0, 0);
	Vertex[2].u = 0.0f;
	Vertex[2].v = 1.0f;
	Vertex[2].su = 0.0f;
	Vertex[2].sv = 0.0f;

	Vertex[3].dif = GetColorU8(255, 255, 255, 255);
	Vertex[3].spc = GetColorU8(0, 0, 0, 0);
	Vertex[3].u = 1.0f;
	Vertex[3].v = 1.0f;
	Vertex[3].su = 0.0f;
	Vertex[3].sv = 0.0f;

	Vertex[4] = Vertex[2];
	Vertex[5] = Vertex[1];

	MATRIX TransformMatrix;

	//�㑤�̕�
	for (int i = 0; i < WALL_UP_HOLE_NUM; i++)
	{
		//���W�ړ��s��̍쐬
		TransformMatrix = MGetTranslate(VGet(-250.0f + i * 100, GROUND_HEIGHT, 30.0f));

		//�s����g���ă��[���h���W���Z�o
		Vertex[0].pos = VTransform(VGet(-35.0f, 35.0f, 0.0f), TransformMatrix);
		Vertex[1].pos = VTransform(VGet(35.0f, 35.0f, 0.0f), TransformMatrix);
		Vertex[2].pos = VTransform(VGet(-35.0f, -35.0f, 0.0f), TransformMatrix);
		Vertex[3].pos = VTransform(VGet(35.0f, -35.0f, 0.0f), TransformMatrix);

		Vertex[4].pos = Vertex[2].pos;
		Vertex[5].pos = Vertex[1].pos;

		// �s����g���Ė@�����Z�o
		Vertex[0].norm = VTransformSR(VGet(0.0f, 0.0f, -1.0f), TransformMatrix);
		Vertex[1].norm = Vertex[0].norm;
		Vertex[2].norm = Vertex[0].norm;
		Vertex[3].norm = Vertex[0].norm;
		Vertex[4].norm = Vertex[0].norm;
		Vertex[5].norm = Vertex[0].norm;

		// �Q�|���S���̕`��
		DrawPolygon3D(Vertex, 2, holeImgHandle, TRUE);
	}

	//�����̕�
	for (int i = 0; i < WALL_SIDE_HOLE_NUM; i++)
	{
		TransformMatrix = MGetRotY(-90.0f * DX_PI_F / 180.0f);
		TransformMatrix = MMult(TransformMatrix, MGetTranslate(VGet(-310.0f, GROUND_HEIGHT, -50.0f - i * 75.0f)));

		//�s����g���ă��[���h���W���Z�o
		Vertex[0].pos = VTransform(VGet(-35.0f, 35.0f, 0.0f), TransformMatrix);
		Vertex[1].pos = VTransform(VGet(35.0f, 35.0f, 0.0f), TransformMatrix);
		Vertex[2].pos = VTransform(VGet(-35.0f, -35.0f, 0.0f), TransformMatrix);
		Vertex[3].pos = VTransform(VGet(35.0f, -35.0f, 0.0f), TransformMatrix);

		Vertex[4].pos = Vertex[2].pos;
		Vertex[5].pos = Vertex[1].pos;

		// �s����g���Ė@�����Z�o
		Vertex[0].norm = VTransformSR(VGet(0.0f, 0.0f, -1.0f), TransformMatrix);
		Vertex[1].norm = Vertex[0].norm;
		Vertex[2].norm = Vertex[0].norm;
		Vertex[3].norm = Vertex[0].norm;
		Vertex[4].norm = Vertex[0].norm;
		Vertex[5].norm = Vertex[0].norm;

		// �Q�|���S���̕`��
		DrawPolygon3D(Vertex, 2, holeImgHandle, TRUE);
	}

	//�E���̕�
	for (int i = 0; i < WALL_SIDE_HOLE_NUM; i++)
	{
		TransformMatrix = MGetRotY(90.0f * DX_PI_F / 180.0f);
		TransformMatrix = MMult(TransformMatrix, MGetTranslate(VGet(330.0f, GROUND_HEIGHT, -50.0f - i * 75.0f)));

		//�s����g���ă��[���h���W���Z�o
		Vertex[0].pos = VTransform(VGet(-35.0f, 35.0f, 0.0f), TransformMatrix);
		Vertex[1].pos = VTransform(VGet(35.0f, 35.0f, 0.0f), TransformMatrix);
		Vertex[2].pos = VTransform(VGet(-35.0f, -35.0f, 0.0f), TransformMatrix);
		Vertex[3].pos = VTransform(VGet(35.0f, -35.0f, 0.0f), TransformMatrix);

		Vertex[4].pos = Vertex[2].pos;
		Vertex[5].pos = Vertex[1].pos;

		// �s����g���Ė@�����Z�o
		Vertex[0].norm = VTransformSR(VGet(0.0f, 0.0f, -1.0f), TransformMatrix);
		Vertex[1].norm = Vertex[0].norm;
		Vertex[2].norm = Vertex[0].norm;
		Vertex[3].norm = Vertex[0].norm;
		Vertex[4].norm = Vertex[0].norm;
		Vertex[5].norm = Vertex[0].norm;

		// �Q�|���S���̕`��
		DrawPolygon3D(Vertex, 2, holeImgHandle, TRUE);
	}

	// ���C�e�B���O��L���ɂ���
	SetUseLighting(TRUE);

	// �y�o�b�t�@�𖳌��ɂ���
	SetUseZBuffer3D(FALSE);
}
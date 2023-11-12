#include"BaseScene.h"
#include"SceneManager.h"
#include"PadInput.h"
#include"UIManager.h"
#include"ModelManager.h"
#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include<cmath>
#include "MenuScene.h"

MenuScene::SELECT MenuScene::choose = SELECT::PLAY;

//�ϐ��ƍ��W�̏������A�e�N�X�`���ƃ��f���̃��[�h
MenuScene::MenuScene() :
	scrollSpeed(1),
	radian(0.0f),
	fallPower(1.0f),
	fallSpeed(-0.05f),
	burnPlayingEffectHandle(0),
	burnPlayTime(0),
	bombPlayingEffectHandle(0),
	isPlayBombEffect(false),
	select(SELECT::PLAY),
	isChoose(false),
	isFadeout(false),
	isCrashRobot(false),
	startFlashing(1),
	resetFlag(0),
	alpha(255),
	blackAlpha(255),
	alphaAdd(-2),
	isStartGame(false),
	isStartMenu(false)
{
	//�J�����̈ʒu���Z�b�g
	SetCameraPositionAndTargetAndUpVec(VGet(0, 215, -500), VGet(0, 0, 0), VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));

	//�w�i�摜�̃X�N���[���ʂ�������
	for (int i = 0; i < BACKGROUND_NUM; i++)
	{
		scrollX[i] = 0;
	}

	//�w�i�摜�����[�h
	backgroundImgHandle[0] = LoadGraph("data/texture/1.png");
	backgroundImgHandle[1] = LoadGraph("data/texture/2.png");
	backgroundImgHandle[2] = LoadGraph("data/texture/3.png");
	backgroundImgHandle[3] = LoadGraph("data/texture/4.png");
	backgroundImgHandle[4] = LoadGraph("data/texture/5.png");

	//UI�����[�h
	playUIHandle = LoadGraph("data/texture/UI/play.png");
	nullUIHandle = LoadGraph("data/texture/UI/null.png");
	buttonUIHandle = UIManager::GetButtonAImgHandle();
	stickLightUIHandle = LoadGraph("data/texture/UI/stick_light.png");
	blackBackgroundHandle = UIManager::GetBlackBackGroundHandle();

	//���{�b�g��3D���f�����擾
	robotModelHandle = MV1DuplicateModel(ModelManager::GetRobotModelHandle());

	//�G�t�F�N�g�����[�h
	burnEffectHandle = LoadEffekseerEffect(GetBurnEffectPath(), 2.0f);
	bombEffectHandle = LoadEffekseerEffect(GetBombEffectPath(), 10.0f);

	//���W�̏�����
	robotPos = VGet(0.0f, -100.0f, 0.0f);

	//���f���̏k��
	MV1SetScale(robotModelHandle, VGet(0.15f, 0.15f, 0.15f));

	//���f���̉�]
	MV1SetRotationXYZ(robotModelHandle, VGet(0.0f, -90.0f * DX_PI_F / 180.0f, 0.0f));

	//UI�̍��W��ݒ�
	playUIPos = VGet(-200.0f, -150.0f, 0.0f);
	nullUIPos = VGet(200.0f, -150.0f, 0.0f);
	buttonUIPos = VGet(-400.0f, 250.0f, 0.0f);
	stickLightUIPos = VGet(-417.0f, 200.0f, 0.0f);
}

//�e�N�X�`���ƃ��f���̌㏈��
MenuScene::~MenuScene()
{
	DeleteGraph(*backgroundImgHandle);
	DeleteGraph(playUIHandle);
	DeleteGraph(nullUIHandle);
	DeleteGraph(buttonUIHandle);
	DeleteGraph(stickLightUIHandle);

	MV1DeleteModel(robotModelHandle);
	DeleteEffekseerEffect(burnEffectHandle);
	DeleteEffekseerEffect(bombEffectHandle);
}

//���j���[�V�[���S�̂̍X�V
void MenuScene::Update()
{
	//���{�b�g�Ɠ��͏����̍X�V
	UpdateRobot();
	UpdateInput();

	//�v���C��I�������ꍇ�̉��o����
	FadeoutProcesse();
	CrashRobotProcess();

	//���o���I�������Q�[���V�[���ɑJ�ڂ���
	if (isStartGame)
	{
		SceneManager::ChangeScene(SceneManager::SCENE::GAME);
	}

	/*if (CheckHitKey(KEY_INPUT_E) != 0)
	{
		SceneManager::ChangeScene(SceneManager::RESULT);
	}*/
}

//���{�b�g�̈ʒu�X�V
void MenuScene::UpdateRobot()
{
	//UI�̑I���ʒu�Ƀ��{�b�g���ړ�
	if (!isChoose)
	{
		if (select == SELECT::PLAY)
		{
			robotPos.x = -180.0f;
		}
		else
		{
			robotPos.x = 180.0f;
		}
	}
	//���{�b�g�̊�{�����̏���
	if (!isCrashRobot)
	{
		radian += speed;
		if (radian >= 2.0f)
		{
			radian = 0.0f;
		}
		robotPos.y += sinf(radian * DX_PI_F);
	}
	//���{�b�g�����������Ƃ��Ƀ��{�b�g�𗎉�������
	if (isPlayBombEffect)
	{
		fallPower += fallSpeed;
		robotPos.y += fallPower;
	}
	MV1SetPosition(robotModelHandle, robotPos);
}

//���͏���
void MenuScene::UpdateInput()
{
	//�I������
	if (isStartMenu && !isChoose)
	{
		if (PadInput::GetPadInput().ThumbLX < 0 || CheckHitKey(KEY_INPUT_A) != 0)
		{
			select = SELECT::PLAY;
		}
		if (PadInput::GetPadInput().ThumbLX > 0 || CheckHitKey(KEY_INPUT_D) != 0)
		{
			select = SELECT::EXIT;
		}
		//PLAY��I�������牉�o���X�^�[�g������
		if (PadInput::GetPadInput().Buttons[12] || CheckHitKey(KEY_INPUT_RETURN) != 0)
		{
			choose = select;
			isChoose = true;
			if (choose == SELECT::PLAY)
			{
				startFlashing = GetNowCount();
			}
			else
			{
				PadInput::End();
			}
		}
	}
}

//���j���[�V�[���`��
void MenuScene::Draw()
{
	//�w�i��UI�̕`��
	DrawBackgound();
	DrawUI();

	//PLAY��I�����Ă�����G�t�F�N�g���`�悳��ĉ�ʂ��t�F�[�h�A�E�g������
	if (isCrashRobot)
	{
		DrawEffekseer3D();
	}
	if (isCrashRobot || !isStartMenu)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, blackAlpha);
		DrawExtendGraph(0, 0, 1920, 1080, blackBackgroundHandle, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	//DrawString(0, 16, "MENU", GetColor(255, 255, 255));
}

//�w�i�`��
void MenuScene::DrawBackgound()
{
	//�w�i�摜�`��
	for (int i = 0; i < BACKGROUND_NUM; i++)
	{
		DrawExtendGraph(0 - scrollX[i], 0, 1920 - scrollX[i], 1080, backgroundImgHandle[i], TRUE);
		DrawExtendGraph(1920 - scrollX[i], 0, 1920 * 2 - scrollX[i], 1080, backgroundImgHandle[i], TRUE);
		scrollX[i] += i * scrollSpeed;
		if (scrollX[i]>=1920)
		{
			scrollX[i] = 0;
		}
	}
	//�^�C�g���`��
	ChangeFont("Starry Night", DX_CHARSET_DEFAULT);
	SetFontSize(200);
	DrawStringF(550.0f, 300.0f, "Fly Again", GetColor(255, 255, 255));
	ChangeFont("ArcadeClassic", DX_CHARSET_DEFAULT);

	//���{�b�g�`��
	MV1DrawModel(robotModelHandle);
}

void MenuScene::DrawUI()
{
	//�t�F�[�h�A�E�g�����邩�ǂ���
	if (isFadeout)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	}
	//PLAY UI
	DrawBillboard3D(playUIPos, 0.5f, 0.5f, 200.0f, 0.0f, nullUIHandle, TRUE);
	//�_�ŏ���
	if (GetNowCount() - startFlashing >= 250 && startFlashing != 0 && choose == SELECT::PLAY)
	{
		DrawBillboard3D(playUIPos, 0.5f, 0.5f, 200.0f, 0.0f, playUIHandle, TRUE);
	}
	if (GetNowCount() - startFlashing >= 500 && isChoose && resetFlag < 2 && choose == SELECT::PLAY)
	{
		startFlashing = GetNowCount();
		resetFlag++;
	}

	//EXIT UI
	SetFontSize(32);
	DrawBillboard3D(nullUIPos, 0.5f, 0.5f, 200.0f, 0.0f, nullUIHandle, TRUE);
	DrawStringF(1240.0f,735.0f, "EXIT", GetColor(184, 134, 11));

	//Controller UI
	SetFontSize(64);
	DrawBillboard3D(buttonUIPos, 0.5f, 0.5f, 50.0f, 0.0f, buttonUIHandle, TRUE);
	DrawBillboard3D(stickLightUIPos, 0.5f, 0.5f, 50.0f, 0.0f, stickLightUIHandle, TRUE);
	DrawStringF(175.0f, 30.0f, "CONFIRM AND JUMP", GetColor(255, 255, 255));
	DrawStringF(175.0f, 140.0f, "SELECT AND MOVE", GetColor(255, 255, 255));
	SetFontSize(16);

	if (isFadeout)
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

//�t�F�[�h�A�E�g�p�̃A���t�@�l�����Z����
void MenuScene::FadeoutProcesse()
{
	//�Q�[���N�����̃t�F�[�h�C������
	if (!isStartMenu)
	{
		blackAlpha += alphaAdd;
		if (blackAlpha <= 0)
		{
			blackAlpha = 0;
			isStartMenu = true;
		}
	}

	//PLAY���_�ł��ă��{�b�g�������������t�F�[�h�A�E�g���n�߂�
	if (resetFlag == 2)
	{
		isFadeout = true;
	}
	if (isFadeout && !isCrashRobot)
	{
		alpha += alphaAdd;
		if (alpha <= 0)
		{
			isCrashRobot = true;
		}
	}
	if (isPlayBombEffect)
	{
		alphaAdd = 1;
		blackAlpha += alphaAdd;
		if (blackAlpha >= 255)
		{
			isStartGame = true;
		}
	}
}

//���{�b�g�̔������o����
void MenuScene::CrashRobotProcess()
{
	if (isCrashRobot)
	{
		if (burnPlayTime % 60 == 0)
		{
			//�G�t�F�N�g���Đ�
			burnPlayingEffectHandle = PlayEffekseer3DEffect(burnEffectHandle);
			if (!isPlayBombEffect)
			{
				bombPlayingEffectHandle = PlayEffekseer3DEffect(bombEffectHandle);
				isPlayBombEffect = true;
			}
		}

		//�Đ����̃G�t�F�N�g�ɍ��W��ݒ肷��
		SetPosPlayingEffekseer3DEffect(burnPlayingEffectHandle, robotPos.x, robotPos.y + 10.0f, robotPos.z);
		SetPosPlayingEffekseer3DEffect(bombPlayingEffectHandle, robotPos.x, robotPos.y + 10.0f, robotPos.z);

		//�Đ����̃G�t�F�N�g���X�V����
		UpdateEffekseer3D();

		//���Ԃ��o�߂�����
		burnPlayTime++;
	}
}

//����G�t�F�N�g�̃p�X�擾
const char* MenuScene::GetBurnEffectPath()
{
	return "data/effect/bomb.efkefc";
}

//�����G�t�F�N�g�̃p�X�擾
const char* MenuScene::GetBombEffectPath()
{
	return "data/effect/crash.efk";
}
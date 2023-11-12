#include"BaseScene.h"
#include"SceneManager.h"
#include"Field.h"
#include"Player.h"
#include"ObstructManager.h"
#include"Collision.h"
#include"GameUI.h"
#include"UIManager.h"
#include"Effect.h"
#include "GameScene.h"

//�Q�[���V�[���ɕK�v�ȃN���X�̏������ƃe�N�X�`���̃��[�h�A���W�̏�����
GameScene::GameScene() :gameSet(false), changeScene(false), blackOutCount(0), alpha(0), alphaAdd(2)
{
	//�J�����̈ʒu���Z�b�g
	SetCameraPositionAndTargetAndUpVec(VGet(0, 215, -500), VGet(0, 0, 0), VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));

	//�N���X�̏�����
	field = new Field();
	player = new Player();
	obstructManager = new ObstructManager();
	collision = new Collision();
	gameUI = new GameUI(player->GetPlayerHP());
	effect = new Effect();

	//�t�F�[�h�C���A�A�E�g�p�̍��w�i�摜�n���h���擾
	blackBackGroundHandle = UIManager::GetBlackBackGroundHandle();

	//���w�i�摜�̍��W������
	blackImgPos = VGet(0.0f, 0.0f, 0.0f);
}

//�N���X�̌㏈��
GameScene::~GameScene()
{
	delete(field);
	delete(player);
	delete(obstructManager);
	delete(collision);
	delete(gameUI);
	delete(effect);
}

//�Q�[���V�[���̍X�V
void GameScene::Update()
{
	//�Q�[�����J�n����Ă����瑼�̃N���X�̍X�V���n�߂�
	if (gameUI->GetIsStartGame())
	{
		player->Update();
		obstructManager->Update();
		collision->HitJudge(player, obstructManager, effect);
		effect->Update(player);
	}
	gameUI->Update(player);
	
	//�Q�[���I������
	if ((player->GetPoint() >= PLAYER_CLEAR_POINT || player->GetPlayerHP() == 0) && !gameSet)
	{
		if (player->GetPoint() >= PLAYER_CLEAR_POINT)
		{
			if (player->GetPlayerHP() == 5)
			{
				SceneManager::ChangeCondition(SceneManager::FINISH_CONDITION::PERFECT);
			}
			else
			{
				SceneManager::ChangeCondition(SceneManager::FINISH_CONDITION::CLEAR);
			}
		}
		else
		{
			SceneManager::ChangeCondition(SceneManager::FINISH_CONDITION::GAMEOVER);
		}
		gameSet = true;
	}
	//�Q�[�����I�������t�F�[�h�A�E�g����
	if (gameSet)
	{
		alpha += alphaAdd;
		if (alpha >= 255)
		{
			changeScene = true;
		}
	}
	//�V�[�������U���g�ɕύX
	if (CheckHitKey(KEY_INPUT_RETURN) != 0 || changeScene)
	{
		SceneManager::ChangeScene(SceneManager::SCENE::RESULT);
	}
}

//�Q�[���V�[���̕`��
void GameScene::Draw()
{
	field->Draw();
	//�Q�[�����X�^�[�g�����瑼�̃N���X�̕`����s�Ȃ�
	if (gameUI->GetIsStartGame())
	{
		player->Draw();
		player->DrawShadow(field);
		obstructManager->Draw(field);
		effect->Draw();
	}
	gameUI->DrawHole(field);
	gameUI->Draw();
	//�Q�[�����I��������̃t�F�[�h�A�E�g�p���w�i�摜��`��
	if (gameSet)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBillboard3D(blackImgPos, 0.5f, 0.5f, 1200.0f, 0.0f, blackBackGroundHandle, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	//DrawString(0, 16, "GAME", GetColor(0, 0, 0));
}
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

//ゲームシーンに必要なクラスの初期化とテクスチャのロード、座標の初期化
GameScene::GameScene() :gameSet(false), changeScene(false), blackOutCount(0), alpha(0), alphaAdd(2)
{
	//カメラの位置をセット
	SetCameraPositionAndTargetAndUpVec(VGet(0, 215, -500), VGet(0, 0, 0), VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));

	//クラスの初期化
	field = new Field();
	player = new Player();
	obstructManager = new ObstructManager();
	collision = new Collision();
	gameUI = new GameUI(player->GetPlayerHP());
	effect = new Effect();

	//フェードイン、アウト用の黒背景画像ハンドル取得
	blackBackGroundHandle = UIManager::GetBlackBackGroundHandle();

	//黒背景画像の座標初期化
	blackImgPos = VGet(0.0f, 0.0f, 0.0f);
}

//クラスの後処理
GameScene::~GameScene()
{
	delete(field);
	delete(player);
	delete(obstructManager);
	delete(collision);
	delete(gameUI);
	delete(effect);
}

//ゲームシーンの更新
void GameScene::Update()
{
	//ゲームが開始されていたら他のクラスの更新を始める
	if (gameUI->GetIsStartGame())
	{
		player->Update();
		obstructManager->Update();
		collision->HitJudge(player, obstructManager, effect);
		effect->Update(player);
	}
	gameUI->Update(player);
	
	//ゲーム終了処理
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
	//ゲームが終わったらフェードアウトする
	if (gameSet)
	{
		alpha += alphaAdd;
		if (alpha >= 255)
		{
			changeScene = true;
		}
	}
	//シーンをリザルトに変更
	if (CheckHitKey(KEY_INPUT_RETURN) != 0 || changeScene)
	{
		SceneManager::ChangeScene(SceneManager::SCENE::RESULT);
	}
}

//ゲームシーンの描画
void GameScene::Draw()
{
	field->Draw();
	//ゲームがスタートしたら他のクラスの描画も行なう
	if (gameUI->GetIsStartGame())
	{
		player->Draw();
		player->DrawShadow(field);
		obstructManager->Draw(field);
		effect->Draw();
	}
	gameUI->DrawHole(field);
	gameUI->Draw();
	//ゲームが終わった時のフェードアウト用黒背景画像を描画
	if (gameSet)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBillboard3D(blackImgPos, 0.5f, 0.5f, 1200.0f, 0.0f, blackBackGroundHandle, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	//DrawString(0, 16, "GAME", GetColor(0, 0, 0));
}
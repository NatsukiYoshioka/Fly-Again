#include "SceneManager.h"
#include"BaseScene.h"
#include"MenuScene.h"
#include"GameScene.h"
#include"ResultScene.h"
#include <cstddef>

BaseScene* SceneManager::nowScene = NULL;
SceneManager::FINISH_CONDITION SceneManager::_condition;

//シーンの初期化
SceneManager::SceneManager()
{
	nowScene = new MenuScene();
	_condition = FINISH_CONDITION::INGAME;
}

//シーンを引数によって変える関数
void SceneManager::ChangeScene(SCENE scene)
{
	if (nowScene != NULL)
	{
		delete nowScene;
	}

	switch (scene)
	{
	case SCENE::TITLE:
		nowScene = new MenuScene();
		break;
	case SCENE::GAME:
		nowScene = new GameScene();
		break;
	case SCENE::RESULT:
		nowScene = new ResultScene();
		break;
	}
}

//ゲーム終了時の状態を変更する関数
void SceneManager::ChangeCondition(FINISH_CONDITION condition)
{
	_condition = condition;
}

//現在のシーンの更新
void SceneManager::Update()
{
	nowScene->Update();
}

//現在のシーンの描画
void SceneManager::Draw()
{
	nowScene->Draw();
}
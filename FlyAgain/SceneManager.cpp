#include "SceneManager.h"
#include"BaseScene.h"
#include"MenuScene.h"
#include"GameScene.h"
#include"ResultScene.h"
#include <cstddef>

BaseScene* SceneManager::nowScene = NULL;
SceneManager::FINISH_CONDITION SceneManager::_condition;

//�V�[���̏�����
SceneManager::SceneManager()
{
	nowScene = new MenuScene();
	_condition = FINISH_CONDITION::INGAME;
}

//�V�[���������ɂ���ĕς���֐�
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

//�Q�[���I�����̏�Ԃ�ύX����֐�
void SceneManager::ChangeCondition(FINISH_CONDITION condition)
{
	_condition = condition;
}

//���݂̃V�[���̍X�V
void SceneManager::Update()
{
	nowScene->Update();
}

//���݂̃V�[���̕`��
void SceneManager::Draw()
{
	nowScene->Draw();
}
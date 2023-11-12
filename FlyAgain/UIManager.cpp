#include"DxLib.h"
#include "UIManager.h"

int UIManager::heartImgHandle;
int UIManager::brokenHeartImgHandle;
int UIManager::wrenchImgHandle;
int UIManager::blackBackGroundHandle;
int UIManager::circleImgHandle;
int UIManager::circleCheeseImgHandle;
int UIManager::holeImgHandle;
int UIManager::buttonAImgHandle;
int UIManager::cheeseMarkerImgHandle;

//UI�摜�̃��[�h
UIManager::UIManager()
{
	heartImgHandle = LoadGraph(GetHeartTexturePath());
	brokenHeartImgHandle = LoadGraph(GetBrokenHeartTexturePath());
	wrenchImgHandle = LoadGraph(GetWrenchTexturePath());
	blackBackGroundHandle = LoadGraph(GetBlackBackGroundPath());
	circleImgHandle = LoadGraph(GetCircleTexturePath());
	circleCheeseImgHandle = LoadGraph(GetCircleCheeseTexturePath());
	holeImgHandle = LoadGraph(GetHoleTexturePath());
	buttonAImgHandle = LoadGraph(GetButtonATexturePath());
	cheeseMarkerImgHandle = LoadGraph(GetCheeseMarkerTexturePath());
}

//UI�摜�̌㏈��
UIManager::~UIManager()
{
	DeleteGraph(heartImgHandle);
	DeleteGraph(brokenHeartImgHandle);
	DeleteGraph(wrenchImgHandle);
	DeleteGraph(blackBackGroundHandle);
	DeleteGraph(circleImgHandle);
	DeleteGraph(circleCheeseImgHandle);
	DeleteGraph(holeImgHandle);
	DeleteGraph(buttonAImgHandle);
	DeleteGraph(cheeseMarkerImgHandle);
}

//�n�[�g�摜�n���h���擾
const char* UIManager::GetHeartTexturePath()
{
	return "data/texture/heart.png";
}

//����n�[�g�摜�n���h���擾
const char* UIManager::GetBrokenHeartTexturePath()
{
	return "data/texture/broken_heart.png";
}

//�����`�摜�n���h���擾
const char* UIManager::GetWrenchTexturePath()
{
	return "data/texture/wrench.png";
}

//���w�i�摜�n���h���擾
const char* UIManager::GetBlackBackGroundPath()
{
	return "data/texture/black.png";
}

//�~�摜�n���h���擾
const char* UIManager::GetCircleTexturePath()
{
	return "data/texture/circle.png";
}

//�~�`�[�Y�摜�n���h���擾
const char* UIManager::GetCircleCheeseTexturePath()
{
	return "data/texture/circle_cheese.png";
}

//�����摜�n���h���擾
const char* UIManager::GetHoleTexturePath()
{
	return "data/texture/hole.png";
}

//A�{�^���摜�n���h���擾
const char* UIManager::GetButtonATexturePath()
{
	return "data/texture/UI/buttonA.png";
}

//�I��p�`�[�Y�}�[�J�[�摜�n���h���擾
const char* UIManager::GetCheeseMarkerTexturePath()
{
	return "data/texture/UI/cheese.png";
}
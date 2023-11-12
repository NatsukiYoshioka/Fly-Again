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

//UI画像のロード
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

//UI画像の後処理
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

//ハート画像ハンドル取得
const char* UIManager::GetHeartTexturePath()
{
	return "data/texture/heart.png";
}

//割れハート画像ハンドル取得
const char* UIManager::GetBrokenHeartTexturePath()
{
	return "data/texture/broken_heart.png";
}

//レンチ画像ハンドル取得
const char* UIManager::GetWrenchTexturePath()
{
	return "data/texture/wrench.png";
}

//黒背景画像ハンドル取得
const char* UIManager::GetBlackBackGroundPath()
{
	return "data/texture/black.png";
}

//円画像ハンドル取得
const char* UIManager::GetCircleTexturePath()
{
	return "data/texture/circle.png";
}

//円チーズ画像ハンドル取得
const char* UIManager::GetCircleCheeseTexturePath()
{
	return "data/texture/circle_cheese.png";
}

//巣穴画像ハンドル取得
const char* UIManager::GetHoleTexturePath()
{
	return "data/texture/hole.png";
}

//Aボタン画像ハンドル取得
const char* UIManager::GetButtonATexturePath()
{
	return "data/texture/UI/buttonA.png";
}

//選択用チーズマーカー画像ハンドル取得
const char* UIManager::GetCheeseMarkerTexturePath()
{
	return "data/texture/UI/cheese.png";
}
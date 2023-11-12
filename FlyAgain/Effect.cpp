#include"Player.h"
#include"common.h"
#include"EffekseerForDXLib.h"
#include"DxLib.h"
#include "Effect.h"

const VECTOR Effect::initialBoundGroundEffectPos = VGet(0.0f, 0.0f, 0.0f);
const VECTOR Effect::initialCheeseEffectPos = VGet(0.0f, 0.0f, 0.0f);
const VECTOR Effect::initialWrenchEffectPos = VGet(0.0f, 0.0f, 0.0f);

//変数の初期化とエフェクトのロード
Effect::Effect():
	boundGroundPlayingEffect	(initialBoundGroundPlayingEffect),
	cheesePlayingEffect			(initialCheesePlayingEffect),
	wrenchPlayingEffect			(initialWrenchPlayingEffect)
{
	boundGroundEffect = LoadEffekseerEffect(GetBoundGroundEffectPath(),effectScale);
	cheeseEffect = LoadEffekseerEffect(GetCheeseEffectPath(), effectScale);
	wrenchEffect = LoadEffekseerEffect(GetWrenchEffectPath(), effectScale);
}

//エフェクトハンドルの後処理
Effect::~Effect()
{
	DeleteEffekseerEffect(boundGroundEffect);
	DeleteEffekseerEffect(boundGroundPlayingEffect);
	DeleteEffekseerEffect(cheeseEffect);
	DeleteEffekseerEffect(cheesePlayingEffect);
	DeleteEffekseerEffect(wrenchEffect);
	DeleteEffekseerEffect(wrenchPlayingEffect);
}

//再生しているエフェクトの位置更新
void Effect::Update(Player* player)
{
	SetPosPlayingEffekseer3DEffect(cheesePlayingEffect, player->GetCollPos().x, player->GetCollPos().y, player->GetCollPos().z);
	SetPosPlayingEffekseer3DEffect(wrenchPlayingEffect, player->GetCollPos().x, player->GetCollPos().y, player->GetCollPos().z);
	UpdateEffekseer3D();
}

//地面に当たった時のエフェクトの再生処理
void Effect::UpdateBoundGroundEffect(VECTOR pos)
{
	boundGroundPlayingEffect = PlayEffekseer3DEffect(boundGroundEffect);
	//エフェクトの位置設定
	SetPosPlayingEffekseer3DEffect(boundGroundPlayingEffect, pos.x, GROUND_HEIGHT, pos.z);
}

//チーズに当たった時のエフェクトの再生処理
void Effect::UpdateCheeseEffect(VECTOR pos)
{
	cheesePlayingEffect = PlayEffekseer3DEffect(cheeseEffect);
	//エフェクトの位置設定
	cheeseEffectPos = pos;
}

//レンチを入手したときのエフェクトの再生処理
void Effect::UpdateWrenchEffect(VECTOR pos)
{
	wrenchPlayingEffect = PlayEffekseer3DEffect(wrenchEffect);
	//エフェクトの位置設定
	wrenchEffectPos = pos;
}

//エフェクトの描画
void Effect::Draw()
{
	DrawEffekseer3D();
}

//地面に当たった時のエフェクトのパス取得
const char* Effect::GetBoundGroundEffectPath()
{
	return boundGroundEffectPath;
}

//チーズを入手した時のエフェクトのパス取得
const char* Effect::GetCheeseEffectPath()
{
	return cheeseEffectPath;
}

//レンチを入手した時のエフェクトのパス取得
const char* Effect::GetWrenchEffectPath()
{
	return wrenchEffectPath;
}
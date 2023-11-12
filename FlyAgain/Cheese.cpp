#include"common.h"
#include"DxLib.h"
#include "Cheese.h"

//Posの初期化用定数
const VECTOR Cheese::initialPos = VGet(0.0f, 0.0f, 0.0f);

//モデルの拡縮度
const VECTOR Cheese::modelScale = VGet(1.5f, 1.5f, 1.5f);

//チーズの3Dモデルと座標、スケールを設定する
Cheese::Cheese(int modelHandle) :
    isAppearance        (false),
    hitRadius           (initialHitRadius),
    appearanceRandNum   (initialAppearanceRandNum)
{
    this->modelHandle = MV1DuplicateModel(modelHandle);

    pos = initialPos;

    MV1SetScale(this->modelHandle, modelScale);
}

//モデルハンドルの後処理
Cheese::~Cheese()
{
    MV1DeleteModel(modelHandle);
}

//チーズを出現させるフラグをランダムで初期化する
void Cheese::InitFlag()
{
    appearanceRandNum = GetRand(CHEESE_PROBABILITY);
    if (appearanceRandNum == CHEESE_APPEARANCE_NUM)
    {
        isAppearance = true;
    }
}

//チーズモデルの座標更新
void Cheese::Update(VECTOR mousePos)
{
    pos = VGet(mousePos.x, GROUND_HEIGHT + CHEESE_FIX_POS_Y, mousePos.z);

    MV1SetPosition(modelHandle, pos);
}

//チーズの描画
void Cheese::Draw()
{
    if (isAppearance)
    {
        MV1DrawModel(modelHandle);

        // デバッグあたり判定.
        //DrawSphere3D(pos, hitRadius, 5, 0x00ffff, 0x00ffff, false);
    }
}

//プレイヤーに当たった時の処理
void Cheese::OnHitPlayer(bool hitFlag)
{
    //当たっていた場合当たり判定と描画のフラグをfalseにする
    if (hitFlag)
    {
        isAppearance = false;
    }
}
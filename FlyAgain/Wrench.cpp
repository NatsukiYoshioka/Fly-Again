#include"DxLib.h"
#include "Wrench.h"

//モデルの取得と座標の初期化
Wrench::Wrench(int modelHandle) :isAppearance(false), rpm(0.0f)
{
    //モデルハンドルの取得
    this->modelHandle = MV1DuplicateModel(modelHandle);

    //座標の初期化
    pos = VGet(0.0f, 0.0f, 0.0f);

    //モデルの拡縮
    MV1SetScale(this->modelHandle, VGet(0.02f, 0.02f, 0.02f));
}

//モデルの後処理
Wrench::~Wrench()
{
    MV1DeleteModel(modelHandle);
}

//出現の初期化
void Wrench::InitAppearance(int startTime)
{
    //12秒おきに出現する
    if (GetNowCount() - startTime > 12000)
    {
        isAppearance = true;
    }
}

//レンチの位置更新
void Wrench::Update(VECTOR cheesePos)
{
    //出現している間回転するようにする
    RotateWrench();

    //座標をチーズの上に来るようにする
    pos = VGet(cheesePos.x, cheesePos.y + WRENCH_FIX_POS_Y, cheesePos.z);

    //モデルの座標をセット
    MV1SetPosition(modelHandle, pos);
}

//レンチの描画
void Wrench::Draw()
{
    MV1DrawModel(modelHandle);
}

//レンチモデルの回転処理
void Wrench::RotateWrench()
{
    rpm += rotationSpeed;
    if (rpm > maxRpm)
    {
        rpm = 0.0f;
    }
    MV1SetRotationXYZ(modelHandle, VGet(0.0f, rpm * DX_PI_F / 180.0f, 0.0f));
}

//プレイヤーに取得されたときの処理
void Wrench::OnHitPlayer()
{
    isAppearance = false;
}
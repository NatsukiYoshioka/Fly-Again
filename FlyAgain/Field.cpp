#include"ModelManager.h"
#include<DxLib.h>
#include "Field.h"

const VECTOR Field::initialPos = VGet(-140.0f, 100.0f, 100.0f);
const VECTOR Field::fieldAngle = VGet(0.0f, -180.0f * DX_PI_F / 180.0f, 0.0f);
const VECTOR Field::modelScale = VGet(100.0f, 100.0f, 100.0f);

//フィールド情報の初期化
Field::Field()
{
	//モデルのロード
	modelHandle = MV1DuplicateModel(ModelManager::GetFieldModelHandle());

	//座標初期化
	pos = initialPos;

	//モデル回転率設定
	MV1SetRotationXYZ(modelHandle, fieldAngle);

	//モデルの拡縮
	MV1SetScale(modelHandle, modelScale);

	//モデルの座標の設定
	MV1SetPosition(modelHandle, pos);

	//コリジョン情報の構築
	MV1SetupCollInfo(modelHandle, frameIndex, spatialPartitionNum, spatialPartitionNum, spatialPartitionNum);
}

//フィールドモデルの後処理
Field::~Field()
{
	MV1DeleteModel(modelHandle);
}

//フィールドの描画
void Field::Draw()
{
	MV1DrawModel(modelHandle);
}
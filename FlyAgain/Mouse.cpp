#include"common.h"
#include"Field.h"
#include"GameUI.h"
#include<cmath>
#include "Mouse.h"

//モデル関連のロードと初期化
Mouse::Mouse(int modelHandle) :animPlayTime(0.0f), RunningAnimation(2), isAppearance(true), MaxTop(25), MaxUnder(-350), MaxLeft(-275), MaxRight(300), fixAngle(150.0f * DX_PI_F / 180.0f), AttachIndex(0), angle(0.0f), animTotalTime(0.0f), appearanceSide(0), runningSpeed(0.0f), hitRadius(15.0f)
{
	//モデルハンドルの取得
	this->modelHandle = MV1DuplicateModel(modelHandle);
	//影テクスチャのロード
	shadowHandle = LoadGraph(GetShadowImgPath());

	//座標の初期化
	pos = VGet(0.0f, 0.0f, 0.0f);
	CollPos = VGet(0.0f, 0.0f, 0.0f);

	firstPos = VGet(0.0f, 0.0f, 0.0f);
	finalPos = VGet(0.0f, 0.0f, 0.0f);
}

//モデルの後処理
Mouse::~Mouse()
{
	MV1DeleteModel(modelHandle);
}

//マウスの出現座標とモデルの再取得
void Mouse::Initialize(int modelHandle)
{
	//アニメーションによってマウスのモデルが崩れるため、ハンドルを初期化
	MV1DeleteModel(this->modelHandle);
	this->modelHandle = MV1DuplicateModel(modelHandle);

	//マウスの初期地点と最終地点の設定
	SetRunningDirection();

	//座標初期化
	pos = firstPos;
	CollPos = pos;

	//モデルが画面内に出現できるようにする
	isAppearance = true;

	//移動速度をランダムで初期化
	runningSpeed = static_cast<float>(GetRand(500) + 300);

	//モデルの拡縮
	MV1SetScale(this->modelHandle, VGet(0.15f, 0.15f, 0.15f));

	// ３Ｄモデルのアニメーションをアタッチする
	AttachIndex = MV1AttachAnim(this->modelHandle, RunningAnimation, this->modelHandle, TRUE);

	// アタッチしたアニメーションの総再生時間を取得する
	animTotalTime = MV1GetAttachAnimTotalTime(this->modelHandle, AttachIndex);

	//アニメーションの再生時間を初期化
	animPlayTime = 0.0f;
}

//アニメーションと座標の更新
void Mouse::Update()
{
	//再生時間を進める
	animPlayTime += 2.0f;

	//再生時間がアニメーションの総再生時間に達したら再生時間を0に戻す
	if (animPlayTime >= animTotalTime)
	{
		animPlayTime = 0.0f;
	}

	//マウスの座標更新
	pos = VAdd(pos, VGet((finalPos.x - firstPos.x) / runningSpeed, 0.0f, (finalPos.z - firstPos.z) / runningSpeed));

	//マウスが出現しなくなったら座標を画面外の最終地点に移動する
	if (!isAppearance)
	{
		pos = finalPos;
	}

	//当たり判定座標更新
	CollPos = VGet(pos.x, pos.y + MOUSE_FIX_POS_Y, pos.z + MOUSE_FIX_POS_Z);
	
	//モデルの座標をセット
	MV1SetPosition(modelHandle, pos);
}

//モデルとアニメーションの更新
void Mouse::Draw()
{
	if (isAppearance)
	{
		//アニメーションの再生時間をセットする
		MV1SetAttachAnimTime(modelHandle, AttachIndex, animPlayTime);
		MV1DrawModel(modelHandle);

		// デバッグあたり判定.
		//DrawSphere3D(CollPos, hitRadius, 5, 0x00ffff, 0x00ffff, false);
	}
}

//モデルの影描画
void Mouse::DrawShadow(Field* field)
{
	MV1_COLL_RESULT_POLY_DIM HitResultDim;
	MV1_COLL_RESULT_POLY* HitResult;
	VERTEX3D Vertex[3];
	VECTOR SlideVec;

	// ライティングを無効にする
	SetUseLighting(FALSE);

	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// テクスチャアドレスモードを CLAMP にする( テクスチャの端より先は端のドットが延々続く )
	SetTextureAddressMode(DX_TEXADDRESS_CLAMP);

	// プレイヤーの直下に存在する地面のポリゴンを取得
	HitResultDim = MV1CollCheck_Capsule(field->GetModelHandle(), -1, pos, VAdd(pos, VGet(0.0f, -MOUSE_SHADOW_HEIGHT, 0.0f)), MOUSE_SHADOW_SIZE);

	// 頂点データで変化が無い部分をセット
	Vertex[0].dif = GetColorU8(255, 255, 255, 255);
	Vertex[0].spc = GetColorU8(0, 0, 0, 0);
	Vertex[0].su = 0.0f;
	Vertex[0].sv = 0.0f;
	Vertex[1] = Vertex[0];
	Vertex[2] = Vertex[0];

	// 球の直下に存在するポリゴンの数だけ繰り返し
	HitResult = HitResultDim.Dim;
	for (int i = 0; i < HitResultDim.HitNum; i++, HitResult++)
	{
		// ポリゴンの座標は地面ポリゴンの座標
		Vertex[0].pos = HitResult->Position[0];
		Vertex[1].pos = HitResult->Position[1];
		Vertex[2].pos = HitResult->Position[2];

		// ちょっと持ち上げて重ならないようにする
		SlideVec = VScale(HitResult->Normal, 0.5f);
		Vertex[0].pos = VAdd(Vertex[0].pos, SlideVec);
		Vertex[1].pos = VAdd(Vertex[1].pos, SlideVec);
		Vertex[2].pos = VAdd(Vertex[2].pos, SlideVec);

		// ポリゴンの不透明度を設定する
		Vertex[0].dif.a = 0;
		Vertex[1].dif.a = 0;
		Vertex[2].dif.a = 0;
		if (HitResult->Position[0].y > pos.y - MOUSE_SHADOW_HEIGHT)
		{
			Vertex[0].dif.a = static_cast<BYTE>(128 * (1.0f - static_cast<float>(fabs(HitResult->Position[0].y - pos.y) / MOUSE_SHADOW_HEIGHT)));
		}

		if (HitResult->Position[1].y > pos.y - MOUSE_SHADOW_HEIGHT)
		{
			Vertex[1].dif.a = static_cast<BYTE>(128 * (1.0f - static_cast<float>(fabs(HitResult->Position[1].y - pos.y) / MOUSE_SHADOW_HEIGHT)));
		}

		if (HitResult->Position[2].y > pos.y - MOUSE_SHADOW_HEIGHT)
		{
			Vertex[2].dif.a = static_cast<BYTE>(128 * (1.0f - static_cast<float>(fabs(HitResult->Position[2].y - pos.y) / MOUSE_SHADOW_HEIGHT)));
		}

		// ＵＶ値は地面ポリゴンとプレイヤーの相対座標から割り出す
		Vertex[0].u = (HitResult->Position[0].x - pos.x) / (MOUSE_SHADOW_SIZE * 2.0f) + 0.5f;
		Vertex[0].v = (HitResult->Position[0].z - pos.z) / (MOUSE_SHADOW_SIZE * 2.0f) + 0.5f;
		Vertex[1].u = (HitResult->Position[1].x - pos.x) / (MOUSE_SHADOW_SIZE * 2.0f) + 0.5f;
		Vertex[1].v = (HitResult->Position[1].z - pos.z) / (MOUSE_SHADOW_SIZE * 2.0f) + 0.5f;
		Vertex[2].u = (HitResult->Position[2].x - pos.x) / (MOUSE_SHADOW_SIZE * 2.0f) + 0.5f;
		Vertex[2].v = (HitResult->Position[2].z - pos.z) / (MOUSE_SHADOW_SIZE * 2.0f) + 0.5f;

		// 影ポリゴンを描画
		if (pos.x > -300.0f && pos.x < 320.0f && pos.z<15.0f && pos.z>-325.0f)
		{
			DrawPolygon3D(Vertex, 1, shadowHandle, TRUE);
		}
	}

	// 検出した地面ポリゴン情報の後始末
	MV1CollResultPolyDimTerminate(HitResultDim);

	// ライティングを有効にする
	SetUseLighting(TRUE);

	// Ｚバッファを無効にする
	SetUseZBuffer3D(FALSE);
}

//マウスの向きをセット
void Mouse::SetRunningDirection()
{
	//出現座標と最終地点から向きを取得
	appearanceSide = GetRand(static_cast<int>(AppearanceSide::RIGHT));
	switch (appearanceSide)
	{
	case static_cast<int>(AppearanceSide::TOP):
		firstPos = VGet(static_cast<float>(-250.0f + GetRand(WALL_UP_HOLE_NUM - 1) * 100.0f), GROUND_HEIGHT, 40.0f);
		finalPos = VGet(static_cast<float>(GetRand(MaxRight - MaxLeft) + MaxLeft), GROUND_HEIGHT, -375.0f);
		break;
	case static_cast<int>(AppearanceSide::UNDER):
		firstPos = VGet(static_cast<float>(GetRand(MaxRight - MaxLeft) + MaxLeft), GROUND_HEIGHT, -375.0f);
		finalPos = VGet(static_cast<float>(-250.0f + GetRand(WALL_UP_HOLE_NUM - 1) * 100.0f), GROUND_HEIGHT, 40.0f);
		break;
	case static_cast<int>(AppearanceSide::LEFT):
		firstPos = VGet(-325.0f, GROUND_HEIGHT, -50.0f - static_cast<float>(GetRand(WALL_SIDE_HOLE_NUM - 1) * 75.0f));
		finalPos = VGet(350.0f, GROUND_HEIGHT, -50.0f - static_cast<float>(GetRand(WALL_SIDE_HOLE_NUM - 1) * 75.0f));
		break;
	case static_cast<int>(AppearanceSide::RIGHT):
		firstPos = VGet(350.0f, GROUND_HEIGHT, -50.0f - static_cast<float>(GetRand(WALL_SIDE_HOLE_NUM - 1) * 75.0f));
		finalPos = VGet(-325.0f, GROUND_HEIGHT, -50.0f - static_cast<float>(GetRand(WALL_SIDE_HOLE_NUM - 1) * 75.0f));
		break;
	}

	//モデルの向きを計算
	angle = -atan2f(finalPos.z - firstPos.z, finalPos.x - firstPos.x);

	//モデルの向きをセット
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, angle + fixAngle, 0.0f));
}

//マウスが画面内にいるかどうかの判定
bool Mouse::IsCheckMouseAppearance()
{
	//最終地点より先にいたらfalseにする
	switch (appearanceSide)
	{
	case static_cast<int>(AppearanceSide::TOP):
		if (pos.z < finalPos.z)
		{
			isAppearance = false;
		}
		break;
	case static_cast<int>(AppearanceSide::UNDER):
		if (pos.z > finalPos.z)
		{
			isAppearance = false;
		}
		break;
	case static_cast<int>(AppearanceSide::LEFT):
		if (pos.x > finalPos.x)
		{
			isAppearance = false;
		}
		break;
	case static_cast<int>(AppearanceSide::RIGHT):
		if (pos.x < finalPos.x)
		{
			isAppearance = false;
		}
		break;
	}

	return isAppearance;
}

//マウスの現在の座標を取得
VECTOR Mouse::GetNowPosition()
{
	return pos;
}

//陰のテクスチャパス取得
const char* Mouse::GetShadowImgPath()
{
	return "data/texture/Shadow.tga";
}
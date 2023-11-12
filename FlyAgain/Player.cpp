#include"DxLib.h"
#include"Field.h"
#include"Wrench.h"
#include"PadInput.h"
#include"ModelManager.h"
#include<cmath>
#include "Player.h"

//変数、座標の初期化とモデルの取得
Player::Player() :hitRadius(20.0f), 
jumpPower(jump), 
gravityPower(0.0f), 
liftPower(0.0f), 
nowXSpeed(0.0f), 
nowZSpeed(0.0f), 
Angle(0.0f), 
HP(5), 
point(0), 
crash(false),
crashRotation(0.0f),
nowFuel(maxFuel)
{
	//モデルのロード
	modelHandle = MV1DuplicateModel(ModelManager::GetRobotModelHandle());

	//影テクスチャのロード
	shadowHandle = LoadGraph(GetShadowImgPath());

	//座標初期化
	pos = VGet(0.0f, 70.0f, -100.0f);
	CollPos = VGet(0.0f, 0.0f, 0.0f);
	MoveVec = VGet(0.0f, 0.0f, 0.0f);

	//モデルの拡縮
	MV1SetScale(modelHandle, VGet(0.2f, 0.2f, 0.2f));
}

//モデルの後処理
Player::~Player()
{
	MV1DeleteModel(modelHandle);
}

//入力処理と座標の更新
void Player::Update()
{
	//入力処理
	if (CheckHitKey(KEY_INPUT_W) || PadInput::GetPadInput().ThumbLY > 0)
	{
		UpdateSpeed(&nowZSpeed,maxSpeed);
		MoveVec = VAdd(MoveVec, VGet(0.0f, 0.0f, speed));
	}
	if (CheckHitKey(KEY_INPUT_S) || PadInput::GetPadInput().ThumbLY < 0)
	{
		UpdateSpeed(&nowZSpeed, -maxSpeed);
		MoveVec = VAdd(MoveVec, VGet(0.0f, 0.0f, -speed));
	}
	if (CheckHitKey(KEY_INPUT_A) || PadInput::GetPadInput().ThumbLX < 0)
	{
		UpdateSpeed(&nowXSpeed, -maxSpeed);
		MoveVec = VAdd(MoveVec, VGet(-speed, 0.0f, 0.0f));
	}
	if (CheckHitKey(KEY_INPUT_D) || PadInput::GetPadInput().ThumbLX > 0)
	{
		UpdateSpeed(&nowXSpeed, maxSpeed);
		MoveVec = VAdd(MoveVec, VGet(speed, 0.0f, 0.0f));
	}

	//ジャンプボタンでプレイヤーに浮力を与える
	if (nowFuel > 0 && (CheckHitKey(KEY_INPUT_SPACE) || PadInput::GetPadInput().Buttons[12]))
	{
		nowFuel += fuelDecreaseSpeed;
		liftPower += lift;
		if (liftPower > maxLiftPower)
		{
			liftPower = maxLiftPower;
		}
		if (nowFuel <= 0)
		{
			nowFuel = 0;
		}
	}
	else
	{
		liftPower -= gravity;
		if (liftPower < 0.0f)
		{
			liftPower = 0.0f;
		}
		if (nowFuel >= maxFuel)
		{
			nowFuel = maxFuel;
		}
	}

	//座標反映
	pos = VAdd(pos, VGet(nowXSpeed, 0.0f, nowZSpeed));
	//プレイヤーの座標修正
	FixPos();

	//抵抗処理
	ResistanceProcess();

	//プレイヤー座標の更新
	pos = VAdd(pos, VGet(0.0f, jumpPower - gravityPower + liftPower, 0.0f));

	//プレイヤーの当たり判定座標更新
	CollPos = VGet(pos.x, pos.y + PLAYER_COLL_POS_Y, pos.z);
	
	//プレイヤーの向きを更新
	UpdateAngle();

	//モデルの位置を更新
	MV1SetPosition(modelHandle, pos);
}

//プレイヤーの動く速さの更新
void Player::UpdateSpeed(float* shaft, const float maxSpeed)
{
	//入力されていない状態でも慣性を発生させる
	if (maxSpeed < 0)
	{
		*shaft -= speed;
		if (*shaft < maxSpeed)
		{
			*shaft = maxSpeed;
		}
	}
	else
	{
		*shaft += speed;
		if (*shaft > maxSpeed)
		{
			*shaft = maxSpeed;
		}
	}
}

//抵抗処理
void Player::ResistanceProcess()
{
	//空気抵抗処理
	if (nowXSpeed > 0)
	{
		nowXSpeed -= airResistance;
	}
	else if (nowXSpeed < 0)
	{
		nowXSpeed += airResistance;
	}

	if (nowZSpeed > 0)
	{
		nowZSpeed -= airResistance;
	}
	else if (nowZSpeed < 0)
	{
		nowZSpeed += airResistance;
	}

	//重力処理
	gravityPower += gravity;
	if (gravityPower > maxGravityPower)
	{
		gravityPower = maxGravityPower;
	}
}

//プレイヤーがフィールド外に出ないようにする処理
void Player::FixPos()
{
	if (pos.z > PLAYER_Z_MAX)
	{
		pos.z = PLAYER_Z_MAX;
	}
	if (pos.z < PLAYER_Z_MIN)
	{
		pos.z = PLAYER_Z_MIN;
	}
	if (pos.x < PLAYER_X_MIN)
	{
		pos.x = PLAYER_X_MIN;
	}
	if (pos.x > PLAYER_X_MAX)
	{
		pos.x = PLAYER_X_MAX;
	}
	if (pos.y > PLAYER_Y_MAX)
	{
		pos.y = PLAYER_Y_MAX;
	}
}

//プレイヤーの向きを修正
void Player::UpdateAngle()
{
	// プレイヤーの移動方向にモデルの方向を近づける
	float TargetAngle;			// 目標角度
	float difference;			// 目標角度と現在の角度との差

	// 移動ベクトルを正規化したものをプレイヤーが向くべき方向として保存
	TargetMoveDirection = VNorm(MoveVec);

	// 目標の方向ベクトルから角度値を算出する
	TargetAngle = static_cast<float>(atan2(TargetMoveDirection.x, TargetMoveDirection.z));

	// 目標の角度と現在の角度との差を割り出す
	// 最初は単純に引き算
	difference = TargetAngle - Angle;

	// ある方向からある方向の差が１８０度以上になることは無いので
		// 差の値が１８０度以上になっていたら修正する
	if (difference < -DX_PI_F)
	{
		difference += DX_TWO_PI_F;
	}
	else if (difference > DX_PI_F)
	{
		difference -= DX_TWO_PI_F;
	}

	// 角度の差が０に近づける
	if (difference > 0.0f)
	{
		// 差がプラスの場合は引く
		difference -= PLAYER_ANGLE_SPEED;
		if (difference < 0.0f)
		{
			difference = 0.0f;
		}
	}
	else
	{
		// 差がマイナスの場合は足す
		difference += PLAYER_ANGLE_SPEED;
		if (difference > 0.0f)
		{
			difference = 0.0f;
		}
	}

	// モデルの角度を更新
	Angle = TargetAngle - difference;

	//クラッシュ時の処理
	if (HP <= 0 || crash && jumpPower - gravityPower > 0)
	{
		crashRotation += PLAYER_CRASH_ROTATION_SPEED;
		if (crashRotation >= 360.0f)
		{
			crashRotation = 0;
		}
	}
	else
	{
		crash = false;
		crashRotation = 0.0f;
	}

	MV1SetRotationXYZ(modelHandle, VGet(crashRotation * DX_PI_F / 180.0f, Angle + DX_PI_F, crashRotation * DX_PI_F / 180.0f));
}

//モデルの描画
void Player::Draw()
{
	MV1DrawModel(modelHandle);

	// デバッグあたり判定.
	//DrawSphere3D(CollPos, hitRadius, 5, 0x00ffff, 0x00ffff, false);
}

//地面に当たった時の処理
void Player::OnHitGround()
{
	//クラッシュアニメーションを有効にする
	crash = true;

	//HPを1つ減らして跳ね上げる
	HP--;
	gravityPower = 0.0f;
	jumpPower = jump;
}

//地面以外のモデルに当たった場合の処理
void Player::OnHitObstruct(bool hitFlag)
{
	if (hitFlag)
	{
		//プレイヤーをバウンドさせる
		gravityPower = 0.0f;
		jumpPower = jump;
	}
}

//ポイント付与関数
bool Player::GivePoint(int randNum)
{
	//当たったモデルにレンチがあればポイント付与
	if (randNum == WRENCH_APPEARANCE_NUM)
	{
		point++;
		return true;
	}
	return false;
}

//プレイヤーの影の描画
void Player::DrawShadow(Field* field)
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
	HitResultDim = MV1CollCheck_Capsule(field->GetModelHandle(), -1, pos, VAdd(pos, VGet(0.0f, -PLAYER_SHADOW_HEIGHT, 0.0f)), PLAYER_SHADOW_SIZE);

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
		if (HitResult->Position[0].y > pos.y - PLAYER_SHADOW_HEIGHT)
		{
			Vertex[0].dif.a = static_cast<BYTE>(128 * (1.0f - static_cast<float>(fabs(HitResult->Position[0].y - pos.y) / PLAYER_SHADOW_HEIGHT)));
		}

		if (HitResult->Position[1].y > pos.y - PLAYER_SHADOW_HEIGHT)
		{
			Vertex[1].dif.a = static_cast<BYTE>(128 * (1.0f - static_cast<float>(fabs(HitResult->Position[1].y - pos.y) / PLAYER_SHADOW_HEIGHT)));
		}

		if (HitResult->Position[2].y > pos.y - PLAYER_SHADOW_HEIGHT)
		{
			Vertex[2].dif.a = static_cast<BYTE>(128 * (1.0f - static_cast<float>(fabs(HitResult->Position[2].y - pos.y) / PLAYER_SHADOW_HEIGHT)));
		}

		// ＵＶ値は地面ポリゴンとプレイヤーの相対座標から割り出す
		Vertex[0].u = (HitResult->Position[0].x - pos.x) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
		Vertex[0].v = (HitResult->Position[0].z - pos.z) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
		Vertex[1].u = (HitResult->Position[1].x - pos.x) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
		Vertex[1].v = (HitResult->Position[1].z - pos.z) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
		Vertex[2].u = (HitResult->Position[2].x - pos.x) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
		Vertex[2].v = (HitResult->Position[2].z - pos.z) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;

		// 影ポリゴンを描画
		DrawPolygon3D(Vertex, 1, shadowHandle, TRUE);
	}

	// 検出した地面ポリゴン情報の後始末
	MV1CollResultPolyDimTerminate(HitResultDim);

	// ライティングを有効にする
	SetUseLighting(TRUE);

	// Ｚバッファを無効にする
	SetUseZBuffer3D(FALSE);
}

//陰のテクスチャパス取得
const char* Player::GetShadowImgPath()
{
	return "data/texture/Shadow.tga";
}

//燃料補給
void Player::FuelSupply()
{
	nowFuel = maxFuel;
}
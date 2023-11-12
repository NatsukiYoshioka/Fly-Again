#include"UIManager.h"
#include"Player.h"
#include"Field.h"
#include"common.h"
#include"DxLib.h"
#include "GameUI.h"

const VECTOR GameUI::initialHeartPos = VGet(0.0f, 0.0f, 0.0f);
const VECTOR GameUI::initialBrokenHeartPos = VGet(0.0f, 0.0f, 0.0f);
const VECTOR GameUI::initialWrenchPos = VGet(0.0f, 0.0f, 0.0f);

const unsigned int GameUI::jumpStringColor = GetColor(0, 0, 0);

GameUI::GameUI(int playerHP) :
	heartPrevNum			(initialHeartPrevNum),
	wrenchNum				(initialWrenchNum),
	brokenStartCount		(initialBrokenStartCount),
	fuelPercent				(initialFuelPercent),
	isStartGame				(false),
	maxCount				(initialMaxCount),
	startFlag				(initialStartFlag),
	blackAlpha				(initialBlackAlpha),
	descriptionAlpha		(initialDescriptionAlpha),
	alphaAdd				(initialAlphaAdd),
	maxAlpha				(initialMaxAlpha)
{
	//UIテクスチャの取得
	heartImgHandle = UIManager::GetHeartImgHandle();
	brokenHeartImgHandle = UIManager::GetBrokenHeartImgHandle();
	wrenchImgHandle = UIManager::GetWrenchImgHandle();
	circleImgHandle = UIManager::GetCircleImgHandle();
	circleCheeseImgHandle = UIManager::GetCircleCheeseImgHandle();
	buttonAImgHandle = UIManager::GetButtonAImgHandle();
	holeImgHandle = UIManager::GetHoleImgHandle();
	blackBackgroundHandle = UIManager::GetBlackBackGroundHandle();

	//テクスチャ座標の設定
	heartPos = initialHeartPos;

	brokenHeartPos = initialBrokenHeartPos;

	wrenchPos = initialWrenchPos;

	heartNum = playerHP;

	//ゲームをスタートする最初の時間を取得
	startGameCount = GetNowCount();
}

//テクスチャの後処理
GameUI::~GameUI()
{
	DeleteGraph(heartImgHandle);
	DeleteGraph(brokenHeartImgHandle);
	DeleteGraph(wrenchImgHandle);
	DeleteGraph(circleImgHandle);
	DeleteGraph(circleCheeseImgHandle);
	DeleteGraph(buttonAImgHandle);
	DeleteGraph(holeImgHandle);
	DeleteGraph(blackBackgroundHandle);
}

//UI描画処理の更新
void GameUI::Update(Player* player)
{
	//プレイヤーの燃料の割合を取得
	fuelPercent = player->GetfuelPercent();

	//プレイヤーの残機が更新されていた場合の処理
	if (heartNum > player->GetPlayerHP())
	{
		//更新される前の残機を保存
		heartPrevNum = heartNum;
		//更新後の残機取得
		heartNum = player->GetPlayerHP();
		//割れハートを描画する最初の時間を取得
		brokenStartCount = GetNowCount();
	}
	//プレイヤーのポイント取得
	wrenchNum = player->GetPoint();
	
	//ゲーム開始カウントダウン
	if (GetNowCount() - startGameCount > secondCount && startFlag <= maxCount)
	{
		startGameCount = GetNowCount();
		startFlag++;
	}

	//開始前のUIアルファ値処理
	if (!isStartGame)
	{
		if (startFlag == maxCount)
		{
			isStartGame = true;
		}
		blackAlpha += alphaAdd;
		descriptionAlpha -= alphaAdd * descriptionFactor;
		if (blackAlpha <= maxAlpha)
		{
			blackAlpha = maxAlpha;
		}
		if (descriptionAlpha >= alphaMaxLimit)
		{
			descriptionAlpha = alphaMaxLimit;
		}
	}
}

//UI描画
void GameUI::Draw()
{
	//プレイヤーの燃料ゲージ描画
	DrawCircleGauge(circleCenterX, circleCenterY, circlePercent, circleImgHandle, circleStartPercent, circleScale, circleReverseX, circleReverseY);
	DrawCircleGauge(circleCheeseCenterX, circleCheeseCenterY, fuelPercent, circleCheeseImgHandle, circleStartPercent, circleCheeseScale, circleReverseX, circleReverseY);
	DrawExtendGraph(jumpUIX1, jumpUIY1, jumpUIX2, jumpUIY2, buttonAImgHandle, TRUE);

	SetFontSize(middleFontSize);
	DrawString(jumpStringX, jumpStringY, jumpString, jumpStringColor);
	//ハートの描画
	for (int i = 0; i < heartNum; i++)
	{
		heartPos = VGet(-400.0f + static_cast<float>(i) * 50.0f, 250.0f, 0.0f);
		DrawBillboard3D(heartPos, 0.5f, 0.5f, 50.0f, 0.0f, heartImgHandle, TRUE);
	}
	//割れハートの描画
	if (heartNum < heartPrevNum && brokenStartCount + (BROKEN_HEART_DRAW_COUNT * 1000) > GetNowCount() && heartNum >= 0)
	{
		brokenHeartPos = VGet(-400.0f + static_cast<float>(heartPrevNum - 1) * 50.0f, 250.0f, 0.0f);
		DrawBillboard3D(brokenHeartPos, 0.5f, 0.5f, 50.0f, 0.0f, brokenHeartImgHandle, TRUE);
	}
	//取得したレンチの描画
	if (wrenchNum > 0)
	{
		for (int i = 0; i < wrenchNum; i++)
		{
			wrenchPos = VGet(-400.0f + static_cast<float>(i) * 50.0f, 200.0f, 0.0f);
			DrawBillboard3D(wrenchPos, 0.5f, 0.5f, 50.0f, 45.0f, wrenchImgHandle, TRUE);
		}
	}

	//開始前の説明
	if (!isStartGame)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, blackAlpha);
		DrawExtendGraph(0, 0, 1920, 1080, blackBackgroundHandle, FALSE);

		ChangeFont("x12y16pxMaruMonica", DX_CHARSET_DEFAULT);
		SetFontSize(64);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, descriptionAlpha);
		DrawStringF(360.0f, 740.0f, "地面に落ちずにネズミを踏んでレンチを5個集めよう！", GetColor(255, 255, 0));

		if (descriptionAlpha == 255)
		{
			SetFontSize(256);
			//カウントダウン表示
			if (static_cast<float>(maxCount) - static_cast<float>(startFlag * 1000 + (GetNowCount() - startGameCount)) / 1000.0f < 1.0f)
			{
				DrawString(700.0f, 340.0f, "Start!", GetColor(255, 255, 255));
			}
			else
			{
				DrawFormatStringF(835.0f, 340.0f, GetColor(255, 255, 255), "%.1f", static_cast<float>(maxCount) - static_cast<float>(startFlag * 1000 + (GetNowCount() - startGameCount)) / 1000.0f);
			}
		}
		ChangeFont("ArcadeClassic", DX_CHARSET_DEFAULT);
		SetFontSize(16);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		
	}
}

void GameUI::DrawHole(Field* field)
{
	VERTEX3D Vertex[6];

	// ライティングを無効にする
	SetUseLighting(FALSE);

	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// ２ポリゴン分の頂点の座標と法線以外のデータをセット
	Vertex[0].dif = GetColorU8(255, 255, 255, 255);
	Vertex[0].spc = GetColorU8(0, 0, 0, 0);
	Vertex[0].u = 0.0f;
	Vertex[0].v = 0.0f;
	Vertex[0].su = 0.0f;
	Vertex[0].sv = 0.0f;

	Vertex[1].dif = GetColorU8(255, 255, 255, 255);
	Vertex[1].spc = GetColorU8(0, 0, 0, 0);
	Vertex[1].u = 1.0f;
	Vertex[1].v = 0.0f;
	Vertex[1].su = 0.0f;
	Vertex[1].sv = 0.0f;

	Vertex[2].dif = GetColorU8(255, 255, 255, 255);
	Vertex[2].spc = GetColorU8(0, 0, 0, 0);
	Vertex[2].u = 0.0f;
	Vertex[2].v = 1.0f;
	Vertex[2].su = 0.0f;
	Vertex[2].sv = 0.0f;

	Vertex[3].dif = GetColorU8(255, 255, 255, 255);
	Vertex[3].spc = GetColorU8(0, 0, 0, 0);
	Vertex[3].u = 1.0f;
	Vertex[3].v = 1.0f;
	Vertex[3].su = 0.0f;
	Vertex[3].sv = 0.0f;

	Vertex[4] = Vertex[2];
	Vertex[5] = Vertex[1];

	MATRIX TransformMatrix;

	//上側の壁
	for (int i = 0; i < WALL_UP_HOLE_NUM; i++)
	{
		//座標移動行列の作成
		TransformMatrix = MGetTranslate(VGet(-250.0f + i * 100, GROUND_HEIGHT, 30.0f));

		//行列を使ってワールド座標を算出
		Vertex[0].pos = VTransform(VGet(-35.0f, 35.0f, 0.0f), TransformMatrix);
		Vertex[1].pos = VTransform(VGet(35.0f, 35.0f, 0.0f), TransformMatrix);
		Vertex[2].pos = VTransform(VGet(-35.0f, -35.0f, 0.0f), TransformMatrix);
		Vertex[3].pos = VTransform(VGet(35.0f, -35.0f, 0.0f), TransformMatrix);

		Vertex[4].pos = Vertex[2].pos;
		Vertex[5].pos = Vertex[1].pos;

		// 行列を使って法線を算出
		Vertex[0].norm = VTransformSR(VGet(0.0f, 0.0f, -1.0f), TransformMatrix);
		Vertex[1].norm = Vertex[0].norm;
		Vertex[2].norm = Vertex[0].norm;
		Vertex[3].norm = Vertex[0].norm;
		Vertex[4].norm = Vertex[0].norm;
		Vertex[5].norm = Vertex[0].norm;

		// ２ポリゴンの描画
		DrawPolygon3D(Vertex, 2, holeImgHandle, TRUE);
	}

	//左側の壁
	for (int i = 0; i < WALL_SIDE_HOLE_NUM; i++)
	{
		TransformMatrix = MGetRotY(-90.0f * DX_PI_F / 180.0f);
		TransformMatrix = MMult(TransformMatrix, MGetTranslate(VGet(-310.0f, GROUND_HEIGHT, -50.0f - i * 75.0f)));

		//行列を使ってワールド座標を算出
		Vertex[0].pos = VTransform(VGet(-35.0f, 35.0f, 0.0f), TransformMatrix);
		Vertex[1].pos = VTransform(VGet(35.0f, 35.0f, 0.0f), TransformMatrix);
		Vertex[2].pos = VTransform(VGet(-35.0f, -35.0f, 0.0f), TransformMatrix);
		Vertex[3].pos = VTransform(VGet(35.0f, -35.0f, 0.0f), TransformMatrix);

		Vertex[4].pos = Vertex[2].pos;
		Vertex[5].pos = Vertex[1].pos;

		// 行列を使って法線を算出
		Vertex[0].norm = VTransformSR(VGet(0.0f, 0.0f, -1.0f), TransformMatrix);
		Vertex[1].norm = Vertex[0].norm;
		Vertex[2].norm = Vertex[0].norm;
		Vertex[3].norm = Vertex[0].norm;
		Vertex[4].norm = Vertex[0].norm;
		Vertex[5].norm = Vertex[0].norm;

		// ２ポリゴンの描画
		DrawPolygon3D(Vertex, 2, holeImgHandle, TRUE);
	}

	//右側の壁
	for (int i = 0; i < WALL_SIDE_HOLE_NUM; i++)
	{
		TransformMatrix = MGetRotY(90.0f * DX_PI_F / 180.0f);
		TransformMatrix = MMult(TransformMatrix, MGetTranslate(VGet(330.0f, GROUND_HEIGHT, -50.0f - i * 75.0f)));

		//行列を使ってワールド座標を算出
		Vertex[0].pos = VTransform(VGet(-35.0f, 35.0f, 0.0f), TransformMatrix);
		Vertex[1].pos = VTransform(VGet(35.0f, 35.0f, 0.0f), TransformMatrix);
		Vertex[2].pos = VTransform(VGet(-35.0f, -35.0f, 0.0f), TransformMatrix);
		Vertex[3].pos = VTransform(VGet(35.0f, -35.0f, 0.0f), TransformMatrix);

		Vertex[4].pos = Vertex[2].pos;
		Vertex[5].pos = Vertex[1].pos;

		// 行列を使って法線を算出
		Vertex[0].norm = VTransformSR(VGet(0.0f, 0.0f, -1.0f), TransformMatrix);
		Vertex[1].norm = Vertex[0].norm;
		Vertex[2].norm = Vertex[0].norm;
		Vertex[3].norm = Vertex[0].norm;
		Vertex[4].norm = Vertex[0].norm;
		Vertex[5].norm = Vertex[0].norm;

		// ２ポリゴンの描画
		DrawPolygon3D(Vertex, 2, holeImgHandle, TRUE);
	}

	// ライティングを有効にする
	SetUseLighting(TRUE);

	// Ｚバッファを無効にする
	SetUseZBuffer3D(FALSE);
}
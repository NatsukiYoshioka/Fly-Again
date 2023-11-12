#include"BaseScene.h"
#include"SceneManager.h"
#include"UIManager.h"
#include"ModelManager.h"
#include"PadInput.h"
#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include<cmath>
#include "ResultScene.h"

//変数と座標の初期化、テクスチャとモデルのロード
ResultScene::ResultScene():
	select(SELECT::MENU),
	choose(SELECT::MENU),
	isChoose(false),
	animationPlayTime(0),
	clearPlayingEffectHandle(0),
	mouseAnimation(1),
	robotScale(0.8f),
	mouseScale(1.0f),
	movePower(0.0f),
	scrollSpeed(1),
	isFadeIn(false),
	isFadeOut(false),
	alpha(255),
	alphaAdd(-2),
	drawStarFlag(0),
	maxStarNum(0),
	prevCount(0)
{
	//スクロール背景の初期化とロード
	for (int i = 0; i < BACKGROUND_NUM; i++)
	{
		scrollX[i] = 0;
	}
	backgroundImgHandle[0] = LoadGraph("data/texture/city/1.png");
	backgroundImgHandle[1] = LoadGraph("data/texture/city/2.png");
	backgroundImgHandle[2] = LoadGraph("data/texture/city/3.png");
	backgroundImgHandle[3] = LoadGraph("data/texture/city/4.png");
	backgroundImgHandle[4] = LoadGraph("data/texture/city/5.png");
	backgroundImgHandle[5] = LoadGraph("data/texture/city/6.png");

	//UI画像のロード
	starImgHandle = LoadGraph("data/texture/UI/Star.png");
	starShadowImgHandle = LoadGraph("data/texture/UI/Star0.png");
	nullUIImgHandle= LoadGraph("data/texture/UI/null.png");
	menuImgHandle= LoadGraph("data/texture/UI/menu.png");
	retryImgHandle = LoadGraph("data/texture/UI/retry.png");
	cheeseMarkerImgHandle = UIManager::GetCheeseMarkerImgHandle();

	//フェードイン＆アウト用画像の取得
	blackBackgroundHandle = UIManager::GetBlackBackGroundHandle();

	//モデルのロード
	robotModelHandle = MV1DuplicateModel(ModelManager::GetRobotModelHandle());
	mouseModelHandle = MV1DuplicateModel(ModelManager::GetMouseModelHandle());

	//エフェクトのロード
	clearEffectHandle = LoadEffekseerEffect(GetClearEffectPath(), 100.0f);
	starEffectHandle = LoadEffekseerEffect(GetStarEffectPath(), 15.0f);
	for (int i = 0; i < 3; i++)
	{
		isPlayingStarEffect[i] = false;
		starPlayingEffectHandle[i] = 0;
	}

	//モデル&テクスチャ座標の初期化
	robotPos = VGet(-100.0f, -100.0f, 0.0f);
	mousePos = VGet(-100.0f, 0.0f, 0.0f);

	//エフェクト座標の初期化
	clearEffectPos = VGet(0.0f, 0.0f, 0.0f);

	starEffectPos[0] = VGet(-56.0f, 128.0f, 0.0f);
	starEffectPos[1] = VGet(-3.0f, 128.0f, 0.0f);
	starEffectPos[2] = VGet(50.0f, 128.0f, 0.0f);

	//モデルの縮小
	MV1SetScale(robotModelHandle, VGet(robotScale, robotScale, robotScale));
	MV1SetScale(mouseModelHandle, VGet(mouseScale, mouseScale, mouseScale));

	//モデルの回転
	MV1SetRotationXYZ(robotModelHandle, VGet(0.0f, -135.0f * DX_PI_F / 180.0f, 0.0f));
	MV1SetRotationXYZ(mouseModelHandle, VGet(0.0f, 110.0f * DX_PI_F / 180.0f, 0.0f));

	//アニメーションのアタッチ
	MV1AttachAnim(mouseModelHandle, mouseAnimation, mouseModelHandle, TRUE);

	//カメラの初期化
	SetDrawScreen(GetActiveGraph());

	//クリア状況で星の最大数を設定
	if (SceneManager::GetCondition() == SceneManager::FINISH_CONDITION::CLEAR)
	{
		maxStarNum = 2;
	}
	else if (SceneManager::GetCondition() == SceneManager::FINISH_CONDITION::PERFECT)
	{
		maxStarNum = 3;
	}
}

//テクスチャとモデルの後処理
ResultScene::~ResultScene()
{
	//ハンドルのアンロード
	DeleteGraph(*backgroundImgHandle);
	DeleteGraph(blackBackgroundHandle);
	DeleteGraph(starImgHandle);
	DeleteGraph(starShadowImgHandle);
	DeleteGraph(nullUIImgHandle);
	DeleteGraph(menuImgHandle);
	DeleteGraph(retryImgHandle);
	DeleteGraph(cheeseMarkerImgHandle);

	MV1DeleteModel(mouseModelHandle);
	MV1DeleteModel(robotModelHandle);
}

//リザルトシーン全体の更新
void ResultScene::Update()
{
	//選択処理
	if (!isChoose)
	{
		if (PadInput::GetPadInput().ThumbLX < 0 || CheckHitKey(KEY_INPUT_A) != 0)
		{
			select = SELECT::MENU;
		}
		if (PadInput::GetPadInput().ThumbLX > 0 || CheckHitKey(KEY_INPUT_D) != 0)
		{
			select = SELECT::RETRY;
		}
		if (PadInput::GetPadInput().Buttons[12] || CheckHitKey(KEY_INPUT_RETURN) != 0)
		{
			isChoose = true;
			choose = select;
		}
	}

	//フェードイン処理
	if (!isFadeIn)
	{
		alpha += alphaAdd;
		if (alpha <= 0)
		{
			alpha = 0;
			isFadeIn = true;
		}
	}

	if (isFadeIn)
	{
		//フェードイン後の演出処理
		movePower += moveSpeed;
		if (movePower >= maxMovePower)
		{
			movePower = maxMovePower;
		}
		UpdateRobot();
		UpdateMouse();
	}

	//フェードアウト処理
	if (isFadeOut)
	{
		alpha -= alphaAdd;
		if (!isChoose && alpha >= 200)
		{
			alpha = 200;
		}
		//スコア表示用のカウントを開始
		if (alpha >= 200 && prevCount == 0)
		{
			prevCount = GetNowCount();
		}
		if (alpha >= 255)
		{
			alpha = 255;
			if (choose == SELECT::MENU)
			{
				SceneManager::ChangeScene(SceneManager::SCENE::TITLE);
			}
			else
			{
				SceneManager::ChangeScene(SceneManager::SCENE::GAME);
			}
		}
	}

	//エフェクトの更新
	UpdateEffect();

	//座標のセット
	MV1SetPosition(robotModelHandle, robotPos);
	MV1SetPosition(mouseModelHandle, mousePos);
}

//ロボットの挙動処理更新
void ResultScene::UpdateRobot()
{
	//ロボットの移動処理
	robotPos.y += risePower;
	robotPos.x += movePower;

	//ロボットのスケール更新
	robotScale -= scaleSub;
	if (robotScale <= 0.0f)
	{
		robotScale = 0.0f;
	}

	//フェードアウトを始めるロボットの位置
	if (robotPos.x >= 1000.0f)
	{
		isFadeOut = true;
	}

	//スケールのセット
	MV1SetScale(robotModelHandle, VGet(robotScale, robotScale, robotScale));
}

//マウスの挙動処理更新
void ResultScene::UpdateMouse()
{
	//マウスの移動処理
	mousePos.y += risePower / 1.1f;
	mousePos.x += movePower;

	//マウスのスケール更新
	mouseScale -= scaleSub / 0.8f;
	if (mouseScale <= 0.0f)
	{
		mouseScale = 0.0f;
	}

	//スケールのセット
	MV1SetScale(mouseModelHandle, VGet(mouseScale, mouseScale, mouseScale));
}

//アニメーション再生処理
void ResultScene::UpdateEffect()
{
	//アニメーションの再生
	if (animationPlayTime % 60 == 0)
	{
		if (SceneManager::GetCondition() == SceneManager::FINISH_CONDITION::CLEAR|| SceneManager::GetCondition() == SceneManager::FINISH_CONDITION::PERFECT)
		{
			clearPlayingEffectHandle = PlayEffekseer3DEffect(clearEffectHandle);
		}
	}

	//プレイ中のエフェクトの座標セット
	if (SceneManager::GetCondition() == SceneManager::FINISH_CONDITION::CLEAR|| SceneManager::GetCondition() == SceneManager::FINISH_CONDITION::PERFECT)
	{
		SetPosPlayingEffekseer3DEffect(clearPlayingEffectHandle, clearEffectPos.x, clearEffectPos.y, clearEffectPos.z);
	}

	//再生中のエフェクトを更新する
	UpdateEffekseer3D();

	animationPlayTime++;
}

//リザルトシーン描画
void ResultScene::Draw()
{
	//スクロール背景の描画
	for (int i = 0; i < BACKGROUND_NUM; i++)
	{
		DrawExtendGraph(0 - scrollX[i], 0, 1920 - scrollX[i], 1080, backgroundImgHandle[i], TRUE);
		DrawExtendGraph(1920 - scrollX[i], 0, 1920 * 2 - scrollX[i], 1080, backgroundImgHandle[i], TRUE);
		scrollX[i] += i * scrollSpeed;
		if (scrollX[i] >= 1920)
		{
			scrollX[i] = 0;
		}
	}

	//モデルの描画
	if (isFadeIn)
	{
		if (SceneManager::GetCondition() == SceneManager::FINISH_CONDITION::CLEAR)
		{
			MV1DrawModel(robotModelHandle);
		}
		else if (SceneManager::GetCondition() == SceneManager::FINISH_CONDITION::PERFECT)
		{
			MV1DrawModel(robotModelHandle);
			MV1DrawModel(mouseModelHandle);
		}
	}

	//DrawString(0, 16, "RESULT", GetColor(255, 255, 255));

	//フェードイン＆アウト後画像描画
	if (!isFadeIn || isFadeOut)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawExtendGraph(0, 0, 1920, 1080, blackBackgroundHandle, FALSE);
		if (isFadeOut && alpha >= 0)
		{
			//スコア用スター描画
			for (int i = 0; i < 3; i++)
			{
				DrawExtendGraph(830 + i * 100, 290, 880 + i * 100, 340, starShadowImgHandle, TRUE);
			}

			//リザルト画面描画
			ChangeFont("Starry Night", DX_CHARSET_DEFAULT);
			SetFontSize(200);
			if (SceneManager::GetCondition() == SceneManager::FINISH_CONDITION::CLEAR)
			{
				DrawStringF(640.0f, 500.0f, "CLEAR", GetColor(255, 255, 255));
			}
			else if (SceneManager::GetCondition() == SceneManager::FINISH_CONDITION::PERFECT)
			{
				DrawStringF(525.0f, 500.0f, "PERFECT", GetColor(255, 255, 255));
			}
			else
			{
				DrawStringF(400.0f, 500.0f, "GAMEOVER", GetColor(255, 255, 255));
			}
			SetFontSize(16);
			ChangeFont("ArcadeClassic", DX_CHARSET_DEFAULT);

			//シーン移動UI描画
			DrawExtendGraphF(660.0f, 740.0f, 814.0f, 810.0f, nullUIImgHandle, FALSE);
			DrawExtendGraphF(1106.0f, 740.0f, 1260.0f, 810.0f, nullUIImgHandle, FALSE);

			DrawExtendGraphF(660.0f, 740.0f, 814.0f, 810.0f, menuImgHandle, FALSE);
			DrawExtendGraphF(1106.0f, 740.0f, 1260.0f, 810.0f, retryImgHandle, FALSE);

			if (select == SELECT::MENU)
			{
				DrawExtendGraph(809.0f, 715.0f, 859.0f, 765.0f, cheeseMarkerImgHandle, TRUE);
			}
			else
			{
				DrawExtendGraph(1255.0f, 715.0f, 1305.0f, 765.0f, cheeseMarkerImgHandle, TRUE);
			}
		}

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//クリア時のスコア表示
	if (isFadeOut && alpha >= 200)
	{
		if (GetNowCount() - prevCount >= 500 && drawStarFlag < maxStarNum)
		{
			prevCount = GetNowCount();
			drawStarFlag++;
		}
		for (int i = 0; i < drawStarFlag; i++)
		{
			if (!isPlayingStarEffect[i])
			{
				starPlayingEffectHandle[i] = PlayEffekseer3DEffect(starEffectHandle);
				SetPosPlayingEffekseer3DEffect(starPlayingEffectHandle[i], starEffectPos[i].x, starEffectPos[i].y, starEffectPos[i].z);
				isPlayingStarEffect[i] = true;
			}
			DrawExtendGraph(830 + i * 100, 290, 880 + i * 100, 340, starImgHandle, TRUE);
		}

		if (isChoose)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			DrawExtendGraph(0, 0, 1920, 1080, blackBackgroundHandle, FALSE);
		}
	}

	//エフェクトの描画
	DrawEffekseer3D();
}

//クリア時のエフェクトのパス取得
const char* ResultScene::GetClearEffectPath()
{
	return "data/effect/wind.efk";
}

//スターが付いた時のエフェクトのパス取得
const char* ResultScene::GetStarEffectPath()
{
	return "data/effect/star.efk";
}
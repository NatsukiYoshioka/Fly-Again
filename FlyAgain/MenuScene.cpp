#include"BaseScene.h"
#include"SceneManager.h"
#include"PadInput.h"
#include"UIManager.h"
#include"ModelManager.h"
#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include<cmath>
#include "MenuScene.h"

MenuScene::SELECT MenuScene::choose = SELECT::PLAY;

//変数と座標の初期化、テクスチャとモデルのロード
MenuScene::MenuScene() :
	scrollSpeed(1),
	radian(0.0f),
	fallPower(1.0f),
	fallSpeed(-0.05f),
	burnPlayingEffectHandle(0),
	burnPlayTime(0),
	bombPlayingEffectHandle(0),
	isPlayBombEffect(false),
	select(SELECT::PLAY),
	isChoose(false),
	isFadeout(false),
	isCrashRobot(false),
	startFlashing(1),
	resetFlag(0),
	alpha(255),
	blackAlpha(255),
	alphaAdd(-2),
	isStartGame(false),
	isStartMenu(false)
{
	//カメラの位置をセット
	SetCameraPositionAndTargetAndUpVec(VGet(0, 215, -500), VGet(0, 0, 0), VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));

	//背景画像のスクロール量を初期化
	for (int i = 0; i < BACKGROUND_NUM; i++)
	{
		scrollX[i] = 0;
	}

	//背景画像をロード
	backgroundImgHandle[0] = LoadGraph("data/texture/1.png");
	backgroundImgHandle[1] = LoadGraph("data/texture/2.png");
	backgroundImgHandle[2] = LoadGraph("data/texture/3.png");
	backgroundImgHandle[3] = LoadGraph("data/texture/4.png");
	backgroundImgHandle[4] = LoadGraph("data/texture/5.png");

	//UIをロード
	playUIHandle = LoadGraph("data/texture/UI/play.png");
	nullUIHandle = LoadGraph("data/texture/UI/null.png");
	buttonUIHandle = UIManager::GetButtonAImgHandle();
	stickLightUIHandle = LoadGraph("data/texture/UI/stick_light.png");
	blackBackgroundHandle = UIManager::GetBlackBackGroundHandle();

	//ロボットの3Dモデルを取得
	robotModelHandle = MV1DuplicateModel(ModelManager::GetRobotModelHandle());

	//エフェクトをロード
	burnEffectHandle = LoadEffekseerEffect(GetBurnEffectPath(), 2.0f);
	bombEffectHandle = LoadEffekseerEffect(GetBombEffectPath(), 10.0f);

	//座標の初期化
	robotPos = VGet(0.0f, -100.0f, 0.0f);

	//モデルの縮小
	MV1SetScale(robotModelHandle, VGet(0.15f, 0.15f, 0.15f));

	//モデルの回転
	MV1SetRotationXYZ(robotModelHandle, VGet(0.0f, -90.0f * DX_PI_F / 180.0f, 0.0f));

	//UIの座標を設定
	playUIPos = VGet(-200.0f, -150.0f, 0.0f);
	nullUIPos = VGet(200.0f, -150.0f, 0.0f);
	buttonUIPos = VGet(-400.0f, 250.0f, 0.0f);
	stickLightUIPos = VGet(-417.0f, 200.0f, 0.0f);
}

//テクスチャとモデルの後処理
MenuScene::~MenuScene()
{
	DeleteGraph(*backgroundImgHandle);
	DeleteGraph(playUIHandle);
	DeleteGraph(nullUIHandle);
	DeleteGraph(buttonUIHandle);
	DeleteGraph(stickLightUIHandle);

	MV1DeleteModel(robotModelHandle);
	DeleteEffekseerEffect(burnEffectHandle);
	DeleteEffekseerEffect(bombEffectHandle);
}

//メニューシーン全体の更新
void MenuScene::Update()
{
	//ロボットと入力処理の更新
	UpdateRobot();
	UpdateInput();

	//プレイを選択した場合の演出処理
	FadeoutProcesse();
	CrashRobotProcess();

	//演出が終わったらゲームシーンに遷移する
	if (isStartGame)
	{
		SceneManager::ChangeScene(SceneManager::SCENE::GAME);
	}

	/*if (CheckHitKey(KEY_INPUT_E) != 0)
	{
		SceneManager::ChangeScene(SceneManager::RESULT);
	}*/
}

//ロボットの位置更新
void MenuScene::UpdateRobot()
{
	//UIの選択位置にロボットを移動
	if (!isChoose)
	{
		if (select == SELECT::PLAY)
		{
			robotPos.x = -180.0f;
		}
		else
		{
			robotPos.x = 180.0f;
		}
	}
	//ロボットの基本挙動の処理
	if (!isCrashRobot)
	{
		radian += speed;
		if (radian >= 2.0f)
		{
			radian = 0.0f;
		}
		robotPos.y += sinf(radian * DX_PI_F);
	}
	//ロボットが爆発したときにロボットを落下させる
	if (isPlayBombEffect)
	{
		fallPower += fallSpeed;
		robotPos.y += fallPower;
	}
	MV1SetPosition(robotModelHandle, robotPos);
}

//入力処理
void MenuScene::UpdateInput()
{
	//選択処理
	if (isStartMenu && !isChoose)
	{
		if (PadInput::GetPadInput().ThumbLX < 0 || CheckHitKey(KEY_INPUT_A) != 0)
		{
			select = SELECT::PLAY;
		}
		if (PadInput::GetPadInput().ThumbLX > 0 || CheckHitKey(KEY_INPUT_D) != 0)
		{
			select = SELECT::EXIT;
		}
		//PLAYを選択したら演出をスタートさせる
		if (PadInput::GetPadInput().Buttons[12] || CheckHitKey(KEY_INPUT_RETURN) != 0)
		{
			choose = select;
			isChoose = true;
			if (choose == SELECT::PLAY)
			{
				startFlashing = GetNowCount();
			}
			else
			{
				PadInput::End();
			}
		}
	}
}

//メニューシーン描画
void MenuScene::Draw()
{
	//背景とUIの描画
	DrawBackgound();
	DrawUI();

	//PLAYを選択していたらエフェクトが描画されて画面をフェードアウトさせる
	if (isCrashRobot)
	{
		DrawEffekseer3D();
	}
	if (isCrashRobot || !isStartMenu)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, blackAlpha);
		DrawExtendGraph(0, 0, 1920, 1080, blackBackgroundHandle, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	//DrawString(0, 16, "MENU", GetColor(255, 255, 255));
}

//背景描画
void MenuScene::DrawBackgound()
{
	//背景画像描画
	for (int i = 0; i < BACKGROUND_NUM; i++)
	{
		DrawExtendGraph(0 - scrollX[i], 0, 1920 - scrollX[i], 1080, backgroundImgHandle[i], TRUE);
		DrawExtendGraph(1920 - scrollX[i], 0, 1920 * 2 - scrollX[i], 1080, backgroundImgHandle[i], TRUE);
		scrollX[i] += i * scrollSpeed;
		if (scrollX[i]>=1920)
		{
			scrollX[i] = 0;
		}
	}
	//タイトル描画
	ChangeFont("Starry Night", DX_CHARSET_DEFAULT);
	SetFontSize(200);
	DrawStringF(550.0f, 300.0f, "Fly Again", GetColor(255, 255, 255));
	ChangeFont("ArcadeClassic", DX_CHARSET_DEFAULT);

	//ロボット描画
	MV1DrawModel(robotModelHandle);
}

void MenuScene::DrawUI()
{
	//フェードアウトさせるかどうか
	if (isFadeout)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	}
	//PLAY UI
	DrawBillboard3D(playUIPos, 0.5f, 0.5f, 200.0f, 0.0f, nullUIHandle, TRUE);
	//点滅処理
	if (GetNowCount() - startFlashing >= 250 && startFlashing != 0 && choose == SELECT::PLAY)
	{
		DrawBillboard3D(playUIPos, 0.5f, 0.5f, 200.0f, 0.0f, playUIHandle, TRUE);
	}
	if (GetNowCount() - startFlashing >= 500 && isChoose && resetFlag < 2 && choose == SELECT::PLAY)
	{
		startFlashing = GetNowCount();
		resetFlag++;
	}

	//EXIT UI
	SetFontSize(32);
	DrawBillboard3D(nullUIPos, 0.5f, 0.5f, 200.0f, 0.0f, nullUIHandle, TRUE);
	DrawStringF(1240.0f,735.0f, "EXIT", GetColor(184, 134, 11));

	//Controller UI
	SetFontSize(64);
	DrawBillboard3D(buttonUIPos, 0.5f, 0.5f, 50.0f, 0.0f, buttonUIHandle, TRUE);
	DrawBillboard3D(stickLightUIPos, 0.5f, 0.5f, 50.0f, 0.0f, stickLightUIHandle, TRUE);
	DrawStringF(175.0f, 30.0f, "CONFIRM AND JUMP", GetColor(255, 255, 255));
	DrawStringF(175.0f, 140.0f, "SELECT AND MOVE", GetColor(255, 255, 255));
	SetFontSize(16);

	if (isFadeout)
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

//フェードアウト用のアルファ値加減算処理
void MenuScene::FadeoutProcesse()
{
	//ゲーム起動時のフェードイン処理
	if (!isStartMenu)
	{
		blackAlpha += alphaAdd;
		if (blackAlpha <= 0)
		{
			blackAlpha = 0;
			isStartMenu = true;
		}
	}

	//PLAYが点滅してロボットが爆発したららフェードアウトを始める
	if (resetFlag == 2)
	{
		isFadeout = true;
	}
	if (isFadeout && !isCrashRobot)
	{
		alpha += alphaAdd;
		if (alpha <= 0)
		{
			isCrashRobot = true;
		}
	}
	if (isPlayBombEffect)
	{
		alphaAdd = 1;
		blackAlpha += alphaAdd;
		if (blackAlpha >= 255)
		{
			isStartGame = true;
		}
	}
}

//ロボットの爆発演出処理
void MenuScene::CrashRobotProcess()
{
	if (isCrashRobot)
	{
		if (burnPlayTime % 60 == 0)
		{
			//エフェクトを再生
			burnPlayingEffectHandle = PlayEffekseer3DEffect(burnEffectHandle);
			if (!isPlayBombEffect)
			{
				bombPlayingEffectHandle = PlayEffekseer3DEffect(bombEffectHandle);
				isPlayBombEffect = true;
			}
		}

		//再生中のエフェクトに座標を設定する
		SetPosPlayingEffekseer3DEffect(burnPlayingEffectHandle, robotPos.x, robotPos.y + 10.0f, robotPos.z);
		SetPosPlayingEffekseer3DEffect(bombPlayingEffectHandle, robotPos.x, robotPos.y + 10.0f, robotPos.z);

		//再生中のエフェクトを更新する
		UpdateEffekseer3D();

		//時間を経過させる
		burnPlayTime++;
	}
}

//炎上エフェクトのパス取得
const char* MenuScene::GetBurnEffectPath()
{
	return "data/effect/bomb.efkefc";
}

//爆発エフェクトのパス取得
const char* MenuScene::GetBombEffectPath()
{
	return "data/effect/crash.efk";
}
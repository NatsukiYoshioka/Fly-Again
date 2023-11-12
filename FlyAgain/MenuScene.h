#pragma once
#include"BaseScene.h"
#include<DxLib.h>

#define BACKGROUND_NUM		5		//背景画像の数

class BaseScene;

/// <summary>
/// メニューシーンを制御するクラス
/// </summary>
class MenuScene :public BaseScene
{
public:
	/// <summary>
	/// ゲームを始めるか終わるか選択する
	/// </summary>
	enum class SELECT
	{
		PLAY,
		EXIT
	};

	/// <summary>
	/// 変数と座標の初期化、テクスチャとモデルのロード
	/// </summary>
	MenuScene();

	/// <summary>
	/// テクスチャとモデルの後処理
	/// </summary>
	~MenuScene();

	/// <summary>
	/// メニューシーン全体の更新
	/// </summary>
	void Update();

	/// <summary>
	/// ロボットの位置更新
	/// </summary>
	void UpdateRobot();

	/// <summary>
	/// 入力処理
	/// </summary>
	void UpdateInput();

	/// <summary>
	/// メニューシーン描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 背景描画
	/// </summary>
	void DrawBackgound();

	/// <summary>
	/// UI描画
	/// </summary>
	void DrawUI();

	/// <summary>
	/// フェードアウト用のアルファ値加減算処理
	/// </summary>
	void FadeoutProcesse();

	/// <summary>
	/// ロボットの爆発演出処理
	/// </summary>
	void CrashRobotProcess();

	/// <summary>
	/// 炎上エフェクトのパス取得
	/// </summary>
	/// <returns>炎上エフェクトのパス</returns>
	const char* GetBurnEffectPath();

	/// <summary>
	/// 爆発エフェクトのパス取得
	/// </summary>
	/// <returns>爆発エフェクトのパス</returns>
	const char* GetBombEffectPath();

	/// <summary>
	/// メニュー画面の選択確定した情報を取得
	/// </summary>
	/// <returns>選んだSELECTの変数</returns>
	static SELECT GetMenuSelect() { return choose; }
private:
	static constexpr float speed = 0.01f;					//sin波による移動のスピード
	static constexpr double exitFontSize = 2.25;			//「EXIT」のフォントサイズ
	static constexpr double controllFontSize = 4.0;			//操作説明のフォントサイズ
	static constexpr double titleFontSize = 8.0;			//タイトルのフォントサイズ

	int backgroundImgHandle[BACKGROUND_NUM];				//背景画像ハンドル
	int robotModelHandle;									//ロボットのモデルハンドル
	
	int burnEffectHandle;									//炎上エフェクトハンドル
	int burnPlayingEffectHandle;							//再生中の炎上エフェクトハンドル
	int burnPlayTime;										//炎上エフェクトを再生する時間

	int bombEffectHandle;									//爆発エフェクトハンドル
	int bombPlayingEffectHandle;							//再生中の爆発エフェクトハンドル
	bool isPlayBombEffect;									//爆発エフェクトを再生したかどうか

	int playUIHandle;										//SELEC::PLAYのUIハンドル
	int nullUIHandle;										//↑以外のUIハンドル
	int buttonUIHandle;										//ゲーム操作ボタンのUIハンドル
	int stickLightUIHandle;									//ゲーム操作スティックのUIハンドル
	int blackBackgroundHandle;								//フェードイン、アウト用の黒背景画像

	int scrollSpeed;										//背景のスクロールスピード
	int scrollX[BACKGROUND_NUM];							//背景のX座標スクロール量

	VECTOR robotPos;										//ロボットの座標
	float radian;											//sin波の値

	float fallPower;										//ロボットが落下する量
	const float fallSpeed;									//ロボットが落下するスピード

	VECTOR playUIPos;										//PLAY画像の座標
	VECTOR nullUIPos;										//枠のみの画像の座標
	VECTOR buttonUIPos;										//ボタン画像の座標
	VECTOR stickLightUIPos;									//左スティック画像の座標

	SELECT select;											//選択しているUI
	static SELECT choose;									//選択確定したUI

	bool isChoose;											//選択したかどうか
	bool isFadeout;											//フェードアウト処理を行うかどうか
	bool isCrashRobot;										//ロボットをクラッシュさせる処理を行うかどうか

	int startFlashing;										//点滅用の初期カウント変数
	int resetFlag;											//startFlashingをリセットした回数を保持するフラグ

	int alpha;												//アルファ値
	int blackAlpha;											//暗転用のアルファ値
	int alphaAdd;											//アルファ値の変化度

	bool isStartGame;										//ゲームをスタートするかどうか
	bool isStartMenu;										//メニュー画面が始まったかどうか
};
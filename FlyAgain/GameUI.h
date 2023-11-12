#pragma once

#define BROKEN_HEART_DRAW_COUNT		1		//割れハート画像を描画する時間
#define WALL_UP_HOLE_NUM			6		//上側の壁の穴の数
#define WALL_SIDE_HOLE_NUM			4		//両端の壁の穴の数
#define HOLE_SIZE					20.0f	//巣穴のサイズ

class Player;
class Field;

/// <summary>
/// ゲームシーンのUI管理クラス
/// </summary>
class GameUI
{
public:
	/// <summary>
	/// 変数の初期化とテクスチャのロード
	/// </summary>
	/// <param name="playerHP">プレイヤーのHP</param>
	GameUI(int playerHP);

	/// <summary>
	/// テクスチャの後処理
	/// </summary>
	~GameUI();

	/// <summary>
	/// UI描画処理の更新
	/// </summary>
	/// <param name="player">プレイヤー制御クラス</param>
	void Update(Player* player);

	/// <summary>
	/// UIの描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 巣穴の描画
	/// </summary>
	/// <param name="field">フィールド管理クラス</param>
	void DrawHole(Field* field);

	/// <summary>
	/// ゲームを開始するかどうかを取得する
	/// </summary>
	/// <returns>ゲーム開始するかどうか確認するフラグ</returns>
	bool GetIsStartGame() { return isStartGame; }
private:
	int heartImgHandle;						//ハート画像ハンドル
	int brokenHeartImgHandle;				//割れハート画像ハンドル
	int wrenchImgHandle;					//レンチ画像ハンドル
	int circleImgHandle;					//円ゲージ画像ハンドル
	int circleCheeseImgHandle;				//チーズ円ゲージ用画像ハンドル
	int buttonAImgHandle;					//Aボタン画像ハンドル
	int holeImgHandle;						//巣穴画像ハンドル
	int blackBackgroundHandle;				//黒背景画像ハンドル

	VECTOR heartPos;						//ハート画像のワールド座標

	VECTOR brokenHeartPos;					//割れハート画像のワールド座標

	VECTOR wrenchPos;						//レンチ画像のワールド座標

	int heartNum;							//ハートの現在の数
	int heartPrevNum;						//ハートの過去の数
	int wrenchNum;							//レンチの現在の数

	double fuelPercent;						//プレイヤーの燃料の割合

	int brokenStartCount;					//割れハート画像を描画する最初の時間

	bool isStartGame;						//ゲーム開始するかどうか
	int startGameCount;						//ゲームをスタートするまでのカウント
	const int maxCount;						//カウントする最大秒数
	int startFlag;							//ゲームを始めるフラグ

	int blackAlpha;							//開始前の黒背景のアルファ値
	int alphaAdd;							//アルファ値の加算値
	int descriptionAlpha;					//フォントのアルファ値
	const int maxAlpha;						//ゲーム内のアルファ値の最大値

	static constexpr int initialHeartPrevNum = 0;			//ハートの過去の数の初期化用定数
	static constexpr int initialWrenchNum = 0;				//レンチの現在の数の初期化用定数
	static constexpr int initialBrokenStartCount = 0;		//割れハート画像を描画する最初の時間の初期化用定数
	static constexpr int initialMaxCount = 7;				//カウントする最大秒数の初期化用定数
	static constexpr int initialStartFlag = 0;				//ゲームを始めるフラグの初期化用定数
	static constexpr int initialBlackAlpha = 255;			//開始前の黒背景のアルファ値の初期化用定数
	static constexpr int initialDescriptionAlpha = 0;		//フォントのアルファ値の初期化用定数
	static constexpr int initialAlphaAdd = -1;				//アルファ値の加算値の初期化用定数
	static constexpr int initialMaxAlpha = 127;				//アルファ値の最大値の初期化用定数
	static constexpr float initialFuelPercent = 0.0f;		//プレイヤーの燃料の割合の初期化用定数
	static const VECTOR initialHeartPos;					//ハート画像のワールド座標の初期化用定数
	static const VECTOR initialBrokenHeartPos;				//割れハート画像のワールド座標の初期化用定数
	static const VECTOR initialWrenchPos;					//レンチ画像のワールド座標の初期化用定数

	static constexpr int secondCount = 1000;				//1秒のカウント用定数
	static constexpr int descriptionFactor = 2;				//フォントのアルファ値加算係数
	static constexpr int alphaMaxLimit = 255;				//アルファ値の最大値

	static constexpr int circleCenterX = 957;				//円画像のX座標
	static constexpr int circleCenterY = 100;				//円画像のY座標
	static constexpr double circlePercent = 100.0;			//円画像の表示割合
	static constexpr double circleStartPercent = 0.0;		//円画像の初期割合
	static constexpr double circleScale = 0.1 * (3.0 / 4.0);//円画像のスケール
	static constexpr int circleReverseX = 0;				//円画像のX軸反転
	static constexpr int circleReverseY = 0;				//円画像のY軸反転

	static constexpr int circleCheeseCenterX = 960;			//円ゲージのX座標
	static constexpr int circleCheeseCenterY = 100;			//円ゲージのY座標
	static constexpr double circleCheeseScale = 0.1;		//円ゲージのスケール

	static constexpr int jumpUIX1 = 860;					//"JUMP"UIの左上のX座標
	static constexpr int jumpUIY1 = 150;					//"JUMP"UIの左上のY座標
	static constexpr int jumpUIX2 = 930;					//"JUMP"UIの右下のX座標
	static constexpr int jumpUIY2 = 220;					//"JUMP"UIの右下のY座標

	static constexpr int middleFontSize = 48;				//フォントの中サイズ
	static constexpr int jumpStringX = 930;					//"JUMP"文字のX座標
	static constexpr int jumpStringY = 165;					//"JUMP"文字のY座標
	static constexpr const char* jumpString = "JUMP";		//"JUMP"文字列
	static const unsigned int jumpStringColor;				//"JUMP"文字のカラー
};


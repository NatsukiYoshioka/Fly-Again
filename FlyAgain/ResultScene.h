#pragma once
#include"BaseScene.h"

#define BACKGROUND_NUM		6			//背景の枚数

class BaseScene;

/// <summary>
/// リザルトシーン制御クラス
/// </summary>
class ResultScene :public BaseScene
{
public:
	/// <summary>
	/// メニュー画面かゲーム画面に移動する
	/// </summary>
	enum class SELECT
	{
		MENU,
		RETRY
	};

	/// <summary>
	/// 変数と座標の初期化、テクスチャとモデルのロード
	/// </summary>
	ResultScene();

	/// <summary>
	/// テクスチャとモデルの後処理
	/// </summary>
	~ResultScene();

	/// <summary>
	/// リザルトシーン全体の更新
	/// </summary>
	void Update();

	/// <summary>
	/// ロボットの挙動処理更新
	/// </summary>
	void UpdateRobot();

	/// <summary>
	/// マウスの挙動処理更新
	/// </summary>
	void UpdateMouse();

	/// <summary>
	/// アニメーション再生処理
	/// </summary>
	void UpdateEffect();

	/// <summary>
	/// リザルトシーン描画
	/// </summary>
	void Draw();

	/// <summary>
	/// クリア時のエフェクトのパス取得
	/// </summary>
	/// <returns>クリア時のエフェクトのパス</returns>
	const char* GetClearEffectPath();

	/// <summary>
	/// スターが付いた時のエフェクトのパス取得
	/// </summary>
	/// <returns>スターが付いた時のエフェクトのパス</returns>
	const char* GetStarEffectPath();
private:
	int backgroundImgHandle[BACKGROUND_NUM];				//背景のハンドル
	int starImgHandle;										//星の画像ハンドル
	int starShadowImgHandle;								//星の影の画像ハンドル
	int nullUIImgHandle;									//文字無しUIハンドル
	int menuImgHandle;										//メニューUIハンドル
	int retryImgHandle;										//リトライUIハンドル
	int cheeseMarkerImgHandle;								//選択用チーズマーカー画像ハンドル
	int blackBackgroundHandle;								//黒背景画像ハンドル

	SELECT select;											//ゲームシーン移動変数
	SELECT choose;											//選択を確定した変数
	bool isChoose;											//選択したかどうか

	int robotModelHandle;									//ロボットのモデルハンドル
	int mouseModelHandle;									//マウスのモデルハンドル

	int clearEffectHandle;									//クリア時のエフェクトハンドル
	int clearPlayingEffectHandle;							//再生中のクリア時のエフェクトハンドル

	int starEffectHandle;									//スター獲得時のエフェクトハンドル
	int starPlayingEffectHandle[3];							//再生中のスター獲得時のエフェクトハンドル

	int mouseAnimation;										//マウスのアニメーション番号

	VECTOR robotPos;										//ロボットの座標
	VECTOR mousePos;										//マウスの座標
	float robotScale;										//ロボットの大きさ
	float mouseScale;										//マウスの大きさ
	float movePower;										//移動値

	int animationPlayTime;									
	VECTOR clearEffectPos;									//クリア時のエフェクト座標
	bool isPlayingStarEffect[3];							//スターエフェクトを再生したかどうか
	VECTOR starEffectPos[3];								//スター獲得時のエフェクト座標

	static constexpr float risePower = 3.5f;				//上昇値
	static constexpr float moveSpeed = 0.05f;				//移動加算値
	static constexpr float maxMovePower = 20.0f;			//最大移動値
	static constexpr float scaleSub = 0.0025f;				//スケールの減算値

	int scrollSpeed;										//背景のスクロールスピード
	int scrollX[BACKGROUND_NUM];							//背景のX座標スクロール量

	bool isFadeIn;											//フェードインしたかどうか
	bool isFadeOut;											//フェードアウトするかどうか
	int alpha;												//アルファ値
	int alphaAdd;											//アルファ加算値
	int prevCount;											//秒カウント用変数
	int maxStarNum;											//星を描画する最大数
	int drawStarFlag;										//星を描画する数を制限するフラグ
};
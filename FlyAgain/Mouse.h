#pragma once
#include<DxLib.h>

#define MOUSE_FIX_POS_Y		2.5f			//マウスのY軸当たり判定調整量
#define MOUSE_FIX_POS_Z		5.0f			//マウスのZ軸当たり判定調整量

#define MOUSE_SHADOW_SIZE		15.0f		//影の大きさ
#define MOUSE_SHADOW_HEIGHT		700.0f		//影が落ちる高さ


class Field;

/// <summary>
/// マウス1つを制御するクラス
/// </summary>
class Mouse
{
public:
    /// <summary>
    /// モデル関連のロードと座標の初期化
    /// </summary>
    /// <param name="modelHandle">マウスのモデルハンドル</param>
    Mouse(int modelHandle);

    /// <summary>
    /// モデルの後処理
    /// </summary>
    ~Mouse();

	/// <summary>
	/// マウスの出現座標とモデルの再取得
	/// </summary>
	/// <param name="modelHandle">マウスのモデルハンドル</param>
	void Initialize(int modelHandle);

	/// <summary>
	/// アニメーションと座標の更新
	/// </summary>
	void Update();

	/// <summary>
	/// モデルとアニメーションの描画
	/// </summary>
	void Draw();

	/// <summary>
	/// モデルの陰描画
	/// </summary>
	/// <param name="field">フィールドモデル管理クラス</param>
	void DrawShadow(Field* field);

	/// <summary>
	/// マウスの向きをセット
	/// </summary>
	void SetRunningDirection();

	/// <summary>
	/// マウスが画面内にいるかどうかの判定
	/// </summary>
	/// <returns>マウスが画面内にいるかどうか判定する変数</returns>
	bool IsCheckMouseAppearance();

	/// <summary>
	/// マウスの現在の座標を取得
	/// </summary>
	/// <returns>マウスの現在の座標</returns>
	VECTOR GetNowPosition();

	/// <summary>
	/// マウスの当たり判定座標を取得
	/// </summary>
	/// <returns>マウスの当たり判定座標</returns>
	VECTOR GetCollPos() { return CollPos; }

	/// <summary>
	/// マウスの当たり判定の球の半径を取得
	/// </summary>
	/// <returns>マウスの当たり判定の球の半径</returns>
	float GetHitRadius() { return hitRadius; }

	/// <summary>
	/// 陰のテクスチャのパス取得
	/// </summary>
	/// <returns></returns>
	const char* GetShadowImgPath();
private:
	enum class AppearanceSide		//マウスが出現する方向
	{
		TOP,						//マウスが画面上の上の壁から出現する
		UNDER,						//マウスが画面上の下の壁から出現する
		LEFT,						//マウスが画面上の左の壁から出現する
		RIGHT						//マウスが画面上の右の壁から出現する
	};
	int appearanceSide;				//マウスが出現する方向を格納する変数
	const int MaxTop;				//各方向のマウスの上限地点
	const int MaxUnder;
	const int MaxLeft;
	const int MaxRight;

	VECTOR pos;						//マウスの座標
	VECTOR CollPos;					//マウスの当たり判定座標
	VECTOR firstPos;				//マウスの初期地点
	VECTOR finalPos;				//マウスの最終地点
	float angle;					//マウスのアングル
	float fixAngle;					//マウスのアングルをX軸に平行に修正

	float runningSpeed;				//移動速度

	int modelHandle;				//フィールドのモデルハンドル
	int AttachIndex;				//アタッチするアニメーション番号
	const int RunningAnimation;		//マウスのランアニメーション番号

	float animPlayTime;				//アニメーション再生時間
	float animTotalTime;			//アニメーション総再生時間

	bool isAppearance;				//画面内にいるかどうか

	float hitRadius;				//当たり判定の球の半径

	int shadowHandle;				//影画像ハンドル
};


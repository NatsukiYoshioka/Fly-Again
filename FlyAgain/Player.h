#pragma once
#include<DxLib.h>

#define PLAYER_Z_MAX				15.0f			//プレイヤーが動けるZ軸の最大座標
#define PLAYER_Z_MIN				-300.0f			//プレイヤーが動けるZ軸の最小座標
#define PLAYER_X_MAX				300.0f			//プレイヤーが動けるX軸の最大座標
#define PLAYER_X_MIN				-275.0f			//プレイヤーが動けるX軸の最小座標
#define PLAYER_Y_MAX				190.0f			//プレイヤーが動けるY軸の最大座標

#define PLAYER_ANGLE_SPEED			20.0f			// 角度変化速度
#define PLAYER_MIN_HEIGHT			0.0f			//プレイヤーが落ちる場所の最低値
#define PLAYER_COLL_POS_Y			12.5f			//プレイヤーのY軸当たり判定調整量
#define PLAYER_SHADOW_SIZE			20.0f			//影の大きさ
#define PLAYER_SHADOW_HEIGHT		700.0f			//影が落ちる高さ

#define PLAYER_CLEAR_POINT			5				//プレイヤーがゲームクリアするのに必要なポイント数

#define PLAYER_CRASH_ROTATION_SPEED	10.0f			//プレイヤークラッシュ時の回転スピード

class Field;

using namespace std;

/// <summary>
/// プレイヤーを制御するクラス
/// </summary>
class Player
{
public:
	/// <summary>
	/// 変数、座標の初期化とモデルの取得
	/// </summary>
	Player();

	/// <summary>
	/// モデルの後処理
	/// </summary>
	~Player();

	/// <summary>
	/// 入力処理と座標の更新
	/// </summary>
	void Update();

	/// <summary>
	/// プレイヤーの動く速さの更新
	/// </summary>
	/// <param name="shaft">慣性の力</param>
	/// <param name="maxSpeed">プレイヤーが横に動くスピードの最大値</param>
	void UpdateSpeed(float* shaft,const float maxSpeed);

	/// <summary>
	/// プレイヤーの向きを修正
	/// </summary>
	void UpdateAngle();

	/// <summary>
	/// 抵抗処理
	/// </summary>
	void ResistanceProcess();

	/// <summary>
	/// プレイヤーがフィールド外に出ないようにする処理
	/// </summary>
	void FixPos();

	/// <summary>
	/// モデルの描画
	/// </summary>
	void Draw();

	/// <summary>
	/// プレイヤーの影の描画
	/// </summary>
	/// <param name="field"></param>
	void DrawShadow(Field* field);

	/// <summary>
	/// 地面に当たった時の処理
	/// </summary>
	void OnHitGround();

	/// <summary>
	/// 地面以外のモデルに当たった場合の処理
	/// </summary>
	/// <param name="hitFlag">モデルに当たったかどうか</param>
	void OnHitObstruct(bool hitFlag);

	/// <summary>
	/// ポイント付与関数
	/// </summary>
	/// <param name="randNum">レンチがそこにあるかどうか</param>
	/// <returns>レンチがあればtrueを返す</returns>
	bool GivePoint(int randNum);

	/// <summary>
	/// 当たり判定座標取得
	/// </summary>
	/// <returns>当たり判定座標</returns>
	VECTOR GetCollPos() { return CollPos; }

	/// <summary>
	/// 当たり判定の球の半径の取得
	/// </summary>
	/// <returns>当たり判定の球の半径</returns>
	float GetHitRadius() { return hitRadius; }

	/// <summary>
	/// 燃料補給
	/// </summary>
	void FuelSupply();

	/// <summary>
	/// プレイヤーの燃料割合取得
	/// </summary>
	/// <returns>燃料割合</returns>
	double GetfuelPercent() { return nowFuel / maxFuel * 100; }

	/// <summary>
	/// プレイヤーの残機取得
	/// </summary>
	/// <returns>プレイヤーの残機</returns>
	int GetPlayerHP() { return HP; };

	/// <summary>
	/// プレイヤーのポイント数取得
	/// </summary>
	/// <returns>プレイヤーのポイント数</returns>
	int GetPoint() { return point; }

	/// <summary>
	/// 陰のテクスチャパス取得
	/// </summary>
	/// <returns></returns>
	const char* GetShadowImgPath();
private:
	static constexpr float jump = 5.0f;						//ジャンプ力固定値
	 			
	static constexpr float gravity = 0.1f;					//重力加算値
	static constexpr float maxGravityPower = 7.0f;			//重力最大値
	 			
	static constexpr float lift = 0.15f;					//揚力加算値
	static constexpr float maxLiftPower = 3.5f;				//揚力最大値
	static constexpr float crashBoundPower = 2.5f;			//地面に当たった時の上昇度
	 			
	static constexpr float speed = 0.3f;					//プレイヤーの横に動くスピードの加算値
	static constexpr float maxSpeed = 4.0f;					//プレイヤーが横に動くスピードの最大値
	static constexpr float airResistance = 0.1f;			//プレイヤーが進む方向にかかる空気抵抗
	 			
	static constexpr double maxFuel = 100.0;				//プレイヤーのホバリング用最大燃料
	static constexpr double fuelDecreaseSpeed = -2.5;		//燃料の減少スピード

	float jumpPower;							//フレーム毎のジャンプ力
	float gravityPower;							//フレーム毎の重力
	float liftPower;							//フレーム毎の揚力
	float nowXSpeed;							//現在のプレイヤーのX軸スピード
	float nowZSpeed;							//現在のプレイヤーのZ軸スピード

	VECTOR MoveVec;								//プレイヤーが動く方向
	VECTOR TargetMoveDirection;					// モデルが向くべき方向のベクトル
	float Angle;								// モデルが向いている方向の角度

	VECTOR pos;									//プレイヤーモデルの座標
	VECTOR CollPos;								//プレイヤーの当たり判定座標
	float hitRadius;							//当たり判定の球の半径

	int modelHandle;							//フィールドのモデルハンドル
	int shadowHandle;							//プレイヤーの影のハンドル

	int HP;										//プレイヤーの残機
	int point;									//プレイヤーがクリアに必要なポイント数

	bool crash;									//プレイヤーが地面に当たったかどうか
	float crashRotation;						//プレイヤーがダメージを受けた時の回転量

	double nowFuel;								//現在の燃料
};


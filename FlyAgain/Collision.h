#pragma once

class Player;
class ObstructManager;
class Effect;

/// <summary>
/// プレイヤーとオブジェクトの当たり判定クラス
/// </summary>
class Collision
{
public:
	/// <summary>
	/// 変数の初期化
	/// </summary>
	Collision();

	/// <summary>
	/// クラスの後処理
	/// </summary>
	~Collision(){}

	/// <summary>
	/// 当たり判定の調査
	/// </summary>
	/// <param name="player">プレイヤー制御クラス</param>
	/// <param name="obstructMgr">プレイヤー以外のオブジェクト制御クラス</param>
	/// <param name="effect">エフェクト制御クラス</param>
	void HitJudge(Player* player, ObstructManager* obstructMgr, Effect* effect);

private:
	bool hitFlag;			//接触フラグ
};


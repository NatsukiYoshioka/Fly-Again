#pragma once

class Player;

/// <summary>
/// ゲームシーン内のエフェクトを制御するクラス
/// </summary>
class Effect
{
public:
	/// <summary>
	/// 変数の初期化とエフェクトのロード
	/// </summary>
	Effect();

	/// <summary>
	/// エフェクトハンドルの後処理
	/// </summary>
	~Effect();

	/// <summary>
	/// 再生しているエフェクトの位置更新
	/// </summary>
	/// <param name="player">プレイヤー制御クラス</param>
	void Update(Player* player);

	/// <summary>
	/// エフェクトの描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 地面に当たった時のエフェクトの再生処理
	/// </summary>
	/// <param name="pos">エフェクトを再生する座標</param>
	void UpdateBoundGroundEffect(VECTOR pos);

	/// <summary>
	/// チーズに当たった時のエフェクトの再生処理
	/// </summary>
	/// <param name="pos">エフェクトを再生する座標</param>
	void UpdateCheeseEffect(VECTOR pos);

	/// <summary>
	/// レンチを入手したときのエフェクトの再生処理
	/// </summary>
	/// <param name="pos">エフェクトを再生する座標</param>
	void UpdateWrenchEffect(VECTOR pos);

	/// <summary>
	/// 地面に当たった時のエフェクトのパス取得
	/// </summary>
	/// <returns>地面に当たった時のエフェクトのパス</returns>
	const char* GetBoundGroundEffectPath();

	/// <summary>
	/// チーズを入手した時のエフェクトのパス取得
	/// </summary>
	/// <returns>チーズを入手した時のエフェクトのパス</returns>
	const char* GetCheeseEffectPath();

	/// <summary>
	/// レンチを入手した時のエフェクトのパス取得
	/// </summary>
	/// <returns>レンチを入手した時のエフェクトのパス</returns>
	const char* GetWrenchEffectPath();
private:
	int boundGroundEffect;				//地面に当たった時のエフェクトハンドル
	int boundGroundPlayingEffect;		//地面に当たった時の再生しているエフェクトハンドル
	VECTOR boundGroundEffectPos;		//地面に当たった時のエフェクトの座標

	int cheeseEffect;					//チーズを入手した時のエフェクトハンドル
	int cheesePlayingEffect;			//チーズを入手した時の再生しているエフェクトハンドル
	VECTOR cheeseEffectPos;				//チーズを入手した時のエフェクトの座標

	int wrenchEffect;					//レンチを入手した時のエフェクトハンドル
	int wrenchPlayingEffect;			//レンチを入手した時の再生しているエフェクトハンドル
	VECTOR wrenchEffectPos;				//レンチを入手した時のエフェクトの座標

	static constexpr int initialBoundGroundPlayingEffect = 0;		//地面に当たった時の再生しているエフェクトハンドルの初期化用定数
	static constexpr int initialCheesePlayingEffect = 0;			//チーズを入手した時の再生しているエフェクトハンドルの初期化用定数
	static constexpr int initialWrenchPlayingEffect = 0;			//レンチを入手した時の再生しているエフェクトハンドルの初期化用定数
	static constexpr float effectScale = 15.0f;						//エフェクトのスケール
	static const VECTOR initialBoundGroundEffectPos;				//地面に当たった時のエフェクトの座標の初期化用定数
	static const VECTOR initialCheeseEffectPos;						//チーズを入手した時のエフェクトの座標の初期化用定数
	static const VECTOR initialWrenchEffectPos;						//レンチを入手した時のエフェクトの座標の初期化用定数
	static constexpr const char* boundGroundEffectPath = "data/effect/boundground.efk";		//地面に当たった時のエフェクトのパス
	static constexpr const char* cheeseEffectPath = "data/effect/getcheese.efk";			//チーズを入手した時のエフェクトのパス
	static constexpr const char* wrenchEffectPath = "data/effect/bounditem.efk";			//レンチを入手した時のエフェクトのパス
};


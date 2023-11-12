#pragma once
#include<DxLib.h>

class Field;
class Player;
class ObstructManager;
class Mouse;
class Collision;
class GameUI;
class Effect;

/// <summary>
/// メインゲームシーンを制御するクラス
/// </summary>
class GameScene :public BaseScene
{
public:
	/// <summary>
	/// ゲームシーンに必要なクラスの初期化とテクスチャのロード、座標の初期化
	/// </summary>
	GameScene();

	/// <summary>
	/// クラスの後処理
	/// </summary>
	~GameScene();

	/// <summary>
	/// ゲームシーンの更新
	/// </summary>
	void Update();

	/// <summary>
	/// ゲームシーンの描画
	/// </summary>
	void Draw();
private:
	Field* field;							//フィールド管理クラス
	Player* player;							//プレイヤー制御クラス
	ObstructManager* obstructManager;		//プレイヤー以外のモデル制御クラス
	Collision* collision;					//当たり判定クラス
	GameUI* gameUI;							//ゲーム内UI制御クラス
	Effect* effect;							//エフェクト制御クラス

	VECTOR blackImgPos;						//黒背景画像の座標
	int blackBackGroundHandle;				//黒背景画像ハンドル

	bool gameSet;							//ゲームが終わっているかどうか
	bool changeScene;						//シーン遷移するかどうか
	int blackOutCount;						//シーン遷移時の暗転するまでの最初の時間
	int alpha;								//暗転用画像のアルファ値
	int alphaAdd;							//アルファ値の変化度
};


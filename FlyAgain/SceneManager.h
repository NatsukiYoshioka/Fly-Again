#pragma once

class BaseScene;

/// <summary>
/// シーン全体を管理、制御するクラス
/// </summary>
class SceneManager
{
public:
	/// <summary>
	/// シーンの状態を管理
	/// </summary>
	enum class SCENE
	{
		TITLE,								//タイトル画面
		GAME,								//ゲーム画面
		RESULT								//リザルト画面
	};

	/// <summary>
	/// ゲーム終了した時の状態
	/// </summary>
	enum class FINISH_CONDITION
	{
		INGAME,								//ゲーム中
		PERFECT,							//パーフェクトクリア
		CLEAR,								//通常クリア
		GAMEOVER							//ゲームオーバー
	};

	/// <summary>
	/// シーンの初期化
	/// </summary>
	SceneManager();

	/// <summary>
	/// クラスの後処理
	/// </summary>
	~SceneManager() {}

	/// <summary>
	/// シーンを引数によって変える関数
	/// </summary>
	/// <param name="scene">変更するシーン</param>
	static void ChangeScene(SCENE scene);

	/// <summary>
	/// ゲーム終了時の状態を変更する関数
	/// </summary>
	/// <param name="condition">ゲーム終了時の状態</param>
	static void ChangeCondition(FINISH_CONDITION condition);

	/// <summary>
	/// 現在のシーンの更新
	/// </summary>
	static void Update();

	/// <summary>
	/// 現在のシーンの描画
	/// </summary>
	static void Draw();

	/// <summary>
	/// ゲーム終了時の状態を取得
	/// </summary>
	/// <returns>ゲーム終了時の状態</returns>
	static FINISH_CONDITION GetCondition() { return _condition; }
private:
	static BaseScene* nowScene;					//現在のシーン
	static FINISH_CONDITION _condition;			//ゲーム終了時の状態
};
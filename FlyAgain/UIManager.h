#pragma once

/// <summary>
/// UI画像管理クラス
/// </summary>
class UIManager
{
public:
	/// <summary>
	/// UI画像のロード
	/// </summary>
	UIManager();

	/// <summary>
	/// UI画像の後処理
	/// </summary>
	~UIManager();

	/// <summary>
	/// ハート画像ハンドル取得
	/// </summary>
	/// <returns>ハート画像ハンドル</returns>
	static int GetHeartImgHandle() { return heartImgHandle; }

	/// <summary>
	/// 割れハート画像ハンドル取得
	/// </summary>
	/// <returns>割れハート画像ハンドル</returns>
	static int GetBrokenHeartImgHandle() { return brokenHeartImgHandle; }

	/// <summary>
	/// レンチ画像ハンドル取得
	/// </summary>
	/// <returns>レンチ画像ハンドル</returns>
	static int GetWrenchImgHandle() { return wrenchImgHandle; }

	/// <summary>
	/// 黒背景画像ハンドル取得
	/// </summary>
	/// <returns>黒背景画像ハンドル</returns>
	static int GetBlackBackGroundHandle() { return blackBackGroundHandle; }

	/// <summary>
	/// 円画像ハンドル取得
	/// </summary>
	/// <returns>円画像ハンドル</returns>
	static int GetCircleImgHandle() { return circleImgHandle; }

	/// <summary>
	/// 円チーズ画像ハンドル取得
	/// </summary>
	/// <returns>円チーズ画像ハンドル</returns>
	static int GetCircleCheeseImgHandle() { return circleCheeseImgHandle; }

	/// <summary>
	/// 巣穴画像ハンドル取得
	/// </summary>
	/// <returns>巣穴画像ハンドル</returns>
	static int GetHoleImgHandle() { return holeImgHandle; }

	/// <summary>
	/// Aボタン画像ハンドル取得
	/// </summary>
	/// <returns>Aボタン画像ハンドル</returns>
	static int GetButtonAImgHandle() { return buttonAImgHandle; }

	/// <summary>
	/// 選択用チーズマーカー画像ハンドル取得
	/// </summary>
	/// <returns>選択用チーズマーカー画像ハンドル</returns>
	static int GetCheeseMarkerImgHandle() { return cheeseMarkerImgHandle; }

	const char* GetHeartTexturePath();				//ハート画像のパス取得
	const char* GetBrokenHeartTexturePath();		//割れハート画像のパス取得
	const char* GetWrenchTexturePath();				//レンチ画像のパス取得
	const char* GetBlackBackGroundPath();			//黒背景画像のパス取得
	const char* GetCircleTexturePath();				//円ゲージ画像パス取得
	const char* GetCircleCheeseTexturePath();		//チーズ円ゲージ用画像のパス取得
	const char* GetHoleTexturePath();				//巣穴画像のパス取得
	const char* GetButtonATexturePath();			//Aボタン画像のパス取得
	const char* GetCheeseMarkerTexturePath();		//選択用チーズマーカー画像のパス取得
private:
	static int heartImgHandle;							//ハート画像ハンドル
	static int brokenHeartImgHandle;					//割れハート画像ハンドル
	static int wrenchImgHandle;							//レンチ画像ハンドル
	static int blackBackGroundHandle;					//黒背景ハンドル
	static int circleImgHandle;							//円ゲージハンドル
	static int circleCheeseImgHandle;					//チーズ円ゲージ用画像ハンドル
	static int holeImgHandle;							//巣穴画像ハンドル
	static int buttonAImgHandle;						//Aボタン画像ハンドル
	static int cheeseMarkerImgHandle;					//選択用チーズマーカー画像ハンドル
};


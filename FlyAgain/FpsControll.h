#pragma once

/// <summary>
/// フレームレート制御クラス
/// </summary>
class FpsControll
{
public:
	/// <summary>
	/// カウントの初期化
	/// </summary>
	FpsControll();

	/// <summary>
	/// クラス後処理
	/// </summary>
	~FpsControll() {}

	/// <summary>
	/// フレームレート制御
	/// </summary>
	void Update();

	/// <summary>
	/// FPS表示
	/// </summary>
	void Draw();

	/// <summary>
	/// フレームレートを60で固定する
	/// </summary>
	void Wait();

private:
	int startTime;				//測定開始時刻
	int count;					//カウンタ
	float nowFps;				//現在のFps
	const int sampleAvg = 60;	//平均を取るサンプル数
	const int FPS = 60;			//設定したFPS
};


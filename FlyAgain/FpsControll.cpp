#include<cmath>
#include"DxLib.h"
#include "FpsControll.h"

//カウントの初期化
FpsControll::FpsControll() :count(0), nowFps(0)
{
	startTime = GetNowCount();
}

//フレームレート制御
void FpsControll::Update()
{
	if (count == 0)
	{
		//1フレーム目なら時刻を記憶
		startTime = GetNowCount();
	}
	if (count == sampleAvg)
	{
		//60フレーム目なら平均を計算する
		int t = GetNowCount();
		nowFps = 1000.f / ((t - startTime) / (float)sampleAvg);
		count = 0;
		startTime = t;
	}
	count++;
}

//FPS表示
void FpsControll::Draw()
{
	DrawFormatString(0, 0, GetColor(0, 0, 255), "%.1f", nowFps);
}

//フレームレートを60で固定する
void FpsControll::Wait()
{
	int tookTime = GetNowCount() - startTime;			//かかった時間
	int waitTime = count * 1000 / FPS - tookTime;		//待つべき時間

	if (waitTime > 0)
	{
		Sleep(waitTime);	//待機
	}
}
#include<cmath>
#include"DxLib.h"
#include "FpsControll.h"

//�J�E���g�̏�����
FpsControll::FpsControll() :count(0), nowFps(0)
{
	startTime = GetNowCount();
}

//�t���[�����[�g����
void FpsControll::Update()
{
	if (count == 0)
	{
		//1�t���[���ڂȂ玞�����L��
		startTime = GetNowCount();
	}
	if (count == sampleAvg)
	{
		//60�t���[���ڂȂ畽�ς��v�Z����
		int t = GetNowCount();
		nowFps = 1000.f / ((t - startTime) / (float)sampleAvg);
		count = 0;
		startTime = t;
	}
	count++;
}

//FPS�\��
void FpsControll::Draw()
{
	DrawFormatString(0, 0, GetColor(0, 0, 255), "%.1f", nowFps);
}

//�t���[�����[�g��60�ŌŒ肷��
void FpsControll::Wait()
{
	int tookTime = GetNowCount() - startTime;			//������������
	int waitTime = count * 1000 / FPS - tookTime;		//�҂ׂ�����

	if (waitTime > 0)
	{
		Sleep(waitTime);	//�ҋ@
	}
}
#pragma once

/// <summary>
/// �t���[�����[�g����N���X
/// </summary>
class FpsControll
{
public:
	/// <summary>
	/// �J�E���g�̏�����
	/// </summary>
	FpsControll();

	/// <summary>
	/// �N���X�㏈��
	/// </summary>
	~FpsControll() {}

	/// <summary>
	/// �t���[�����[�g����
	/// </summary>
	void Update();

	/// <summary>
	/// FPS�\��
	/// </summary>
	void Draw();

	/// <summary>
	/// �t���[�����[�g��60�ŌŒ肷��
	/// </summary>
	void Wait();

private:
	int startTime;				//����J�n����
	int count;					//�J�E���^
	float nowFps;				//���݂�Fps
	const int sampleAvg = 60;	//���ς����T���v����
	const int FPS = 60;			//�ݒ肵��FPS
};


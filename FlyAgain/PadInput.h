#pragma once
#include<DxLib.h>

/// <summary>
/// ���͏�������N���X
/// </summary>
class PadInput
{
public:
	/// <summary>
	/// �R���g���[���[���͍X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �Q�[���̏I����m�点��
	/// </summary>
	static void End();

	/// <summary>
	/// �R���g���[���[���͂��擾
	/// </summary>
	/// <returns>�R���g���[���[���͏��</returns>
	static XINPUT_STATE GetPadInput() { return input; }

	/// <summary>
	/// �Q�[�����I������邩�ǂ����擾
	/// </summary>
	/// <returns>�Q�[���̏I����m�点��t���O</returns>
	static bool  GetIsEnd() { return isEnd; }
private:
	static XINPUT_STATE input;				//Xinput�R���g���[���[��Pad�����i�[�����\����
	static bool isEnd;						//�Q�[�����I�����邩�ǂ���
};

// XInput�{�^�����͒�`
//#define XINPUT_BUTTON_DPAD_UP		(0)	�� �f�W�^�������{�^����
//#define XINPUT_BUTTON_DPAD_DOWN		(1)	�� �f�W�^�������{�^����
//#define XINPUT_BUTTON_DPAD_LEFT		(2)	�� �f�W�^�������{�^����
//#define XINPUT_BUTTON_DPAD_RIGHT	(3)	�� �f�W�^�������{�^���E
//#define XINPUT_BUTTON_START		(4)	�� START�{�^��
//#define XINPUT_BUTTON_BACK		(5)	�� BACK�{�^��
//#define XINPUT_BUTTON_LEFT_THUMB	(6)	�� ���X�e�B�b�N��������
//#define XINPUT_BUTTON_RIGHT_THUMB	(7)	�� �E�X�e�B�b�N��������
//#define XINPUT_BUTTON_LEFT_SHOULDER	(8)	�� LB�{�^��
//#define XINPUT_BUTTON_RIGHT_SHOULDER	(9)	�� RB�{�^��
//#define XINPUT_BUTTON_A			(12)	�� A�{�^��
//#define XINPUT_BUTTON_B			(13)	�� B�{�^��
//#define XINPUT_BUTTON_X			(14)	�� X�{�^��
//#define XINPUT_BUTTON_Y			(15)	�� Y�{�^��

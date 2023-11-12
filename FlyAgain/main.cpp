#include"common.h"
#include"FpsControll.h"
#include"UIManager.h"
#include"ModelManager.h"
#include"SceneManager.h"
#include"PadInput.h"
#include"Font.h"
#include"DxLib.h"
#include"EffekseerForDXLib.h"

//WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//--------------------------------------//
	//�����ݒ�
	//--------------------------------------//
	//DxLib������
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	// Effekseer������
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͎��s����
	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h��
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	// Z�o�b�t�@�ւ̏������݂�L���ɂ���
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	SetWaitVSyncFlag(0);		//����������؂�

	//��ʃ��[�h�̐ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR);
	ChangeWindowMode(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);

	FpsControll FpsControll;
	UIManager UIManager;
	ModelManager ModelManager;
	SceneManager SceneManager;
	PadInput PadInput;
	Font Font;
	
	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����
	Effekseer_Sync3DSetting();

	//--------------------------------------//
	//���C�����[�v
	//--------------------------------------//
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && !PadInput::GetIsEnd())
	{
		ClearDrawScreen();
		//�t���[�����[�g����
		FpsControll.Update();

		//�Q�[������
		PadInput.Update();

		SceneManager.Update();

		SceneManager.Draw();

		//�t���[�����[�g�\��
		//FpsControll.Draw();

		//�ҋ@
		FpsControll.Wait();

		ScreenFlip();
	}

	//DX���C�u�����̌�n��
	DxLib_End();

	//�G�t�F�N�V�A�̌�n��
	Effkseer_End();

	//�\�t�g�̏I��
	return 0;
}
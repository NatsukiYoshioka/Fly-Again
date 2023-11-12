#include"common.h"
#include"FpsControll.h"
#include"UIManager.h"
#include"ModelManager.h"
#include"SceneManager.h"
#include"PadInput.h"
#include"Font.h"
#include"DxLib.h"
#include"EffekseerForDXLib.h"

//WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//--------------------------------------//
	//初期設定
	//--------------------------------------//
	//DxLib初期化
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	// Effekseer初期化
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}
	// ウインドウとフルスクリーンの切り替えが発生する場合は実行する
	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	// DXライブラリのデバイスロストした時のコールバックを設定する
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	// Zバッファへの書き込みを有効にする
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	SetWaitVSyncFlag(0);		//垂直同期を切る

	//画面モードの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR);
	ChangeWindowMode(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);

	FpsControll FpsControll;
	UIManager UIManager;
	ModelManager ModelManager;
	SceneManager SceneManager;
	PadInput PadInput;
	Font Font;
	
	// DXライブラリのカメラとEffekseerのカメラを同期する
	Effekseer_Sync3DSetting();

	//--------------------------------------//
	//メインループ
	//--------------------------------------//
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && !PadInput::GetIsEnd())
	{
		ClearDrawScreen();
		//フレームレート制御
		FpsControll.Update();

		//ゲーム処理
		PadInput.Update();

		SceneManager.Update();

		SceneManager.Draw();

		//フレームレート表示
		//FpsControll.Draw();

		//待機
		FpsControll.Wait();

		ScreenFlip();
	}

	//DXライブラリの後始末
	DxLib_End();

	//エフェクシアの後始末
	Effkseer_End();

	//ソフトの終了
	return 0;
}
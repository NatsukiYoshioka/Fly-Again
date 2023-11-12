#include "PadInput.h"

XINPUT_STATE PadInput::input;
bool PadInput::isEnd = false;

//コントローラー入力更新
void PadInput::Update()
{
	GetJoypadXInputState(DX_INPUT_PAD1,&input);
}

//ゲームの終了を知らせる
void PadInput::End()
{
	isEnd = true;
}
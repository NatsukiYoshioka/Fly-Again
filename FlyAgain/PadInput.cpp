#include "PadInput.h"

XINPUT_STATE PadInput::input;
bool PadInput::isEnd = false;

//�R���g���[���[���͍X�V
void PadInput::Update()
{
	GetJoypadXInputState(DX_INPUT_PAD1,&input);
}

//�Q�[���̏I����m�点��
void PadInput::End()
{
	isEnd = true;
}
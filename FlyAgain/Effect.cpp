#include"Player.h"
#include"common.h"
#include"EffekseerForDXLib.h"
#include"DxLib.h"
#include "Effect.h"

const VECTOR Effect::initialBoundGroundEffectPos = VGet(0.0f, 0.0f, 0.0f);
const VECTOR Effect::initialCheeseEffectPos = VGet(0.0f, 0.0f, 0.0f);
const VECTOR Effect::initialWrenchEffectPos = VGet(0.0f, 0.0f, 0.0f);

//�ϐ��̏������ƃG�t�F�N�g�̃��[�h
Effect::Effect():
	boundGroundPlayingEffect	(initialBoundGroundPlayingEffect),
	cheesePlayingEffect			(initialCheesePlayingEffect),
	wrenchPlayingEffect			(initialWrenchPlayingEffect)
{
	boundGroundEffect = LoadEffekseerEffect(GetBoundGroundEffectPath(),effectScale);
	cheeseEffect = LoadEffekseerEffect(GetCheeseEffectPath(), effectScale);
	wrenchEffect = LoadEffekseerEffect(GetWrenchEffectPath(), effectScale);
}

//�G�t�F�N�g�n���h���̌㏈��
Effect::~Effect()
{
	DeleteEffekseerEffect(boundGroundEffect);
	DeleteEffekseerEffect(boundGroundPlayingEffect);
	DeleteEffekseerEffect(cheeseEffect);
	DeleteEffekseerEffect(cheesePlayingEffect);
	DeleteEffekseerEffect(wrenchEffect);
	DeleteEffekseerEffect(wrenchPlayingEffect);
}

//�Đ����Ă���G�t�F�N�g�̈ʒu�X�V
void Effect::Update(Player* player)
{
	SetPosPlayingEffekseer3DEffect(cheesePlayingEffect, player->GetCollPos().x, player->GetCollPos().y, player->GetCollPos().z);
	SetPosPlayingEffekseer3DEffect(wrenchPlayingEffect, player->GetCollPos().x, player->GetCollPos().y, player->GetCollPos().z);
	UpdateEffekseer3D();
}

//�n�ʂɓ����������̃G�t�F�N�g�̍Đ�����
void Effect::UpdateBoundGroundEffect(VECTOR pos)
{
	boundGroundPlayingEffect = PlayEffekseer3DEffect(boundGroundEffect);
	//�G�t�F�N�g�̈ʒu�ݒ�
	SetPosPlayingEffekseer3DEffect(boundGroundPlayingEffect, pos.x, GROUND_HEIGHT, pos.z);
}

//�`�[�Y�ɓ����������̃G�t�F�N�g�̍Đ�����
void Effect::UpdateCheeseEffect(VECTOR pos)
{
	cheesePlayingEffect = PlayEffekseer3DEffect(cheeseEffect);
	//�G�t�F�N�g�̈ʒu�ݒ�
	cheeseEffectPos = pos;
}

//�����`����肵���Ƃ��̃G�t�F�N�g�̍Đ�����
void Effect::UpdateWrenchEffect(VECTOR pos)
{
	wrenchPlayingEffect = PlayEffekseer3DEffect(wrenchEffect);
	//�G�t�F�N�g�̈ʒu�ݒ�
	wrenchEffectPos = pos;
}

//�G�t�F�N�g�̕`��
void Effect::Draw()
{
	DrawEffekseer3D();
}

//�n�ʂɓ����������̃G�t�F�N�g�̃p�X�擾
const char* Effect::GetBoundGroundEffectPath()
{
	return boundGroundEffectPath;
}

//�`�[�Y����肵�����̃G�t�F�N�g�̃p�X�擾
const char* Effect::GetCheeseEffectPath()
{
	return cheeseEffectPath;
}

//�����`����肵�����̃G�t�F�N�g�̃p�X�擾
const char* Effect::GetWrenchEffectPath()
{
	return wrenchEffectPath;
}
#include"common.h"
#include"DxLib.h"
#include "Cheese.h"

//Pos�̏������p�萔
const VECTOR Cheese::initialPos = VGet(0.0f, 0.0f, 0.0f);

//���f���̊g�k�x
const VECTOR Cheese::modelScale = VGet(1.5f, 1.5f, 1.5f);

//�`�[�Y��3D���f���ƍ��W�A�X�P�[����ݒ肷��
Cheese::Cheese(int modelHandle) :
    isAppearance        (false),
    hitRadius           (initialHitRadius),
    appearanceRandNum   (initialAppearanceRandNum)
{
    this->modelHandle = MV1DuplicateModel(modelHandle);

    pos = initialPos;

    MV1SetScale(this->modelHandle, modelScale);
}

//���f���n���h���̌㏈��
Cheese::~Cheese()
{
    MV1DeleteModel(modelHandle);
}

//�`�[�Y���o��������t���O�������_���ŏ���������
void Cheese::InitFlag()
{
    appearanceRandNum = GetRand(CHEESE_PROBABILITY);
    if (appearanceRandNum == CHEESE_APPEARANCE_NUM)
    {
        isAppearance = true;
    }
}

//�`�[�Y���f���̍��W�X�V
void Cheese::Update(VECTOR mousePos)
{
    pos = VGet(mousePos.x, GROUND_HEIGHT + CHEESE_FIX_POS_Y, mousePos.z);

    MV1SetPosition(modelHandle, pos);
}

//�`�[�Y�̕`��
void Cheese::Draw()
{
    if (isAppearance)
    {
        MV1DrawModel(modelHandle);

        // �f�o�b�O�����蔻��.
        //DrawSphere3D(pos, hitRadius, 5, 0x00ffff, 0x00ffff, false);
    }
}

//�v���C���[�ɓ����������̏���
void Cheese::OnHitPlayer(bool hitFlag)
{
    //�������Ă����ꍇ�����蔻��ƕ`��̃t���O��false�ɂ���
    if (hitFlag)
    {
        isAppearance = false;
    }
}
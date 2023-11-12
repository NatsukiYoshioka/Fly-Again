#include"DxLib.h"
#include "Wrench.h"

//���f���̎擾�ƍ��W�̏�����
Wrench::Wrench(int modelHandle) :isAppearance(false), rpm(0.0f)
{
    //���f���n���h���̎擾
    this->modelHandle = MV1DuplicateModel(modelHandle);

    //���W�̏�����
    pos = VGet(0.0f, 0.0f, 0.0f);

    //���f���̊g�k
    MV1SetScale(this->modelHandle, VGet(0.02f, 0.02f, 0.02f));
}

//���f���̌㏈��
Wrench::~Wrench()
{
    MV1DeleteModel(modelHandle);
}

//�o���̏�����
void Wrench::InitAppearance(int startTime)
{
    //12�b�����ɏo������
    if (GetNowCount() - startTime > 12000)
    {
        isAppearance = true;
    }
}

//�����`�̈ʒu�X�V
void Wrench::Update(VECTOR cheesePos)
{
    //�o�����Ă���ԉ�]����悤�ɂ���
    RotateWrench();

    //���W���`�[�Y�̏�ɗ���悤�ɂ���
    pos = VGet(cheesePos.x, cheesePos.y + WRENCH_FIX_POS_Y, cheesePos.z);

    //���f���̍��W���Z�b�g
    MV1SetPosition(modelHandle, pos);
}

//�����`�̕`��
void Wrench::Draw()
{
    MV1DrawModel(modelHandle);
}

//�����`���f���̉�]����
void Wrench::RotateWrench()
{
    rpm += rotationSpeed;
    if (rpm > maxRpm)
    {
        rpm = 0.0f;
    }
    MV1SetRotationXYZ(modelHandle, VGet(0.0f, rpm * DX_PI_F / 180.0f, 0.0f));
}

//�v���C���[�Ɏ擾���ꂽ�Ƃ��̏���
void Wrench::OnHitPlayer()
{
    isAppearance = false;
}
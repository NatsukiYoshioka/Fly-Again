#include"common.h"
#include"Field.h"
#include"GameUI.h"
#include<cmath>
#include "Mouse.h"

//���f���֘A�̃��[�h�Ə�����
Mouse::Mouse(int modelHandle) :animPlayTime(0.0f), RunningAnimation(2), isAppearance(true), MaxTop(25), MaxUnder(-350), MaxLeft(-275), MaxRight(300), fixAngle(150.0f * DX_PI_F / 180.0f), AttachIndex(0), angle(0.0f), animTotalTime(0.0f), appearanceSide(0), runningSpeed(0.0f), hitRadius(15.0f)
{
	//���f���n���h���̎擾
	this->modelHandle = MV1DuplicateModel(modelHandle);
	//�e�e�N�X�`���̃��[�h
	shadowHandle = LoadGraph(GetShadowImgPath());

	//���W�̏�����
	pos = VGet(0.0f, 0.0f, 0.0f);
	CollPos = VGet(0.0f, 0.0f, 0.0f);

	firstPos = VGet(0.0f, 0.0f, 0.0f);
	finalPos = VGet(0.0f, 0.0f, 0.0f);
}

//���f���̌㏈��
Mouse::~Mouse()
{
	MV1DeleteModel(modelHandle);
}

//�}�E�X�̏o�����W�ƃ��f���̍Ď擾
void Mouse::Initialize(int modelHandle)
{
	//�A�j���[�V�����ɂ���ă}�E�X�̃��f��������邽�߁A�n���h����������
	MV1DeleteModel(this->modelHandle);
	this->modelHandle = MV1DuplicateModel(modelHandle);

	//�}�E�X�̏����n�_�ƍŏI�n�_�̐ݒ�
	SetRunningDirection();

	//���W������
	pos = firstPos;
	CollPos = pos;

	//���f������ʓ��ɏo���ł���悤�ɂ���
	isAppearance = true;

	//�ړ����x�������_���ŏ�����
	runningSpeed = static_cast<float>(GetRand(500) + 300);

	//���f���̊g�k
	MV1SetScale(this->modelHandle, VGet(0.15f, 0.15f, 0.15f));

	// �R�c���f���̃A�j���[�V�������A�^�b�`����
	AttachIndex = MV1AttachAnim(this->modelHandle, RunningAnimation, this->modelHandle, TRUE);

	// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
	animTotalTime = MV1GetAttachAnimTotalTime(this->modelHandle, AttachIndex);

	//�A�j���[�V�����̍Đ����Ԃ�������
	animPlayTime = 0.0f;
}

//�A�j���[�V�����ƍ��W�̍X�V
void Mouse::Update()
{
	//�Đ����Ԃ�i�߂�
	animPlayTime += 2.0f;

	//�Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ�0�ɖ߂�
	if (animPlayTime >= animTotalTime)
	{
		animPlayTime = 0.0f;
	}

	//�}�E�X�̍��W�X�V
	pos = VAdd(pos, VGet((finalPos.x - firstPos.x) / runningSpeed, 0.0f, (finalPos.z - firstPos.z) / runningSpeed));

	//�}�E�X���o�����Ȃ��Ȃ�������W����ʊO�̍ŏI�n�_�Ɉړ�����
	if (!isAppearance)
	{
		pos = finalPos;
	}

	//�����蔻����W�X�V
	CollPos = VGet(pos.x, pos.y + MOUSE_FIX_POS_Y, pos.z + MOUSE_FIX_POS_Z);
	
	//���f���̍��W���Z�b�g
	MV1SetPosition(modelHandle, pos);
}

//���f���ƃA�j���[�V�����̍X�V
void Mouse::Draw()
{
	if (isAppearance)
	{
		//�A�j���[�V�����̍Đ����Ԃ��Z�b�g����
		MV1SetAttachAnimTime(modelHandle, AttachIndex, animPlayTime);
		MV1DrawModel(modelHandle);

		// �f�o�b�O�����蔻��.
		//DrawSphere3D(CollPos, hitRadius, 5, 0x00ffff, 0x00ffff, false);
	}
}

//���f���̉e�`��
void Mouse::DrawShadow(Field* field)
{
	MV1_COLL_RESULT_POLY_DIM HitResultDim;
	MV1_COLL_RESULT_POLY* HitResult;
	VERTEX3D Vertex[3];
	VECTOR SlideVec;

	// ���C�e�B���O�𖳌��ɂ���
	SetUseLighting(FALSE);

	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �e�N�X�`���A�h���X���[�h�� CLAMP �ɂ���( �e�N�X�`���̒[����͒[�̃h�b�g�����X���� )
	SetTextureAddressMode(DX_TEXADDRESS_CLAMP);

	// �v���C���[�̒����ɑ��݂���n�ʂ̃|���S�����擾
	HitResultDim = MV1CollCheck_Capsule(field->GetModelHandle(), -1, pos, VAdd(pos, VGet(0.0f, -MOUSE_SHADOW_HEIGHT, 0.0f)), MOUSE_SHADOW_SIZE);

	// ���_�f�[�^�ŕω��������������Z�b�g
	Vertex[0].dif = GetColorU8(255, 255, 255, 255);
	Vertex[0].spc = GetColorU8(0, 0, 0, 0);
	Vertex[0].su = 0.0f;
	Vertex[0].sv = 0.0f;
	Vertex[1] = Vertex[0];
	Vertex[2] = Vertex[0];

	// ���̒����ɑ��݂���|���S���̐������J��Ԃ�
	HitResult = HitResultDim.Dim;
	for (int i = 0; i < HitResultDim.HitNum; i++, HitResult++)
	{
		// �|���S���̍��W�͒n�ʃ|���S���̍��W
		Vertex[0].pos = HitResult->Position[0];
		Vertex[1].pos = HitResult->Position[1];
		Vertex[2].pos = HitResult->Position[2];

		// ������Ǝ����グ�ďd�Ȃ�Ȃ��悤�ɂ���
		SlideVec = VScale(HitResult->Normal, 0.5f);
		Vertex[0].pos = VAdd(Vertex[0].pos, SlideVec);
		Vertex[1].pos = VAdd(Vertex[1].pos, SlideVec);
		Vertex[2].pos = VAdd(Vertex[2].pos, SlideVec);

		// �|���S���̕s�����x��ݒ肷��
		Vertex[0].dif.a = 0;
		Vertex[1].dif.a = 0;
		Vertex[2].dif.a = 0;
		if (HitResult->Position[0].y > pos.y - MOUSE_SHADOW_HEIGHT)
		{
			Vertex[0].dif.a = static_cast<BYTE>(128 * (1.0f - static_cast<float>(fabs(HitResult->Position[0].y - pos.y) / MOUSE_SHADOW_HEIGHT)));
		}

		if (HitResult->Position[1].y > pos.y - MOUSE_SHADOW_HEIGHT)
		{
			Vertex[1].dif.a = static_cast<BYTE>(128 * (1.0f - static_cast<float>(fabs(HitResult->Position[1].y - pos.y) / MOUSE_SHADOW_HEIGHT)));
		}

		if (HitResult->Position[2].y > pos.y - MOUSE_SHADOW_HEIGHT)
		{
			Vertex[2].dif.a = static_cast<BYTE>(128 * (1.0f - static_cast<float>(fabs(HitResult->Position[2].y - pos.y) / MOUSE_SHADOW_HEIGHT)));
		}

		// �t�u�l�͒n�ʃ|���S���ƃv���C���[�̑��΍��W���犄��o��
		Vertex[0].u = (HitResult->Position[0].x - pos.x) / (MOUSE_SHADOW_SIZE * 2.0f) + 0.5f;
		Vertex[0].v = (HitResult->Position[0].z - pos.z) / (MOUSE_SHADOW_SIZE * 2.0f) + 0.5f;
		Vertex[1].u = (HitResult->Position[1].x - pos.x) / (MOUSE_SHADOW_SIZE * 2.0f) + 0.5f;
		Vertex[1].v = (HitResult->Position[1].z - pos.z) / (MOUSE_SHADOW_SIZE * 2.0f) + 0.5f;
		Vertex[2].u = (HitResult->Position[2].x - pos.x) / (MOUSE_SHADOW_SIZE * 2.0f) + 0.5f;
		Vertex[2].v = (HitResult->Position[2].z - pos.z) / (MOUSE_SHADOW_SIZE * 2.0f) + 0.5f;

		// �e�|���S����`��
		if (pos.x > -300.0f && pos.x < 320.0f && pos.z<15.0f && pos.z>-325.0f)
		{
			DrawPolygon3D(Vertex, 1, shadowHandle, TRUE);
		}
	}

	// ���o�����n�ʃ|���S�����̌�n��
	MV1CollResultPolyDimTerminate(HitResultDim);

	// ���C�e�B���O��L���ɂ���
	SetUseLighting(TRUE);

	// �y�o�b�t�@�𖳌��ɂ���
	SetUseZBuffer3D(FALSE);
}

//�}�E�X�̌������Z�b�g
void Mouse::SetRunningDirection()
{
	//�o�����W�ƍŏI�n�_����������擾
	appearanceSide = GetRand(static_cast<int>(AppearanceSide::RIGHT));
	switch (appearanceSide)
	{
	case static_cast<int>(AppearanceSide::TOP):
		firstPos = VGet(static_cast<float>(-250.0f + GetRand(WALL_UP_HOLE_NUM - 1) * 100.0f), GROUND_HEIGHT, 40.0f);
		finalPos = VGet(static_cast<float>(GetRand(MaxRight - MaxLeft) + MaxLeft), GROUND_HEIGHT, -375.0f);
		break;
	case static_cast<int>(AppearanceSide::UNDER):
		firstPos = VGet(static_cast<float>(GetRand(MaxRight - MaxLeft) + MaxLeft), GROUND_HEIGHT, -375.0f);
		finalPos = VGet(static_cast<float>(-250.0f + GetRand(WALL_UP_HOLE_NUM - 1) * 100.0f), GROUND_HEIGHT, 40.0f);
		break;
	case static_cast<int>(AppearanceSide::LEFT):
		firstPos = VGet(-325.0f, GROUND_HEIGHT, -50.0f - static_cast<float>(GetRand(WALL_SIDE_HOLE_NUM - 1) * 75.0f));
		finalPos = VGet(350.0f, GROUND_HEIGHT, -50.0f - static_cast<float>(GetRand(WALL_SIDE_HOLE_NUM - 1) * 75.0f));
		break;
	case static_cast<int>(AppearanceSide::RIGHT):
		firstPos = VGet(350.0f, GROUND_HEIGHT, -50.0f - static_cast<float>(GetRand(WALL_SIDE_HOLE_NUM - 1) * 75.0f));
		finalPos = VGet(-325.0f, GROUND_HEIGHT, -50.0f - static_cast<float>(GetRand(WALL_SIDE_HOLE_NUM - 1) * 75.0f));
		break;
	}

	//���f���̌������v�Z
	angle = -atan2f(finalPos.z - firstPos.z, finalPos.x - firstPos.x);

	//���f���̌������Z�b�g
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, angle + fixAngle, 0.0f));
}

//�}�E�X����ʓ��ɂ��邩�ǂ����̔���
bool Mouse::IsCheckMouseAppearance()
{
	//�ŏI�n�_����ɂ�����false�ɂ���
	switch (appearanceSide)
	{
	case static_cast<int>(AppearanceSide::TOP):
		if (pos.z < finalPos.z)
		{
			isAppearance = false;
		}
		break;
	case static_cast<int>(AppearanceSide::UNDER):
		if (pos.z > finalPos.z)
		{
			isAppearance = false;
		}
		break;
	case static_cast<int>(AppearanceSide::LEFT):
		if (pos.x > finalPos.x)
		{
			isAppearance = false;
		}
		break;
	case static_cast<int>(AppearanceSide::RIGHT):
		if (pos.x < finalPos.x)
		{
			isAppearance = false;
		}
		break;
	}

	return isAppearance;
}

//�}�E�X�̌��݂̍��W���擾
VECTOR Mouse::GetNowPosition()
{
	return pos;
}

//�A�̃e�N�X�`���p�X�擾
const char* Mouse::GetShadowImgPath()
{
	return "data/texture/Shadow.tga";
}
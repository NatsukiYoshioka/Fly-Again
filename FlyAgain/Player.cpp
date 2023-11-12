#include"DxLib.h"
#include"Field.h"
#include"Wrench.h"
#include"PadInput.h"
#include"ModelManager.h"
#include<cmath>
#include "Player.h"

//�ϐ��A���W�̏������ƃ��f���̎擾
Player::Player() :hitRadius(20.0f), 
jumpPower(jump), 
gravityPower(0.0f), 
liftPower(0.0f), 
nowXSpeed(0.0f), 
nowZSpeed(0.0f), 
Angle(0.0f), 
HP(5), 
point(0), 
crash(false),
crashRotation(0.0f),
nowFuel(maxFuel)
{
	//���f���̃��[�h
	modelHandle = MV1DuplicateModel(ModelManager::GetRobotModelHandle());

	//�e�e�N�X�`���̃��[�h
	shadowHandle = LoadGraph(GetShadowImgPath());

	//���W������
	pos = VGet(0.0f, 70.0f, -100.0f);
	CollPos = VGet(0.0f, 0.0f, 0.0f);
	MoveVec = VGet(0.0f, 0.0f, 0.0f);

	//���f���̊g�k
	MV1SetScale(modelHandle, VGet(0.2f, 0.2f, 0.2f));
}

//���f���̌㏈��
Player::~Player()
{
	MV1DeleteModel(modelHandle);
}

//���͏����ƍ��W�̍X�V
void Player::Update()
{
	//���͏���
	if (CheckHitKey(KEY_INPUT_W) || PadInput::GetPadInput().ThumbLY > 0)
	{
		UpdateSpeed(&nowZSpeed,maxSpeed);
		MoveVec = VAdd(MoveVec, VGet(0.0f, 0.0f, speed));
	}
	if (CheckHitKey(KEY_INPUT_S) || PadInput::GetPadInput().ThumbLY < 0)
	{
		UpdateSpeed(&nowZSpeed, -maxSpeed);
		MoveVec = VAdd(MoveVec, VGet(0.0f, 0.0f, -speed));
	}
	if (CheckHitKey(KEY_INPUT_A) || PadInput::GetPadInput().ThumbLX < 0)
	{
		UpdateSpeed(&nowXSpeed, -maxSpeed);
		MoveVec = VAdd(MoveVec, VGet(-speed, 0.0f, 0.0f));
	}
	if (CheckHitKey(KEY_INPUT_D) || PadInput::GetPadInput().ThumbLX > 0)
	{
		UpdateSpeed(&nowXSpeed, maxSpeed);
		MoveVec = VAdd(MoveVec, VGet(speed, 0.0f, 0.0f));
	}

	//�W�����v�{�^���Ńv���C���[�ɕ��͂�^����
	if (nowFuel > 0 && (CheckHitKey(KEY_INPUT_SPACE) || PadInput::GetPadInput().Buttons[12]))
	{
		nowFuel += fuelDecreaseSpeed;
		liftPower += lift;
		if (liftPower > maxLiftPower)
		{
			liftPower = maxLiftPower;
		}
		if (nowFuel <= 0)
		{
			nowFuel = 0;
		}
	}
	else
	{
		liftPower -= gravity;
		if (liftPower < 0.0f)
		{
			liftPower = 0.0f;
		}
		if (nowFuel >= maxFuel)
		{
			nowFuel = maxFuel;
		}
	}

	//���W���f
	pos = VAdd(pos, VGet(nowXSpeed, 0.0f, nowZSpeed));
	//�v���C���[�̍��W�C��
	FixPos();

	//��R����
	ResistanceProcess();

	//�v���C���[���W�̍X�V
	pos = VAdd(pos, VGet(0.0f, jumpPower - gravityPower + liftPower, 0.0f));

	//�v���C���[�̓����蔻����W�X�V
	CollPos = VGet(pos.x, pos.y + PLAYER_COLL_POS_Y, pos.z);
	
	//�v���C���[�̌������X�V
	UpdateAngle();

	//���f���̈ʒu���X�V
	MV1SetPosition(modelHandle, pos);
}

//�v���C���[�̓��������̍X�V
void Player::UpdateSpeed(float* shaft, const float maxSpeed)
{
	//���͂���Ă��Ȃ���Ԃł������𔭐�������
	if (maxSpeed < 0)
	{
		*shaft -= speed;
		if (*shaft < maxSpeed)
		{
			*shaft = maxSpeed;
		}
	}
	else
	{
		*shaft += speed;
		if (*shaft > maxSpeed)
		{
			*shaft = maxSpeed;
		}
	}
}

//��R����
void Player::ResistanceProcess()
{
	//��C��R����
	if (nowXSpeed > 0)
	{
		nowXSpeed -= airResistance;
	}
	else if (nowXSpeed < 0)
	{
		nowXSpeed += airResistance;
	}

	if (nowZSpeed > 0)
	{
		nowZSpeed -= airResistance;
	}
	else if (nowZSpeed < 0)
	{
		nowZSpeed += airResistance;
	}

	//�d�͏���
	gravityPower += gravity;
	if (gravityPower > maxGravityPower)
	{
		gravityPower = maxGravityPower;
	}
}

//�v���C���[���t�B�[���h�O�ɏo�Ȃ��悤�ɂ��鏈��
void Player::FixPos()
{
	if (pos.z > PLAYER_Z_MAX)
	{
		pos.z = PLAYER_Z_MAX;
	}
	if (pos.z < PLAYER_Z_MIN)
	{
		pos.z = PLAYER_Z_MIN;
	}
	if (pos.x < PLAYER_X_MIN)
	{
		pos.x = PLAYER_X_MIN;
	}
	if (pos.x > PLAYER_X_MAX)
	{
		pos.x = PLAYER_X_MAX;
	}
	if (pos.y > PLAYER_Y_MAX)
	{
		pos.y = PLAYER_Y_MAX;
	}
}

//�v���C���[�̌������C��
void Player::UpdateAngle()
{
	// �v���C���[�̈ړ������Ƀ��f���̕������߂Â���
	float TargetAngle;			// �ڕW�p�x
	float difference;			// �ڕW�p�x�ƌ��݂̊p�x�Ƃ̍�

	// �ړ��x�N�g���𐳋K���������̂��v���C���[�������ׂ������Ƃ��ĕۑ�
	TargetMoveDirection = VNorm(MoveVec);

	// �ڕW�̕����x�N�g������p�x�l���Z�o����
	TargetAngle = static_cast<float>(atan2(TargetMoveDirection.x, TargetMoveDirection.z));

	// �ڕW�̊p�x�ƌ��݂̊p�x�Ƃ̍�������o��
	// �ŏ��͒P���Ɉ����Z
	difference = TargetAngle - Angle;

	// ����������炠������̍����P�W�O�x�ȏ�ɂȂ邱�Ƃ͖����̂�
		// ���̒l���P�W�O�x�ȏ�ɂȂ��Ă�����C������
	if (difference < -DX_PI_F)
	{
		difference += DX_TWO_PI_F;
	}
	else if (difference > DX_PI_F)
	{
		difference -= DX_TWO_PI_F;
	}

	// �p�x�̍����O�ɋ߂Â���
	if (difference > 0.0f)
	{
		// �����v���X�̏ꍇ�͈���
		difference -= PLAYER_ANGLE_SPEED;
		if (difference < 0.0f)
		{
			difference = 0.0f;
		}
	}
	else
	{
		// �����}�C�i�X�̏ꍇ�͑���
		difference += PLAYER_ANGLE_SPEED;
		if (difference > 0.0f)
		{
			difference = 0.0f;
		}
	}

	// ���f���̊p�x���X�V
	Angle = TargetAngle - difference;

	//�N���b�V�����̏���
	if (HP <= 0 || crash && jumpPower - gravityPower > 0)
	{
		crashRotation += PLAYER_CRASH_ROTATION_SPEED;
		if (crashRotation >= 360.0f)
		{
			crashRotation = 0;
		}
	}
	else
	{
		crash = false;
		crashRotation = 0.0f;
	}

	MV1SetRotationXYZ(modelHandle, VGet(crashRotation * DX_PI_F / 180.0f, Angle + DX_PI_F, crashRotation * DX_PI_F / 180.0f));
}

//���f���̕`��
void Player::Draw()
{
	MV1DrawModel(modelHandle);

	// �f�o�b�O�����蔻��.
	//DrawSphere3D(CollPos, hitRadius, 5, 0x00ffff, 0x00ffff, false);
}

//�n�ʂɓ����������̏���
void Player::OnHitGround()
{
	//�N���b�V���A�j���[�V������L���ɂ���
	crash = true;

	//HP��1���炵�Ē��ˏグ��
	HP--;
	gravityPower = 0.0f;
	jumpPower = jump;
}

//�n�ʈȊO�̃��f���ɓ��������ꍇ�̏���
void Player::OnHitObstruct(bool hitFlag)
{
	if (hitFlag)
	{
		//�v���C���[���o�E���h������
		gravityPower = 0.0f;
		jumpPower = jump;
	}
}

//�|�C���g�t�^�֐�
bool Player::GivePoint(int randNum)
{
	//�����������f���Ƀ����`������΃|�C���g�t�^
	if (randNum == WRENCH_APPEARANCE_NUM)
	{
		point++;
		return true;
	}
	return false;
}

//�v���C���[�̉e�̕`��
void Player::DrawShadow(Field* field)
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
	HitResultDim = MV1CollCheck_Capsule(field->GetModelHandle(), -1, pos, VAdd(pos, VGet(0.0f, -PLAYER_SHADOW_HEIGHT, 0.0f)), PLAYER_SHADOW_SIZE);

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
		if (HitResult->Position[0].y > pos.y - PLAYER_SHADOW_HEIGHT)
		{
			Vertex[0].dif.a = static_cast<BYTE>(128 * (1.0f - static_cast<float>(fabs(HitResult->Position[0].y - pos.y) / PLAYER_SHADOW_HEIGHT)));
		}

		if (HitResult->Position[1].y > pos.y - PLAYER_SHADOW_HEIGHT)
		{
			Vertex[1].dif.a = static_cast<BYTE>(128 * (1.0f - static_cast<float>(fabs(HitResult->Position[1].y - pos.y) / PLAYER_SHADOW_HEIGHT)));
		}

		if (HitResult->Position[2].y > pos.y - PLAYER_SHADOW_HEIGHT)
		{
			Vertex[2].dif.a = static_cast<BYTE>(128 * (1.0f - static_cast<float>(fabs(HitResult->Position[2].y - pos.y) / PLAYER_SHADOW_HEIGHT)));
		}

		// �t�u�l�͒n�ʃ|���S���ƃv���C���[�̑��΍��W���犄��o��
		Vertex[0].u = (HitResult->Position[0].x - pos.x) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
		Vertex[0].v = (HitResult->Position[0].z - pos.z) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
		Vertex[1].u = (HitResult->Position[1].x - pos.x) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
		Vertex[1].v = (HitResult->Position[1].z - pos.z) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
		Vertex[2].u = (HitResult->Position[2].x - pos.x) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
		Vertex[2].v = (HitResult->Position[2].z - pos.z) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;

		// �e�|���S����`��
		DrawPolygon3D(Vertex, 1, shadowHandle, TRUE);
	}

	// ���o�����n�ʃ|���S�����̌�n��
	MV1CollResultPolyDimTerminate(HitResultDim);

	// ���C�e�B���O��L���ɂ���
	SetUseLighting(TRUE);

	// �y�o�b�t�@�𖳌��ɂ���
	SetUseZBuffer3D(FALSE);
}

//�A�̃e�N�X�`���p�X�擾
const char* Player::GetShadowImgPath()
{
	return "data/texture/Shadow.tga";
}

//�R���⋋
void Player::FuelSupply()
{
	nowFuel = maxFuel;
}
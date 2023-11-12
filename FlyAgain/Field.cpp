#include"ModelManager.h"
#include<DxLib.h>
#include "Field.h"

const VECTOR Field::initialPos = VGet(-140.0f, 100.0f, 100.0f);
const VECTOR Field::fieldAngle = VGet(0.0f, -180.0f * DX_PI_F / 180.0f, 0.0f);
const VECTOR Field::modelScale = VGet(100.0f, 100.0f, 100.0f);

//�t�B�[���h���̏�����
Field::Field()
{
	//���f���̃��[�h
	modelHandle = MV1DuplicateModel(ModelManager::GetFieldModelHandle());

	//���W������
	pos = initialPos;

	//���f����]���ݒ�
	MV1SetRotationXYZ(modelHandle, fieldAngle);

	//���f���̊g�k
	MV1SetScale(modelHandle, modelScale);

	//���f���̍��W�̐ݒ�
	MV1SetPosition(modelHandle, pos);

	//�R���W�������̍\�z
	MV1SetupCollInfo(modelHandle, frameIndex, spatialPartitionNum, spatialPartitionNum, spatialPartitionNum);
}

//�t�B�[���h���f���̌㏈��
Field::~Field()
{
	MV1DeleteModel(modelHandle);
}

//�t�B�[���h�̕`��
void Field::Draw()
{
	MV1DrawModel(modelHandle);
}
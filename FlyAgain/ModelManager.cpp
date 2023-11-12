#include"DxLib.h"
#include "ModelManager.h"

int ModelManager::robotModelHandle;
int ModelManager::fieldModelHandle;
int ModelManager::mouseModelHandle;
int ModelManager::cheeseModelHandle;
int ModelManager::wrenchModelHandle;

//���f���̃��[�h
ModelManager::ModelManager()
{
    robotModelHandle = MV1LoadModel(GetRobotModelPath());
    fieldModelHandle = MV1LoadModel(GetFiledModelPath());
    mouseModelHandle = MV1LoadModel(GetMouseModelPath());
    cheeseModelHandle = MV1LoadModel(GetCheeseModelPath());
    wrenchModelHandle = MV1LoadModel(GetWrenchModelPath());
}

//���f���̌㏈��
ModelManager::~ModelManager()
{
    MV1DeleteModel(robotModelHandle);
    MV1DeleteModel(fieldModelHandle);
    MV1DeleteModel(mouseModelHandle);
    MV1DeleteModel(cheeseModelHandle);
    MV1DeleteModel(wrenchModelHandle);
}

//���{�b�g���f���̃p�X�擾
const char* ModelManager::GetRobotModelPath()
{
    return "data/model/robot.mv1";
}

//�t�B�[���h���f���̃p�X�擾
const char* ModelManager::GetFiledModelPath()
{
    return "data/model/room.pmx";
}

//�}�E�X���f���̃p�X�擾
const char* ModelManager::GetMouseModelPath()
{
    return "data/model/mouse.mv1";
}

//�`�[�Y���f���̃p�X�擾
const char* ModelManager::GetCheeseModelPath()
{
    return "data/model/cheese.mv1";
}

//�����`���f���̃p�X�擾
const char* ModelManager::GetWrenchModelPath()
{
    return "data/model/wrench.mv1";
}
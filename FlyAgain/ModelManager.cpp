#include"DxLib.h"
#include "ModelManager.h"

int ModelManager::robotModelHandle;
int ModelManager::fieldModelHandle;
int ModelManager::mouseModelHandle;
int ModelManager::cheeseModelHandle;
int ModelManager::wrenchModelHandle;

//モデルのロード
ModelManager::ModelManager()
{
    robotModelHandle = MV1LoadModel(GetRobotModelPath());
    fieldModelHandle = MV1LoadModel(GetFiledModelPath());
    mouseModelHandle = MV1LoadModel(GetMouseModelPath());
    cheeseModelHandle = MV1LoadModel(GetCheeseModelPath());
    wrenchModelHandle = MV1LoadModel(GetWrenchModelPath());
}

//モデルの後処理
ModelManager::~ModelManager()
{
    MV1DeleteModel(robotModelHandle);
    MV1DeleteModel(fieldModelHandle);
    MV1DeleteModel(mouseModelHandle);
    MV1DeleteModel(cheeseModelHandle);
    MV1DeleteModel(wrenchModelHandle);
}

//ロボットモデルのパス取得
const char* ModelManager::GetRobotModelPath()
{
    return "data/model/robot.mv1";
}

//フィールドモデルのパス取得
const char* ModelManager::GetFiledModelPath()
{
    return "data/model/room.pmx";
}

//マウスモデルのパス取得
const char* ModelManager::GetMouseModelPath()
{
    return "data/model/mouse.mv1";
}

//チーズモデルのパス取得
const char* ModelManager::GetCheeseModelPath()
{
    return "data/model/cheese.mv1";
}

//レンチモデルのパス取得
const char* ModelManager::GetWrenchModelPath()
{
    return "data/model/wrench.mv1";
}
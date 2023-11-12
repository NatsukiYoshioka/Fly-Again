#include"Mouse.h"
#include"Cheese.h"
#include"Wrench.h"
#include"ModelManager.h"
#include "ObstructManager.h"

//各モデルの初期化
ObstructManager::ObstructManager()
{
	//モデルのロード
	mouseModelHandle = MV1DuplicateModel(ModelManager::GetMouseModelHandle());
	cheeseModelHandle = MV1DuplicateModel(ModelManager::GetCheeseModelHandle());
	wrenchModelHandle = MV1DuplicateModel(ModelManager::GetWrenchModelHandle());

	//ネズミ初期追加
	InitMouse();

	//チーズ初期追加
	InitCheese();

	//レンチ初期追加
	InitWrench();

	//レンチが出現し始める時間の最初の時間を取得
	startTime = GetNowCount();
}

//各モデルの後処理
ObstructManager::~ObstructManager()
{
	MV1DeleteModel(mouseModelHandle);
	MV1DeleteModel(cheeseModelHandle);
	MV1DeleteModel(wrenchModelHandle);
}

//各モデルの更新
void ObstructManager::Update()
{
	UpdateMouse();
	UpdateCheese();
	UpdateWrench();
}

//各モデルの描画
void ObstructManager::Draw(Field* field)
{
	DrawMouse(field);
	DrawCheese();
	DrawWrench();
}

//全マウスの初期処理
void ObstructManager::InitMouse()
{
	for (int i = 0; i < MOUSE_NUM; i++)
	{
		//マウスの初期追加
		mouse.push_back(new Mouse(mouseModelHandle));
	}
	for (mouse_itr = mouse.begin(); mouse_itr != mouse.end(); mouse_itr++)
	{
		//マウス1体の初期化
		(*mouse_itr)->Initialize(mouseModelHandle);
	}
}

//全チーズの初期処理
void ObstructManager::InitCheese()
{
	for (int i = 0; i < MOUSE_NUM; i++)
	{
		//チーズの初期追加
		cheese.push_back(new Cheese(cheeseModelHandle));
	}
}

//全レンチの初期処理
void ObstructManager::InitWrench()
{
	for (int i = 0; i < MOUSE_NUM; i++)
	{
		//レンチの初期追加
		wrench.push_back(new Wrench(wrenchModelHandle));
	}
}

//全マウスの更新処理
void ObstructManager::UpdateMouse()
{
	for (mouse_itr = mouse.begin(); mouse_itr != mouse.end(); mouse_itr++)
	{
		//各マウスの更新
		(*mouse_itr)->Update();
	}
}

//全チーズの更新処理
void ObstructManager::UpdateCheese()
{
	mouse_itr = mouse.begin();
	for (cheese_itr = cheese.begin(); cheese_itr != cheese.end(); cheese_itr++)
	{
		//各チーズの更新
		(*cheese_itr)->Update((*mouse_itr)->GetNowPosition());
		mouse_itr++;
	}
}

//全レンチの更新処理
void ObstructManager::UpdateWrench()
{
	cheese_itr = cheese.begin();
	for (wrench_itr = wrench.begin(); wrench_itr != wrench.end(); wrench_itr++)
	{
		//各レンチの更新
		(*wrench_itr)->Update((*cheese_itr)->GetPos());
		cheese_itr++;
	}
}

//全マウス描画
void ObstructManager::DrawMouse(Field* field)
{
	cheese_itr = cheese.begin();
	wrench_itr = wrench.begin();
	for (mouse_itr = mouse.begin(); mouse_itr != mouse.end(); mouse_itr++)
	{
		//各マウスの描画
		(*mouse_itr)->Draw();
		(*mouse_itr)->DrawShadow(field);

		//マウスが目標地点に到達していたら初期化する
		if (!(*mouse_itr)->IsCheckMouseAppearance())
		{
			(*mouse_itr)->Initialize(mouseModelHandle);
			(*cheese_itr)->InitFlag();
			(*wrench_itr)->InitAppearance(startTime);
		}
		cheese_itr++;
		wrench_itr++;
	}
}

//全チーズ描画
void ObstructManager::DrawCheese()
{
	for (cheese_itr = cheese.begin(); cheese_itr != cheese.end(); cheese_itr++)
	{
		//各チーズの描画
		(*cheese_itr)->Draw();
	}
}

//全レンチ描画
void ObstructManager::DrawWrench()
{
	cheese_itr = cheese.begin();
	for (wrench_itr = wrench.begin(); wrench_itr != wrench.end(); wrench_itr++)
	{
		//出現していれば描画する
		if ((*wrench_itr)->GetIsAppearance())
		{
			(*wrench_itr)->Draw();
			startTime = GetNowCount();
		}
		cheese_itr++;
	}
}

//マウスのクラスを1つ取得
Mouse* ObstructManager::GetMouse(int index)
{
	mouse_itr = mouse.begin();
	for (int i = 0; i < index; i++)
	{
		mouse_itr++;
	}
	return (*mouse_itr);
}

//チーズのクラスを1つ取得
Cheese* ObstructManager::GetCheese(int index)
{
	cheese_itr = cheese.begin();
	for (int i = 0; i < index; i++)
	{
		cheese_itr++;
	}
	return (*cheese_itr);
}

//レンチのクラスを1つ取得
Wrench* ObstructManager::GetWrench(int index)
{
	wrench_itr = wrench.begin();
	for (int i = 0; i < index; i++)
	{
		wrench_itr++;
	}
	return (*wrench_itr);
}
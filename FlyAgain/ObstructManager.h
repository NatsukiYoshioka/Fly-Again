#pragma once
#include<DxLib.h>
#include<list>

#define MOUSE_NUM				5			//マウスの最大出現数

class Mouse;
class Cheese;
class Wrench;
class Field;

using namespace std;

/// <summary>
/// プレイヤー以外のモデルを制御するクラス
/// </summary>
class ObstructManager
{
public:
	/// <summary>
	/// 各モデルの初期化
	/// </summary>
	ObstructManager();

	/// <summary>
	/// 各モデルの後処理
	/// </summary>
	~ObstructManager();

	/// <summary>
	/// 各モデルの更新
	/// </summary>
	void Update();

	/// <summary>
	/// 各モデルの描画
	/// </summary>
	/// <param name="field">フィールドを管理するクラス</param>
	void Draw(Field* field);

	/// <summary>
	/// 全マウスの初期処理
	/// </summary>
	void InitMouse();

	/// <summary>
	/// 全チーズの初期処理
	/// </summary>
	void InitCheese();

	/// <summary>
	/// 全レンチの初期処理
	/// </summary>
	void InitWrench();

	/// <summary>
	/// 全マウスの更新処理
	/// </summary>
	void UpdateMouse();

	/// <summary>
	/// 全チーズの更新処理
	/// </summary>
	void UpdateCheese();

	/// <summary>
	/// 全レンチの更新処理
	/// </summary>
	void UpdateWrench();

	/// <summary>
	/// 全マウス描画
	/// </summary>
	/// <param name="field">フィールドを管理するクラス</param>
	void DrawMouse(Field* field);

	/// <summary>
	/// 全チーズ描画
	/// </summary>
	void DrawCheese();

	/// <summary>
	/// 全レンチ描画
	/// </summary>
	void DrawWrench();

	/// <summary>
	/// マウスのクラスを1つ取得
	/// </summary>
	/// <param name="index">マウスクラスを1つ指定する変数</param>
	/// <returns>マウスのクラス</returns>
	Mouse* GetMouse(int index);

	/// <summary>
	/// チーズのクラスを1つ取得
	/// </summary>
	/// <param name="index">チーズクラスを1つ指定する変数</param>
	/// <returns>チーズのクラス</returns>
	Cheese* GetCheese(int index);

	/// <summary>
	/// レンチのクラスを1つ取得
	/// </summary>
	/// <param name="index">レンチクラスを1つ指定する変数</param>
	/// <returns>レンチのクラス</returns>
	Wrench* GetWrench(int index);
private:
	list<Mouse*> mouse;					//Mouseクラスのlist
	list<Mouse*>::iterator mouse_itr;	//Mouseクラスlistのイテレータ
	int mouseModelHandle;				//マウスのモデルハンドル

	list<Cheese*> cheese;				//Cheeseクラスのlist
	list<Cheese*>::iterator cheese_itr;	//Cheeseクラスlistのイテレータ
	int cheeseModelHandle;				//チーズのモデルハンドル

	list<Wrench*> wrench;				//Wrenchクラスのlist
	list<Wrench*>::iterator wrench_itr;	//Wrenchクラスlistイテレータ
	int wrenchModelHandle;				//レンチのモデルハンドル
	int isAppearance;					//モデルが出現するかどうかを確率で操作する
	int startTime;						//レンチの出現するまでのカウント
};


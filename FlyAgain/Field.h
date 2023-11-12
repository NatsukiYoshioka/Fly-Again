#pragma once
#include<DxLib.h>

/// <summary>
/// フィールドモデル管理クラス
/// </summary>
class Field
{
public:
	/// <summary>
	/// フィールド情報の初期化
	/// </summary>
	Field();

	/// <summary>
	/// フィールドモデルの後処理
	/// </summary>
	~Field();

	/// <summary>
	/// フィールドモデルの初期化
	/// </summary>
	void Draw();

	/// <summary>
	/// フィールドモデルハンドルの取得
	/// </summary>
	/// <returns>フィールドのモデルハンドル</returns>
	int GetModelHandle() { return modelHandle; }
private:
	VECTOR pos;			//フィールドモデルの座標

	int modelHandle;	//フィールドのモデルハンドル

	static const VECTOR initialPos;					//フィールドの座標の初期化用定数
	static const VECTOR fieldAngle;					//フィールドの初期角度
	static const VECTOR modelScale;					//フィールドの拡縮度
	static constexpr int frameIndex = -1;			//モデル全体のポリゴンをコリジョン情報
	static constexpr int spatialPartitionNum = 10;	//コリジョン情報の空間分割数
};


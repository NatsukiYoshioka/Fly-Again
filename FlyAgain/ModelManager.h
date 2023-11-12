#pragma once

/// <summary>
/// 3Dモデル管理クラス
/// </summary>
class ModelManager
{
public:
    /// <summary>
    /// モデルのロード
    /// </summary>
    ModelManager();

    /// <summary>
    /// モデルの後処理
    /// </summary>
    ~ModelManager();

    /// <summary>
    /// ロボットモデルハンドルを取得
    /// </summary>
    /// <returns>ロボットモデルハンドル</returns>
    static int GetRobotModelHandle() { return robotModelHandle; }

    /// <summary>
    /// フィールドモデルハンドルを取得
    /// </summary>
    /// <returns>フィールドモデルハンドル</returns>
    static int GetFieldModelHandle() { return fieldModelHandle; }

    /// <summary>
    /// マウスモデルハンドルを取得
    /// </summary>
    /// <returns>マウスモデルハンドル</returns>
    static int GetMouseModelHandle() { return mouseModelHandle; }

    /// <summary>
    /// チーズモデルハンドルを取得
    /// </summary>
    /// <returns>チーズモデルハンドル</returns>
    static int GetCheeseModelHandle() { return cheeseModelHandle; }

    /// <summary>
    /// レンチモデルハンドルを取得
    /// </summary>
    /// <returns>レンチモデルハンドル</returns>
    static int GetWrenchModelHandle() { return wrenchModelHandle; }

    /// <summary>
    /// ロボットモデルのパス取得
    /// </summary>
    /// <returns>ロボットモデルのパス</returns>
    const char* GetRobotModelPath();

    /// <summary>
    /// フィールドモデルのパス取得
    /// </summary>
    /// <returns>フィールドモデルのパス</returns>
    const char* GetFiledModelPath();

    /// <summary>
    /// マウスモデルのパス取得
    /// </summary>
    /// <returns>マウスモデルのパス</returns>
    const char* GetMouseModelPath();

    /// <summary>
    /// チーズモデルのパス取得
    /// </summary>
    /// <returns>チーズモデルのパス</returns>
    const char* GetCheeseModelPath();

    /// <summary>
    /// レンチモデルのパス取得
    /// </summary>
    /// <returns>レンチモデルのパス</returns>
    const char* GetWrenchModelPath();
private:
    static int robotModelHandle;        //ロボットモデルハンドル
    static int fieldModelHandle;        //フィールドモデルハンドル
    static int mouseModelHandle;        //マウスモデルハンドル
    static int cheeseModelHandle;       //チーズモデルハンドル
    static int wrenchModelHandle;       //レンチモデルハンドル
};


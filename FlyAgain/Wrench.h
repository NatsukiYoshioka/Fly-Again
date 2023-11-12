#pragma once

#define WRENCH_FIX_POS_Y        15.0f       //レンチのY座標調整量
#define WRENCH_PROBABILITY		4			//レンチが出現する確率の最大値
#define WRENCH_APPEARANCE_NUM   1           //レンチが出る乱数の数値

class Wrench
{
public:
    /// <summary>
    /// モデルの取得と座標の初期化
    /// </summary>
    /// <param name="modelHandle">レンチのモデルハンドル</param>
    Wrench(int modelHandle);

    /// <summary>
    /// モデルの後処理
    /// </summary>
    ~Wrench();

    /// <summary>
    /// 出現の初期化
    /// </summary>
    /// <param name="startTime">レンチの出現するまでのカウント</param>
    void InitAppearance(int startTime);

    /// <summary>
    /// レンチの位置更新
    /// </summary>
    /// <param name="cheesePos">チーズの座標</param>
    void Update(VECTOR cheesePos);

    /// <summary>
    /// レンチの描画
    /// </summary>
    void Draw();

    /// <summary>
    /// レンチモデルの回転処理
    /// </summary>
    void RotateWrench();

    /// <summary>
    /// プレイヤーに取得されたときの処理
    /// </summary>
    void OnHitPlayer();

    /// <summary>
    /// レンチの座標取得
    /// </summary>
    /// <returns>レンチの座標</returns>
    VECTOR GetPos() { return pos; }

    /// <summary>
    /// レンチが出現しているか取得
    /// </summary>
    /// <returns>レンチが出現しているかどうか</returns>
    bool GetIsAppearance() { return isAppearance; }
private:
    VECTOR pos;                                         //レンチの座標
    int modelHandle;                                    //レンチのモデルハンドル

    static constexpr float rotationSpeed = 1.0f;        //レンチの回転スピード
    static constexpr float maxRpm = 360.0f;             //レンチの最大回転数
    float rpm;                                          //レンチの回転数

    bool isAppearance;                                  //レンチ出現用変数
};


#pragma once
#include<DxLib.h>

#define CHEESE_FIX_POS_Y    26.0f       //チーズモデルの位置調整量
#define CHEESE_PROBABILITY  2           //チーズが出現する確率の最大値
#define CHEESE_APPEARANCE_NUM   1       //チーズが出現する数

/// <summary>
/// チーズ1つを制御するクラス
/// </summary>
class Cheese
{
public:
    /// <summary>
    /// チーズの3Dモデルと座標、スケールを設定する
    /// </summary>
    /// <param name="modelHandle">チーズの3Dモデルハンドル</param>
    Cheese(int modelHandle);

    /// <summary>
    /// モデルハンドルの後処理
    /// </summary>
    ~Cheese();

    /// <summary>
    /// チーズを出現させるフラグをランダムで初期化する
    /// </summary>
    void InitFlag();

    /// <summary>
    /// チーズモデルの座標更新
    /// </summary>
    /// <param name="mousePos">マウスの座標</param>
    void Update(VECTOR mousePos);

    /// <summary>
    /// チーズの描画
    /// </summary>
    void Draw();

    /// <summary>
    /// プレイヤーに当たっていたら当たり判定と描画のフラグをfalseにする
    /// </summary>
    /// <param name="hitFlag">プレイヤーに当たっているかどうか</param>
    void OnHitPlayer(bool hitFlag);

    /// <summary>
    /// チーズが存在しているか取得する
    /// </summary>
    /// <returns>チーズの存在を確認する変数</returns>
    bool GetFlag() { return isAppearance; }

    /// <summary>
    /// チーズの座標を取得
    /// </summary>
    /// <returns>チーズの座標</returns>
    VECTOR GetPos() { return pos; }

    /// <summary>
    /// チーズの当たり判定の球の半径を取得
    /// </summary>
    /// <returns>チーズの当たり判定の球の半径</returns>
    float GetHitRadius() { return hitRadius; }

private:
    VECTOR pos;                                  //チーズの座標
    float hitRadius;                             //当たり判定の球の半径

    int modelHandle;                             //モデルハンドル

    int appearanceRandNum;                       //出現するかどうかを乱数で取得する変数
    bool isAppearance;                           //出現しているかのフラグ

    static constexpr float initialHitRadius = 12.5f;        //当たり判定の球の半径の初期化用定数
    static constexpr int initialAppearanceRandNum = 0;      //出現するかどうかを乱数で取得する変数の初期化用定数
    static const VECTOR initialPos;                         //チーズの座標の初期化用定数
    static const VECTOR modelScale;                         //モデルの拡縮度
};


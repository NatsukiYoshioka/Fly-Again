#pragma once

/// <summary>
/// フォント管理クラス
/// </summary>
class Font
{
public:
    /// <summary>
    /// フォントのロードと変更
    /// </summary>
    Font();

    /// <summary>
    /// フォントの後処理
    /// </summary>
    ~Font();
private:
    LPCSTR defaultFontPath;        //デフォルトのフォントのパス
    LPCSTR titleFontPath;          //タイトルのフォントのパス
    LPCSTR descriptionFontPath;    //ゲーム説明用フォントのパス
};


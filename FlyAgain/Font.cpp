#include"DxLib.h"
#include "Font.h"

//�t�H���g�̃��[�h�ƕύX
Font::Font()
{
    defaultFontPath = "data/font/ARCADECLASSIC.TTF";
    titleFontPath = "data/font/night.ttf";
    descriptionFontPath = "data/font/japan.ttf";

    AddFontResourceEx(defaultFontPath, FR_PRIVATE, NULL);
    AddFontResourceEx(titleFontPath, FR_PRIVATE, NULL);
    AddFontResourceEx(descriptionFontPath, FR_PRIVATE, NULL);

    ChangeFont("ArcadeClassic", DX_CHARSET_DEFAULT);
}

//�t�H���g�̌㏈��
Font::~Font()
{
    RemoveFontResourceEx(defaultFontPath, FR_PRIVATE, NULL);
    RemoveFontResourceEx(titleFontPath, FR_PRIVATE, NULL);
    RemoveFontResourceEx(descriptionFontPath, FR_PRIVATE, NULL);
}
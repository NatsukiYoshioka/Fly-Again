#pragma once

/// <summary>
/// �t�H���g�Ǘ��N���X
/// </summary>
class Font
{
public:
    /// <summary>
    /// �t�H���g�̃��[�h�ƕύX
    /// </summary>
    Font();

    /// <summary>
    /// �t�H���g�̌㏈��
    /// </summary>
    ~Font();
private:
    LPCSTR defaultFontPath;        //�f�t�H���g�̃t�H���g�̃p�X
    LPCSTR titleFontPath;          //�^�C�g���̃t�H���g�̃p�X
    LPCSTR descriptionFontPath;    //�Q�[�������p�t�H���g�̃p�X
};


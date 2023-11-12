#pragma once

/// <summary>
/// 3D���f���Ǘ��N���X
/// </summary>
class ModelManager
{
public:
    /// <summary>
    /// ���f���̃��[�h
    /// </summary>
    ModelManager();

    /// <summary>
    /// ���f���̌㏈��
    /// </summary>
    ~ModelManager();

    /// <summary>
    /// ���{�b�g���f���n���h�����擾
    /// </summary>
    /// <returns>���{�b�g���f���n���h��</returns>
    static int GetRobotModelHandle() { return robotModelHandle; }

    /// <summary>
    /// �t�B�[���h���f���n���h�����擾
    /// </summary>
    /// <returns>�t�B�[���h���f���n���h��</returns>
    static int GetFieldModelHandle() { return fieldModelHandle; }

    /// <summary>
    /// �}�E�X���f���n���h�����擾
    /// </summary>
    /// <returns>�}�E�X���f���n���h��</returns>
    static int GetMouseModelHandle() { return mouseModelHandle; }

    /// <summary>
    /// �`�[�Y���f���n���h�����擾
    /// </summary>
    /// <returns>�`�[�Y���f���n���h��</returns>
    static int GetCheeseModelHandle() { return cheeseModelHandle; }

    /// <summary>
    /// �����`���f���n���h�����擾
    /// </summary>
    /// <returns>�����`���f���n���h��</returns>
    static int GetWrenchModelHandle() { return wrenchModelHandle; }

    /// <summary>
    /// ���{�b�g���f���̃p�X�擾
    /// </summary>
    /// <returns>���{�b�g���f���̃p�X</returns>
    const char* GetRobotModelPath();

    /// <summary>
    /// �t�B�[���h���f���̃p�X�擾
    /// </summary>
    /// <returns>�t�B�[���h���f���̃p�X</returns>
    const char* GetFiledModelPath();

    /// <summary>
    /// �}�E�X���f���̃p�X�擾
    /// </summary>
    /// <returns>�}�E�X���f���̃p�X</returns>
    const char* GetMouseModelPath();

    /// <summary>
    /// �`�[�Y���f���̃p�X�擾
    /// </summary>
    /// <returns>�`�[�Y���f���̃p�X</returns>
    const char* GetCheeseModelPath();

    /// <summary>
    /// �����`���f���̃p�X�擾
    /// </summary>
    /// <returns>�����`���f���̃p�X</returns>
    const char* GetWrenchModelPath();
private:
    static int robotModelHandle;        //���{�b�g���f���n���h��
    static int fieldModelHandle;        //�t�B�[���h���f���n���h��
    static int mouseModelHandle;        //�}�E�X���f���n���h��
    static int cheeseModelHandle;       //�`�[�Y���f���n���h��
    static int wrenchModelHandle;       //�����`���f���n���h��
};


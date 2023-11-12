#pragma once
#include<DxLib.h>

#define CHEESE_FIX_POS_Y    26.0f       //�`�[�Y���f���̈ʒu������
#define CHEESE_PROBABILITY  2           //�`�[�Y���o������m���̍ő�l
#define CHEESE_APPEARANCE_NUM   1       //�`�[�Y���o�����鐔

/// <summary>
/// �`�[�Y1�𐧌䂷��N���X
/// </summary>
class Cheese
{
public:
    /// <summary>
    /// �`�[�Y��3D���f���ƍ��W�A�X�P�[����ݒ肷��
    /// </summary>
    /// <param name="modelHandle">�`�[�Y��3D���f���n���h��</param>
    Cheese(int modelHandle);

    /// <summary>
    /// ���f���n���h���̌㏈��
    /// </summary>
    ~Cheese();

    /// <summary>
    /// �`�[�Y���o��������t���O�������_���ŏ���������
    /// </summary>
    void InitFlag();

    /// <summary>
    /// �`�[�Y���f���̍��W�X�V
    /// </summary>
    /// <param name="mousePos">�}�E�X�̍��W</param>
    void Update(VECTOR mousePos);

    /// <summary>
    /// �`�[�Y�̕`��
    /// </summary>
    void Draw();

    /// <summary>
    /// �v���C���[�ɓ������Ă����瓖���蔻��ƕ`��̃t���O��false�ɂ���
    /// </summary>
    /// <param name="hitFlag">�v���C���[�ɓ������Ă��邩�ǂ���</param>
    void OnHitPlayer(bool hitFlag);

    /// <summary>
    /// �`�[�Y�����݂��Ă��邩�擾����
    /// </summary>
    /// <returns>�`�[�Y�̑��݂��m�F����ϐ�</returns>
    bool GetFlag() { return isAppearance; }

    /// <summary>
    /// �`�[�Y�̍��W���擾
    /// </summary>
    /// <returns>�`�[�Y�̍��W</returns>
    VECTOR GetPos() { return pos; }

    /// <summary>
    /// �`�[�Y�̓����蔻��̋��̔��a���擾
    /// </summary>
    /// <returns>�`�[�Y�̓����蔻��̋��̔��a</returns>
    float GetHitRadius() { return hitRadius; }

private:
    VECTOR pos;                                  //�`�[�Y�̍��W
    float hitRadius;                             //�����蔻��̋��̔��a

    int modelHandle;                             //���f���n���h��

    int appearanceRandNum;                       //�o�����邩�ǂ����𗐐��Ŏ擾����ϐ�
    bool isAppearance;                           //�o�����Ă��邩�̃t���O

    static constexpr float initialHitRadius = 12.5f;        //�����蔻��̋��̔��a�̏������p�萔
    static constexpr int initialAppearanceRandNum = 0;      //�o�����邩�ǂ����𗐐��Ŏ擾����ϐ��̏������p�萔
    static const VECTOR initialPos;                         //�`�[�Y�̍��W�̏������p�萔
    static const VECTOR modelScale;                         //���f���̊g�k�x
};


#pragma once

#define WRENCH_FIX_POS_Y        15.0f       //�����`��Y���W������
#define WRENCH_PROBABILITY		4			//�����`���o������m���̍ő�l
#define WRENCH_APPEARANCE_NUM   1           //�����`���o�闐���̐��l

class Wrench
{
public:
    /// <summary>
    /// ���f���̎擾�ƍ��W�̏�����
    /// </summary>
    /// <param name="modelHandle">�����`�̃��f���n���h��</param>
    Wrench(int modelHandle);

    /// <summary>
    /// ���f���̌㏈��
    /// </summary>
    ~Wrench();

    /// <summary>
    /// �o���̏�����
    /// </summary>
    /// <param name="startTime">�����`�̏o������܂ł̃J�E���g</param>
    void InitAppearance(int startTime);

    /// <summary>
    /// �����`�̈ʒu�X�V
    /// </summary>
    /// <param name="cheesePos">�`�[�Y�̍��W</param>
    void Update(VECTOR cheesePos);

    /// <summary>
    /// �����`�̕`��
    /// </summary>
    void Draw();

    /// <summary>
    /// �����`���f���̉�]����
    /// </summary>
    void RotateWrench();

    /// <summary>
    /// �v���C���[�Ɏ擾���ꂽ�Ƃ��̏���
    /// </summary>
    void OnHitPlayer();

    /// <summary>
    /// �����`�̍��W�擾
    /// </summary>
    /// <returns>�����`�̍��W</returns>
    VECTOR GetPos() { return pos; }

    /// <summary>
    /// �����`���o�����Ă��邩�擾
    /// </summary>
    /// <returns>�����`���o�����Ă��邩�ǂ���</returns>
    bool GetIsAppearance() { return isAppearance; }
private:
    VECTOR pos;                                         //�����`�̍��W
    int modelHandle;                                    //�����`�̃��f���n���h��

    static constexpr float rotationSpeed = 1.0f;        //�����`�̉�]�X�s�[�h
    static constexpr float maxRpm = 360.0f;             //�����`�̍ő��]��
    float rpm;                                          //�����`�̉�]��

    bool isAppearance;                                  //�����`�o���p�ϐ�
};


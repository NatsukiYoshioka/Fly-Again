#pragma once
#include<DxLib.h>

/// <summary>
/// �t�B�[���h���f���Ǘ��N���X
/// </summary>
class Field
{
public:
	/// <summary>
	/// �t�B�[���h���̏�����
	/// </summary>
	Field();

	/// <summary>
	/// �t�B�[���h���f���̌㏈��
	/// </summary>
	~Field();

	/// <summary>
	/// �t�B�[���h���f���̏�����
	/// </summary>
	void Draw();

	/// <summary>
	/// �t�B�[���h���f���n���h���̎擾
	/// </summary>
	/// <returns>�t�B�[���h�̃��f���n���h��</returns>
	int GetModelHandle() { return modelHandle; }
private:
	VECTOR pos;			//�t�B�[���h���f���̍��W

	int modelHandle;	//�t�B�[���h�̃��f���n���h��

	static const VECTOR initialPos;					//�t�B�[���h�̍��W�̏������p�萔
	static const VECTOR fieldAngle;					//�t�B�[���h�̏����p�x
	static const VECTOR modelScale;					//�t�B�[���h�̊g�k�x
	static constexpr int frameIndex = -1;			//���f���S�̂̃|���S�����R���W�������
	static constexpr int spatialPartitionNum = 10;	//�R���W�������̋�ԕ�����
};


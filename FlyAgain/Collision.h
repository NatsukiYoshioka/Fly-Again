#pragma once

class Player;
class ObstructManager;
class Effect;

/// <summary>
/// �v���C���[�ƃI�u�W�F�N�g�̓����蔻��N���X
/// </summary>
class Collision
{
public:
	/// <summary>
	/// �ϐ��̏�����
	/// </summary>
	Collision();

	/// <summary>
	/// �N���X�̌㏈��
	/// </summary>
	~Collision(){}

	/// <summary>
	/// �����蔻��̒���
	/// </summary>
	/// <param name="player">�v���C���[����N���X</param>
	/// <param name="obstructMgr">�v���C���[�ȊO�̃I�u�W�F�N�g����N���X</param>
	/// <param name="effect">�G�t�F�N�g����N���X</param>
	void HitJudge(Player* player, ObstructManager* obstructMgr, Effect* effect);

private:
	bool hitFlag;			//�ڐG�t���O
};


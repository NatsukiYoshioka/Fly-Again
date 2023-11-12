#include"Player.h"
#include"ObstructManager.h"
#include"Effect.h"
#include"Mouse.h"
#include"Cheese.h"
#include"Wrench.h"
#include"common.h"
#include "Collision.h"

Collision::Collision():
	hitFlag(false)
{
	
}

//�����蔻��̒���
void Collision::HitJudge(Player* player, ObstructManager* obstructMgr, Effect* effect)
{
	//�n�ʂɓ������Ă����ꍇ�̔���
	if (player->GetCollPos().y < GROUND_HEIGHT)
	{
		player->OnHitGround();
		effect->UpdateBoundGroundEffect(player->GetCollPos());
	}

	if (!hitFlag)
	{
		for (int i = 0; i < MOUSE_NUM; i++)
		{
			// ���݂��̃|�W�V�����Ɣ��a�̋������d�Ȃ��Ă��āA���A�v���C���[�̈ʒu����Q����荂���Ɠ������Ă��邱�ƂɂȂ�
			VECTOR playerToCheese = VSub(obstructMgr->GetCheese(i)->GetPos(), player->GetCollPos());
			if (VSize(playerToCheese) < player->GetHitRadius() + obstructMgr->GetCheese(i)->GetHitRadius() && player->GetCollPos().y > obstructMgr->GetCheese(i)->GetPos().y && obstructMgr->GetCheese(i)->GetFlag())
			{
				hitFlag = true;

				//�`�[�Y�ɓ����������̏���
				obstructMgr->GetCheese(i)->OnHitPlayer(hitFlag);

				//�R���⋋
				player->FuelSupply();

				//�`�[�Y�ɓ����������̃G�t�F�N�g�̏���
				effect->UpdateCheeseEffect(player->GetCollPos());

				//���������`�[�Y�̏ꏊ�Ƀ����`������΃v���C���[�Ƀ|�C���g��t�^���ă����`������
				if (player->GivePoint(obstructMgr->GetWrench(i)->GetIsAppearance()))
				{
					//�����`�̕`�����������
					obstructMgr->GetWrench(i)->OnHitPlayer();

					//�����`����肵���Ƃ��̃G�t�F�N�g�̏���
					effect->UpdateWrenchEffect(obstructMgr->GetWrench(i)->GetPos());
				}
				break;
			}

			VECTOR playerToMouse = VSub(obstructMgr->GetMouse(i)->GetCollPos(), player->GetCollPos());
			if (VSize(playerToMouse) < player->GetHitRadius() + obstructMgr->GetMouse(i)->GetHitRadius() && player->GetCollPos().y > obstructMgr->GetMouse(i)->GetCollPos().y)
			{
				hitFlag = true;

				//���������}�E�X�̏ꏊ�Ƀ����`������΃v���C���[�Ƀ|�C���g��t�^���ă����`������
				if (player->GivePoint(obstructMgr->GetWrench(i)->GetIsAppearance()))
				{
					//�����`�̕`�����������
					obstructMgr->GetWrench(i)->OnHitPlayer();

					//�����`����肵���Ƃ��̃G�t�F�N�g�̏���
					effect->UpdateWrenchEffect(obstructMgr->GetWrench(i)->GetPos());
				}				
				break;
			}
		}
	}
	//�v���C���[�̓����蔻�菈��
	player->OnHitObstruct(hitFlag);
	hitFlag = false;
}
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

//当たり判定の調査
void Collision::HitJudge(Player* player, ObstructManager* obstructMgr, Effect* effect)
{
	//地面に当たっていた場合の判定
	if (player->GetCollPos().y < GROUND_HEIGHT)
	{
		player->OnHitGround();
		effect->UpdateBoundGroundEffect(player->GetCollPos());
	}

	if (!hitFlag)
	{
		for (int i = 0; i < MOUSE_NUM; i++)
		{
			// お互いのポジションと半径の距離が重なっていて、かつ、プレイヤーの位置が障害物より高いと当たっていることになる
			VECTOR playerToCheese = VSub(obstructMgr->GetCheese(i)->GetPos(), player->GetCollPos());
			if (VSize(playerToCheese) < player->GetHitRadius() + obstructMgr->GetCheese(i)->GetHitRadius() && player->GetCollPos().y > obstructMgr->GetCheese(i)->GetPos().y && obstructMgr->GetCheese(i)->GetFlag())
			{
				hitFlag = true;

				//チーズに当たった時の処理
				obstructMgr->GetCheese(i)->OnHitPlayer(hitFlag);

				//燃料補給
				player->FuelSupply();

				//チーズに当たった時のエフェクトの処理
				effect->UpdateCheeseEffect(player->GetCollPos());

				//当たったチーズの場所にレンチがあればプレイヤーにポイントを付与してレンチを消す
				if (player->GivePoint(obstructMgr->GetWrench(i)->GetIsAppearance()))
				{
					//レンチの描画を消す処理
					obstructMgr->GetWrench(i)->OnHitPlayer();

					//レンチを入手したときのエフェクトの処理
					effect->UpdateWrenchEffect(obstructMgr->GetWrench(i)->GetPos());
				}
				break;
			}

			VECTOR playerToMouse = VSub(obstructMgr->GetMouse(i)->GetCollPos(), player->GetCollPos());
			if (VSize(playerToMouse) < player->GetHitRadius() + obstructMgr->GetMouse(i)->GetHitRadius() && player->GetCollPos().y > obstructMgr->GetMouse(i)->GetCollPos().y)
			{
				hitFlag = true;

				//当たったマウスの場所にレンチがあればプレイヤーにポイントを付与してレンチを消す
				if (player->GivePoint(obstructMgr->GetWrench(i)->GetIsAppearance()))
				{
					//レンチの描画を消す処理
					obstructMgr->GetWrench(i)->OnHitPlayer();

					//レンチを入手したときのエフェクトの処理
					effect->UpdateWrenchEffect(obstructMgr->GetWrench(i)->GetPos());
				}				
				break;
			}
		}
	}
	//プレイヤーの当たり判定処理
	player->OnHitObstruct(hitFlag);
	hitFlag = false;
}
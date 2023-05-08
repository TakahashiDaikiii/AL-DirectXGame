#include "Player.h"
#include<cassert>
#include"WorldTransform.h"
#include"Model.h"

void Player::Initialize(Model* model, uint32_t textureHandle) 
{ assert(model); 
	
    model_ = model;
	textureHandle_ = textureHandle;


	worldtransform_.Initialize();


}

void Player::Update() {}

void Player::Drow(ViewProjection&viewProjection)
{
	model_->Draw(worldtransform_, viewProjection, textureHandle_);
}
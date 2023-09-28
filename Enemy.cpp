#include "Enemy.h"
#include "MyMath.h"
#include <cassert>

void Enemy::Initialize(Model* model, const Vector3& position) {

	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("enemy2.png");

	// 拡大縮小
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	// 回転量
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	// 座標
	worldTransform_.translation_ = position;

	worldTransform_.Initialize();

	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = {0.0f,0.0f,0.3f};

}

void Enemy::Update() 
{
	// 座標を移動させる
	worldTransform_.translation_.x -= velocity_.x;
	worldTransform_.translation_.y -= velocity_.y;
	worldTransform_.translation_.z -= velocity_.z;

	/*worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();*/
	worldTransform_.UpdateMatrix();

	switch (phase_) {

	case Enemy::Phase::Approach:
	default:
		//移動（ベクトルを加算）
		worldTransform_.translation_.x -= velocity_.x;
		worldTransform_.translation_.y -= velocity_.y;
		worldTransform_.translation_.z -= velocity_.z;
		//既定の位置に到達したら離脱
		if (worldTransform_.translation_.z<0.0f) 
		{
			phase_ = Phase::Leave;
		}

		break;
	case Enemy::Phase::Leave:
		// 移動（ベクトルを加算）
		worldTransform_.translation_.x -= 0.2f;
		worldTransform_.translation_.y += 0.2f;
		worldTransform_.translation_.z -= 0.2f;
		break;
	}


}

void Enemy::Draw(const ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
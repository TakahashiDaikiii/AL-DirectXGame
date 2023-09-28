#include "Enemy.h"
#include "MyMath.h"
#include <cassert>



Enemy::~Enemy() {
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
}

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
	velocity_ = {0.0f,0.0f,0.1f};

	Approach();
}

void Enemy::Update() 
{
	worldTransform_.translation_.x = 3;
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
		timer++;
		if (timer == 150)
		{
			Fire();

			timer = kFireInterval;
		}

		break;
	case Enemy::Phase::Leave:
		// 移動（ベクトルを加算）
		worldTransform_.translation_.x -= 0.2f;
		worldTransform_.translation_.y += 0.2f;
		worldTransform_.translation_.z -= 0.2f;
		break;
	}

	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}

}




void Enemy::Draw(const ViewProjection& viewProjection) 
{

	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

		
}

void Enemy::Fire() {
	// 弾の速度
	const float kBulletSpeed = 0.5f;
	Vector3 velocity(0, 0, -kBulletSpeed);

	// 速度ベクトルを自機の向きに合わせて回転させる
	velocity = TransformNormal(velocity, worldTransform_.matWorld_);

	// 弾を生成し初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	bullets_.push_back(newBullet);

}

void Enemy::Approach() 
{ timer = kFireInterval;


}


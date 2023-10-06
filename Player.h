#pragma once
#include "Model.h"
#include "PlayerBullet.h"
#include "WorldTransform.h"
#include <Input.h>
#include <PrimitiveDrawer.h>
#include <cassert>
#include <list>

class Player {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	///
	/// 攻撃
	///
	void Attack();

	/// <summary>
	/// 描画
	/// </summary>
	void Drow(ViewProjection& viewProjection);

	/// <summary>
	/// デストラクタ
	/// </summary>

	~Player();

	Vector3 GetWorldPosition();

	void OnCollision();

	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

	float GetRadius() { return r; }

private:
	float r = 1.0f;

	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;

	// 弾
	std::list<PlayerBullet*> bullets_;
};

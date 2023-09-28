#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include"EnemyBullet.h"
#include<list>

class Player;

class Enemy {

public:
	///< summary>
	/// 初期化
	///  </summary>
	///  <parm name="model">モデル</param>
	///  <parm name="position">初期座標</param>

	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void Fire();

	void Approach();

	void SetPlayer(Player* player) { player_ = player; }

	Vector3 GetWorldPosition();

	//発射間隔
	static const int kFireInterval = 60;

	
	/// <summary>
	/// デストラクタ
	/// </summary>

	~Enemy();

private:
	enum class Phase {
		Initial,  // 初期
		Approach, // 接近する
		Leave,    // 離脱する
	};
	// 行動フェーズ

	Phase phase_ = Phase::Initial;
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Vector3 velocity_;

	std::list<EnemyBullet*> bullets_;

	int32_t timer = 0;
	Player* player_ = nullptr;
};


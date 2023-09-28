#pragma once
#include "Model.h"
#include "WorldTransform.h"
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

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Vector3 velocity_;
};

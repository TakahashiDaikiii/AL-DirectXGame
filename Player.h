#pragma once
#include"Model.h"
#include"WorldTransform.h"
#include<cassert>
#include<PrimitiveDrawer.h>
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
	/// <summary>
	/// 描画
	/// </summary>
	void Drow(ViewProjection&viewProjection);

private:
	WorldTransform worldtransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

};

#include "Ground.h"
#include <cassert>

void Ground::Initialize(Model* model) {

	assert(model);

	model_ = model;

	worldTransform_.Initialize();

	worldTransform_.scale_ = {60.0f, 60.0f, 60.0f};

	worldTransform_.UpdateMatrix();
}

void Ground::Update() {}

void Ground::Draw(ViewProjection& viewProjection)

{
	model_->Draw(worldTransform_, viewProjection);
}
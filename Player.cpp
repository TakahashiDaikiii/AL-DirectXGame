#include "Player.h"
#include<cassert>
#include"WorldTransform.h"
#include"Model.h"
#include"MyMath.h"
#include"ImGuiManager.h"
void Player::Initialize(Model* model) 
{
	assert(model); 
	
    model_ = model;
	

	input_ = Input::GetInstance();


	// X,Y,Z 方向のスケーリングを設定
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};

	worldTransform_.Initialize();
	
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};

	worldTransform_.Initialize();

	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};

	worldTransform_.Initialize();


}

void Player::Update() {
	Vector3 move = {0, 0, 0};

	const float kCharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	if (input_->PushKey(DIK_UP)) {
		move.y -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y += kCharacterSpeed;
	}

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y -= move.y;
	worldTransform_.translation_.z += move.z;

	// スケーリング行列を宣言

	Matrix4x4 matScale = {0};

	matScale.m[0][0] = worldTransform_.scale_.x;
	matScale.m[1][1] = worldTransform_.scale_.y;
	matScale.m[2][2] = worldTransform_.scale_.z;
	matScale.m[3][3] = 1;

	worldTransform_.TransferMatrix();

	Matrix4x4 matRotX = {0};

	matRotX.m[0][0] = 1;
	matRotX.m[1][1] = cosf(worldTransform_.rotation_.x);
	matRotX.m[2][1] = -sinf(worldTransform_.rotation_.x);
	matRotX.m[1][2] = sinf(worldTransform_.rotation_.x);
	matRotX.m[2][2] = cosf(worldTransform_.rotation_.x);
	matRotX.m[3][3] = 1;

	// 行列の転送
	worldTransform_.TransferMatrix();

	// Y

	Matrix4x4 matRotY = {0};
	matRotY.m[0][0] = cosf(worldTransform_.rotation_.y);
	matRotY.m[1][1] = 1;
	matRotY.m[0][2] = -sinf(worldTransform_.rotation_.y);
	matRotY.m[2][0] = sinf(worldTransform_.rotation_.y);
	matRotY.m[2][2] = cosf(worldTransform_.rotation_.y);
	matRotY.m[3][3] = 1;

	worldTransform_.TransferMatrix();

	// Z
	Matrix4x4 matRotZ = {0};
	matRotZ.m[0][0] = cosf(worldTransform_.rotation_.z);
	matRotZ.m[1][0] = sinf(worldTransform_.rotation_.z);
	matRotZ.m[0][1] = -sinf(worldTransform_.rotation_.z);
	matRotZ.m[1][1] = cosf(worldTransform_.rotation_.z);
	matRotZ.m[2][2] = 1;
	matRotZ.m[3][3] = 1;

	Matrix4x4 matRot=Multiply(Multiply( matRotZ,matRotX), matRotY);

	worldTransform_.TransferMatrix();

	Matrix4x4 matTrans = {0};

	matTrans.m[0][0] = 1;
	matTrans.m[1][1] = 1;
	matTrans.m[2][2] = 1;
	matTrans.m[3][3] = 1;
	matTrans.m[3][0] = worldTransform_.translation_.x;
	matTrans.m[3][1] = worldTransform_.translation_.y;
	matTrans.m[3][2] = worldTransform_.translation_.z;

	worldTransform_.matWorld_ = Multiply(Multiply(matScale, matRot) , matTrans);


	worldTransform_.TransferMatrix();

	//キャラクターの座標を画面表示する処理

	ImGui::Begin("Debug");
	float playerPos[] = {
	    worldTransform_.translation_.x,
	    worldTransform_.translation_.y,
	    worldTransform_.translation_.z,

	};

	ImGui::SliderFloat3("PlayerPos", playerPos, 0, 1);

	worldTransform_.translation_.x = playerPos[0];

	worldTransform_.translation_.y = playerPos[1];

	worldTransform_.translation_.z = playerPos[2];

	ImGui::End();

	const float kMoveLimitX = 31;

	const float kMoveLimitY = 17;

	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);

	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);

	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);

	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);
}




	void Player::Drow(ViewProjection & viewProjection) 
	{
		model_->Draw(worldTransform_, viewProjection);
	}

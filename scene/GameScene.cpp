#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete debugCamera_;
	delete enemy_;
	delete skydome_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandle_ = TextureManager::Load("Playerr1.png");
	model_ = Model::Create();

	worldTransform_.Initialize();

	viewProjection_.Initialize();

	railCamera_.Initialize();

	player_ = new Player();

	player_->Initialize(model_, textureHandle_);

	enemy_ = new Enemy();

	enemy_->Initialize(model_, {0.0f, 0.0f, 50.0f});

	enemy_->SetPlayer(player_);

	debugCamera_ = new DebugCamera(1280, 720);

	AxisIndicator::GetInstance()->SetVisible(true);

	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	skydome_ = new Skydome();

	skydome_->Initialize(modelSkydome_);
}

void GameScene::Update() {
	player_->Update();

	enemy_->Update();

	debugCamera_->Update();

	skydome_->Update();

	railCamera_.Update();

	CheckALLCollisions();

#ifdef _DEBUG

	if (input_->TriggerKey(DIK_0)) {
		isDebugCameraActive_ = true;
	}

#endif // _DEBUG

	if (isDebugCameraActive_) {
		debugCamera_->Update();

		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		viewProjection_.TransferMatrix();
	}

	else {
		viewProjection_.UpdateMatrix();
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	//
	player_->Drow(viewProjection_);

	enemy_->Draw(viewProjection_);

	skydome_->Draw(viewProjection_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckALLCollisions() {

	// 判定対象AとBの座標
	Vector3 posA, posB;
	// 自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();

	// 敵弾リストの取得
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

#pragma region
	// 自キャラの座標
	Vector3 player = player_->GetWorldPosition();

	posA = player_->GetWorldPosition();

	// 自キャラと敵弾全ての当たり判定
	for (EnemyBullet* bullet : enemyBullets) {
		posB = bullet->GetWorldPosition();

		Vector3 d = Subtract(posA, posB);
		// d x y z を二乗してタス
		float dist = d.x * d.x + d.y * d.y + d.z * d.z;

		float r1 = player_->GetRadius(); // プレイヤーの半径

		float r2 = bullet->GetRadius(); // 敵弾の半径

		float radius = r1 * r1 + r2 * r2;
		if (dist <= radius) {
			player_->OnCollision();

			bullet->OnCollision();
		}
	}

	// 自弾と敵キャラの当たり判定

	// 敵キャラの座標
	Vector3 Enemy = enemy_->GetWorldPosition();

	posA = enemy_->GetWorldPosition();
	// 敵キャラと自弾の当たり判定

	for (PlayerBullet* bullet : playerBullets) {
	
	    posB = bullet->GetWorldPosition();

		Vector3 d = Subtract(posA, posB);

		float dist = d.x * d.x + d.y * d.y + d.z * d.z;

		float r1 = enemy_->GetRadius();

		float r2 = bullet->GetRadius();

		float radius = r1 * r1 + r2 * r2;
		if (dist <= radius) {
			enemy_->OnCollision();

			bullet->OnCollision();
		}

	
	}



}
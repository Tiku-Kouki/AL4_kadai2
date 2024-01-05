#include "Enemy.h"

#include "ImGuiManager.h"
 #define _USE_MATH_DEFINES
#include <math.h>

void Enemy::Initalize(const std::vector<Model*>& models) {

	BaseCharacter::Initalize(models);

	// 親子関係の設定
	worldTransform_[1].parent_ = &worldTransform_[0];
	worldTransform_[2].parent_ = &worldTransform_[0];
	

	worldTransform_[0].scale_ = {3.0f, 3.0f, 3.0f};
	worldTransform_[0].rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_[0].translation_ = {0.0f, 0.0f, 0.0f};

	

	worldTransform_[1].scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_[1].rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_[1].translation_ = {-0.9f, 1.0f, 0.0f};

	worldTransform_[2].scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_[2].rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_[2].translation_ = {0.9f, 1.0f, 0.0f};

	for (int i = 0; i < 3; i++) {
		worldTransform_[i].Initialize();
	}
	
}

void Enemy::Update() {

	BaseCharacter::Update();
	
	angle += 1.0f / 180.0f * (float)M_PI;

	worldTransform_[0].rotation_.y = -angle;
		

	worldTransform_[0].translation_.x = 0 + std::cos(angle) * 10.0f;
	worldTransform_[0].translation_.z = 0 + std::sin(angle) * 10.0f;
	
	for (int i = 0; i < 3; i++) {
		

		worldTransform_[i].UpdateMatrix();
	}

	ImGui::Begin("Enemy");

	ImGui::DragFloat3("Body", &worldTransform_[0].translation_.x, 0.01f);
	ImGui::DragFloat3("Arm_L", &worldTransform_[1].translation_.x, 0.01f);
	ImGui::DragFloat3("Arm_R", &worldTransform_[2].translation_.x, 0.01f);
	ImGui::DragFloat3("Root", &worldTransform_[0].rotation_.x, 0.01f);
	ImGui::End();
}

void Enemy::Draw(ViewProjection& viewProjection) {

	for (int i = 0; i < 3; i++) {
		models_[i]->Draw(worldTransform_[i], viewProjection);
	}
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos = {};

	worldPos.x = worldTransform_[0].matWorld_.m[3][0];
	worldPos.y = worldTransform_[0].matWorld_.m[3][1];
	worldPos.z = worldTransform_[0].matWorld_.m[3][2];

	return worldPos;
}

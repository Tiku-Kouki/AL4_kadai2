#include "Aitem.h"

void Aitem::Initalize(const std::vector<Model*>& models) {
	
	BaseCharacter::Initalize(models);

	

	worldTransform_[0].scale_ = {3.0f, 3.0f, 3.0f};
	worldTransform_[0].rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_[0].translation_ = {0.0f, 0.0f, 0.0f};

	worldTransform_[1].scale_ = {3.0f, 3.0f, 3.0f};
	worldTransform_[1].rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_[1].translation_ = {10.0f, 0.0f, 0.0f};

	worldTransform_[2].scale_ = {3.0f, 3.0f, 3.0f};
	worldTransform_[2].rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_[2].translation_ = {0.9f, 0.0f, 0.0f};

	for (int i = 0; i < 3; i++) {
		worldTransform_[i].Initialize();
	}
}

void Aitem::Update() {
	
	
	BaseCharacter::Update();

	for (int i = 0; i < 3; i++) {

		worldTransform_[i].UpdateMatrix();
	}


}

void Aitem::Draw(ViewProjection& viewProjection) {

	for (int i = 0; i < 3; i++) {
		models_[i]->Draw(worldTransform_[i], viewProjection);
	}
}

Vector3 Aitem::GetWorldPosition1() {
	Vector3 worldPos = {};

	worldPos.x = worldTransform_[0].matWorld_.m[3][0];
	worldPos.y = worldTransform_[0].matWorld_.m[3][1];
	worldPos.z = worldTransform_[0].matWorld_.m[3][2];

	return worldPos;
}

Vector3 Aitem::GetWorldPosition2() {
	Vector3 worldPos = {};

	worldPos.x = worldTransform_[1].matWorld_.m[3][0];
	worldPos.y = worldTransform_[1].matWorld_.m[3][1];
	worldPos.z = worldTransform_[1].matWorld_.m[3][2];

	return worldPos;
}

Vector3 Aitem::GetWorldPosition3() {
	Vector3 worldPos = {};

	worldPos.x = worldTransform_[2].matWorld_.m[3][0];
	worldPos.y = worldTransform_[2].matWorld_.m[3][1];
	worldPos.z = worldTransform_[2].matWorld_.m[3][2];

	return worldPos;
}



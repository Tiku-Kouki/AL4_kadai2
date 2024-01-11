#include "Aitem.h"
#include <stdlib.h>
#include <random>
#include<time.h>
#include <functional>

void Aitem::Initalize(const std::vector<Model*>& models) {
	
	BaseCharacter::Initalize(models);

	

	worldTransform_[0].scale_ = {3.0f, 3.0f, 3.0f};
	worldTransform_[0].rotation_ = {0.0f, 10.0f, 0.0f};
	worldTransform_[0].translation_ = {0.0f, 4.0f, 10.0f};

	worldTransform_[1].scale_ = {3.0f, 3.0f, 3.0f};
	worldTransform_[1].rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_[1].translation_ = {10.0f, 4.0f, -20.0f};

	worldTransform_[2].scale_ = {3.0f, 3.0f, 3.0f};
	worldTransform_[2].rotation_ = {0.0f, -2.0f, 0.0f};
	worldTransform_[2].translation_ = {50.9f, 4.0f, 1.0f};

	for (int i = 0; i < 3; i++) {
		worldTransform_[i].Initialize();
	}
}

void Aitem::Update() {
	
	
	BaseCharacter::Update();

	for (int i = 0; i < 3; i++) {

		worldTransform_[i].rotation_.y += 0.01f;

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

void Aitem::OnColision1() {
	
	int n = 0;

	n = rand() % 100 - 100;
  
	worldTransform_[0].translation_.x = (float)n;

	

	n = rand() % 100 - 100;

	worldTransform_[0].translation_.z = (float)n;

}

void Aitem::OnColision2() {


	int n = 0;

	n = rand() % 100 - 100;

	worldTransform_[1].translation_.x = (float)n;

	n = rand() % 9 + 1;
	if (n > 5) {

	n = 9;

	} else {
	n = 4;
	}
	worldTransform_[1].translation_.y = (float)n;


	n = rand() % 100 - 100;

	worldTransform_[1].translation_.z = (float)n;

}

void Aitem::OnColision3() {
	

	int n = 0;

	n = rand() % 100 - 100;

	worldTransform_[2].translation_.x = (float)n;

	n = rand() % 9 + 1;
	if (n > 3) {

	n = 9;

	} else {
	n = 4;
	}
	worldTransform_[2].translation_.y = (float)n;

	n = rand() % 100 - 100;

	worldTransform_[2].translation_.z = (float)n;

}



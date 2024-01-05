#include "Ground.h"
#include"cassert"

void Ground::Initialize(Model* model) { 
	assert(model);
	model_ = model;

	worldTransform_.scale_ = {12.0f, 12.0f, 12.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};

	worldTransform_.Initialize();


}

void Ground::Update() { worldTransform_.UpdateMatrix(); }

void Ground::Draw(ViewProjection& viewProjection) {

model_->Draw(worldTransform_, viewProjection);



}

Ground::~Ground() {



}

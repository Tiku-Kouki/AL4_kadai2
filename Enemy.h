#pragma once
#include "Affine.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "BaseCharacter.h"

class Enemy : public BaseCharacter {

	public:
	void Initalize(const std::vector<Model*>& models) override;

	void Update() override;

	void Draw(ViewProjection& viewProjection) override;

	Vector3 GetWorldPosition();

	

private:
	WorldTransform worldTransform_[3];

	Model* model_ = nullptr;

	// 3Dモデル
	Model* modelEnemyBody_ = nullptr;
	Model* modelEnemyL_arm_ = nullptr;
	Model* modelEnemyR_arm_ = nullptr;

	Input* input_ = nullptr;

	uint32_t textureHandle_ = 0u;

	// 　カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

	  float angle = 0.0f;





};

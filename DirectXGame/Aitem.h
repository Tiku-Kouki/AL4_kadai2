#pragma once
#include "Affine.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "BaseCharacter.h"

class Aitem : public BaseCharacter {

public:

	void Initalize(const std::vector<Model*>& models) override;

	void Update() override;

	void Draw(ViewProjection& viewProjection) override;

	Vector3 GetWorldPosition1();

	Vector3 GetWorldPosition2();

	Vector3 GetWorldPosition3();

	void OnColision1();

	void OnColision2();

	void OnColision3();

private:
	WorldTransform worldTransform_[3];

	Model* model_ = nullptr;

	// 3Dモデル
	Model* aitem = nullptr;
	

	Input* input_ = nullptr;

	uint32_t textureHandle_ = 0u;

	// 　カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

	
};

#pragma once
#include "Affine.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <list>
#include "Windows.h"
#include "FollowCamera.h"
#include "BaseCharacter.h"
#include <optional>



class Player : public BaseCharacter {

	enum  class Behavior {
		kRoot,
		kAttack,

	};



 public:

	void Initalize(const std::vector<Model*>& models) override;


	void Update() override;



	void Draw(ViewProjection& viewProjection) override;

	Vector3 GetWorldPosition();

	const WorldTransform& GetWorldTransform() { return worldTransform_[0]; }

	void SetViewProjection(const ViewProjection* viewProjection) {viewProjection_ = viewProjection;}

	//浮遊ギミック初期化
	void InitializeFloatingGimmick();
	//浮遊ギミック更新
	void UpdateFloatingGimmick();

	//通常行動更新
	void BehaviorRootUpdate();
	// 攻撃行動更新 
	void BehaviorAttackUpdate();

	// 通常行動初期化
	void BehaviorRootInitialize();
	// 攻撃行動初期化
	void BehaviorAttackInitialize();


private:

	WorldTransform worldTransform_[4];

	WorldTransform hammer;

	Input* input_ = nullptr;

	uint32_t textureHandle_ = 0u;

	//　カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

	//浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;

	  //振るまい
	Behavior behavior_ = Behavior::kRoot;

	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	float X = 0;
	float Ease = 0;

	};

#pragma once
#include "Affine.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class FollowCamera {
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	Vector3 GetWorldPosition();

	const ViewProjection& GetViewProjection() { return viewProjection_; }

	const WorldTransform& GetWorldTransform() { return worldTransform_; }
	
	void SetTarget(const WorldTransform* target) { target_ = target; }

private:
	
	bool isDebugCameraActive_ = false;

	WorldTransform worldTransform_;
	
	ViewProjection viewProjection_; 

	const WorldTransform* target_ = nullptr;


};

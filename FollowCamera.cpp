#include "FollowCamera.h"
#include "ImGuiManager.h"
#include "cassert"
void FollowCamera::Initialize() { 
	
	//worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};

	//worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};

	//worldTransform_.translation_ = {1.0f, 1.0f, 1.0f};
	
	viewProjection_.Initialize();


}

void FollowCamera::Update() {

	if (target_) {
	
	 Vector3 offset = {0.0f, 8.0f, -20.0f};

	 Matrix4x4 rotateXMatrix = MakeRotateXMatrix(viewProjection_.rotation_.x);
	 Matrix4x4 rotateYMatrix = MakeRotateYMatrix(viewProjection_.rotation_.y);
	 Matrix4x4 rotateZMatrix = MakeRotateZMatrix(viewProjection_.rotation_.z);

	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));


	 offset = TransformNormal(offset, rotateXYZMatrix);

	
	viewProjection_.translation_ = Add(target_->translation_, offset);
	
	viewProjection_.translation_.y = 5.0f;
	
	}
	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		 Vector3 rotationSpeed = {0.05f, 0.05f, 0.05f};

		 viewProjection_.rotation_.y +=
		     (float)joyState.Gamepad.sThumbRX / SHRT_MAX * rotationSpeed.y;

	}

	
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	viewProjection_.matView = Inverse(worldTransform_.matWorld_);

	viewProjection_.UpdateMatrix();
	// viewProjection_.TransferMatrix();

	ImGui::Begin("Camera");

	ImGui::DragFloat3("Translation", &viewProjection_.translation_.x, 0.01f);
	ImGui::DragFloat3("Rotation", &viewProjection_.rotation_.x, 0.01f);

	ImGui::End();

}
Vector3 FollowCamera::GetWorldPosition() {
	Vector3 worldPos = {};

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
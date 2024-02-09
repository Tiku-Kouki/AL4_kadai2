#include "TitleAitem.h"
  #include "ImGuiManager.h"
 #define _USE_MATH_DEFINES
#include <math.h>

void TitleAitem::Initalize(const std::vector<Model*>& models) {

	BaseCharacter::Initalize(models);

	worldTransform_.scale_ = {3.0f, 3.0f, 3.0f};
	worldTransform_.rotation_ = {0.0f, 10.0f, 0.0f};
	worldTransform_.translation_ = {-15.0f, -4.48f, -9.0f};

	
	worldTransform_.Initialize();
	
}

void TitleAitem::Update() {

	BaseCharacter::Update();

	   

	worldTransform_.rotation_.y += 0.01f;

	worldTransform_.UpdateMatrix();

	#ifdef _DEBUG
	ImGui::Begin("ain");

	ImGui::DragFloat3("Body", &worldTransform_.translation_.x, 0.01f);
	
	ImGui::End();
#endif
	    
}

void TitleAitem::Draw(ViewProjection& viewProjection) {

	   for (int i = 0; i < 1; i++) {
		models_[i]->Draw(worldTransform_, viewProjection);
	}


}

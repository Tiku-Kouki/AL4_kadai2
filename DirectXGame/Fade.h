#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <memory>

class Fade {

	enum FadeMode {
		Num,
		In,
		Out,
	   
	};



public:
	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(float a);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(int sw);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	int GetFadeMode(){

		return fadeSwich;
	}
	float GetColor() { return fadeColor_.w; }


	void FadeInStart() { fadeSwich = In; }
	void FadeOutStart() { fadeSwich = Out; }

	private:
	

	Sprite* fadeSprite_ = nullptr;

	Vector4 fadeColor_ = {1.0f, 1.0f, 1.0f, 0.0f};

	int fadeSwich = 0;

};

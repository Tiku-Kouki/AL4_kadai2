#include "ClearScene.h"
#include "AxisIndicator.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include <cassert>
#include <math.h>
#include<fstream>

ClearScene::ClearScene() {}

ClearScene::~ClearScene() {


delete clear_;

}

void ClearScene::Initialize() {

	isSceneEnd = false;
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	uint32_t textureClear = TextureManager::Load("clear.png");

	// スプライト生成
	clear_ = Sprite::Create(textureClear, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1}, {0.5f, 0.5f});

	soundDataHandle_ = audio_->LoadWave("koto.wav");

	fade_ = std::make_unique<Fade>();

	fade_->Initialize(fadeNom);

}

void ClearScene::Update() {

	fade_->Update(fadeSw);
	
	fadeSw = fade_->GetFadeMode();

	if ((fade_->GetColor() > 0.0f) && (isSceneEnd == false) && (fadeOut == false)) {
		fadeIn = true;
		fade_->FadeInStart();
	}

	if ((fade_->GetColor() < 1.0f) && (fadeOut == true) && (fadeIn == false)) {

		fade_->FadeOutStart();
	}

	if (fade_->GetFadeMode() == 0) {
		fadeIn = false;
		fadeOut = false;
	}

	if (clear == 0 && (fade_->GetColor() == 0.0f)) {

		voiceHandle_ = audio_->PlayWave(soundDataHandle_);

		clear++;
	}


	if (input_->TriggerKey(DIK_SPACE) && fade_->GetFadeMode() == 0) {
		
		 flage = true;

	} 
	if (flage == true) {
	
		fadeOut = true;

		if (fade_->GetColor() == 1.0f) {
			clear = 0;
			isSceneEnd = true;
		}
	
	} else {
		flage = false;
		isSceneEnd = false;
	}


	

}

void ClearScene::Draw() {


	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる

	clear_->Draw();

	fade_->Draw();

	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

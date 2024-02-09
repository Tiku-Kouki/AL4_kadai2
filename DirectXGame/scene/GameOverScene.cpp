#include "GameOverScene.h"
#include "AxisIndicator.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include <cassert>
#include <math.h>
#include<fstream>

GameOverScene::GameOverScene() {}

GameOverScene::~GameOverScene() {

delete gameOver_;

}

void GameOverScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	uint32_t textureGameOver = TextureManager::Load("gameOver.png");
	gameOver_ = Sprite::Create(textureGameOver, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1}, {0.5f, 0.5f});

	
	soundDataHandle_ = audio_->LoadWave("bom.wav");


}

void GameOverScene::Update() {

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

	if (bom == 0 && (fade_->GetColor() == 0.0f)) {

		voiceHandle_ = audio_->PlayWave(soundDataHandle_);
		bom = 1;
	}

	if (input_->TriggerKey(DIK_SPACE) && fade_->GetFadeMode() == 0) {

		flage = true;
	}
	if (flage == true) {

		fadeOut = true;

		if (fade_->GetColor() == 1.0f) {
			bom = 0;
			isSceneEnd = true;
		}

	} else {
		flage = false;
		isSceneEnd = false;
	}

}

void GameOverScene::Draw() {


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

	gameOver_->Draw();

	fade_->Draw();

	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

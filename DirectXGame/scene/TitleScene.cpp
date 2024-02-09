#include "TitleScene.h"
#include "AxisIndicator.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include <cassert>
#include <math.h>
#include<fstream>

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	delete title_; 
	delete manual_;


}

void TitleScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	
	uint32_t textureTitle = TextureManager::Load("title.png");
	uint32_t textureManual = TextureManager::Load("manual.png");

	viewProjection_.Initialize();
	
	title_ = Sprite::Create(textureTitle, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1}, {0.5f, 0.5f});
	manual_ = Sprite::Create(textureManual, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1}, {0.5f, 0.5f});

	soundDataHandle_ = audio_->LoadWave("title.wav");

	 aitem_ = std::make_unique<TitleAitem>();

	   // 3Dモデル
	 modelUme_.reset(Model::CreateFromOBJ("ume", true));

	std::vector<Model*> aitemModels = {modelUme_.get()};

	aitem_->Initalize(aitemModels);

	debugCamera_ = new DebugCamera(1280, 720);

	 fade_ = std::make_unique<Fade>();

	fade_->Initialize(fadeNom);

}

void TitleScene::Update()
{
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

	aitem_->Update();

	if (!audio_->IsPlaying(voiceHandle_)) {

		voiceHandle_ = audio_->PlayWave(soundDataHandle_);
	}
	
	  XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
	
		  if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_A && titleMenu == kManual) {
			flage = true;
		} 
	
		 if (input_->TriggerKey(DIK_SPACE) && titleMenu == kTitle) {

			titleMenu = kManual;
		} 

		

	}
	if (input_->TriggerKey(DIK_R)) {

		titleMenu = kTitle;
	} 

	if (flage == true) {

		fadeOut = true;

		if (fade_->GetColor() == 1.0f) {
			titleMenu = kTitle;
			audio_->StopWave(voiceHandle_);
			isSceneEnd = true;
		}

	
		
	} else {
		isSceneEnd = false;
	}

	
	 #ifdef _DEBUG

	/*if (input_->PushKey(DIK_SPACE)) {
		isDebugCameraActive_ = true;
	}*/

#endif // DEBUG
	
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		//viewProjection_.TransferMatrix();
	
		viewProjection_.UpdateMatrix();
	
	   
}

void TitleScene::Draw()
{

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	if (titleMenu == kTitle) {

		title_->Draw();
	}

	if (titleMenu == kManual) {

		manual_->Draw();
	} 

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

	 if (titleMenu == kTitle) {
		aitem_->Draw(viewProjection_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる

	
		 fade_->Draw();
	


	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion

}

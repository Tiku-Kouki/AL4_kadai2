#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() { 
	

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("mario.png");

	

	// 3Dモデル

	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("float_L_arm", true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("float_R_arm", true));

	Hammer.reset(Model::CreateFromOBJ("hammer", true));

	modelEnemyBody_.reset(Model::CreateFromOBJ("needle_Body", true));
	
	modelEnemyL_arm_.reset(Model::CreateFromOBJ("needle_L_arm", true));
	modelEnemyR_arm_.reset(Model::CreateFromOBJ("needle_R_arm", true));

	viewProjection_.Initialize();

	followCamera_ = std::make_unique<FollowCamera>();
	
	followCamera_->Initialize();

	player_ = std::make_unique<Player>();

	std::vector<Model*> plyerModels = {
	    modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),
	    modelFighterR_arm_.get(), Hammer.get()};

	player_->Initalize(plyerModels);

	enemy_ = std::make_unique<Enemy>();

	std::vector<Model*> enemyModels = {
	    modelEnemyBody_.get(), modelEnemyL_arm_.get(), 
		modelEnemyR_arm_.get()};

	enemy_->Initalize(enemyModels);


	

	followCamera_->SetTarget(&player_->GetWorldTransform());
	
	player_->SetViewProjection(&followCamera_->GetViewProjection());

	//debugCamera_ = new DebugCamera(1280, 720);

	skydome_ = std::make_unique<Skydome>();
	modelSkydome_.reset(Model::CreateFromOBJ("skydome", true));
	skydome_->Initialize(modelSkydome_.get());

	ground_ = std::make_unique<Ground>();
	modelGround_.reset(Model::CreateFromOBJ("ground", true));
	ground_->Initialize(modelGround_.get());

	
	

}

void GameScene::Update() {

	
	player_->Update();
	skydome_->Update();
	ground_->Update();
	enemy_->Update();


#ifdef _DEBUG

	if (input_->PushKey(DIK_SPACE)) {
		isDebugCameraActive_ = true;
	}

#endif // DEBUG
	
	followCamera_->Update();
	viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
	viewProjection_.matView = followCamera_->GetViewProjection().matView;
	viewProjection_.TransferMatrix();
	//viewProjection_.UpdateMatrix();
	
}

void GameScene::Draw() {

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

	player_->Draw(viewProjection_);

	skydome_->Draw(viewProjection_);

	ground_->Draw(viewProjection_);

	enemy_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

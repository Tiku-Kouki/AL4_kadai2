#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() { 
		// スプライト生成
	for (int i = 0; i < 15; i++) {

		delete scoreSp[i]; 
	}

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	
	scoreHandle_ = TextureManager::Load("onigiri.png");

	// スプライト生成
	for (int i = 0; i < 15; i++) {

		scoreSp[i] = Sprite::Create(
		    scoreHandle_, {40.0f + (20.0f * i), 40.0f}, {1.0f, 1.0f, 1.0f, 1}, {0.5f, 0.5f});
	}
	// 3Dモデル

	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("float_L_arm", true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("float_R_arm", true));

	Hammer.reset(Model::CreateFromOBJ("hammer", true));

	modelEnemyBody_.reset(Model::CreateFromOBJ("needle_Body", true));
	
	modelEnemyL_arm_.reset(Model::CreateFromOBJ("needle_L_arm", true));
	modelEnemyR_arm_.reset(Model::CreateFromOBJ("needle_R_arm", true));

	  // 3Dモデル
	modelUme_.reset(Model::CreateFromOBJ("ume", true));
	modelNori_.reset(Model::CreateFromOBJ("nori", true));
	modelEbi_.reset(Model::CreateFromOBJ("ebi", true));


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

	  aitem_ = std::make_unique<Aitem>();
	
	  std::vector<Model*> aitemModels = {modelUme_.get(), modelNori_.get(), modelEbi_.get()};

	  aitem_->Initalize(aitemModels);

	followCamera_->SetTarget(&player_->GetWorldTransform());
	
	player_->SetViewProjection(&followCamera_->GetViewProjection());

	//debugCamera_ = new DebugCamera(1280, 720);

	skydome_ = std::make_unique<Skydome>();
	modelSkydome_.reset(Model::CreateFromOBJ("skydome", true));
	skydome_->Initialize(modelSkydome_.get());

	ground_ = std::make_unique<Ground>();
	modelGround_.reset(Model::CreateFromOBJ("ground", true));
	ground_->Initialize(modelGround_.get());

	 soundDataHandle_ = audio_->LoadWave("wafuu.wav");
	eatSound_ = audio_->LoadWave("eat.wav");

	
}

void GameScene::Update() {

	if (!audio_->IsPlaying(voiceHandle_)) {

		voiceHandle_ = audio_->PlayWave(soundDataHandle_);
	 }
	
	player_->Update();
	skydome_->Update();
	ground_->Update();
	enemy_->Update();
	aitem_->Update();

	 CheckAllCollisions();

	 if (score >= maxScore) {
		audio_->StopWave(voiceHandle_);
	 	   isSceneEnd = true;
	 
	 } else {
		   isSceneEnd = false;
	 }


	 if (life <= 0) {
		   audio_->StopWave(voiceHandle_);
	 isGameOver = true;
	 
	 } else {
	 isGameOver = false;
	 }



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

void GameScene::CheckAllCollisions() {

Vector3 posA[3], posB[3];

float X[3] = {};
float Y[3] ;
float Z[3] ;

float center[3] ;
	float R1 = 3.0f; // 自分で決める
	float R2 = 3.0f; // 自分で決める
	float RR = (R1 + R2);
	

#pragma region // 自キャラとアイテム1の当たり判定
	
	 R1 = 3.0f; // 自分で決める
	 R2 = 3.0f; // 自分で決める
	

	posA[0] = player_->GetWorldPosition();

	posB[0] = aitem_->GetWorldPosition1();

		 X[0] = (posB[0].x - posA[0].x);
		 Y[0] = (posB[0].y - posA[0].y);
	     Z[0] = (posB[0].z - posA[0].z);

		 center[0] = X[0] * X[0] + Y[0] * Y[0] + Z[0] * Z[0];
		

		if (center[0] <= (RR * RR)) {
			// 自キャラの衝突時コールバックを呼び出す
			player_->OnColision();
			// 敵弾の衝突時コールバックを呼び出す
			aitem_->OnColision1();
			
			score += 1;

			voiceHandle2_ = audio_->PlayWave(eatSound_);
		}
	
#pragma endregion

#pragma region  // 自キャラとアイテム2の当たり判定

		R1 = 3.0f; // 自分で決める
	    R2 = 3.0f; // 自分で決める

	posA[1] = player_->GetWorldPosition();

	    posB[1] = aitem_->GetWorldPosition2();

	    X[1] = (posB[1].x - posA[1].x);
	    Y[1] = (posB[1].y - posA[1].y);
	    Z[1] = (posB[1].z - posA[1].z);

	    center[1] = X[1] * X[1] + Y[1] * Y[1] + Z[1] * Z[1];
	  

	    if (center[1] <= (RR * RR)) {
		    // 自キャラの衝突時コールバックを呼び出す
		    player_->OnColision();
		    // 敵弾の衝突時コールバックを呼び出す
		    aitem_->OnColision2();

		    score += 1;

			voiceHandle2_ = audio_->PlayWave(eatSound_);
	    }
#pragma endregion

#pragma region  // 自キャラとアイテム3の当たり判定
	  
		R1 = 3.0f; // 自分で決める
	    R2 = 3.0f; // 自分で決める
		
		posA[2] = player_->GetWorldPosition();

	    posB[2] = aitem_->GetWorldPosition3();

	    X[2] = (posB[2].x - posA[2].x);
	    Y[2] = (posB[2].y - posA[2].y);
	    Z[2] = (posB[2].z - posA[2].z);

	    center[2] = X[2] * X[2] + Y[2] * Y[2] + Z[2] * Z[2];
	   

	    if (center[2] <= (RR * RR)) {
		    // 自キャラの衝突時コールバックを呼び出す
		    player_->OnColision();
		    // 敵弾の衝突時コールバックを呼び出す
		    aitem_->OnColision3();

		    score += 1;

			voiceHandle2_ = audio_->PlayWave(eatSound_);
	    }
#pragma endregion

		#pragma region // 自キャラと敵の当たり判定

		R1 = 1.0f; // 自分で決める
	    R2 = 1.0f; // 自分で決める

	    posA[0] = player_->GetWorldPosition();

	    posB[0] = enemy_->GetWorldPosition();

	    X[0] = (posB[0].x - posA[0].x);
	    Y[0] = (posB[0].y - posA[0].y);
	    Z[0] = (posB[0].z - posA[0].z);

	    center[0] = X[0] * X[0] + Y[0] * Y[0] + Z[0] * Z[0];

	    if (center[0] <= (RR * RR)) {
		    // 自キャラの衝突時コールバックを呼び出す
		    player_->OnColision();
		   

		    life -= 1;
	    }

#pragma endregion

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

	aitem_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト生成
	for (int i = 0; i < 15; i++) {
		    if (score >= i + 1) {

			    scoreSp[i]->Draw();
		    }

	}

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::Reset() {

player_->Reset();

 score = 0;

life = 1;	 

}

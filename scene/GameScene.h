#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include <memory>
#include "DebugCamera.h"
#include "Skydome.h"
#include "Ground.h"
#include "FollowCamera.h"
#include "Enemy.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t textureHandle_ = 0;
	std::unique_ptr <Model> model_ = nullptr;

	//3Dモデル
	std::unique_ptr<Model> modelFighterBody_ = nullptr;
	std::unique_ptr<Model> modelFighterHead_ = nullptr;
	std::unique_ptr<Model> modelFighterL_arm_ = nullptr;
	std::unique_ptr<Model> modelFighterR_arm_ = nullptr;

	std::unique_ptr<Model> Hammer = nullptr;

	// 3Dモデル
	std::unique_ptr<Model> modelEnemyBody_ = nullptr;
	std::unique_ptr<Model> modelEnemyL_arm_ = nullptr;
	std::unique_ptr<Model> modelEnemyR_arm_ = nullptr;

	
	std::unique_ptr<Skydome> skydome_ = nullptr;
	std::unique_ptr<Model> modelSkydome_ = nullptr;
	
	std::unique_ptr<Ground> ground_ = nullptr;
	std::unique_ptr<Model> modelGround_ = nullptr;

	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;


	ViewProjection viewProjection_;
	std::unique_ptr<Player> player_ = nullptr;
	std::unique_ptr<Enemy> enemy_ = nullptr;

	std::unique_ptr<FollowCamera>followCamera_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};

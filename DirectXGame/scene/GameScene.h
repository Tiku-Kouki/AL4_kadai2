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
#include "Aitem.h"
#include "Scene.h"

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
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool isSceneEnd = false;
	bool IsSceneEnd() { return isSceneEnd; }

	bool isGameOver = false;
	bool IsGameOver() { return isGameOver; }

	SceneType NextScene() {

		if (isSceneEnd == true) {
			return SceneType::kClearGame;
		} else if (isGameOver == true) {
			return SceneType::kGameOver;
		}
		return SceneType::kGamePlay;
	}

	SceneType GameOver() { return SceneType::kGameOver; }

	void Reset();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	
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

	  // 3Dモデル
	std::unique_ptr<Model> modelUme_ = nullptr;
	std::unique_ptr<Model> modelNori_ = nullptr;
	std::unique_ptr<Model> modelEbi_ = nullptr;



	std::unique_ptr<Skydome> skydome_ = nullptr;
	std::unique_ptr<Model> modelSkydome_ = nullptr;
	
	std::unique_ptr<Ground> ground_ = nullptr;
	std::unique_ptr<Model> modelGround_ = nullptr;

	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;


	ViewProjection viewProjection_;
	std::unique_ptr<Player> player_ = nullptr;
	std::unique_ptr<Enemy> enemy_ = nullptr;

	std::unique_ptr<Aitem> aitem_ = nullptr;

	std::unique_ptr<FollowCamera>followCamera_ = nullptr;

	int score = 0;

	int maxScore = 15;

	 int life = 1;

	 // ライフ
	 uint32_t scoreHandle_;
	 Sprite* scoreSp[15] = {nullptr};

	 // サウンドハンドル
	 uint32_t soundDataHandle_ = 0;

	 uint32_t voiceHandle_ = 0;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};

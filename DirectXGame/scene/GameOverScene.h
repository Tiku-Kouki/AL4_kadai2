#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Scene.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Fade.h"

class GameOverScene {



public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameOverScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameOverScene();

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

	bool isSceneEnd = false;
	bool IsSceneEnd() { return isSceneEnd; }

	SceneType NextScene() { return SceneType::kTitle; }

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	Sprite* gameOver_ = nullptr;

	// サウンドハンドル
	uint32_t soundDataHandle_ = 0;

	uint32_t voiceHandle_ = 0;

	int bom = 0;

	int fadeSw = 0;
	float fadeNom = 1.0f;

	bool fadeIn = false;
	bool fadeOut = false;

	bool flage = false;

	std::unique_ptr<Fade> fade_ = nullptr;

};

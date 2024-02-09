#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "DebugCamera.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Scene.h"
#include "TitleAitem.h"
#include "FollowCamera.h"
#include "Fade.h"

enum TitleSceneType {
	kTitle,
	kManual,
	
};


class TitleScene
{

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	TitleScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleScene();

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

	SceneType NextScene() { return SceneType::kGamePlay; }

	


private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	  // 3Dモデル
	std::unique_ptr<Model> modelUme_ = nullptr;

	std::unique_ptr<TitleAitem> aitem_ = nullptr;
	
	Sprite* title_ = nullptr;
	Sprite* manual_ = nullptr;

	int titleMenu = kTitle;

	// サウンドハンドル
	uint32_t soundDataHandle_ = 0;

	uint32_t voiceHandle_ = 0;

	ViewProjection viewProjection_;

	std::unique_ptr<FollowCamera> followCamera_ = nullptr;

	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;

	int fadeSw = 0;
	float fadeNom = 1.0f;

	bool fadeIn = false;
	bool fadeOut = false;

	bool flage = false;

	std::unique_ptr<Fade> fade_ = nullptr;

};


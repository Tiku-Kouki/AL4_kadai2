#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <list>
#include "Windows.h"

class BaseCharacter {

public:
	virtual void Initalize(const std::vector<Model*>& models);

	virtual void Update();

	virtual void Draw(ViewProjection& viewProjection);

	/// <summary>
	/// ワールド変換データを取得
	/// </summary>
	/// <returns>
	const WorldTransform& GetWorldTransform() { return worldTransform_; }
	

protected:
	WorldTransform worldTransform_;

	std::vector<Model*> models_;

	



};

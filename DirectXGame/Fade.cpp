#include "Fade.h"
#include "TextureManager.h"
#include <cassert>

void Fade::Initialize(float a) {

	fadeColor_.w = a;

uint32_t fadeTexHandle = TextureManager::Load("fade.png");
	fadeSprite_ = Sprite::Create(fadeTexHandle, {0, 0});

}

void Fade::Update( int sw) {

	fadeSwich;

	  sw;

	switch (fadeSwich) {

		case FadeMode::In:

		if (fadeColor_.w >= 0) {

			fadeColor_.w -= 0.005f;
		} else 
		{
			fadeColor_.w = 0.0f;
			fadeSwich = Num;
		}

	  break;

	    case FadeMode::Out:
		if (fadeColor_.w <= 1) {

			fadeColor_.w += 0.01f;
		} else

		{ 
			fadeColor_.w = 1.0f;
			fadeSwich = Num;
		}
		break;


	}
	  fadeSprite_->SetColor(fadeColor_);


}

void Fade::Draw() {


	  fadeSprite_->Draw();

}

#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"

class Player : public GameObject
{
private:
	Animation m_walkDown;
	Animation* m_currentAnimation;

	const float INPUT_BUFFER_LENGTH = 0.1f;
	const float APPROX_ONE_OVER_ROOT_TWO = 0.70710678f;	// 1 / sqrt(2)

public:
	Player();

	void update(float dt);
	void handleInput(float dt);
};


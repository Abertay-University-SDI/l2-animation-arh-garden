#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"

class Player : public GameObject
{
private:
	Animation m_walkDown;
	Animation* m_currentAnimation;

public:
	Player();

	void update(float dt);
	void handleInput(float dt);
};


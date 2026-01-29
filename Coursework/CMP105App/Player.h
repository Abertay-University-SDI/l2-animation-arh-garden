#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"

class Player : public GameObject
{
private:

public:
	Player();

	void update(float dt);
	void handleInput(float dt);
};

